################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=eabi -O2 --include_path="/home/gerik/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

n64.obj: ../n64.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=eabi -O2 --include_path="/home/gerik/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="n64.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

nrf24l01.obj: ../nrf24l01.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=eabi -O2 --include_path="/home/gerik/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="nrf24l01.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

spi.obj: ../spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmsp --abi=eabi -O2 --include_path="/home/gerik/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/gerik/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="spi.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


