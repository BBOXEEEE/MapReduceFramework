################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MapReduceFramework/MapReduceFramework.cpp 

CPP_DEPS += \
./src/MapReduceFramework/MapReduceFramework.d 

OBJS += \
./src/MapReduceFramework/MapReduceFramework.o 


# Each subdirectory must supply rules for building sources it contributes
src/MapReduceFramework/%.o: ../src/MapReduceFramework/%.cpp src/MapReduceFramework/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-MapReduceFramework

clean-src-2f-MapReduceFramework:
	-$(RM) ./src/MapReduceFramework/MapReduceFramework.d ./src/MapReduceFramework/MapReduceFramework.o

.PHONY: clean-src-2f-MapReduceFramework

