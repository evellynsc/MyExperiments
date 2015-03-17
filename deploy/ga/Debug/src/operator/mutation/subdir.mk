################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/operator/mutation/BitInversionMutation.cpp 

OBJS += \
./src/operator/mutation/BitInversionMutation.o 

CPP_DEPS += \
./src/operator/mutation/BitInversionMutation.d 


# Each subdirectory must supply rules for building sources it contributes
src/operator/mutation/%.o: ../src/operator/mutation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


