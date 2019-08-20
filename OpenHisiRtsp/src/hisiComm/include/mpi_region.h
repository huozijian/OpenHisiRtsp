/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_region.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/05/07
  Description   : 
  History       :
  1.Date        : 2013/05/07
    Author      : c00191088 
    Modification: Created file

******************************************************************************/
#ifndef __MPI_REGION_H__
#define __MPI_REGION_H__

#include "../../hisiComm/include/hi_comm_region.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 HI_MPI_RGN_Create(RGN_HANDLE Handle, const RGN_ATTR_S *pstRegion);
HI_S32 HI_MPI_RGN_Destroy(RGN_HANDLE Handle);

HI_S32 HI_MPI_RGN_GetAttr(RGN_HANDLE Handle, RGN_ATTR_S *pstRegion);
HI_S32 HI_MPI_RGN_SetAttr(RGN_HANDLE Handle, const RGN_ATTR_S *pstRegion);

HI_S32 HI_MPI_RGN_SetBitMap(RGN_HANDLE Handle, const BITMAP_S *pstBitmap);

HI_S32 HI_MPI_RGN_AttachToChn(RGN_HANDLE Handle, const MPP_CHN_S *pstChn, const RGN_CHN_ATTR_S *pstChnAttr);
HI_S32 HI_MPI_RGN_DetachFromChn(RGN_HANDLE Handle, const MPP_CHN_S *pstChn);

HI_S32 HI_MPI_RGN_SetDisplayAttr(RGN_HANDLE Handle, const MPP_CHN_S *pstChn, const RGN_CHN_ATTR_S *pstChnAttr);
HI_S32 HI_MPI_RGN_GetDisplayAttr(RGN_HANDLE Handle, const MPP_CHN_S *pstChn, RGN_CHN_ATTR_S *pstChnAttr);

HI_S32 HI_MPI_RGN_SetAttachField(RGN_HANDLE Handle, VIDEO_FIELD_E enAttachField);
HI_S32 HI_MPI_RGN_GetAttachField(RGN_HANDLE Handle, VIDEO_FIELD_E *penAttachField);

HI_S32 HI_MPI_RGN_GetCanvasInfo(RGN_HANDLE Handle, RGN_CANVAS_INFO_S *pstCanvasInfo);
HI_S32 HI_MPI_RGN_UpdateCanvas(RGN_HANDLE Handle);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __MPI_REGION_H__ */

