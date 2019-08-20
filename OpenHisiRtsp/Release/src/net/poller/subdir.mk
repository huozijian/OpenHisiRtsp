################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/poller/EPollPoller.cpp \
../src/net/poller/PollPoller.cpp \
../src/net/poller/Poller.cpp \
../src/net/poller/SelectPoller.cpp 

OBJS += \
./src/net/poller/EPollPoller.o \
./src/net/poller/PollPoller.o \
./src/net/poller/Poller.o \
./src/net/poller/SelectPoller.o 

CPP_DEPS += \
./src/net/poller/EPollPoller.d \
./src/net/poller/PollPoller.d \
./src/net/poller/Poller.d \
./src/net/poller/SelectPoller.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/poller/%.o: ../src/net/poller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-hisiv500-linux-g++ -mcpu=arm926ej-s  -mno-unaligned-access -fno-aggressive-loop-optimizations -DHICHIP=0x3516C300 -DHI_MIPI_ENABLE -DHI_RELEASE -DHI_XXXX -DISP_V2 -DGYRO_BOSCH -DHI_ACODEC_TYPE_INNER -I/opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/include -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src/hisiComm/include" -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


