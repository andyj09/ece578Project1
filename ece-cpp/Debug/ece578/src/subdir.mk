################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ece578/src/MainProgram.cpp \
../ece578/src/StationClass.cpp \
../ece578/src/TimelineSlots.cpp 

OBJS += \
./ece578/src/MainProgram.o \
./ece578/src/StationClass.o \
./ece578/src/TimelineSlots.o 

CPP_DEPS += \
./ece578/src/MainProgram.d \
./ece578/src/StationClass.d \
./ece578/src/TimelineSlots.d 


# Each subdirectory must supply rules for building sources it contributes
ece578/src/%.o: ../ece578/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-7 -O0 -g3 -Wall -Wextra -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


