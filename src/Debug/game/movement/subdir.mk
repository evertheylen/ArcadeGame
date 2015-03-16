################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../game/movement/movement.o 

CPP_SRCS += \
../game/movement/movement.cpp 

OBJS += \
./game/movement/movement.o 

CPP_DEPS += \
./game/movement/movement.d 


# Each subdirectory must supply rules for building sources it contributes
game/movement/%.o: ../game/movement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


