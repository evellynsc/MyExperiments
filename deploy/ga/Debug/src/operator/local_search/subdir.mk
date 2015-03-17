################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/operator/local_search/InsertAroundMeanIntersections.cpp \
../src/operator/local_search/ReplaceBelowAverageIntersections.cpp \
../src/operator/local_search/ReplaceLessUsedIntersections.cpp \
../src/operator/local_search/ReplaceMoreUsedIntersections.cpp 

OBJS += \
./src/operator/local_search/InsertAroundMeanIntersections.o \
./src/operator/local_search/ReplaceBelowAverageIntersections.o \
./src/operator/local_search/ReplaceLessUsedIntersections.o \
./src/operator/local_search/ReplaceMoreUsedIntersections.o 

CPP_DEPS += \
./src/operator/local_search/InsertAroundMeanIntersections.d \
./src/operator/local_search/ReplaceBelowAverageIntersections.d \
./src/operator/local_search/ReplaceLessUsedIntersections.d \
./src/operator/local_search/ReplaceMoreUsedIntersections.d 


# Each subdirectory must supply rules for building sources it contributes
src/operator/local_search/%.o: ../src/operator/local_search/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


