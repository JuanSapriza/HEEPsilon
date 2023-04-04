#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "csr.h"
#include "hart.h"
#include "handler.h"
#include "core_v_mini_mcu.h"
#include "rv_plic.h"
#include "rv_plic_regs.h"
#include "cgra_x_heep.h"
#include "cgra.h"
#include "cgra/cgra_bitstream.h"
#include "cgra/function.h"

// TEST PARAMETERS
#define RNG_SEED 18765456
#define REPETITIONS 1

// cgra variables
#define CGRA_COLS 4
#define IN_VARS 2
#define OUT_VARS 1
int32_t cgra_input[CGRA_COLS][IN_VARS] __attribute__ ((aligned (4)));
int32_t cgra_output[CGRA_COLS][OUT_VARS] __attribute__ ((aligned (4)));
int32_t sw_res = {0};
int8_t cgra_intr_flag;
uint8_t cgra_slot;
cgra_t cgra;

// Plic controller variables
dif_plic_params_t rv_plic_params;
dif_plic_t rv_plic;
dif_plic_result_t plic_res;
dif_plic_irq_id_t intr_num;

// Test variables
int errors = 0;

/* 
    CGRA IRQ Handler
*/
void handler_irq_external(void) {
    // Claim/clear interrupt
    plic_res = dif_plic_irq_claim(&rv_plic, 0, &intr_num);
    if (plic_res == kDifPlicOk && intr_num == CGRA_INTR) {
      cgra_intr_flag = 1;
    }
    // Complete the interrupt
    plic_res = dif_plic_irq_complete(&rv_plic, 0, &intr_num);
    if (plic_res != kDifPlicOk || intr_num != CGRA_INTR) {
        printf("CGRA interrupt complete failed\n");
    }
}

/* 
    Interrupt configuration
*/
void plic_interrupt_init(dif_plic_irq_id_t irq) {
    // Init the PLIC
    rv_plic_params.base_addr = mmio_region_from_addr((uintptr_t)RV_PLIC_START_ADDRESS);
    plic_res = dif_plic_init(rv_plic_params, &rv_plic);
    if (plic_res != kDifPlicOk) {
        printf("PLIC init failed\n;");
    }

    // Set CGRA priority to 1 (target threshold is by default 0) to trigger an interrupt to the target (the processor)
    plic_res = dif_plic_irq_set_priority(&rv_plic, irq, 1);
    if (plic_res != kDifPlicOk) {
        printf("Set interrupt priority to 1 failed\n");
    }

    plic_res = dif_plic_irq_set_enabled(&rv_plic, irq, 0, kDifPlicToggleEnabled);
    if (plic_res != kDifPlicOk) {
        printf("Enable interrupt failed\n");
    }

    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    // Set mie.MEIE bit to one to enable machine-level external interrupts
    const uint32_t mask = 1 << 11;//IRQ_EXT_ENABLE_OFFSET;
    CSR_SET_BITS(CSR_REG_MIE, mask);
}

/* 
    CGRA init config
*/
void cgra_config(void){
    cgra_cmem_init(cgra_imem_bistream, cgra_kem_bitstream);
    cgra.base_addr = mmio_region_from_addr((uintptr_t)CGRA_PERIPH_START_ADDRESS);
    // Select request slot of CGRA (2 slots)
    cgra_slot = cgra_get_slot(&cgra);
    cgra_perf_cnt_enable(&cgra, 1);
    // Set CGRA kernel L/S pointers
    for(int8_t column_idx = 0 ; column_idx < CGRA_COLS ; column_idx++){
        cgra_set_read_ptr(&cgra, cgra_slot, (uint32_t)cgra_input[column_idx], column_idx);
        cgra_set_write_ptr(&cgra, cgra_slot, (uint32_t)cgra_output[column_idx], column_idx);
    }
}

/* 
    CGRA performance results
*/
void cgra_print_perf(void){
    printf("CGRA kernel executed: %d\n", cgra_perf_cnt_get_kernel(&cgra));
    for(int8_t column_idx = 0 ; column_idx < CGRA_COLS ; column_idx++){
        printf("CGRA column %d active cycles: %d\n", column_idx, cgra_perf_cnt_get_col_active(&cgra, column_idx));
        printf("CGRA column %d stall cycles : %d\n", column_idx, cgra_perf_cnt_get_col_stall(&cgra, column_idx));
    }
}

unsigned int pseudoRand()
{
   static unsigned int z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   unsigned int b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

int main(void) {

    printf( "GSM!\n" );

    plic_interrupt_init(CGRA_INTR);

    cgra_config();
    cgra_intr_flag = 0;

    // Test loop
    for(int r=0 ; r < REPETITIONS ; r++){

        int32_t d[40];
		int32_t d_sw[40];
		for(int i=0 ; i < 40 ; i++)
			d_sw[i] = d[i] = pseudoRand() % (32767 - -32768 + 1) + -32768;
		
		cgra_input[1][0] = d;
		cgra_input[3][0] = 32767;
		cgra_input[3][1] = -32768;
		

        int32_t sw_res = gsm ( d_sw );
     

        // CGRA execution 
        cgra_set_kernel(&cgra, cgra_slot, 1 );

        // Wait CGRA is done
        while(cgra_intr_flag==0) {
            wait_for_interrupt();
        }
        cgra_intr_flag = 0;

        unsigned cgra_res = cgra_output[3][0];
		if (cgra_res != sw_res) {
			errors++;
		}
		for(int i=0 ; i < 40 ; i++)
		{
			if (d[i] != d_sw[i])
				errors++;
		}

        
    }

    if(errors == 0)
        printf("TEST SUCCESS! %d repetitions\n", REPETITIONS);
    else
        printf("TEST FAILED! %d fails out of %d repetitions\n", errors, REPETITIONS);

    cgra_print_perf();

    return EXIT_SUCCESS;
}