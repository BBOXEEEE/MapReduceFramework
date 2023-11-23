################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/WordCount/WordCount.cpp \
../src/WordCount/WordCountMapper.cpp \
../src/WordCount/WordCountReducer.cpp 

CPP_DEPS += \
./src/WordCount/WordCount.d \
./src/WordCount/WordCountMapper.d \
./src/WordCount/WordCountReducer.d 

OBJS += \
./src/WordCount/WordCount.o \
./src/WordCount/WordCountMapper.o \
./src/WordCount/WordCountReducer.o 


# Each subdirectory must supply rules for building sources it contributes
src/WordCount/%.o: ../src/WordCount/%.cpp src/WordCount/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-WordCount

clean-src-2f-WordCount:
	-$(RM) ./src/WordCount/WordCount.d ./src/WordCount/WordCount.o ./src/WordCount/WordCountMapper.d ./src/WordCount/WordCountMapper.o ./src/WordCount/WordCountReducer.d ./src/WordCount/WordCountReducer.o

.PHONY: clean-src-2f-WordCount

