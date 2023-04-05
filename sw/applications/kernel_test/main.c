/*
                              *******************
******************************* C SOURCE FILE *******************************
**                            *******************                          **
**                                                                         **
** project  : CGRA-X-HEEP                                                  **
** filename : main.c                                                       **
** version  : 1                                                            **
** date     : 05/04/23                                                     **
**                                                                         **
*****************************************************************************
**                                                                         **
** Copyright (c) EPFL                                                      **
** All rights reserved.                                                    **
**                                                                         **
*****************************************************************************
*/

/***************************************************************************/
/***************************************************************************/

/**
* @file   main.c
* @date   05/04/23
* @brief  An application to run a number of kernels under a same given 
* structure.
*
*/

#define _KERNELS_C

/****************************************************************************/
/**                                                                        **/
/*                             MODULES USED                                 */
/**                                                                        **/
/****************************************************************************/

// For interrupt handling
#include "csr.h"
#include "hart.h"
#include "handler.h"
#include "core_v_mini_mcu.h"
#include "rv_plic.h"
#include "rv_plic_regs.h"

//Include kernels!
#include "bitcount/bitcount.h"

/****************************************************************************/
/**                                                                        **/
/*                        DEFINITIONS AND MACROS                            */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                        TYPEDEFS AND STRUCTURES                           */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                      PROTOTYPES OF LOCAL FUNCTIONS                       */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED VARIABLES                             */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                            GLOBAL VARIABLES                              */
/**                                                                        **/
/****************************************************************************/

static kcom_kernel_t *kernels[] = { 
    &bitc_kernel, 
    // Add all other kernels here
    };


static uint8_t              cgra_slot;
static cgra_t               cgra;
static kcom_cgra_stats_t    kstats;

// Plic controller variables
dif_plic_params_t           rv_plic_params;
dif_plic_t                  rv_plic;
dif_plic_result_t           plic_res;
dif_plic_irq_id_t           intr_num;
int8_t                      cgra_intr_flag;

/****************************************************************************/
/**                                                                        **/
/*                           EXPORTED FUNCTIONS                             */
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/*                            LOCAL FUNCTIONS                               */
/**                                                                        **/
/****************************************************************************/


void cgra_config( kcom_kernel_t *ker )
{
    cgra_cmem_init(ker->imem, ker->kmem );
    cgra.base_addr = mmio_region_from_addr((uintptr_t)CGRA_PERIPH_START_ADDRESS);
    // Select request slot of CGRA
    cgra_slot = cgra_get_slot(&cgra);
    cgra_perf_cnt_enable(&cgra, 1);
    // Set CGRA kernel L/S pointers
    for(int8_t col_idx = 0 ; col_idx < ker->col_n ; col_idx++){
        cgra_set_read_ptr ( &cgra, cgra_slot, (uint32_t)ker->input  [col_idx],  col_idx );
        cgra_set_write_ptr( &cgra, cgra_slot, (uint32_t)ker->output [col_idx],  col_idx );
    }
}

void plic_interrupt_init(dif_plic_irq_id_t irq) {
    // Init the PLIC
    rv_plic_params.base_addr = mmio_region_from_addr((uintptr_t)RV_PLIC_START_ADDRESS);
    plic_res = dif_plic_init(rv_plic_params, &rv_plic);
    if (plic_res != kDifPlicOk) {
        PRINTF("PLIC init failed\n;");
    }

    // Set CGRA priority to 1 (target threshold is by default 0) to trigger an interrupt to the target (the processor)
    plic_res = dif_plic_irq_set_priority(&rv_plic, irq, 1);
    if (plic_res != kDifPlicOk) {
        PRINTF("Set interrupt priority to 1 failed\n");
    }

    plic_res = dif_plic_irq_set_enabled(&rv_plic, irq, 0, kDifPlicToggleEnabled);
    if (plic_res != kDifPlicOk) {
        PRINTF("Enable interrupt failed\n");
    }

    // Enable interrupt on processor side
    // Enable global interrupt for machine-level interrupts
    CSR_SET_BITS(CSR_REG_MSTATUS, 0x8);
    // Set mie.MEIE bit to one to enable machine-level external interrupts
    const uint32_t mask = 1 << 11;//IRQ_EXT_ENABLE_OFFSET;
    CSR_SET_BITS(CSR_REG_MIE, mask);
}

void handler_irq_external(void) {
    // Claim/clear interrupt
    plic_res = dif_plic_irq_claim(&rv_plic, 0, &intr_num);
    if (plic_res == kDifPlicOk && intr_num == CGRA_INTR) {
      kcom_timeStop( &(kstats.time.cgra), &(kstats.time.timer) );  
      cgra_intr_flag = 1;
    }


    // Complete the interrupt
    plic_res = dif_plic_irq_complete(&rv_plic, 0, &intr_num);
    if (plic_res != kDifPlicOk || intr_num != CGRA_INTR) {
        PRINTF("CGRA interrupt complete failed\n");
    }
}



void main()
{

    PRINTF("Will execute many kernels! \n");

    kcom_timerInit( &(kstats.time.timer) );

    plic_interrupt_init(CGRA_INTR);
    cgra_intr_flag = 0;

    uint8_t kernels_n = sizeof( kernels ) / sizeof( kcom_kernel_t * );
    for( uint8_t ker_idx = 0; ker_idx < kernels_n; ker_idx++ )
    {
        kcom_kernel_t* kernel = kernels[ ker_idx ];
        
        /* Software */
        kcom_timeStart( &(kstats.time.sw), &(kstats.time.timer) );
        kernel->function();
        kcom_timeStop( &(kstats.time.sw), &(kstats.time.timer) );

        /* CGRA Configuration */
        kcom_timeStart( &(kstats.time.config), &(kstats.time.timer) );
        cgra_config( kernel );
        kcom_timeStop( &(kstats.time.config), &(kstats.time.timer) );
        
        /* CGRA Execution */
        kcom_timeStart( &(kstats.time.cgra), &(kstats.time.timer) );


        cgra_set_kernel(&cgra, cgra_slot, 1 );


        printf("salio!");
        return;

        while(cgra_intr_flag==0) {};

        PRINTF("M");

        /* Result comparison */
        kcom_func_ret_t errors = kernel->check();
        PRINTF("ERRORS:\t%d", errors);


        /* Performance report */
        kcom_printPerf( &cgra, &kstats );
    }
}




/****************************************************************************/
/**                                                                        **/
/*                                 EOF                                      */
/**                                                                        **/
/****************************************************************************/