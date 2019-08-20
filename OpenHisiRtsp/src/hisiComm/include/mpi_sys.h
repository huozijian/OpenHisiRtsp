/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_sys.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2007/1/31
  Description   :
  History       :
  1.Date        : 2006/1/31
    Author      : c42025
    Modification: Created file

  2.Date        : 2008/03/03
    Author      : c42025
    Modification: add a new funtion "HI_MPI_SYS_GetVersion"

******************************************************************************/
#ifndef __MPI_SYS_H__
#define __MPI_SYS_H__

#include "../../hisiComm/include/hi_comm_sys.h"
#include "../../hisiComm/include/hi_common.h"
#include "../../hisiComm/include/hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 HI_MPI_SYS_Init(HI_VOID);
HI_S32 HI_MPI_SYS_Exit(HI_VOID);

HI_S32 HI_MPI_SYS_SetConf(const MPP_SYS_CONF_S* pstSysConf);
HI_S32 HI_MPI_SYS_GetConf(MPP_SYS_CONF_S* pstSysConf);

HI_S32  HI_MPI_SYS_Bind(MPP_CHN_S* pstSrcChn, MPP_CHN_S* pstDestChn);
HI_S32  HI_MPI_SYS_UnBind(MPP_CHN_S* pstSrcChn, MPP_CHN_S* pstDestChn);
HI_S32  HI_MPI_SYS_GetBindbyDest(MPP_CHN_S* pstDestChn, MPP_CHN_S* pstSrcChn);

HI_S32 HI_MPI_SYS_GetVersion(MPP_VERSION_S* pstVersion);

HI_S32 HI_MPI_SYS_GetChipId(HI_U32 *pu32ChipId);

/*
** u64Base is the global PTS of the system.
** ADVICE:
** 1. Better to call HI_MPI_SYS_GetCurPts on the host board to get u64Base.
** 2. When os start up, call HI_MPI_SYS_InitPtsBase to set the init PTS.
** 3. When media bussines is running, synchronize the PTS one time per minute
**     by calling HI_MPI_SYS_SyncPts.
*/
HI_S32 HI_MPI_SYS_GetCurPts(HI_U64* pu64CurPts);
HI_S32 HI_MPI_SYS_InitPtsBase(HI_U64 u64PtsBase);
HI_S32 HI_MPI_SYS_SyncPts(HI_U64 u64PtsBase);

/* alloc mmz memory in user context                                         */
HI_S32 HI_MPI_SYS_MmzAlloc(HI_U32* pu32PhyAddr, HI_VOID** ppVirtAddr,
                           const HI_CHAR* strMmb, const HI_CHAR* strZone, HI_U32 u32Len);

/* alloc mmz memory with cache */
HI_S32 HI_MPI_SYS_MmzAlloc_Cached(HI_U32* pu32PhyAddr, HI_VOID** ppVitAddr,
                                  const HI_CHAR* pstrMmb, const HI_CHAR* pstrZone, HI_U32 u32Len);

/* free mmz memory in user context                                          */
HI_S32 HI_MPI_SYS_MmzFree(HI_U32 u32PhyAddr, HI_VOID* pVirtAddr);

/* fulsh cache */
HI_S32 HI_MPI_SYS_MmzFlushCache(HI_U32 u32PhyAddr, HI_VOID* pVitAddr, HI_U32 u32Size);

/*
** Call the mmap function to map physical address to virtual address
** The system function mmap is too complicated, so we packge it.
*/
HI_VOID* HI_MPI_SYS_Mmap(HI_U32 u32PhyAddr, HI_U32 u32Size);
HI_VOID* HI_MPI_SYS_MmapCache(HI_U32 u32PhyAddr, HI_U32 u32Size);
HI_S32 HI_MPI_SYS_Munmap(HI_VOID* pVirAddr, HI_U32 u32Size);
HI_S32 HI_MPI_SYS_MflushCache(HI_U32 u32PhyAddr, HI_VOID *pVirAddr, HI_U32 u32Size);

/*
** Access the physical address.
** You can use this function to access memory address or register address.
*/

HI_S32 HI_MPI_SYS_SetMemConf(MPP_CHN_S* pstMppChn, const HI_CHAR* pcMmzName);
HI_S32 HI_MPI_SYS_GetMemConf(MPP_CHN_S* pstMppChn, HI_CHAR* pcMmzName);

/* Close all the FD which is used by sys module */
HI_S32 HI_MPI_SYS_CloseFd(HI_VOID);

/* Get VI VPSS work mode, 0: offline, >0: online */
HI_S32 HI_MPI_SYS_GetViVpssMode(HI_U32* pu32Mode);

/* media profile setting, for low power */
HI_S32 HI_MPI_SYS_SetProfile(PROFILE_TYPE_E enProfile);

/* Get virtual meminfo according to virtual addr, should be in one process */
HI_S32 HI_MPI_SYS_GetVirMemInfo(const void* pVitAddr, SYS_VIRMEM_INFO_S* pstMemInfo);

/* Set/get Scale coefficient level for VPSS/VGS*/
HI_S32 HI_MPI_SYS_SetScaleCoefLevel(SCALE_RANGE_S *pstScaleRange,SCALE_COEFF_LEVEL_S *pstScaleCoeffLevel);
HI_S32 HI_MPI_SYS_GetScaleCoefLevel(SCALE_RANGE_S *pstScaleRange,SCALE_COEFF_LEVEL_S *pstScaleCoeffLevel);

/* Set/Get local timezone, range: [-86400, 86400] seconds (that is: [-24, 24] hours)  */
HI_S32 HI_MPI_SYS_SetTimeZone(HI_S32 s32TimeZone);
HI_S32 HI_MPI_SYS_GetTimeZone(HI_S32 *ps32TimeZone);

HI_S32 HI_MPI_SYS_SetGPSInfo(GPS_INFO_S *pstGPSInfo);
HI_S32 HI_MPI_SYS_GetGPSInfo(GPS_INFO_S *pstGPSInfo);

HI_S32 HI_MPI_SYS_SetCheckResult(HI_S32 s32Result);
HI_S32 HI_MPI_SYS_GetCheckResult(HI_S32* ps32Result);
HI_S32 HI_MPI_SYS_GetCustomCode(HI_U32 *pu32CustomCode);

HI_S32 HI_MPI_LOG_SetLevelConf(LOG_LEVEL_CONF_S *pstConf);
HI_S32 HI_MPI_LOG_SetWaitFlag(HI_BOOL bWait);
HI_S32 HI_MPI_LOG_GetLevelConf(LOG_LEVEL_CONF_S *pstConf);
HI_S32 HI_MPI_LOG_Read(HI_CHAR *pBuf, HI_U32 u32Size);
HI_VOID HI_MPI_LOG_Close(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__MPI_SYS_H__ */

