################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LinTuHisi/sample_comm_isp.c \
../src/LinTuHisi/sample_comm_sys.c \
../src/LinTuHisi/sample_comm_venc.c \
../src/LinTuHisi/sample_comm_vi.c \
../src/LinTuHisi/sample_comm_vpss.c 

OBJS += \
./src/LinTuHisi/sample_comm_isp.o \
./src/LinTuHisi/sample_comm_sys.o \
./src/LinTuHisi/sample_comm_venc.o \
./src/LinTuHisi/sample_comm_vi.o \
./src/LinTuHisi/sample_comm_vpss.o 

C_DEPS += \
./src/LinTuHisi/sample_comm_isp.d \
./src/LinTuHisi/sample_comm_sys.d \
./src/LinTuHisi/sample_comm_venc.d \
./src/LinTuHisi/sample_comm_vi.d \
./src/LinTuHisi/sample_comm_vpss.d 


# Each subdirectory must supply rules for building sources it contributes
src/LinTuHisi/%.o: ../src/LinTuHisi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-hisiv500-linux-gcc -mcpu=arm926ej-s  -mno-unaligned-access -fno-aggressive-loop-optimizations -DHICHIP=0x3516C300 -Dhi3516cv300 -DHI_MIPI_ENABLE -DHI_RELEASE -DHI_XXXX -DISP_V2 -DGYRO_BOSCH -DHI_ACODEC_TYPE_INNER -I/opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/include -I/root/workspace/opencvVpssDemo/src/LinTuHisi/include -I/root/workspace/opencvVpssDemo/src/LinTuOpencv -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


