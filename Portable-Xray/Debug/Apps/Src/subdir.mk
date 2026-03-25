################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Apps/Src/adc.c \
../Apps/Src/buzzer.c \
../Apps/Src/data_logger.c \
../Apps/Src/eeprom.c \
../Apps/Src/error.c \
../Apps/Src/fw_info.c \
../Apps/Src/key.c \
../Apps/Src/lcd.c \
../Apps/Src/led.c \
../Apps/Src/main_system.c \
../Apps/Src/system_job.c \
../Apps/Src/unit_conversion.c 

OBJS += \
./Apps/Src/adc.o \
./Apps/Src/buzzer.o \
./Apps/Src/data_logger.o \
./Apps/Src/eeprom.o \
./Apps/Src/error.o \
./Apps/Src/fw_info.o \
./Apps/Src/key.o \
./Apps/Src/lcd.o \
./Apps/Src/led.o \
./Apps/Src/main_system.o \
./Apps/Src/system_job.o \
./Apps/Src/unit_conversion.o 

C_DEPS += \
./Apps/Src/adc.d \
./Apps/Src/buzzer.d \
./Apps/Src/data_logger.d \
./Apps/Src/eeprom.d \
./Apps/Src/error.d \
./Apps/Src/fw_info.d \
./Apps/Src/key.d \
./Apps/Src/lcd.d \
./Apps/Src/led.d \
./Apps/Src/main_system.d \
./Apps/Src/system_job.d \
./Apps/Src/unit_conversion.d 


# Each subdirectory must supply rules for building sources it contributes
Apps/Src/%.o Apps/Src/%.su Apps/Src/%.cyclo: ../Apps/Src/%.c Apps/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Apps/Inc -I../Apps/States/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Apps-2f-Src

clean-Apps-2f-Src:
	-$(RM) ./Apps/Src/adc.cyclo ./Apps/Src/adc.d ./Apps/Src/adc.o ./Apps/Src/adc.su ./Apps/Src/buzzer.cyclo ./Apps/Src/buzzer.d ./Apps/Src/buzzer.o ./Apps/Src/buzzer.su ./Apps/Src/data_logger.cyclo ./Apps/Src/data_logger.d ./Apps/Src/data_logger.o ./Apps/Src/data_logger.su ./Apps/Src/eeprom.cyclo ./Apps/Src/eeprom.d ./Apps/Src/eeprom.o ./Apps/Src/eeprom.su ./Apps/Src/error.cyclo ./Apps/Src/error.d ./Apps/Src/error.o ./Apps/Src/error.su ./Apps/Src/fw_info.cyclo ./Apps/Src/fw_info.d ./Apps/Src/fw_info.o ./Apps/Src/fw_info.su ./Apps/Src/key.cyclo ./Apps/Src/key.d ./Apps/Src/key.o ./Apps/Src/key.su ./Apps/Src/lcd.cyclo ./Apps/Src/lcd.d ./Apps/Src/lcd.o ./Apps/Src/lcd.su ./Apps/Src/led.cyclo ./Apps/Src/led.d ./Apps/Src/led.o ./Apps/Src/led.su ./Apps/Src/main_system.cyclo ./Apps/Src/main_system.d ./Apps/Src/main_system.o ./Apps/Src/main_system.su ./Apps/Src/system_job.cyclo ./Apps/Src/system_job.d ./Apps/Src/system_job.o ./Apps/Src/system_job.su ./Apps/Src/unit_conversion.cyclo ./Apps/Src/unit_conversion.d ./Apps/Src/unit_conversion.o ./Apps/Src/unit_conversion.su

.PHONY: clean-Apps-2f-Src

