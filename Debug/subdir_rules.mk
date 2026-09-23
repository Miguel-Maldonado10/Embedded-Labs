################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'GNU Compiler: "$<"'
	"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"/home/Kiki/Downloads/empty_driverlib_src" -I"/home/Kiki/Downloads/empty_driverlib_src/Debug" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo ' '

build-1308347889: ../empty.syscfg
	@echo 'SysConfig: "$<"'
	"/home/Kiki/ti/sysconfig_1.26.2/sysconfig_cli.sh" -s "/home/Kiki/ti/mspm0_sdk_2_11_00_07/.metadata/product.json" --script "/home/Kiki/Downloads/empty_driverlib_src/empty.syscfg" -o "." --compiler gcc
	@echo ' '

device_linker.lds: build-1308347889 ../empty.syscfg
device.opt: build-1308347889
device.lds.genlibs: build-1308347889
ti_msp_dl_config.c: build-1308347889
ti_msp_dl_config.h: build-1308347889
Event.dot: build-1308347889

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'GNU Compiler: "$<"'
	"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"/home/Kiki/Downloads/empty_driverlib_src" -I"/home/Kiki/Downloads/empty_driverlib_src/Debug" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo ' '

startup_mspm0g350x_gcc.o: /home/Kiki/ti/mspm0_sdk_2_11_00_07/source/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0g350x_gcc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'GNU Compiler: "$<"'
	"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/bin/arm-none-eabi-gcc-9.2.1" -c @"device.opt"  -mcpu=cortex-m0plus -march=armv6-m -mthumb -mfloat-abi=soft -I"/home/Kiki/Downloads/empty_driverlib_src" -I"/home/Kiki/Downloads/empty_driverlib_src/Debug" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"/home/Kiki/ti/mspm0_sdk_2_11_00_07/source" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include/newlib-nano" -I"/home/Kiki/ti/gcc_arm_none_eabi_9_2_1/arm-none-eabi/include" -O2 -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo ' '


