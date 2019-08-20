/*
 * debugComm.h
 *
 *  Created on: 2019年8月19日
 *      Author: JasonHuo
 */

#ifndef DEBUGCOMM_H_
#define DEBUGCOMM_H_

#define RTSP_DEBUG						true			//是否开启调试信息
#if RTSP_DEBUG
#define RTSP_PRINTF_NONE "\e[0m"
#define RTSP_PRINTF_GREEN "\e[0;32m"
#define RTSP_PRINTF_RED "\e[0;31m"
#define RTSP_printf(fmt...)  			do{}while(0)//do {    printf(fmt);  }while(0)
#define RTSP_VENC_DEBUG(fmt...) 		do { 	printf("[ RTSP_VENC ]===>\e[0;34m");	printf(fmt);	printf(RTSP_PRINTF_NONE);}while(0)
#define RTSP_VENC_DEBUG_ERR(fmt...) 	do { 	printf("[ RTSP_VENC ]===>\e[0;31m");	printf(fmt);	printf(RTSP_PRINTF_NONE);}while(0)
#define RTSP_IVE_DEBUG(fmt...) 		do { 	printf("[ RTSP_IVE  ]===>");			printf(fmt);	printf(RTSP_PRINTF_NONE);}while(0)
#define RTSP_SYS_DEBUG(fmt...) 		do { 	printf("[ RTSP_SYS  ]===>\e[0;32m");	printf(fmt);	printf(RTSP_PRINTF_NONE);}while(0)
#define RTSP_EXC_DEBUG(fmt...)		do {	printf("[RTSP_EXCHND]===>\e[0;31m");	printf(fmt);	printf(RTSP_PRINTF_NONE);}while(0)
#else
#define RTSP_printf(fmt...)  			do{}while(0)
#define RTSP_VENC_DEBUG(fmt...) 		do{}while(0)
#define RTSP_VENC_DEBUG_ERR(fmt...) 	do{}while(0)
#define RTSP_IVE_DEBUG(fmt...) 		do{}while(0)
#define RTSP_SYS_DEBUG(fmt...) 		do{}while(0)
#define RTSP_EXC_DEBUG(fmt...)		do{}while(0)
#endif



#endif /* DEBUGCOMM_H_ */
