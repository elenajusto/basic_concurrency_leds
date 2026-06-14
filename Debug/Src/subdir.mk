################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/delay.c \
../Src/gpio.c \
../Src/gpio_exti.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/tim.c 

OBJS += \
./Src/delay.o \
./Src/gpio.o \
./Src/gpio_exti.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/tim.o 

C_DEPS += \
./Src/delay.d \
./Src/gpio.d \
./Src/gpio_exti.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32G071RBTx -DSTM32 -DSTM32G0 -DNUCLEO_G071RB -DSTM32G071xx -c -I../Inc -I"../CMSIS/Include" -I"../CMSIS/Device/ST/STM32G0xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/gpio_exti.cyclo ./Src/gpio_exti.d ./Src/gpio_exti.o ./Src/gpio_exti.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/tim.cyclo ./Src/tim.d ./Src/tim.o ./Src/tim.su

.PHONY: clean-Src

