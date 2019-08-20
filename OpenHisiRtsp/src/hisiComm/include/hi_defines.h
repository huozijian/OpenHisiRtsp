/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_defines.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : The common data type defination
Function List :
History       :
******************************************************************************/
#ifndef __HI_DEFINES_H__
#define __HI_DEFINES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define HI3516A_V100 0x3516A100
#define HI3516A_V200 0x3516A200
#define HI3516D_V100 0x3516D100
#define HI3518E_V200 0x3518E200
#define HI3519_V100  0x3519100
#define HI3516C_V300 0x3516C300
#define HI3516E_V100 0x3516E100
#define HI3519_V101  0x35190101
#define HI3559_V100  0x3559100
#define HI35xx_Vxxx  0x35000000

#ifndef HICHIP
    #define HICHIP HI3516C_V300
#endif

#if HICHIP==HI3516A_V100
    #define CHIP_NAME    "Hi3516A"
    #define MPP_VER_PRIX "_MPP_V"
#elif HICHIP==HI3516A_V200
    #define CHIP_NAME    "Hi3516AV200"
    #define MPP_VER_PRIX "_MPP_V"
#elif HICHIP==HI3518E_V200
    #define CHIP_NAME    "Hi3518EV200"
    #define MPP_VER_PRIX "_MPP_V"
#elif HICHIP==HI3519_V100
    #define CHIP_NAME    "Hi3519V100"
    #define MPP_VER_PRIX "_MPP_V"
#elif HICHIP==HI3516C_V300
    #define CHIP_NAME    "Hi3516CV300"
    #define MPP_VER_PRIX "_MPP_V"
#elif HICHIP==HI35xx_Vxxx
    #error HuHu, I am an dummy chip
#else
    #error HICHIP define may be error
#endif


#define DEFAULT_ALIGN                16
#define MAX_MMZ_NAME_LEN             16

#define MAX_NODE_NUM                 16

/* For VDA */
#define VDA_MAX_NODE_NUM             32
#define VDA_MAX_INTERNAL             256
#define VDA_CHN_NUM_MAX              32
#define VDA_MAX_WIDTH                960
#define VDA_MAX_HEIGHT               960
#define VDA_MIN_WIDTH                32
#define VDA_MIN_HEIGHT               32

/* For VENC */
#define VENC_MAX_NAME_LEN            16
#define VENC_MAX_CHN_NUM             16
#define VENC_MAX_GRP_NUM             16
#define VEDU_NUM                     1
#define H264E_MAX_WIDTH              2048
#define H264E_MAX_HEIGHT             2048
#define H264E_MIN_WIDTH              128
#define H264E_MIN_HEIGHT             128
#define H264E_LIMITED_WIDTH_HEIGHT   2048
#define H264E_MAX_AREA               (2048*2048)

#define H265E_MAX_WIDTH              2048
#define H265E_MAX_HEIGHT             2048
#define H265E_MIN_WIDTH              128
#define H265E_MIN_HEIGHT             128
#define H265E_LIMITED_WIDTH_HEIGHT   2048
#define H265E_MAX_AREA               (2048*2048)

#define JPEGE_MAX_WIDTH              2048
#define JPEGE_MAX_HEIGHT             2048
#define JPEGE_MIN_WIDTH              32
#define JPEGE_MIN_HEIGHT             32
#define VENC_MAX_ROI_NUM             8
#define H264E_MIN_HW_INDEX           0
#define H264E_MAX_HW_INDEX           11
#define H264E_MIN_VW_INDEX           0
#define H264E_MAX_VW_INDEX           3
#define VENC_MAX_SSE_NUM             8
#define VENC_QP_HISGRM_NUM           52

/* For RC */
#define RC_TEXTURE_THR_SIZE          16
//#define RC_RQRATIO_SIZE            8

/* For VDEC, this chip not support */
#define VDEC_MAX_CHN_NUM             0

/* For Region */
/* For Region */
#define RGN_MIN_WIDTH                2
#define RGN_MIN_HEIGHT               2

#define RGN_COVER_MIN_X              -8190
#define RGN_COVER_MIN_Y              -8190
#define RGN_COVER_MAX_X              8190
#define RGN_COVER_MAX_Y              8190
#define RGN_COVER_MAX_WIDTH          8190
#define RGN_COVER_MAX_HEIGHT         8190

#define RGN_OVERLAY_MIN_X            0
#define RGN_OVERLAY_MIN_Y            0
#define RGN_OVERLAY_MAX_X            8190
#define RGN_OVERLAY_MAX_Y            8190
#define RGN_OVERLAY_MAX_WIDTH        2048
#define RGN_OVERLAY_MAX_HEIGHT       2048

#define RGN_MAX_BUF_NUM 2

#define RGN_MOSAIC_MIN_X             0
#define RGN_MOSAIC_MIN_Y             0
#define RGN_MOSAIC_MAX_X             2048
#define RGN_MOSAIC_MAX_Y             2048
#define RGN_MOSAIC_MIN_WIDTH         32
#define RGN_MOSAIC_MIN_HEIGHT        32
#define RGN_MOSAIC_MAX_WIDTH         2048
#define RGN_MOSAIC_MAX_HEIGHT        2048

#define RGN_ALIGN                    2

#define RGN_HANDLE_MAX               1024

#define COVER_MAX_NUM_VI             0
#define COVEREX_MAX_NUM_VI           16
#define OVERLAY_MAX_NUM_VI           0
#define OVERLAYEX_MAX_NUM_VI         16

#define OVERLAY_MAX_NUM_VENC         8
#define OVERLAY_MAX_X_VENC           8190
#define OVERLAY_MAX_Y_VENC           8190

#define OVERLAYEX_MAX_NUM_VENC       8
#define OVERLAYEX_MAX_X_VENC         8190
#define OVERLAYEX_MAX_Y_VENC         8190

#define COVER_MAX_NUM_VPSS           8
#define COVEREX_MAX_NUM_VPSS         8
#define OVERLAY_MAX_NUM_VPSS         0
#define OVERLAYEX_MAX_NUM_VPSS       8
#define MOSAIC_MAX_NUM_VPSS          4


#define COVEREX_MAX_NUM_VO           1
#define OVERLAYEX_MAX_NUM_VO         1

#define OVERLAYEX_MAX_NUM_PCIV       0


#define HISI_MAX_SENSOR_NUM          4

/* number of channle and device on video input unit of chip
 * Note! VIU_MAX_CHN_NUM is NOT equal to VIU_MAX_DEV_NUM
 * multiplied by VIU_MAX_CHN_NUM, because all VI devices
 * can't work at mode of 4 channles at the same time.
 */
#define VIU_MAX_DEV_NUM              1
#define VIU_MAX_WAY_NUM_PER_DEV      1
#define VIU_MAX_CHN_NUM_PER_DEV      1
#define VIU_MAX_PHYCHN_NUM           1
#define VIU_MAX_RAWCHN_NUM           1      /* raw data chn, DVR/NVR: 0 */
#define VIU_EXT_CHN_START            VIU_MAX_PHYCHN_NUM
#define VIU_MAX_EXT_CHN_NUM          16
#define VIU_MAX_EXTCHN_BIND_PER_CHN  8

#define VIU_MAX_CHN_NUM              (VIU_MAX_PHYCHN_NUM + VIU_MAX_EXT_CHN_NUM)
#define VIU_MAX_UFLIST_NUM           (VIU_MAX_CHN_NUM + VIU_MAX_RAWCHN_NUM)
#define VIU_MAX_RAWLIST_NUM 		 2

#define VIU_DEV_MIN_WIDTH       64
#define VIU_DEV_MIN_HEIGHT      64
#define VIU_DEV_MAX_WIDTH       2048
#define VIU_DEV_MAX_HEIGHT      2048
#define VIU_CHN_MIN_WIDTH       64
#define VIU_CHN_MIN_HEIGHT      64
#define VIU_CHN_MAX_WIDTH       VIU_DEV_MAX_WIDTH
#define VIU_CHN_MAX_HEIGHT      VIU_DEV_MAX_HEIGHT
#define VIU_EXTCHN_MIN_WIDTH    64
#define VIU_EXTCHN_MIN_HEIGHT   64
#define VIU_EXTCHN_MAX_WIDTH    2048
#define VIU_EXTCHN_MAX_HEIGHT   2048
#define VIU_EXTCHN_MINIFICATION 13  /* The maximum minification for the ext chn */

#define VIU_ROTATE_MAX_WIDTH    2048

#define VIU_CHNID_DEV_FACTOR    2

/* Don't support cascade. The definition of Macro is just for compiling */
#define VIU_MAX_CAS_CHN_NUM     2
#define VIU_SUB_CHN_START       16      /* The starting number of sub channel */
#define VIU_CAS_CHN_START       32      /* The starting number of cascade channel */

/* max number of VBI region*/
#define VIU_MAX_VBI_NUM         2
/* max length of one VBI region (by word) */
#define VIU_MAX_VBI_LEN         8


/* for DIS*/
#define DIS_PYRAMID_LAYER_NUM   5

/* For VO */
#define VO_MIN_CHN_WIDTH        32      /* channel minimal width */
#define VO_MIN_CHN_HEIGHT       32      /* channel minimal height */

#define VO_MAX_ZOOM_RATIO       1000    /* max zoom ratio, 1000 means 100% scale */

#define VO_MAX_DEV_NUM          1       /* max dev num */
#define VO_MAX_LAYER_NUM        1       /* max layer num */
#define PIP_MAX_CHN_NUM         8
#define VHD_MAX_CHN_NUM         8       /* max VHD chn num */
#define VO_MAX_CHN_NUM          VHD_MAX_CHN_NUM      /* max chn num */
#define VO_MAX_LAYER_IN_DEV     1      /* max layer num of each dev */
#define VO_MIN_CHN_LINE         2


#define VO_MAX_GFX_LAYER_PER_DEV    1
#define VO_MAX_GRAPHICS_LAYER_NUM   1
#define MDDRC_ZONE_MAX_NUM          32

#define VO_MAX_PRIORITY         2
#define VO_MIN_TOLERATE         1       /* min play toleration 1ms */
#define VO_MAX_TOLERATE         100000  /* max play toleration 100s */

#define AI_DEV_MAX_NUM          1
#define AO_DEV_MIN_NUM          0
#define AO_DEV_MAX_NUM          1
#define AIO_MAX_NUM             1
#define AIO_MAX_CHN_NUM         2
#define AENC_MAX_CHN_NUM        32
#define ADEC_MAX_CHN_NUM        32

/* For VPSS */
#define VPSS_MAX_GRP_NUM   		32

#define VPSS_MAX_PHY_CHN_NUM	3
#define VPSS_MAX_EXT_CHN_NUM  	8
#define VPSS_MAX_CHN_NUM   		(VPSS_MAX_PHY_CHN_NUM + VPSS_MAX_EXT_CHN_NUM)
#define VPSS_MAX_DELAY_CHN_NUM  3

#define VPSS_MIN_IMAGE_WIDTH    64
#define VPSS_MIN_IMAGE_HEIGHT   64

#define VPSS_MAX_IMAGE_WIDTH            2048
#define VPSS_MAX_IMAGE_HEIGHT           2048

#define VPSS_EXTCHN_MAX_IMAGE_WIDTH     VPSS_MAX_IMAGE_WIDTH
#define VPSS_EXTCHN_MAX_IMAGE_HEIGHT    VPSS_MAX_IMAGE_HEIGHT

#define VPSS_MAX_ZOOMIN 16
#define VPSS_MAX_ZOOMOUT 15

#define VPSS_EXT_CHN_MAX_ZOOMIN  16
#define VPSS_EXT_CHN_MAX_ZOOMOUT  15

/* For pciv, hi3516a not support */
#define PCIV_MAX_CHN_NUM        0       /* max pciv channel number in each pciv device */

/*For IVS_MD*/
#define MD_MAX_CHN				64
#define MD_MAX_WIDTH			1920
#define MD_MAX_HEIGHT			1080
#define MD_MIN_WIDTH			64
#define MD_MIN_HEIGHT			64

/**************************************************************
VB size calculate for compressed frame.
	[param input]
		w: 	width
		h: 	height
		fmt:	pixel format, 0: SP420, 1: SP422
		z:	compress mode, 0: no compress, 1: default compress
	[param output]
		size: vb blk size
***************************************************************/
#define VB_W_ALIGN		    16
#define VB_H_ALIGN		    2
#define VB_HEADER_STRIDE    16
#define VB_ALIGN(x, a)	    ((a) * (((x) + (a) - 1) / (a)))

#define VB_PIC_Y_HEADER_SIZE(Width, Height, size)\
	do{\
            size = VB_HEADER_STRIDE * (Height);\
	}while(0)

#define VB_PIC_HEADER_SIZE(Width, Height, Type, size)\
	do{\
            if (PIXEL_FORMAT_YUV_SEMIPLANAR_422 == Type || PIXEL_FORMAT_RGB_BAYER == Type )\
            {\
		        size = VB_HEADER_STRIDE * (Height) * 2;\
            }\
            else if(PIXEL_FORMAT_YUV_SEMIPLANAR_420 == Type)\
            {\
                size = (VB_HEADER_STRIDE * (Height) * 3) >> 1;\
            }\
            else if(PIXEL_FORMAT_YUV_400 == Type)\
            {\
                size = VB_HEADER_STRIDE * (Height);\
            }\
	}while(0)

#define VB_PIC_BLK_SIZE(Width, Height, Type, size)\
	do{\
			unsigned int u32AlignWidth;\
			unsigned int u32AlignHeight;\
			unsigned int u32HeadSize;\
		    u32AlignWidth = VB_ALIGN(Width, 16);\
		    u32AlignHeight= VB_ALIGN(Height, 2);\
		    u32HeadSize = VB_HEADER_STRIDE * u32AlignHeight;/* compress header stride 16 */\
		    if (PIXEL_FORMAT_YUV_SEMIPLANAR_422 == Type)\
            {\
		        size = (u32AlignWidth * u32AlignHeight + u32HeadSize) * 2;\
            }\
            else if (PIXEL_FORMAT_YUV_400 == Type)\
            {\
				size = (u32AlignWidth * u32AlignHeight + u32HeadSize);\
			}\
            else\
            {\
                size = ((u32AlignWidth * u32AlignHeight + u32HeadSize) * 3) >> 1;\
            }\
	}while(0)

#define VIU_GET_RAW_CHN(ViDev, RawChn)\
    do{\
			RawChn = VIU_MAX_CHN_NUM + ViDev;\
	}while(0)

#define VENC_H264_BLK_SIZE(Width, Height, size)\
    do{\
        HI_U32 u32AlignWidth, u32AlignHeight, u32Align256Width, u32Align2048Width;\
        HI_U32 u32PmeSize, u32PmeInfoSize;\
        HI_U32 u32YSize, u32CSize, u32HeaderSize;\
        u32AlignWidth     = ((Width  +   63)>> 6)<<6;\
        u32AlignHeight    = ((Height +   15)>> 4)<<4;\
        u32Align256Width  = ((Width  +  255)>> 8)<<8;\
        u32Align2048Width = ((Width  + 2047)>>11)<<11;\
        u32HeaderSize  = (u32Align256Width>>4) * (u32AlignHeight>>4) * 4;  \
        u32YSize       = u32AlignWidth * u32AlignHeight;\
        u32CSize       = u32YSize >> 1;  \
        u32PmeSize     = (u32AlignWidth * u32AlignHeight) >> 4;  \
        u32PmeInfoSize = (u32Align2048Width * u32AlignHeight) >> 11;    \
        size = u32YSize + u32CSize + u32HeaderSize + u32PmeSize + u32PmeInfoSize;\
    }while(0)


#define VENC_H265_BLK_SIZE(Width, Height, size)\
    do{\
        HI_U32 u32AlignWidth, u32AlignHeight, u32Align512Width;\
        HI_U32 u32TmvSize, u32PmeSize, u32PmeInfoSize, u32LcuNum;\
        HI_U32 u32YSize, u32CSize, u32HeaderSize;\
        u32AlignWidth    = ((Width  +  63)>>6)<<6;\
        u32AlignHeight   = ((Height +  63)>>6)<<6;\
        u32Align512Width = ((Width  + 511)>>9)<<9;\
        u32LcuNum = (u32AlignWidth>>6) * (u32AlignHeight>>6);\
        u32TmvSize     = u32LcuNum << 7;\
        u32PmeSize     = u32LcuNum << 8;\
        u32PmeInfoSize = ((u32Align512Width * u32AlignHeight) >> 10);\
        u32HeaderSize  = u32LcuNum << 6;  \
        u32YSize       = u32AlignWidth * u32AlignHeight;\
        u32CSize       = u32YSize >> 1;\
        size = u32YSize + u32CSize + u32HeaderSize + u32TmvSize + u32PmeSize + u32PmeInfoSize;\
    }while(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_DEFINES_H__ */

