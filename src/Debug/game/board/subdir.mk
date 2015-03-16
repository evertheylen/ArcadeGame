################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../game/board/barrel.o \
../game/board/board.o \
../game/board/obstacle.o \
../game/board/player.o \
../game/board/thing.o \
../game/board/wall.o 

CPP_SRCS += \
../game/board/barrel.cpp \
../game/board/board.cpp \
../game/board/obstacle.cpp \
../game/board/player.cpp \
../game/board/thing.cpp \
../game/board/wall.cpp 

OBJS += \
./game/board/barrel.o \
./game/board/board.o \
./game/board/obstacle.o \
./game/board/player.o \
./game/board/thing.o \
./game/board/wall.o 

CPP_DEPS += \
./game/board/barrel.d \
./game/board/board.d \
./game/board/obstacle.d \
./game/board/player.d \
./game/board/thing.d \
./game/board/wall.d 


# Each subdirectory must supply rules for building sources it contributes
game/board/%.o: ../game/board/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


