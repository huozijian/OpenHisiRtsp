/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vpss.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Last Modified :
  Description   : mpi functions declaration
  Function List :
  History       :
  1.Date        : 20130508
    Author      : l00183122
    Modification: Create
******************************************************************************/
#ifndef __MPI_VPSS_H__
#define __MPI_VPSS_H__

#include "../../hisiComm/include/hi_comm_fisheye.h"
#include "../../hisiComm/include/hi_comm_video.h"
#include "../../hisiComm/include/hi_comm_vpss.h"
#include "../../hisiComm/include/hi_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/* Group Settings */
HI_S32 HI_MPI_VPSS_CreateGrp(VPSS_GRP VpssGrp, VPSS_GRP_ATTR_S *pstGrpAttr);
HI_S32 HI_MPI_VPSS_DestroyGrp(VPSS_GRP VpssGrp);

HI_S32 HI_MPI_VPSS_StartGrp(VPSS_GRP VpssGrp);
HI_S32 HI_MPI_VPSS_StopGrp(VPSS_GRP VpssGrp);

HI_S32 HI_MPI_VPSS_ResetGrp(VPSS_GRP VpssGrp);

HI_S32 HI_MPI_VPSS_GetGrpAttr(VPSS_GRP VpssGrp, VPSS_GRP_ATTR_S *pstGrpAttr);
HI_S32 HI_MPI_VPSS_SetGrpAttr(VPSS_GRP VpssGrp, VPSS_GRP_ATTR_S *pstGrpAttr);

HI_S32 HI_MPI_VPSS_SetGrpDelay(VPSS_GRP VpssGrp, HI_U32 u32Delay);
HI_S32 HI_MPI_VPSS_GetGrpDelay(VPSS_GRP VpssGrp, HI_U32 *pu32Delay);

HI_S32 HI_MPI_VPSS_SetGrpFrameRate(VPSS_GRP VpssGrp, VPSS_FRAME_RATE_S *pstVpssFrameRate);
HI_S32 HI_MPI_VPSS_GetGrpFrameRate(VPSS_GRP VpssGrp, VPSS_FRAME_RATE_S *pstVpssFrameRate);

HI_S32 HI_MPI_VPSS_SetGrpCrop(VPSS_GRP VpssGrp,  VPSS_CROP_INFO_S *pstCropInfo);
HI_S32 HI_MPI_VPSS_GetGrpCrop(VPSS_GRP VpssGrp,  VPSS_CROP_INFO_S *pstCropInfo);

HI_S32 HI_MPI_VPSS_SendFrame(VPSS_GRP VpssGrp,  VIDEO_FRAME_INFO_S *pstVideoFrame, HI_S32 s32MilliSec);

HI_S32 HI_MPI_VPSS_GetGrpFrame(VPSS_GRP VpssGrp, VIDEO_FRAME_INFO_S *pstVideoFrame, HI_U32 u32FrameIndex);
HI_S32 HI_MPI_VPSS_ReleaseGrpFrame(VPSS_GRP VpssGrp,  VIDEO_FRAME_INFO_S *pstVideoFrame);

HI_S32 HI_MPI_VPSS_EnableBackupFrame(VPSS_GRP VpssGrp);
HI_S32 HI_MPI_VPSS_DisableBackupFrame(VPSS_GRP VpssGrp);

/* only for Hi3516CV300 */
HI_S32 HI_MPI_VPSS_SetGrpSharpen (VPSS_GRP VpssGrp, VPSS_GRP_SHARPEN_ATTR_S *pstGrpSharpenAttr);
HI_S32 HI_MPI_VPSS_GetGrpSharpen (VPSS_GRP VpssGrp, VPSS_GRP_SHARPEN_ATTR_S *pstGrpSharpenAttr);

/* Chn Settings */
HI_S32 HI_MPI_VPSS_EnableChn(VPSS_GRP VpssGrp, VPSS_CHN VpssChn);
HI_S32 HI_MPI_VPSS_DisableChn(VPSS_GRP VpssGrp, VPSS_CHN VpssChn);

HI_S32 HI_MPI_VPSS_SetChnMode(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_MODE_S *pstVpssMode);
HI_S32 HI_MPI_VPSS_GetChnMode(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_MODE_S *pstVpssMode);

HI_S32 HI_MPI_VPSS_GetChnAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_ATTR_S *pstChnAttr);
HI_S32 HI_MPI_VPSS_SetChnAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_ATTR_S *pstChnAttr);

HI_S32 HI_MPI_VPSS_SetChnParam(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_PARAM_S *pstChnSpParam);
HI_S32 HI_MPI_VPSS_GetChnParam(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CHN_PARAM_S *pstChnSpParam);

HI_S32 HI_MPI_VPSS_SetDepth(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, HI_U32 u32Depth);
HI_S32 HI_MPI_VPSS_GetDepth(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, HI_U32 *pu32Depth);

HI_S32 HI_MPI_VPSS_GetChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, 
                               VIDEO_FRAME_INFO_S *pstVideoFrame, HI_S32 s32MilliSec);
HI_S32 HI_MPI_VPSS_ReleaseChnFrame(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,  VIDEO_FRAME_INFO_S *pstVideoFrame);

HI_S32 HI_MPI_VPSS_SetChnNR(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, HI_BOOL bEnable);
HI_S32 HI_MPI_VPSS_GetChnNR(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, HI_BOOL *pbEnable);

HI_S32 HI_MPI_VPSS_SetChnCrop(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,  VPSS_CROP_INFO_S *pstCropInfo);
HI_S32 HI_MPI_VPSS_GetChnCrop(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,  VPSS_CROP_INFO_S *pstCropInfo);

HI_S32 HI_MPI_VPSS_SetChnCover(VPSS_GRP VpssGrp,VPSS_CHN VpssChn, HI_U32 u32CoverMask);	
HI_S32 HI_MPI_VPSS_GetChnCover(VPSS_GRP VpssGrp,VPSS_CHN VpssChn, HI_U32 *pu32CoverMask);	

HI_S32 HI_MPI_VPSS_SetChnOverlay(VPSS_GRP VpssGrp,VPSS_CHN VpssChn, HI_U32 u32OverlayMask);
HI_S32 HI_MPI_VPSS_GetChnOverlay(VPSS_GRP VpssGrp,VPSS_CHN VpssChn, HI_U32 *pu32OverlayMask);

HI_S32 HI_MPI_VPSS_SetLDCAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,  const VPSS_LDC_ATTR_S *pstLDCAttr);
HI_S32 HI_MPI_VPSS_GetLDCAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn,  VPSS_LDC_ATTR_S *pstLDCAttr);	

HI_S32 HI_MPI_VPSS_SetFisheyeConfig(VPSS_GRP VpssGrp, const FISHEYE_CONFIG_S *pstFisheyeConfig);
HI_S32 HI_MPI_VPSS_GetFisheyeConfig(VPSS_GRP VpssGrp, FISHEYE_CONFIG_S *pstFisheyeConfig);

HI_S32 HI_MPI_VPSS_SetFisheyeAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, const FISHEYE_ATTR_S *pstFisheyeAttr);
HI_S32 HI_MPI_VPSS_GetFisheyeAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, FISHEYE_ATTR_S *pstFisheyeAttr);

HI_S32 HI_MPI_VPSS_SetRotate(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, ROTATE_E enRotate);
HI_S32 HI_MPI_VPSS_GetRotate(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, ROTATE_E *penRotate);	

HI_S32 HI_MPI_VPSS_GetRegionLuma(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_REGION_INFO_S *pstRegionInfo,                                                
                                                HI_U32 *pu32LumaData,HI_S32 s32MilliSec);

HI_S32 HI_MPI_VPSS_SetLowDelayAttr(VPSS_GRP VpssGrp,  VPSS_CHN VpssChn,  VPSS_LOW_DELAY_INFO_S *pstLowDelayInfo);
HI_S32 HI_MPI_VPSS_GetLowDelayAttr(VPSS_GRP VpssGrp,  VPSS_CHN VpssChn,  VPSS_LOW_DELAY_INFO_S *pstLowDelayInfo);

/* ExtChn Settings */
HI_S32 HI_MPI_VPSS_SetExtChnAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_EXT_CHN_ATTR_S *pstExtChnAttr);
HI_S32 HI_MPI_VPSS_GetExtChnAttr(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_EXT_CHN_ATTR_S *pstExtChnAttr);

HI_S32 HI_MPI_VPSS_SetExtChnCrop(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, const VPSS_CROP_INFO_S *pstCropInfo);
HI_S32 HI_MPI_VPSS_GetExtChnCrop(VPSS_GRP VpssGrp, VPSS_CHN VpssChn, VPSS_CROP_INFO_S *pstCropInfo);


/* For 3DNR */
HI_S32 HI_MPI_VPSS_SetRefSelect(VPSS_GRP VpssGrp, const VPSS_REF_SEL_MODE_E enRefSelMode);	
HI_S32 HI_MPI_VPSS_GetRefSelect(VPSS_GRP VpssGrp, VPSS_REF_SEL_MODE_E *penRefSelMode);

/* only for HI3516AV100 */
HI_S32 HI_MPI_VPSS_SetGrpParam(VPSS_GRP VpssGrp, VPSS_GRP_PARAM_S *pstVpssParam);
HI_S32 HI_MPI_VPSS_GetGrpParam(VPSS_GRP VpssGrp, VPSS_GRP_PARAM_S *pstVpssParam);

HI_S32 HI_MPI_VPSS_SetNRV3Param(VPSS_GRP VpssGrp, VPSS_GRP_VPPNRBEX_S *pstVpssNrParam);
HI_S32 HI_MPI_VPSS_GetNRV3Param(VPSS_GRP VpssGrp, VPSS_GRP_VPPNRBEX_S *pstVpssNrParam);

HI_S32 HI_MPI_VPSS_SetGrpParamV2(VPSS_GRP VpssGrp, VPSS_GRP_PARAM_V2_S *pstVpssParamV2);
HI_S32 HI_MPI_VPSS_GetGrpParamV2(VPSS_GRP VpssGrp, VPSS_GRP_PARAM_V2_S *pstVpssParamV2);

/* only for HI3518EV200 HI3518EV201 HI3516CV200 */
HI_S32 HI_MPI_VPSS_SetNRParam(VPSS_GRP VpssGrp, VPSS_NR_PARAM_U *punNrParam);   
HI_S32 HI_MPI_VPSS_GetNRParam(VPSS_GRP VpssGrp, VPSS_NR_PARAM_U *punNrParam);

/* only for HI3519V100 */
HI_S32 HI_MPI_VPSS_SetNRBParam(VPSS_GRP VpssGrp, VPSS_GRP_VPPNRB_S *pstVpssNrBParam);
HI_S32 HI_MPI_VPSS_GetNRBParam(VPSS_GRP VpssGrp, VPSS_GRP_VPPNRB_S *pstVpssNrBParam);

/* only for HI3518EV200 HI3518EV201 HI3516CV200 HI3519V100*/
HI_S32 HI_MPI_VPSS_SetGrpNRBParam(VPSS_GRP VpssGrp, VPSS_GRP_NRB_PARAM_S *pstNRBParam);
HI_S32 HI_MPI_VPSS_GetGrpNRBParam(VPSS_GRP VpssGrp, VPSS_GRP_NRB_PARAM_S *pstNRBParam);

/* for all chip except Hi3516A */
HI_S32 HI_MPI_VPSS_SetGrpNRSParam(VPSS_GRP VpssGrp, VPSS_GRP_NRS_PARAM_S *pstNRSParam);
HI_S32 HI_MPI_VPSS_GetGrpNRSParam(VPSS_GRP VpssGrp, VPSS_GRP_NRS_PARAM_S *pstNRSParam);

/* only for HI3516CV300 HI3519V101*/
HI_S32 HI_MPI_VPSS_SetGrpNRXParam(VPSS_GRP VpssGrp, VPSS_GRP_NRX_PARAM_S *pstNRXParam);
HI_S32 HI_MPI_VPSS_GetGrpNRXParam(VPSS_GRP VpssGrp, VPSS_GRP_NRX_PARAM_S *pstNRXParam);
HI_S32 HI_MPI_VPSS_GetGrpNRIntfType(VPSS_GRP VpssGrp, VPSS_NR_INTF_E *penNrIntfType);

/* Module Param Settings */
HI_S32 HI_MPI_VPSS_SetModParam(VPSS_MOD_PARAM_S *pstModParam);
HI_S32 HI_MPI_VPSS_GetModParam(VPSS_MOD_PARAM_S *pstModParam);

HI_S32 HI_MPI_VPSS_GetChnFd(VPSS_GRP VpssGrp, VPSS_CHN VpssChn);
HI_S32 HI_MPI_VPSS_CloseFd(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __MPI_VPSS_H__ */

