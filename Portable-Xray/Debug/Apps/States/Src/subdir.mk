################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Apps/States/Src/battmgmt_state.c \
../Apps/States/Src/configure_state.c \
../Apps/States/Src/duty_wait_state.c \
../Apps/States/Src/error_state.c \
../Apps/States/Src/exposure_state.c \
../Apps/States/Src/init_state.c \
../Apps/States/Src/pass_input_state.c \
../Apps/States/Src/standby_state.c \
../Apps/States/Src/state_machine.c 

OBJS += \
./Apps/States/Src/battmgmt_state.o \
./Apps/States/Src/configure_state.o \
./Apps/States/Src/duty_wait_state.o \
./Apps/States/Src/error_state.o \
./Apps/States/Src/exposure_state.o \
./Apps/States/Src/init_state.o \
./Apps/States/Src/pass_input_state.o \
./Apps/States/Src/standby_state.o \
./Apps/States/Src/state_machine.o 

C_DEPS += \
./Apps/States/Src/battmgmt_state.d \
./Apps/States/Src/configure_state.d \
./Apps/States/Src/duty_wait_state.d \
./Apps/States/Src/error_state.d \
./Apps/States/Src/exposure_state.d \
./Apps/States/Src/init_state.d \
./Apps/States/Src/pass_input_state.d \
./Apps/States/Src/standby_state.d \
./Apps/States/Src/state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
Apps/States/Src/%.o Apps/States/Src/%.su Apps/States/Src/%.cyclo: ../Apps/States/Src/%.c Apps/States/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Apps/Inc -I../Apps/States/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Apps-2f-States-2f-Src

clean-Apps-2f-States-2f-Src:
	-$(RM) ./Apps/States/Src/battmgmt_state.cyclo ./Apps/States/Src/battmgmt_state.d ./Apps/States/Src/battmgmt_state.o ./Apps/States/Src/battmgmt_state.su ./Apps/States/Src/configure_state.cyclo ./Apps/States/Src/configure_state.d ./Apps/States/Src/configure_state.o ./Apps/States/Src/configure_state.su ./Apps/States/Src/duty_wait_state.cyclo ./Apps/States/Src/duty_wait_state.d ./Apps/States/Src/duty_wait_state.o ./Apps/States/Src/duty_wait_state.su ./Apps/States/Src/error_state.cyclo ./Apps/States/Src/error_state.d ./Apps/States/Src/error_state.o ./Apps/States/Src/error_state.su ./Apps/States/Src/exposure_state.cyclo ./Apps/States/Src/exposure_state.d ./Apps/States/Src/exposure_state.o ./Apps/States/Src/exposure_state.su ./Apps/States/Src/init_state.cyclo ./Apps/States/Src/init_state.d ./Apps/States/Src/init_state.o ./Apps/States/Src/init_state.su ./Apps/States/Src/pass_input_state.cyclo ./Apps/States/Src/pass_input_state.d ./Apps/States/Src/pass_input_state.o ./Apps/States/Src/pass_input_state.su ./Apps/States/Src/standby_state.cyclo ./Apps/States/Src/standby_state.d ./Apps/States/Src/standby_state.o ./Apps/States/Src/standby_state.su ./Apps/States/Src/state_machine.cyclo ./Apps/States/Src/state_machine.d ./Apps/States/Src/state_machine.o ./Apps/States/Src/state_machine.su

.PHONY: clean-Apps-2f-States-2f-Src

