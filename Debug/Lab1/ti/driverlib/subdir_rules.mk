################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Lab1/ti/driverlib/%.o: ../Lab1/ti/driverlib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'GNU Compiler: "$<"'
	"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"/home/Kiki/Downloads/empty_driverlib_src" -I"/home/Kiki/Downloads/empty_driverlib_src/Debug" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"Lab1/ti/driverlib/$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo ' '


