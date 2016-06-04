################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/icxxabi.cpp \
../src/list.cpp \
../src/memory.cpp \
../src/string.cpp 

OBJS += \
./src/icxxabi.o \
./src/list.o \
./src/memory.o \
./src/string.o 

CPP_DEPS += \
./src/icxxabi.d \
./src/list.d \
./src/memory.d \
./src/string.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	i686-elf-g++ -I"/home/chris/git/feta/include" -O0 -g3 -Wall -c -fmessage-length=0 -fno-exceptions -nostdlib -ffreestanding -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


