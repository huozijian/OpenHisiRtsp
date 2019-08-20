################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/base/AsyncLogging.cpp \
../src/base/Condition.cpp \
../src/base/Logging.cpp \
../src/base/Mutex.cpp \
../src/base/Sem.cpp \
../src/base/Thread.cpp \
../src/base/ThreadPool.cpp 

OBJS += \
./src/base/AsyncLogging.o \
./src/base/Condition.o \
./src/base/Logging.o \
./src/base/Mutex.o \
./src/base/Sem.o \
./src/base/Thread.o \
./src/base/ThreadPool.o 

CPP_DEPS += \
./src/base/AsyncLogging.d \
./src/base/Condition.d \
./src/base/Logging.d \
./src/base/Mutex.d \
./src/base/Sem.d \
./src/base/Thread.d \
./src/base/ThreadPool.d 


# Each subdirectory must supply rules for building sources it contributes
src/base/%.o: ../src/base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-hisiv500-linux-g++ -mcpu=arm926ej-s  -mno-unaligned-access -fno-aggressive-loop-optimizations -DHICHIP=0x3516C300 -DHI_MIPI_ENABLE -DHI_RELEASE -DHI_XXXX -DISP_V2 -DGYRO_BOSCH -DHI_ACODEC_TYPE_INNER -I/opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/include -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src/hisiComm/include" -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


