# Copyright EPFL contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0


# Makefile to generates cgra-x-heep files and build the design with fusesoc

.PHONY: clean help

TARGET 		?= sim
FPGA_BOARD 	?= pynq-z2
PORT		?= /dev/ttyUSB2

# 1 external domain for the CGRA
EXTERNAL_DOMAINS = 1
# Use more memory banks
MEMORY_BANKS = 4

# Project options are based on the app to be build (default - hello_world)
PROJECT  ?= hello_world

# HEEP_DIR might already be defined, you may want to move it to the top
export HEEP_DIR = hw/vendor/esl_epfl_x_heep/

# Get the path of this Makefile to pass to the Makefile help generator
MKFILE_PATH = $(shell dirname "$(realpath $(firstword $(MAKEFILE_LIST)))")
export FILE_FOR_HELP = $(MKFILE_PATH)/Makefile

## Call the help generator. Calling simply
## $ make
## or
## $ make help
## Will print the help of this project.
## With the parameter WHICH you can select to print
## either the help of X-HEEP (WHICH=xheep)
## or both this project's and X-HEEP's (WHICH=all)
help:
ifndef WHICH
	${HEEP_DIR}/util/MakefileHelp
else ifeq ($(filter $(WHICH),xheep x-heep),)
	${HEEP_DIR}/util/MakefileHelp
	$(MAKE) -C $(HEEP_DIR) help
else
	$(MAKE) -C $(HEEP_DIR) help
endif


include $(HEEP_DIR)Makefile.venv


## Generates mcu files. First the mcu-gen from X-HEEP is called.
## This is needed to be done after the X-HEEP mcu-gen because the test-bench to be used is the one from CGRA-X-HEEP, not the one from X-HEEP.
mcu-gen:
	$(MAKE) -f $(XHEEP_MAKE) EXTERNAL_DOMAINS=${EXTERNAL_DOMAINS} MEMORY_BANKS=${MEMORY_BANKS} $(MAKECMDGOALS)
	cd hw/vendor/esl_epfl_x_heep &&\
	python util/mcu_gen.py --cfg mcu_cfg.hjson --pads_cfg pad_cfg.hjson  --outdir ../../../tb/ --memorybanks $(MEMORY_BANKS) --tpl-sv ../../../tb/tb_util.svh.tpl

## Builds (synthesis and implementation) the bitstream for the FPGA version using Vivado
## @param FPGA_BOARD=nexys-a7-100t,pynq-z2
## @param FUSESOC_FLAGS=--flag=<flagname>
vivado-fpga: |venv
	fusesoc --cores-root . run --no-export --target=$(FPGA_BOARD) $(FUSESOC_FLAGS) --setup --build eslepfl:systems:cgra-x-heep 2>&1 | tee buildvivado.log


## Runs verible formating
verible:
	util/format-verible;

## @section Simulation

## Simulation in verilator
verilator-sim:
	fusesoc --cores-root . run --no-export --target=sim --tool=verilator $(FUSESOC_FLAGS) --setup --build eslepfl:systems:cgra-x-heep 2>&1 | tee buildsim.log

## Simulation in Questasim
questasim-sim:
	fusesoc --cores-root . run --no-export --target=sim --tool=modelsim $(FUSESOC_FLAGS) --setup --build eslepfl:systems:cgra-x-heep 2>&1 | tee buildsim.log

## Simulation in Questasim (optimized)
questasim-sim-opt: questasim-sim
	$(MAKE) -C build/eslepfl_systems_cgra-x-heep_0/sim-modelsim opt

## Simulation in VCS
vcs-sim:
	fusesoc --cores-root . run --no-export --target=sim --tool=vcs $(FUSESOC_FLAGS) --setup --build eslepfl:systems:cgra-x-heep 2>&1 | tee buildsim.log


## Generates the build output for a given application
## Uses verilator to simulate the HW model and run the FW
## UART Dumping in uart0.log to show recollected results
run-verilator:
	$(MAKE) app PROJECT=$(PROJECT)
	cd ./build/eslepfl_systems_cgra-x-heep_0/sim-verilator; \
	./Vtestharness +firmware=../../../sw/build/main.hex; \
	cat uart0.log; \
	cd ../../..;

## Generates the build output for a given application
## Uses questasim to simulate the HW model and run the FW
## UART Dumping in uart0.log to show recollected results
run-questasim:
	$(MAKE) app PROJECT=$(PROJECT)
	cd ./build/eslepfl_systems_cgra-x-heep_0/sim-modelsim; \
	make run PLUSARGS="c firmware=../../../sw/build/main.hex"; \
	cat uart0.log; \
	cd ../../..;


## Builds the program and uses flash-load to run on the FPGA
run-fpga:
	$(MAKE) app PROJECT=$(PROJECT) LINKER=flash_load TARGET=pynq-z2
	( cd hw/vendor/esl_epfl_x_heep/sw/vendor/yosyshq_icestorm/iceprog && make clean && make all ) ;\
	$(MAKE) flash-prog ;\

# Builds the program and uses flash-load to run on the FPGA.
# Additionally opens picocom (if available) to see the output.
run-fpga-com:
	$(MAKE) app PROJECT=$(PROJECT) LINKER=flash_load TARGET=pynq-z2
	( cd hw/vendor/esl_epfl_x_heep/sw/vendor/yosyshq_icestorm/iceprog && make clean && make all ) ;\
	$(MAKE) flash-prog ;\
	picocom -b 115200 -r -l --imap lfcrlf $(PORT)


XHEEP_MAKE = $(HEEP_DIR)/external.mk
include $(XHEEP_MAKE)

## @section Cleaning

## Add a dependency on the existing app target of XHEEP to create a link to the build folder
app: link_build

## Cleans the links
clean-app: link_rm

## Builds the links
link_build:
	ln -sf ../hw/vendor/esl_epfl_x_heep/sw/build sw/build

link_rm:
	rm sw/build

## Removes the simulation model and log
clean:
	rm -rf build buildsim.log
