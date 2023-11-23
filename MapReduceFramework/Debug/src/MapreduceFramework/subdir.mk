################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MapreduceFramework/MapReduceFramework.cpp 

CPP_DEPS += \
./src/MapreduceFramework/MapReduceFramework.d 

OBJS += \
./src/MapreduceFramework/MapReduceFramework.o 


# Each subdirectory must supply rules for building sources it contributes
src/MapreduceFramework/%.o: ../src/MapreduceFramework/%.cpp src/MapreduceFramework/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-MapreduceFramework

clean-src-2f-MapreduceFramework:
	-$(RM) ./src/MapreduceFramework/MapReduceFramework.d ./src/MapreduceFramework/MapReduceFramework.o

.PHONY: clean-src-2f-MapreduceFramework

