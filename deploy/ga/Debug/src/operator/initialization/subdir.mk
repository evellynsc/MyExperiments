################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/operator/initialization/FullerIntersectionsInitialization.cpp \
../src/operator/initialization/GreedInitialization.cpp \
../src/operator/initialization/RandomGreedInitialization.cpp \
../src/operator/initialization/RandomInitialization.cpp 

OBJS += \
./src/operator/initialization/FullerIntersectionsInitialization.o \
./src/operator/initialization/GreedInitialization.o \
./src/operator/initialization/RandomGreedInitialization.o \
./src/operator/initialization/RandomInitialization.o 

CPP_DEPS += \
./src/operator/initialization/FullerIntersectionsInitialization.d \
./src/operator/initialization/GreedInitialization.d \
./src/operator/initialization/RandomGreedInitialization.d \
./src/operator/initialization/RandomInitialization.d 


# Each subdirectory must supply rules for building sources it contributes
src/operator/initialization/%.o: ../src/operator/initialization/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


