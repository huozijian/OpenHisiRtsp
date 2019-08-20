################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/AACFileMediaSource.cpp \
../src/net/AACRtpSink.cpp \
../src/net/Acceptor.cpp \
../src/net/Buffer.cpp \
../src/net/Event.cpp \
../src/net/EventScheduler.cpp \
../src/net/H264FileMediaSource.cpp \
../src/net/H264RtpSink.cpp \
../src/net/HisiMediaSource.cpp \
../src/net/InetAddress.cpp \
../src/net/MediaSession.cpp \
../src/net/MediaSource.cpp \
../src/net/RtpSink.cpp \
../src/net/RtspConnection.cpp \
../src/net/RtspServer.cpp \
../src/net/SocketsOps.cpp \
../src/net/TcpConnection.cpp \
../src/net/TcpServer.cpp \
../src/net/TcpSocket.cpp \
../src/net/Timer.cpp \
../src/net/UsageEnvironment.cpp 

OBJS += \
./src/net/AACFileMediaSource.o \
./src/net/AACRtpSink.o \
./src/net/Acceptor.o \
./src/net/Buffer.o \
./src/net/Event.o \
./src/net/EventScheduler.o \
./src/net/H264FileMediaSource.o \
./src/net/H264RtpSink.o \
./src/net/HisiMediaSource.o \
./src/net/InetAddress.o \
./src/net/MediaSession.o \
./src/net/MediaSource.o \
./src/net/RtpSink.o \
./src/net/RtspConnection.o \
./src/net/RtspServer.o \
./src/net/SocketsOps.o \
./src/net/TcpConnection.o \
./src/net/TcpServer.o \
./src/net/TcpSocket.o \
./src/net/Timer.o \
./src/net/UsageEnvironment.o 

CPP_DEPS += \
./src/net/AACFileMediaSource.d \
./src/net/AACRtpSink.d \
./src/net/Acceptor.d \
./src/net/Buffer.d \
./src/net/Event.d \
./src/net/EventScheduler.d \
./src/net/H264FileMediaSource.d \
./src/net/H264RtpSink.d \
./src/net/HisiMediaSource.d \
./src/net/InetAddress.d \
./src/net/MediaSession.d \
./src/net/MediaSource.d \
./src/net/RtpSink.d \
./src/net/RtspConnection.d \
./src/net/RtspServer.d \
./src/net/SocketsOps.d \
./src/net/TcpConnection.d \
./src/net/TcpServer.d \
./src/net/TcpSocket.d \
./src/net/Timer.d \
./src/net/UsageEnvironment.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/%.o: ../src/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-hisiv500-linux-g++ -mcpu=arm926ej-s  -mno-unaligned-access -fno-aggressive-loop-optimizations -DHICHIP=0x3516C300 -DHI_MIPI_ENABLE -DHI_RELEASE -DHI_XXXX -DISP_V2 -DGYRO_BOSCH -DHI_ACODEC_TYPE_INNER -I/opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/include -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src/hisiComm/include" -I"/media/hzj_jason/_dde_data/workspaceEclipse/OpenHisiRtsp/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


