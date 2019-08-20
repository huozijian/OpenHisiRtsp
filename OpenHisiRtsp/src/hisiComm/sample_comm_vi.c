
/******************************************************************************
  Some simple Hisilicon Hi35xx video input functions.

  Copyright (C), 2010-2018, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
    Modification:  2017-8 Created
******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include "../hisiComm/include/hi_mipi.h"

#include "../hisiComm/include/hi_common.h"
#include "../hisiComm/sample_comm.h"

VI_DEV_ATTR_S DEV_ATTR_BT656D1_1MUX =
{
    /* interface mode */
    VI_MODE_BT656,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFF000000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_INTERLACED,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YVYU,
    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_FIELD, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SINGAL, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            0,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            0,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* ISP bypass */
    VI_PATH_BYPASS,
    /* input data type */
    VI_DATA_TYPE_YUV
};

/* BT1120 1080I */
VI_DEV_ATTR_S DEV_ATTR_BT1120_1080I_1MUX =
{
    /* interface mode */
    VI_MODE_BT1120_STANDARD,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFF000000,    0xFF0000},
    /* progessive or interleaving */
    VI_SCAN_INTERLACED,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_UVUV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_NORM_PULSE, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            0,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            0,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* ISP bypass */
    VI_PATH_BYPASS,
    /* input data type */
    VI_DATA_TYPE_YUV,
    /* bReverse */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1920, 1080}
};

/* BT1120 1080p */
VI_DEV_ATTR_S DEV_ATTR_BT1120_1080P_BASE =
{
    /* interface mode */
    VI_MODE_BT1120_STANDARD,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFF000000,    0xFF0000},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_UVUV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_NORM_PULSE, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            0,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            0,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* ISP bypass */
    VI_PATH_BYPASS,
    /* input data type */
    VI_DATA_TYPE_YUV,
    /* bReverse */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1920, 1080}
};


/* BT1120 720P */
VI_DEV_ATTR_S DEV_ATTR_BT1120_720P_BASE =
    /* classical timing 3:7441 BT1120 720P@60fps*/
{
    /* interface mode */
    VI_MODE_BT1120_STANDARD,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFF000000,    0xFF0000},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    //VI_SCAN_INTERLACED,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_UVUV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_NORM_PULSE, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1280,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            720,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* ISP bypass */
    VI_PATH_BYPASS,
    /* input data type */
    VI_DATA_TYPE_YUV,
    /* bReverse */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1280, 720}
};

/*imx122 DC 12bit*/
VI_DEV_ATTR_S DEV_ATTR_IMX122_DC_1080P =
{
    /* interface mode */
    VI_MODE_DIGITAL_CAMERA,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF00000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_NORM_PULSE, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1920,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            1080,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB
};

/*mt9p006 DC 12bit*/
VI_DEV_ATTR_S DEV_ATTR_MT9P006_DC_1080P =
{
    /* interface mode */
    VI_MODE_DIGITAL_CAMERA,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF00000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SINGAL, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1920,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            1080,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB
};

VI_DEV_ATTR_S DEV_ATTR_LVDS_BASE =
{
    /* interface mode */
    VI_MODE_LVDS,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF00000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_LOW, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SINGAL, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1280,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            720,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB,
    /* bRever */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1920, 1080}
};


VI_DEV_ATTR_S DEV_ATTR_MIPI_BASE =
{
    /* interface mode */
    VI_MODE_MIPI,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF00000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_LOW, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SINGAL, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1280,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            720,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB,
    /* bRever */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1920, 1080}
};

VI_DEV_ATTR_S DEV_ATTR_MIPI_BASE_IMX323 =
{
    /* interface mode */
    VI_MODE_DIGITAL_CAMERA,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF0000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_PULSE, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_VALID_SINGAL, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1920,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            1080,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB,
    /* bRever */
    HI_FALSE,
    /* DEV CROP */
    {200, 20, 1920, 1080}
};



VI_DEV_ATTR_S DEV_ATTR_MIPI_BASE_SC2235 =
{
    /* interface mode */
    VI_MODE_DIGITAL_CAMERA,
    /* multiplex mode */
    VI_WORK_MODE_1Multiplex,
    /* r_mask    g_mask    b_mask*/
    {0xFFF0000,    0x0},
    /* progessive or interleaving */
    VI_SCAN_PROGRESSIVE,
    /*AdChnId*/
    { -1, -1, -1, -1},
    /*enDataSeq, only support yuv*/
    VI_INPUT_DATA_YUYV,

    /* synchronization information */
    {
        /*port_vsync   port_vsync_neg     port_hsync        port_hsync_neg        */
        VI_VSYNC_FIELD, VI_VSYNC_NEG_HIGH, VI_HSYNC_VALID_SINGNAL, VI_HSYNC_NEG_HIGH, VI_VSYNC_NORM_PULSE, VI_VSYNC_VALID_NEG_HIGH,

        /*hsync_hfb    hsync_act    hsync_hhb*/
        {
            0,            1920,        0,
            /*vsync0_vhb vsync0_act vsync0_hhb*/
            0,            1080,        0,
            /*vsync1_vhb vsync1_act vsync1_hhb*/
            0,            0,            0
        }
    },
    /* use interior ISP */
    VI_PATH_ISP,
    /* input data type */
    VI_DATA_TYPE_RGB,
    /* bRever */
    HI_FALSE,
    /* DEV CROP */
    {0, 0, 1920, 1080}
};


combo_dev_attr_t MIPI_4lane_SENSOR_MN34220_MIPI_12BIT_ATTR =
{
    .devno         = 0,
    .input_mode    = INPUT_MODE_MIPI,

    {
        .mipi_attr =
        {
            .raw_data_type = RAW_DATA_12BIT,
            .wdr_mode      = HI_WDR_MODE_NONE,
            .lane_id       ={0, 1, 2, 3}
        }
    }

};

combo_dev_attr_t SUBLVDS_4lane_SENSOR_MN34220_12BIT_1080_NOWDR_ATTR =
{
    /* input mode */
    .devno = 0,
    .input_mode = INPUT_MODE_SUBLVDS,
    .lvds_attr = {
        .img_size = {1920, 1080},
        .raw_data_type = RAW_DATA_12BIT,
        .wdr_mode = HI_WDR_MODE_NONE,
        .sync_mode = LVDS_SYNC_MODE_SOF,

        .data_endian = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 2, 1, 3},
        .sync_code =  {
              {{0x002, 0x003, 0x000, 0x001}, //PHY0_lane0
              {0x002, 0x003, 0x000, 0x001},
              {0x002, 0x003, 0x000, 0x001},
              {0x002, 0x003, 0x000, 0x001}},

              {{0x012, 0x013, 0x010, 0x011}, //PHY0_lane1
              {0x012, 0x013, 0x010, 0x011},
              {0x012, 0x013, 0x010, 0x011},
              {0x012, 0x013, 0x010, 0x011}},

              {{0x006, 0x007, 0x004, 0x005}, //PHY0_lane2
              {0x006, 0x007, 0x004, 0x005},
              {0x006, 0x007, 0x004, 0x005},
              {0x006, 0x007, 0x004, 0x005}},

              {{0x016, 0x017, 0x014, 0x015}, //PHY0_lane3  INPUT_MODE_LVDS
              {0x016, 0x017, 0x014, 0x015},
              {0x016, 0x017, 0x014, 0x015},
              {0x016, 0x017, 0x014, 0x015}},
           }
    }

};

combo_dev_attr_t SUBLVDS_4lane_SENSOR_MN34220_12BIT_720_NOWDR_ATTR =
{
    /* input mode */
    .devno = 0,
    .input_mode = INPUT_MODE_SUBLVDS,
    .lvds_attr = {
        .img_size = {1280, 720},
        .raw_data_type = RAW_DATA_12BIT,
        .wdr_mode = HI_WDR_MODE_NONE,
        .sync_mode = LVDS_SYNC_MODE_SOF,

        .data_endian = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 2, 1, 3},
        .sync_code =  {
              {{0x002, 0x003, 0x000, 0x001}, //PHY0_lane0
              {0x002, 0x003, 0x000, 0x001},
              {0x002, 0x003, 0x000, 0x001},
              {0x002, 0x003, 0x000, 0x001}},

              {{0x012, 0x013, 0x010, 0x011}, //PHY0_lane1
              {0x012, 0x013, 0x010, 0x011},
              {0x012, 0x013, 0x010, 0x011},
              {0x012, 0x013, 0x010, 0x011}},

              {{0x006, 0x007, 0x004, 0x005}, //PHY0_lane2
              {0x006, 0x007, 0x004, 0x005},
              {0x006, 0x007, 0x004, 0x005},
              {0x006, 0x007, 0x004, 0x005}},

              {{0x016, 0x017, 0x014, 0x015}, //PHY0_lane3  INPUT_MODE_LVDS
              {0x016, 0x017, 0x014, 0x015},
              {0x016, 0x017, 0x014, 0x015},
              {0x016, 0x017, 0x014, 0x015}},
           }
    }

};



combo_dev_attr_t SUBLVDS_4lane_SENSOR_MN34220_12BIT_1080_2WDR1_ATTR =
{
    /* input mode */
    .devno = 0,
    .input_mode = INPUT_MODE_SUBLVDS,
    .lvds_attr = {
        .img_size = {1920, 1108},
        .raw_data_type = RAW_DATA_12BIT,
        .wdr_mode = HI_WDR_MODE_2F,
        .sync_mode = LVDS_SYNC_MODE_SOF,

        .data_endian = LVDS_ENDIAN_BIG,
        .sync_code_endian = LVDS_ENDIAN_BIG,
        .lane_id = {0, 2, 1, 3},
        .sync_code =  {
              {{0x002, 0x003, 0x000, 0x001}, //PHY0_lane0
              {0x202, 0x203, 0x200, 0x201},
              {0x102, 0x103, 0x100, 0x101},
              {0x302, 0x303, 0x300, 0x301}},

              {{0x012, 0x013, 0x010, 0x011}, //PHY0_lane1
              {0x212, 0x213, 0x210, 0x211},
              {0x112, 0x113, 0x110, 0x111},
              {0x312, 0x313, 0x310, 0x311}},

              {{0x006, 0x007, 0x004, 0x005}, //PHY0_lane2
              {0x206, 0x207, 0x204, 0x205},
              {0x106, 0x107, 0x104, 0x105},
              {0x306, 0x307, 0x304, 0x305}},

              {{0x016, 0x017, 0x014, 0x015}, //PHY0_lane3  INPUT_MODE_LVDS
              {0x216, 0x217, 0x214, 0x215},
              {0x116, 0x117, 0x114, 0x115},
              {0x316, 0x317, 0x314, 0x315}},
           }
    }

};

combo_dev_attr_t SUBLVDS_4lane_SENSOR_AR0237_12BIT_1080_2WDR1_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_HISPI,

    {
        .lvds_attr = {
            .img_size = {1920, 1080},
            .wdr_mode = HI_WDR_MODE_2F,
            .sync_mode = LVDS_SYNC_MODE_SOF,
            .raw_data_type    =RAW_DATA_12BIT,
            .data_endian = LVDS_ENDIAN_LITTLE,
            .sync_code_endian = LVDS_ENDIAN_LITTLE,
            .lane_id = {0, 1, 2, 3},
            .sync_code = {
                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane0
                   {0x043, 0x047, 0x041, 0x045},
                   {0x023, 0x027, 0x021, 0x025},
                   {0x083, 0x087, 0x081, 0x085}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane1
                   {0x043, 0x047, 0x041, 0x045},
                   {0x023, 0x027, 0x021, 0x025},
                   {0x083, 0x087, 0x081, 0x085}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane2
                   {0x043, 0x047, 0x041, 0x045},
                   {0x023, 0x027, 0x021, 0x025},
                   {0x083, 0x087, 0x081, 0x085}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane3
                   {0x043, 0x047, 0x041, 0x045},
                   {0x023, 0x027, 0x021, 0x025},
                   {0x083, 0x087, 0x081, 0x085}},
            }

        }
    }
};

combo_dev_attr_t SUBLVDS_4lane_SENSOR_AR0237_12BIT_1080_NOWDR_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_HISPI,

    {
        .lvds_attr = {
            .img_size = {1920, 1080},
            .wdr_mode = HI_WDR_MODE_NONE,
            .sync_mode = LVDS_SYNC_MODE_SOF,
            .raw_data_type    =RAW_DATA_12BIT,
            .data_endian = LVDS_ENDIAN_LITTLE,
            .sync_code_endian = LVDS_ENDIAN_LITTLE,
            .lane_id = {0, 1, 2, 3},
            .sync_code = {
                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane0
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane1
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane2
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5}},

                   {{0x3, 0x7, 0x1, 0x5}, //PHY0_lane3
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5},
                   {0x3, 0x7, 0x1, 0x5}},
            }

        }
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX290_12BIT_1080_NOWDR_ATTR =
{
	.devno = 0,
	.input_mode = INPUT_MODE_MIPI,
	{
		.mipi_attr =
		{
			RAW_DATA_12BIT,
			HI_MIPI_WDR_MODE_NONE,
			{0, 1, 2, 3}
		}
	}
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX290_10BIT_1080_2DOL1_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,

    .mipi_attr =
    {
        .raw_data_type = RAW_DATA_10BIT,
        .wdr_mode = HI_MIPI_WDR_MODE_DOL,
        .lane_id = {0, 1, 2, 3}
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX385_12BIT_1080_NOWDR_ATTR =
{
	.devno = 0,
	.input_mode = INPUT_MODE_MIPI,
	{
		.mipi_attr =
		{
			RAW_DATA_12BIT,
			HI_MIPI_WDR_MODE_NONE,
			{0, 1, 2, 3}
		}
	}
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX385_10BIT_1080_2DOL1_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    .mipi_attr =
    {
        .raw_data_type = RAW_DATA_12BIT,
        .wdr_mode = HI_MIPI_WDR_MODE_DOL,
        .lane_id = {0, 1, 2, 3}
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX307_12BIT_1080_NOWDR_ATTR =
{
	.devno = 0,
	.input_mode = INPUT_MODE_MIPI,
	{
		.mipi_attr =
		{
			RAW_DATA_12BIT,
			HI_MIPI_WDR_MODE_NONE,
			{0, 1, 2, 3}
		}
	}
};

combo_dev_attr_t MIPI_4lane_SENSOR_IMX307_12BIT_1080_2DOL1_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    .mipi_attr =
    {
        .raw_data_type = RAW_DATA_12BIT,
        .wdr_mode = HI_MIPI_WDR_MODE_DOL,
        .lane_id = {0, 1, 2, 3}
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_JXF22_10BIT_1080_NOWDR_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,

    .mipi_attr =
    {
        .raw_data_type = RAW_DATA_10BIT,
        .wdr_mode = HI_MIPI_WDR_MODE_NONE,
        .lane_id = {0, 1, -1, -1}
    }
};

combo_dev_attr_t MIPI_CMOS_SENSOR_SC2235_12BIT_1080_NOWDR_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_CMOS,
    {

    }
};



combo_dev_attr_t MIPI_4lane_SENSOR_OV2718_12BIT_NOWDR_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    {
        .mipi_attr =
        {
            RAW_DATA_12BIT,
            HI_MIPI_WDR_MODE_NONE,
            {0, 1, 2, 3}
        }
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_OV2718_12BIT_2WDR1_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    {
        .mipi_attr =
        {
            RAW_DATA_12BIT,
            HI_MIPI_WDR_MODE_VC,
           {0, 1, 2, 3}
        }
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_OV2718_2A_12BIT_NOWDR_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    {
        .mipi_attr =
        {
            RAW_DATA_12BIT,
            HI_MIPI_WDR_MODE_NONE,
            {0, 1, 2, 3}
        }
    }
};

combo_dev_attr_t MIPI_4lane_SENSOR_OV2718_2A_16BIT_2WDR1_ATTR =
{
    .devno = 0,
    .input_mode = INPUT_MODE_MIPI,
    {
        .mipi_attr =
        {
            RAW_DATA_16BIT,
            HI_MIPI_WDR_MODE_VC,
           {0, 1, 2, 3}
        }
    }
};

combo_dev_attr_t MIPI_BT1120_ATTR =
{
    .devno         = 0,
    .input_mode    = INPUT_MODE_BT1120,

    {

    }
};

combo_dev_attr_t MIPI_CMOS323_ATTR =
{
    /* input mode */
    .input_mode = INPUT_MODE_CMOS,
    {

    }
};

VI_CHN_ATTR_S CHN_ATTR_1920x1080_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 1920,   1080},
    /* dest_w  dest_h */
    {1920,   1080 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_860x540_422 =
{
    /*crop_x crop_y crop_w  crop_h*/
    {0,     0, 860,   540},
    /* dest_w  dest_h */
    {860,   540 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};


VI_CHN_ATTR_S CHN_ATTR_1280x720_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 1280,   720 },
    /* dest_w  dest_h */
    {1280,   720 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_640x360_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 640,   360},
    /* dest_w  dest_h */
    {640,   360 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};


VI_CHN_ATTR_S CHN_ATTR_1280x720_420 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 1280,   720},
    /* dest_w  dest_h */
    {1280,   720 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};


VI_CHN_ATTR_S CHN_ATTR_720x576_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 720,   576 },
    /* dest_w  dest_h */
    {720,   576 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_720x576_420 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 720,   576},
    /* dest_w  dest_h */
    {720,   576},
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_360x288_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 360,   288 },
    /* dest_w  dest_h */
    {360,   288 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_360x288_420 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 360,   288},
    /* dest_w  dest_h */
    {360,   288},
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_420,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_16x16_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 16,   16 },
    /* dest_w  dest_h */
    {16,   16 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_960x576_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 960,   576 },
    /* dest_w  dest_h */
    {960,   576 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_CHN_ATTR_S CHN_ATTR_480x288_422 =
{
    /* crop_x crop_y crop_w  crop_h */
    {0,     0, 480,   288},
    /* dest_w  dest_h */
    {480,   288 },
    /*enCapSel*/
    VI_CAPSEL_BOTH,
    /* channel  pixel format */
    PIXEL_FORMAT_YUV_SEMIPLANAR_422,
    /*bMirr  bFlip   bChromaResample*/
    0,      0,      0,
    /*s32SrcFrameRate   s32DstFrameRate*/
    -1, -1
};

VI_DEV g_as32ViDev[VIU_MAX_DEV_NUM];
VI_CHN g_as32MaxChn[VIU_MAX_CHN_NUM];
VI_CHN g_as32SubChn[VIU_MAX_CHN_NUM];

HI_S32 SAMPLE_TW2865_CfgV(VIDEO_NORM_E enVideoMode, VI_WORK_MODE_E enWorkMode)
{
#if 0
    int fd, i;
    int video_mode;
    tw2865_video_norm stVideoMode;
    tw2865_work_mode work_mode;

    int chip_cnt = 4;

    fd = open(TW2865_FILE, O_RDWR);
    if (fd < 0)
    {
        SAMPLE_PRT("open 2865 (%s) fail\n", TW2865_FILE);
        return -1;
    }

    video_mode = (VIDEO_ENCODING_MODE_PAL == enVideoMode) ? TW2865_PAL : TW2865_NTSC ;

    for (i = 0; i < chip_cnt; i++)
    {
        stVideoMode.chip    = i;
        stVideoMode.mode    = video_mode;
        if (ioctl(fd, TW2865_SET_VIDEO_NORM, &stVideoMode))
        {
            SAMPLE_PRT("set tw2865(%d) video mode fail\n", i);
            close(fd);
            return -1;
        }
    }

    for (i = 0; i < chip_cnt; i++)
    {
        work_mode.chip = i;
        if (VI_WORK_MODE_4Multiplex == enWorkMode)
        {
            work_mode.mode = TW2865_4D1_MODE;
        }
        else if (VI_WORK_MODE_2Multiplex == enWorkMode)
        {
            work_mode.mode = TW2865_2D1_MODE;
        }
        else if (VI_WORK_MODE_1Multiplex == enWorkMode)
        {
            work_mode.mode = TW2865_1D1_MODE;
        }
        else
        {
            SAMPLE_PRT("work mode not support\n");
            return -1;
        }
        ioctl(fd, TW2865_SET_WORK_MODE, &work_mode);
    }

    close(fd);
#endif
    return 0;
}

HI_S32 SAMPLE_COMM_VI_Mode2Param(SAMPLE_VI_MODE_E enViMode, SAMPLE_VI_PARAM_S* pstViParam)
{
    switch (enViMode)
    {
        default:
            pstViParam->s32ViDevCnt      = 1;
            pstViParam->s32ViDevInterval = 1;
            pstViParam->s32ViChnCnt      = 1;
            pstViParam->s32ViChnInterval = 1;
            break;
    }
    return HI_SUCCESS;
}

/*****************************************************************************
* function : get vi parameter, according to vi type
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_ADStart(SAMPLE_VI_MODE_E enViMode, VIDEO_NORM_E enNorm)
{
    VI_WORK_MODE_E enWorkMode;
    HI_S32 s32Ret;

    switch (enViMode)
    {
        case SAMPLE_VI_MODE_1_D1:
            enWorkMode = VI_WORK_MODE_1Multiplex;
            s32Ret = SAMPLE_TW2865_CfgV(enNorm, enWorkMode);
            if (s32Ret != HI_SUCCESS)
            {
                SAMPLE_PRT("SAMPLE_TW2865_CfgV failed with %#x!\n", \
                           s32Ret);
                return HI_FAILURE;
            }
            break;

            /* use 7601 without drv */
        case SAMPLE_VI_MODE_BT1120_1080I:
        case SAMPLE_VI_MODE_BT1120_720P:
        case SAMPLE_VI_MODE_BT1120_1080P:
            break;

        default:
            SAMPLE_PRT("AD not support!\n");
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}



/*****************************************************************************
* function : get vi parameter, according to vi type
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_Mode2Size(SAMPLE_VI_MODE_E enViMode, VIDEO_NORM_E enNorm, SIZE_S* pstSize)
{
    switch (enViMode)
    {
        case SAMPLE_VI_MODE_1_D1:
            pstSize->u32Width = 720;
            pstSize->u32Height = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 576 : 480;
            break;

        case SAMPLE_VI_MODE_BT1120_1080I:
        case SAMPLE_VI_MODE_BT1120_1080P:
            pstSize->u32Width = 1920;
            pstSize->u32Height = 1080;
            break;

        case SAMPLE_VI_MODE_BT1120_720P:
            pstSize->u32Width = 1280;
            pstSize->u32Height = 720;
            break;

        default:
            SAMPLE_PRT("vi mode invaild!\n");
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : Get Vi Dev No. according to Vi_Chn No.
*****************************************************************************/
VI_DEV SAMPLE_COMM_VI_GetDev(SAMPLE_VI_MODE_E enViMode, VI_CHN ViChn)
{
    HI_S32 s32Ret, s32ChnPerDev;
    SAMPLE_VI_PARAM_S stViParam;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("vi get param failed!\n");
        return (VI_DEV) - 1;
    }

    s32ChnPerDev = stViParam.s32ViChnCnt / stViParam.s32ViDevCnt;
    return (VI_DEV)(ViChn / stViParam.s32ViChnInterval / s32ChnPerDev * stViParam.s32ViDevInterval);
}

/******************************************************************************
* function : Set vi system memory location
******************************************************************************/
HI_S32 SAMPLE_COMM_VI_MemConfig(SAMPLE_VI_MODE_E enViMode)
{
    HI_CHAR* pcMmzName;
    MPP_CHN_S stMppChnVI;
    SAMPLE_VI_PARAM_S stViParam;
    VI_DEV ViDev;
    VI_CHN ViChn;

    HI_S32 i, s32Ret;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("vi get param failed!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < stViParam.s32ViChnCnt; i++)
    {
        ViChn = i * stViParam.s32ViChnInterval;
        ViDev = SAMPLE_COMM_VI_GetDev(enViMode, ViChn);
        //printf("dev:%d, chn:%d\n", ViDev, ViChn);
        if (ViDev < 0)
        {
            SAMPLE_PRT("get vi dev failed !\n");
            return HI_FAILURE;
        }

        pcMmzName = (0 == i % 2) ? NULL : "ddr1";
        stMppChnVI.enModId = HI_ID_VIU;
        stMppChnVI.s32DevId = 0; //For VIU mode, this item must be set to zero
        stMppChnVI.s32ChnId = ViChn;
        s32Ret = HI_MPI_SYS_SetMemConf(&stMppChnVI, pcMmzName);
        if (s32Ret)
        {
            SAMPLE_PRT("VI HI_MPI_SYS_SetMemConf failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_SetMipiAttr(SAMPLE_VI_CONFIG_S* pstViConfig);

/*****************************************************************************
* function : init mipi
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_StartMIPI(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    int s32Ret;

    /* SAMPLE_COMM_VI_SetMipiAttr */
    s32Ret = SAMPLE_COMM_VI_SetMipiAttr(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("%s: mipi init failed!\n", __FUNCTION__);
        /* disable videv */
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : star vi dev (cfg vi_dev_attr; set_dev_cfg; enable dev)
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_StartDev(VI_DEV ViDev, SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 s32Ret;
    HI_S32 s32IspDev = 0;
    ISP_WDR_MODE_S stWdrMode;
    VI_DEV_ATTR_S  stViDevAttr;

    memset(&stViDevAttr, 0, sizeof(stViDevAttr));

    switch (enViMode)
    {
        case PANASONIC_MN34220_SUBLVDS_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 6;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case SONY_IMX290_MIPI_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case SONY_IMX385_MIPI_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case SONY_IMX307_MIPI_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;
            
        case JX_F22_MIPI_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;
            
        case SMARTSENS_SC2235_CMOS_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE_SC2235, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case OMNIVISION_OV2718_MIPI_1080P_30FPS:
		case OMNIVISION_OV2718_2A_MIPI_1080P_30FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case PANASONIC_MN34220_SUBLVDS_720P_120FPS:
            memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 6;
            stViDevAttr.stDevRect.u32Width  = 1280;
            stViDevAttr.stDevRect.u32Height = 720;
            break;

	 case SONY_IMX323_CMOS_1080P_30FPS:
	 	memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE_IMX323, sizeof(stViDevAttr));
            stViDevAttr.stDevRect.s32X = 200;
            stViDevAttr.stDevRect.s32Y = 20;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

	case APTINA_AR0237_LVDS_1080P_30FPS:
		memcpy(&stViDevAttr, &DEV_ATTR_MIPI_BASE, sizeof(stViDevAttr));
		stViDevAttr.stDevRect.s32X = 0;
            stViDevAttr.stDevRect.s32Y = 0;
            stViDevAttr.stDevRect.u32Width  = 1920;
            stViDevAttr.stDevRect.u32Height = 1080;
            break;

        case SAMPLE_VI_MODE_BT1120_1080P:
            memcpy(&stViDevAttr, &DEV_ATTR_BT1120_1080P_BASE, sizeof(stViDevAttr));
            break;

        default:
            memcpy(&stViDevAttr, &DEV_ATTR_LVDS_BASE, sizeof(stViDevAttr));
    }

    stWdrMode.enWDRMode = WDR_MODE_NONE;
    if ((SAMPLE_VI_MODE_BT1120_1080P != enViMode)
        && (SAMPLE_VI_MODE_BT1120_1080I != enViMode)
        && (SAMPLE_VI_MODE_BT1120_720P != enViMode))
    {
        s32Ret = HI_MPI_ISP_GetWDRMode(s32IspDev, &stWdrMode);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("HI_MPI_ISP_GetWDRMode failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }
    }

    if (SONY_IMX290_MIPI_1080P_30FPS == enViMode &&
        (WDR_MODE_2To1_LINE == stWdrMode.enWDRMode))
    {
        stViDevAttr.au32CompMask[0] = 0xFFC00000;
    }

	if (OMNIVISION_OV2718_2A_MIPI_1080P_30FPS == enViMode &&
        (WDR_MODE_2To1_LINE == stWdrMode.enWDRMode))
    {
        stViDevAttr.au32CompMask[0] = 0xFFFF0000;   // valid data is 16 bit
    }

    if (PANASONIC_MN34220_SUBLVDS_1080P_30FPS == enViMode &&
        (WDR_MODE_3To1_LINE == stWdrMode.enWDRMode || WDR_MODE_4To1_LINE == stWdrMode.enWDRMode))
    {
        stViDevAttr.au32CompMask[0] = 0x3FF00000;   // valid data is low 10 bit
    }

    s32Ret = HI_MPI_VI_SetDevAttr(ViDev, &stViDevAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("HI_MPI_VI_SetDevAttr failed with %#x!\n", s32Ret);
        return HI_FAILURE;
    }

    if ((SAMPLE_VI_MODE_BT1120_1080P != enViMode)
        && (SAMPLE_VI_MODE_BT1120_1080I != enViMode)
        && (SAMPLE_VI_MODE_BT1120_720P != enViMode))
    {
        VI_WDR_ATTR_S stWdrAttr;

        stWdrAttr.enWDRMode = stWdrMode.enWDRMode;
        stWdrAttr.bCompress = HI_FALSE;

        s32Ret = HI_MPI_VI_SetWDRAttr(ViDev, &stWdrAttr);
        if (s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_SetWDRAttr failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }
    }

    s32Ret = HI_MPI_VI_EnableDev(ViDev);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("HI_MPI_VI_EnableDev failed with %#x!\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : star vi chn
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_StartChn(VI_CHN ViChn, RECT_S* pstCapRect, SIZE_S* pstTarSize, SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 s32Ret;
    VI_CHN_ATTR_S stChnAttr;
    ROTATE_E enRotate = ROTATE_NONE;
    SAMPLE_VI_CHN_SET_E enViChnSet = VI_CHN_SET_NORMAL;

    if (pstViConfig)
    {
        enViChnSet = pstViConfig->enViChnSet;
        enRotate = pstViConfig->enRotate;
    }

    /* step  5: config & start vicap dev */
    memcpy(&stChnAttr.stCapRect, pstCapRect, sizeof(RECT_S));
    stChnAttr.enCapSel = VI_CAPSEL_BOTH;
    /* to show scale. this is a sample only, we want to show dist_size = D1 only */
    stChnAttr.stDestSize.u32Width = pstTarSize->u32Width;
    stChnAttr.stDestSize.u32Height = pstTarSize->u32Height;
    stChnAttr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;   /* sp420 or sp422 */

    stChnAttr.bMirror = HI_FALSE;
    stChnAttr.bFlip = HI_FALSE;

    switch (enViChnSet)
    {
        case VI_CHN_SET_MIRROR:
            stChnAttr.bMirror = HI_TRUE;
            break;

        case VI_CHN_SET_FLIP:
            stChnAttr.bFlip = HI_TRUE;
            break;

        case VI_CHN_SET_FLIP_MIRROR:
            stChnAttr.bMirror = HI_TRUE;
            stChnAttr.bFlip = HI_TRUE;
            break;

        default:
            break;
    }

    stChnAttr.s32SrcFrameRate = -1;
    stChnAttr.s32DstFrameRate = -1;
    stChnAttr.enCompressMode = COMPRESS_MODE_NONE;

    s32Ret = HI_MPI_VI_SetChnAttr(ViChn, &stChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        return HI_FAILURE;
    }

    // when VI-VPSS online, VI Rotate is not support, HI_MPI_VI_SetRotate will failed
    if (ROTATE_NONE != enRotate && !SAMPLE_COMM_IsViVpssOnline())
    {
        s32Ret = HI_MPI_VI_SetRotate(ViChn, enRotate);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("HI_MPI_VI_SetRotate failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }
    }

    s32Ret = HI_MPI_VI_EnableChn(ViChn);
    if (s32Ret != HI_SUCCESS)
    {
        SAMPLE_PRT("failed with %#x!\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : star vi according to product type
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_StartBT656(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 i, s32Ret = HI_SUCCESS;
    VI_DEV ViDev;
    VI_CHN ViChn;
    HI_U32 u32DevNum = 1;
    HI_U32 u32ChnNum = 1;
    SIZE_S stTargetSize;
    RECT_S stCapRect;
    SAMPLE_VI_MODE_E enViMode;

    if (!pstViConfig)
    {
        SAMPLE_PRT("%s: null ptr\n", __FUNCTION__);
        return HI_FAILURE;
    }
    enViMode = pstViConfig->enViMode;

    /******************************************
     step 1: mipi configure
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartMIPI_BT1120(enViMode);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("%s: MIPI init failed!\n", __FUNCTION__);
        return HI_FAILURE;
    }

    for (i = 0; i < u32DevNum; i++)
    {
        ViDev = i;
        s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, enViMode);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("%s: start vi dev[%d] failed!\n", __FUNCTION__, i);
            return HI_FAILURE;
        }
    }

    /******************************************************
    * Step 2: config & start vicap chn (max 1)
    ******************************************************/
    for (i = 0; i < u32ChnNum; i++)
    {
        ViChn = i;

        stCapRect.s32X = 0;
        stCapRect.s32Y = 0;
        switch (enViMode)
        {
            case SAMPLE_VI_MODE_BT1120_720P:
                stCapRect.u32Width = 1280;
                stCapRect.u32Height = 720;
                break;
            case SAMPLE_VI_MODE_BT1120_1080I:
            case SAMPLE_VI_MODE_BT1120_1080P:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;
            default:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;
        }

        stTargetSize.u32Width = stCapRect.u32Width;
        stTargetSize.u32Height = stCapRect.u32Height;

        s32Ret = SAMPLE_COMM_VI_StartChn(ViChn, &stCapRect, &stTargetSize, pstViConfig);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_COMM_ISP_Stop();
            return HI_FAILURE;
        }
    }

    return s32Ret;
}

/*****************************************************************************
* function : stop vi accroding to product type
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_StopBT656(SAMPLE_VI_MODE_E enViMode)
{
    VI_DEV ViDev;
    VI_CHN ViChn;
    HI_S32 i;
    HI_S32 s32Ret;
    SAMPLE_VI_PARAM_S stViParam;

    /*** get parameter from Sample_Vi_Mode ***/
    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VI_Mode2Param failed!\n");
        return HI_FAILURE;
    }

    /*** Stop VI Chn ***/
    for (i = 0; i < stViParam.s32ViChnCnt; i++)
    {
        /* Stop vi phy-chn */
        ViChn = i * stViParam.s32ViChnInterval;
        s32Ret = HI_MPI_VI_DisableChn(ViChn);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_VI_StopChn failed with %#x\n", s32Ret);
            return HI_FAILURE;
        }
    }

    /*** Stop VI Dev ***/
    for (i = 0; i < stViParam.s32ViDevCnt; i++)
    {
        ViDev = i * stViParam.s32ViDevInterval;
        s32Ret = HI_MPI_VI_DisableDev(ViDev);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("SAMPLE_COMM_VI_StopDev failed with %#x\n", s32Ret);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : Vi chn bind vpss group
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_BindVpss(SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 j, s32Ret;
    VPSS_GRP VpssGrp;
    MPP_CHN_S stSrcChn;
    MPP_CHN_S stDestChn;
    SAMPLE_VI_PARAM_S stViParam;
    VI_CHN ViChn;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VI_Mode2Param failed!\n");
        return HI_FAILURE;
    }

    VpssGrp = 0;
    for (j = 0; j < stViParam.s32ViChnCnt; j++)
    {
        ViChn = j * stViParam.s32ViChnInterval;

        stSrcChn.enModId  = HI_ID_VIU;
        stSrcChn.s32DevId = 0;
        stSrcChn.s32ChnId = ViChn;

        stDestChn.enModId  = HI_ID_VPSS;
        stDestChn.s32DevId = VpssGrp;
        stDestChn.s32ChnId = 0;

        s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }

        VpssGrp ++;
    }
    return HI_SUCCESS;
}

HI_BOOL IsSensorInput(SAMPLE_VI_MODE_E enViMode)
{
    HI_BOOL bRet = HI_TRUE;

    switch (enViMode)
    {
        case SAMPLE_VI_MODE_1_D1:
        case SAMPLE_VI_MODE_BT1120_1080I:
        case SAMPLE_VI_MODE_BT1120_1080P:
        case SAMPLE_VI_MODE_BT1120_720P:
            bRet = HI_FALSE;
            break;
        default:
            break;
    }

    return bRet;
}


HI_S32 SAMPLE_COMM_VI_BindVenc(SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 j, s32Ret;
    VENC_GRP  VencGrp;
    MPP_CHN_S stSrcChn;
    MPP_CHN_S stDestChn;
    SAMPLE_VI_PARAM_S stViParam;
    VI_CHN ViChn;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VI_Mode2Param failed!\n");
        return HI_FAILURE;
    }

    VencGrp = 0;
    for (j = 0; j < stViParam.s32ViChnCnt; j++)
    {
        ViChn = j * stViParam.s32ViChnInterval;

        stSrcChn.enModId = HI_ID_VIU;
        stSrcChn.s32DevId = 0;
        stSrcChn.s32ChnId = ViChn;

        stDestChn.enModId = HI_ID_GROUP;
        stDestChn.s32DevId = VencGrp;
        stDestChn.s32ChnId = 0;

        s32Ret = HI_MPI_SYS_Bind(&stSrcChn, &stDestChn);
        if (s32Ret != HI_SUCCESS)
        {
            SAMPLE_PRT("failed with %#x!\n", s32Ret);
            return HI_FAILURE;
        }

        VencGrp ++;
    }

    return HI_SUCCESS;
}

HI_BOOL SAMPLE_COMM_IsViVpssOnline(void)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32OnlineMode = 0;

    s32Ret = HI_MPI_SYS_GetViVpssMode(&u32OnlineMode);

    if (s32Ret != HI_SUCCESS)
    {
        printf("###################HI_MPI_SYS_GetViVpssMode err: 0x%x.\n", s32Ret);
        return HI_TRUE;
    }

    printf("============vi_vpss mode: %s\n", u32OnlineMode ? "online" : "offline");

    return u32OnlineMode;
}

HI_S32 SAMPLE_COMM_VI_StartMIPI_BT1120(SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 fd;
	combo_dev_attr_t *pstcomboDevAttr = NULL;

    fd = open("/dev/hi_mipi", O_RDWR);
    if (fd < 0)
    {
        printf("warning: open hi_mipi dev failed\n");
        return -1;
    }

    if ((enViMode == SAMPLE_VI_MODE_BT1120_1080I)
        || (enViMode == SAMPLE_VI_MODE_BT1120_720P)
        || (enViMode == SAMPLE_VI_MODE_BT1120_1080P))
    {
        pstcomboDevAttr = &MIPI_BT1120_ATTR;
    }
    else
    {
    }

    if (NULL == pstcomboDevAttr)
    {
        printf("Func %s() Line[%d], unsupported enViMode: %d\n", __FUNCTION__, __LINE__, enViMode);
        close(fd);
        return HI_FAILURE;
    }

	if (ioctl(fd, HI_MIPI_SET_DEV_ATTR, pstcomboDevAttr))
	{
		printf("set mipi attr failed\n");
		close(fd);
		return HI_FAILURE;
	}
	close(fd);
	return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_SetMipiAttr(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 fd;
    combo_dev_attr_t* pstcomboDevAttr = NULL;

    /* mipi reset unrest */
    fd = open("/dev/hi_mipi", O_RDWR);
    if (fd < 0)
    {
        printf("warning: open hi_mipi dev failed\n");
        return -1;
    }

    if ( pstViConfig->enViMode == PANASONIC_MN34220_SUBLVDS_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &SUBLVDS_4lane_SENSOR_MN34220_12BIT_1080_2WDR1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &SUBLVDS_4lane_SENSOR_MN34220_12BIT_1080_NOWDR_ATTR;
        }
    }
    else if (pstViConfig->enViMode == PANASONIC_MN34220_SUBLVDS_720P_120FPS)
    {
        pstcomboDevAttr = &SUBLVDS_4lane_SENSOR_MN34220_12BIT_720_NOWDR_ATTR;
    }
    else if (pstViConfig->enViMode == SONY_IMX290_MIPI_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX290_10BIT_1080_2DOL1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX290_12BIT_1080_NOWDR_ATTR;
        }
    }
    else if (pstViConfig->enViMode == SONY_IMX385_MIPI_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX385_10BIT_1080_2DOL1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX385_12BIT_1080_NOWDR_ATTR;
        }
    }
    else if (pstViConfig->enViMode == SONY_IMX307_MIPI_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX307_12BIT_1080_2DOL1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_IMX307_12BIT_1080_NOWDR_ATTR;
        }
    }
    else if(pstViConfig->enViMode == JX_F22_MIPI_1080P_30FPS)
    {
        pstcomboDevAttr = &MIPI_4lane_SENSOR_JXF22_10BIT_1080_NOWDR_ATTR;
    }
    else if(pstViConfig->enViMode == SMARTSENS_SC2235_CMOS_1080P_30FPS)
    {
        pstcomboDevAttr = &MIPI_CMOS_SENSOR_SC2235_12BIT_1080_NOWDR_ATTR;
    }
    else if (pstViConfig->enViMode == OMNIVISION_OV2718_MIPI_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_OV2718_12BIT_2WDR1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_OV2718_12BIT_NOWDR_ATTR;
        }
    }
	else if (pstViConfig->enViMode == OMNIVISION_OV2718_2A_MIPI_1080P_30FPS)
    {
        if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_OV2718_2A_16BIT_2WDR1_ATTR;
        }
        else
        {
            pstcomboDevAttr = &MIPI_4lane_SENSOR_OV2718_2A_12BIT_NOWDR_ATTR;
        }
    }
    else if (pstViConfig->enViMode == SONY_IMX323_CMOS_1080P_30FPS)
    {
    	  pstcomboDevAttr = &MIPI_CMOS323_ATTR;
    }
    else if(pstViConfig->enViMode == APTINA_AR0237_LVDS_1080P_30FPS)
    {
    	  if (pstViConfig->enWDRMode == WDR_MODE_2To1_LINE)
    	  {
    	       pstcomboDevAttr = &SUBLVDS_4lane_SENSOR_AR0237_12BIT_1080_2WDR1_ATTR;
    	  }
	  else
	  {
	      pstcomboDevAttr = &SUBLVDS_4lane_SENSOR_AR0237_12BIT_1080_NOWDR_ATTR;
	  }
    }
    printf("=============SAMPLE_COMM_VI_SetMipiAttr enWDRMode: %d\n", pstViConfig->enWDRMode);

    /* 1. reset mipi */
    ioctl(fd, HI_MIPI_RESET_MIPI, &pstcomboDevAttr->devno);

    /* 2. reset sensor */
    ioctl(fd, HI_MIPI_RESET_SENSOR, &pstcomboDevAttr->devno);

    /* 3. set mipi attr */
    if (ioctl(fd, HI_MIPI_SET_DEV_ATTR, pstcomboDevAttr))
    {
        printf("set mipi attr failed\n");
        close(fd);
        return HI_FAILURE;
    }

	usleep(10000);

    /* 4. unreset mipi */
    ioctl(fd, HI_MIPI_UNRESET_MIPI, &pstcomboDevAttr->devno);

    /* 5. unreset sensor */
    ioctl(fd, HI_MIPI_UNRESET_SENSOR, &pstcomboDevAttr->devno);

    close(fd);
    return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_StartIspAndVi(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 i, s32Ret = HI_SUCCESS;
    VI_DEV ViDev;
    VI_CHN ViChn;
    HI_U32 u32DevNum = 1;
    HI_U32 u32ChnNum = 1;
    SIZE_S stTargetSize;
    RECT_S stCapRect;
    SAMPLE_VI_MODE_E enViMode;

    if (!pstViConfig)
    {
        SAMPLE_PRT("%s: null ptr\n", __FUNCTION__);
        return HI_FAILURE;
    }
    enViMode = pstViConfig->enViMode;
    //printf("[%s]-%d: ", __FUNCTION__, __LINE__);

    /******************************************
     step 1: mipi configure
    ******************************************/
    s32Ret = SAMPLE_COMM_VI_StartMIPI(pstViConfig);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("%s: MIPI init failed!\n", __FUNCTION__);
        return HI_FAILURE;
    }


    /******************************************
     step 2: configure sensor and ISP (include WDR mode).
     note: you can jump over this step, if you do not use Hi3516CV300 interal isp.
    ******************************************/
    #ifdef hi3516ev100
    #ifdef __HuaweiLite__
    pstViConfig->enFrmRate = 30;
    #else
    pstViConfig->enFrmRate = 20;
    #endif
    #endif
    s32Ret = SAMPLE_COMM_ISP_Init(pstViConfig->enWDRMode, pstViConfig->enFrmRate);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("%s: Sensor init failed!\n", __FUNCTION__);
        return HI_FAILURE;
    }

    /******************************************
     step 3: run isp thread
     note: you can jump over this step, if you do not use Hi3516CV300 interal isp.
    ******************************************/
    s32Ret = SAMPLE_COMM_ISP_Run();
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("%s: ISP init failed!\n", __FUNCTION__);
        /* disable videv */
        return HI_FAILURE;
    }

    /******************************************************
     step 4 : config & start vicap dev
    ******************************************************/
    for (i = 0; i < u32DevNum; i++)
    {
        ViDev = i;
        s32Ret = SAMPLE_COMM_VI_StartDev(ViDev, enViMode);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("%s: start vi dev[%d] failed!\n", __FUNCTION__, i);
            return HI_FAILURE;
        }
    }

    /******************************************************
    * Step 5: config & start vicap chn (max 1)
    ******************************************************/
    for (i = 0; i < u32ChnNum; i++)
    {
        ViChn = i;

        stCapRect.s32X = 0;
        stCapRect.s32Y = 0;
        switch (enViMode)
        {
            case PANASONIC_MN34220_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

            case SONY_IMX290_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;
                
            case SONY_IMX385_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

            case SONY_IMX307_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

            case JX_F22_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;
            case SMARTSENS_SC2235_CMOS_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

            case OMNIVISION_OV2718_MIPI_1080P_30FPS:
			case OMNIVISION_OV2718_2A_MIPI_1080P_30FPS:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

	     case SONY_IMX323_CMOS_1080P_30FPS:
		   stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

	    case APTINA_AR0237_LVDS_1080P_30FPS:
		   stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;

            default:
                stCapRect.u32Width  = 1920;
                stCapRect.u32Height = 1080;
                break;
        }

        stTargetSize.u32Width = stCapRect.u32Width;
        stTargetSize.u32Height = stCapRect.u32Height;

        s32Ret = SAMPLE_COMM_VI_StartChn(ViChn, &stCapRect, &stTargetSize, pstViConfig);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_COMM_ISP_Stop();
            return HI_FAILURE;
        }
    }

    return s32Ret;
}

HI_S32 SAMPLE_COMM_VI_StopIsp(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    VI_DEV ViDev;
    VI_CHN ViChn;
    HI_S32 i;
    HI_S32 s32Ret;
    HI_U32 u32DevNum = 1;
    HI_U32 u32ChnNum = 1;

    if (!pstViConfig)
    {
        SAMPLE_PRT("%s: null ptr\n", __FUNCTION__);
        return HI_FAILURE;
    }

    /*** Stop VI Chn ***/
    for (i = 0; i < u32ChnNum; i++)
    {
        /* Stop vi phy-chn */
        ViChn = i;
        s32Ret = HI_MPI_VI_DisableChn(ViChn);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_DisableChn failed with %#x\n", s32Ret);
            return HI_FAILURE;
        }
    }

    /*** Stop VI Dev ***/
    for (i = 0; i < u32DevNum; i++)
    {
        ViDev = i;
        s32Ret = HI_MPI_VI_DisableDev(ViDev);
        if (HI_SUCCESS != s32Ret)
        {
            SAMPLE_PRT("HI_MPI_VI_DisableDev failed with %#x\n", s32Ret);
            return HI_FAILURE;
        }
    }

    SAMPLE_COMM_ISP_Stop();
    return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_StartVi(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_VI_MODE_E enViMode;

    if (!pstViConfig)
    {
        SAMPLE_PRT("%s: null ptr\n", __FUNCTION__);
        return HI_FAILURE;
    }

    enViMode = pstViConfig->enViMode;
    if (!IsSensorInput(enViMode))
    {
        s32Ret = SAMPLE_COMM_VI_StartBT656(pstViConfig);
    }
    else
    {
        s32Ret = SAMPLE_COMM_VI_StartIspAndVi(pstViConfig);
    }


    return s32Ret;
}

HI_S32 SAMPLE_COMM_VI_StopVi(SAMPLE_VI_CONFIG_S* pstViConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_VI_MODE_E enViMode;

    if (!pstViConfig)
    {
        SAMPLE_PRT("%s: null ptr\n", __FUNCTION__);
        return HI_FAILURE;
    }
    enViMode = pstViConfig->enViMode;

    if (!IsSensorInput(enViMode))
    {
        s32Ret = SAMPLE_COMM_VI_StopBT656(enViMode);
    }
    else
    {
        s32Ret = SAMPLE_COMM_VI_StopIsp(pstViConfig);
    }

    return s32Ret;
}

HI_S32 SAMPLE_COMM_VI_SwitchResParam( SAMPLE_VI_CONFIG_S* pstViConfig,
                                        ISP_PUB_ATTR_S* pstPubAttr,
                                        RECT_S* pstCapRect )
{
    CHECK_NULL_PTR(pstViConfig);
    CHECK_NULL_PTR(pstPubAttr);
    CHECK_NULL_PTR(pstCapRect);
    if (PANASONIC_MN34220_SUBLVDS_1080P_30FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = PANASONIC_MN34220_SUBLVDS_720P_120FPS;
        pstPubAttr->stWndRect.u32Width = 1280;
        pstPubAttr->stWndRect.u32Height = 720;
        pstPubAttr->f32FrameRate = 120;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1280;
        pstCapRect->u32Height = 720;
    }

    else if (PANASONIC_MN34220_SUBLVDS_720P_120FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = PANASONIC_MN34220_SUBLVDS_1080P_30FPS;
        pstPubAttr->stWndRect.u32Width = 1920;
        pstPubAttr->stWndRect.u32Height = 1080;
        pstPubAttr->f32FrameRate = 30;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1920;
        pstCapRect->u32Height = 1080;
    }
    else if (PANASONIC_MN34220_MIPI_1080P_30FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = PANASONIC_MN34220_MIPI_720P_120FPS;
        pstPubAttr->stWndRect.u32Width = 1280;
        pstPubAttr->stWndRect.u32Height = 720;
        pstPubAttr->f32FrameRate = 120;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1280;
        pstCapRect->u32Height = 720;
    }
    else if (PANASONIC_MN34220_MIPI_720P_120FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = PANASONIC_MN34220_MIPI_1080P_30FPS;
        pstPubAttr->stWndRect.u32Width = 1920;
        pstPubAttr->stWndRect.u32Height = 1080;
        pstPubAttr->f32FrameRate = 30;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1920;
        pstCapRect->u32Height = 1080;
    }
    else if (OMNIVISION_OV4689_MIPI_4M_30FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = OMNIVISION_OV4689_MIPI_1080P_30FPS;
        pstPubAttr->stWndRect.u32Width = 1920;
        pstPubAttr->stWndRect.u32Height = 1080;
        pstPubAttr->f32FrameRate = 30;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1920;
        pstCapRect->u32Height = 1080;
    }
    else if (OMNIVISION_OV4689_MIPI_1080P_30FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = OMNIVISION_OV4689_MIPI_4M_30FPS;
        pstPubAttr->stWndRect.u32Width = 2592;
        pstPubAttr->stWndRect.u32Height = 1520;
        pstPubAttr->f32FrameRate = 30;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 2592;
        pstCapRect->u32Height = 1520;
    }
    else if (SONY_IMX117_LVDS_1080P_120FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = SONY_IMX117_LVDS_720P_240FPS;
        pstPubAttr->stWndRect.u32Width = 1280;
        pstPubAttr->stWndRect.u32Height = 720;
        pstPubAttr->f32FrameRate = 120;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1280;
        pstCapRect->u32Height = 720;
    }
    else if (SONY_IMX117_LVDS_720P_240FPS == pstViConfig->enViMode)
    {
        pstViConfig->enViMode = SONY_IMX117_LVDS_1080P_120FPS;
        pstPubAttr->stWndRect.u32Width = 1920;
        pstPubAttr->stWndRect.u32Height = 1080;
        pstPubAttr->f32FrameRate = 60;

        pstCapRect->s32X = 0;
        pstCapRect->s32Y = 0;
        pstCapRect->u32Width = 1920;
        pstCapRect->u32Height = 1080;

    }
    else
    {
        SAMPLE_PRT("This sensor type is not surpport!");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* function : Vi chn unbind vpss group
*****************************************************************************/
HI_S32 SAMPLE_COMM_VI_UnBindVpss(SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 i, j, s32Ret;
    VPSS_GRP VpssGrp;
    MPP_CHN_S stSrcChn;
    MPP_CHN_S stDestChn;
    SAMPLE_VI_PARAM_S stViParam;
    VI_DEV ViDev;
    VI_CHN ViChn;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VI_Mode2Param failed!\n");
        return HI_FAILURE;
    }

    VpssGrp = 0;
    for (i = 0; i < stViParam.s32ViDevCnt; i++)
    {
        ViDev = i * stViParam.s32ViDevInterval;

        for (j = 0; j < stViParam.s32ViChnCnt; j++)
        {
            ViChn = j * stViParam.s32ViChnInterval;

            stSrcChn.enModId = HI_ID_VIU;
            stSrcChn.s32DevId = ViDev;
            stSrcChn.s32ChnId = ViChn;

            stDestChn.enModId = HI_ID_VPSS;
            stDestChn.s32DevId = VpssGrp;
            stDestChn.s32ChnId = 0;

            s32Ret = HI_MPI_SYS_UnBind(&stSrcChn, &stDestChn);
            if (s32Ret != HI_SUCCESS)
            {
                SAMPLE_PRT("failed with %#x!\n", s32Ret);
                return HI_FAILURE;
            }

            VpssGrp ++;
        }
    }
    return HI_SUCCESS;
}


HI_S32 SAMPLE_COMM_VI_UnBindVenc(SAMPLE_VI_MODE_E enViMode)
{
    HI_S32 i, j, s32Ret;
    VENC_GRP  VencGrp;
    MPP_CHN_S stSrcChn;
    MPP_CHN_S stDestChn;
    SAMPLE_VI_PARAM_S stViParam;
    VI_DEV ViDev;
    VI_CHN ViChn;

    s32Ret = SAMPLE_COMM_VI_Mode2Param(enViMode, &stViParam);
    if (HI_SUCCESS != s32Ret)
    {
        SAMPLE_PRT("SAMPLE_COMM_VI_Mode2Param failed!\n");
        return HI_FAILURE;
    }

    VencGrp = 0;
    for (i = 0; i < stViParam.s32ViDevCnt; i++)
    {
        ViDev = i * stViParam.s32ViDevInterval;

        for (j = 0; j < stViParam.s32ViChnCnt; j++)
        {
            ViChn = j * stViParam.s32ViChnInterval;

            stSrcChn.enModId = HI_ID_VIU;
            stSrcChn.s32DevId = ViDev;
            stSrcChn.s32ChnId = ViChn;

            stDestChn.enModId = HI_ID_GROUP;
            stDestChn.s32DevId = VencGrp;
            stDestChn.s32ChnId = 0;

            s32Ret = HI_MPI_SYS_UnBind(&stSrcChn, &stDestChn);
            if (s32Ret != HI_SUCCESS)
            {
                SAMPLE_PRT("failed with %#x!\n", s32Ret);
                return HI_FAILURE;
            }

            VencGrp ++;
        }
    }

    return HI_SUCCESS;
}


/******************************************************************************
* function : read frame
******************************************************************************/
HI_VOID SAMPLE_COMM_VI_ReadFrame(FILE* fp, HI_U8* pY, HI_U8* pU, HI_U8* pV, HI_U32 width, HI_U32 height, HI_U32 stride, HI_U32 stride2)
{
    HI_U8* pDst;

    HI_U32 u32Row;

    pDst = pY;
    for ( u32Row = 0; u32Row < height; u32Row++ )
    {
		if (fread( pDst, width, 1, fp ) != 1)
        {
            fprintf(stderr, "fread failed\n");
        	return;
        }
        pDst += stride;
    }

    pDst = pU;
    for ( u32Row = 0; u32Row < height / 2; u32Row++ )
    {
        if (fread( pDst, width / 2, 1, fp ) != 1)
        {
            fprintf(stderr, "fread failed\n");
        	return;
        }
        pDst += stride2;
    }

    pDst = pV;
    for ( u32Row = 0; u32Row < height / 2; u32Row++ )
    {
        if (fread( pDst, width / 2, 1, fp ) != 1)
        {
            fprintf(stderr, "fread failed\n");
        	return;
        }
        pDst += stride2;
    }
}

/******************************************************************************
* function : Plan to Semi
******************************************************************************/
HI_S32 SAMPLE_COMM_VI_PlanToSemi(HI_U8* pY, HI_S32 yStride,
                                 HI_U8* pU, HI_S32 uStride,
                                 HI_U8* pV, HI_S32 vStride,
                                 HI_S32 picWidth, HI_S32 picHeight)
{
    HI_S32 i;
    HI_U8* pTmpU, *ptu;
    HI_U8* pTmpV, *ptv;
    HI_S32 s32HafW = uStride >> 1 ;
    HI_S32 s32HafH = picHeight >> 1 ;
    HI_S32 s32Size = s32HafW * s32HafH;

    pTmpU = malloc( s32Size );
    ptu = pTmpU;
    if (NULL == ptu)
    {
        fprintf(stderr, "alloc memory failed\n");
        return HI_FAILURE;
    }
    pTmpV = malloc( s32Size );
    ptv = pTmpV;
    if (NULL == ptv)
    {
        fprintf(stderr, "alloc memory failed\n");
		free(pTmpU);
        return HI_FAILURE;
    }

    memcpy(pTmpU, pU, s32Size);
    memcpy(pTmpV, pV, s32Size);

    for (i = 0; i<s32Size >> 1; i++)
    {
        *pU++ = *pTmpV++;
        *pU++ = *pTmpU++;

    }
    for (i = 0; i<s32Size >> 1; i++)
    {
        *pV++ = *pTmpV++;
        *pV++ = *pTmpU++;
    }

    free( ptu );
    free( ptv );

    return HI_SUCCESS;
}

int SAMPLE_COMM_VI_ExitMpp( int s32poolId)
{
    if (s32poolId < 0)
    {
        if (HI_MPI_SYS_Exit())
        {
            printf("sys exit fail\n");
            return -1;
        }

        if (HI_MPI_VB_Exit())
        {
            printf("vb exit fail\n");
            return -1;
        }
        return -1;
    }

    return 0;
}


/******************************************************************************
* function : Get from YUV
******************************************************************************/
HI_S32 SAMPLE_COMM_VI_GetVFrameFromYUV(FILE* pYUVFile, HI_U32 u32Width, HI_U32 u32Height, HI_U32 u32Stride, VIDEO_FRAME_INFO_S* pstVFrameInfo)
{
    HI_U32             u32LStride;
    HI_U32             u32CStride;
    HI_U32             u32LumaSize;
    HI_U32             u32ChrmSize;
    HI_U32             u32Size;
    VB_BLK VbBlk;
    HI_U32 u32PhyAddr;
    HI_U8* pVirAddr;

    u32LStride  = u32Stride;
    u32CStride  = u32Stride;

    u32LumaSize = (u32LStride * u32Height);
    u32ChrmSize = (u32CStride * u32Height) >> 2;/* YUV 420 */
    u32Size = u32LumaSize + (u32ChrmSize << 1);

    /* alloc video buffer block ---------------------------------------------------------- */
    VbBlk = HI_MPI_VB_GetBlock(VB_INVALID_POOLID, u32Size, NULL);
    if (VB_INVALID_HANDLE == VbBlk)
    {
        SAMPLE_PRT("HI_MPI_VB_GetBlock err! size:%d\n", u32Size);
        return -1;
    }
    u32PhyAddr = HI_MPI_VB_Handle2PhysAddr(VbBlk);
    if (0 == u32PhyAddr)
    {
        return -1;
    }

    pVirAddr = (HI_U8*) HI_MPI_SYS_Mmap(u32PhyAddr, u32Size);
    if (NULL == pVirAddr)
    {
        return -1;
    }

    pstVFrameInfo->u32PoolId = HI_MPI_VB_Handle2PoolId(VbBlk);
    if (VB_INVALID_POOLID == pstVFrameInfo->u32PoolId)
    {
        return -1;
    }
    SAMPLE_PRT("pool id :%d, phyAddr:%x,virAddr:%x\n" , pstVFrameInfo->u32PoolId, u32PhyAddr, (int)pVirAddr);

    pstVFrameInfo->stVFrame.u32PhyAddr[0] = u32PhyAddr;
    pstVFrameInfo->stVFrame.u32PhyAddr[1] = pstVFrameInfo->stVFrame.u32PhyAddr[0] + u32LumaSize;
    pstVFrameInfo->stVFrame.u32PhyAddr[2] = pstVFrameInfo->stVFrame.u32PhyAddr[1] + u32ChrmSize;

    pstVFrameInfo->stVFrame.pVirAddr[0] = pVirAddr;
    pstVFrameInfo->stVFrame.pVirAddr[1] = (void *)((unsigned long)pstVFrameInfo->stVFrame.pVirAddr[0] + u32LumaSize);
    pstVFrameInfo->stVFrame.pVirAddr[2] = (void *)((unsigned long)pstVFrameInfo->stVFrame.pVirAddr[1] + u32ChrmSize);

    pstVFrameInfo->stVFrame.u32Width  = u32Width;
    pstVFrameInfo->stVFrame.u32Height = u32Height;
    pstVFrameInfo->stVFrame.u32Stride[0] = u32LStride;
    pstVFrameInfo->stVFrame.u32Stride[1] = u32CStride;
    pstVFrameInfo->stVFrame.u32Stride[2] = u32CStride;
    pstVFrameInfo->stVFrame.enPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
    pstVFrameInfo->stVFrame.u32Field = VIDEO_FIELD_INTERLACED;/* Intelaced D1,otherwise VIDEO_FIELD_FRAME */

    /* read Y U V data from file to the addr ----------------------------------------------*/
    SAMPLE_COMM_VI_ReadFrame(pYUVFile, pstVFrameInfo->stVFrame.pVirAddr[0],
                             pstVFrameInfo->stVFrame.pVirAddr[1], pstVFrameInfo->stVFrame.pVirAddr[2],
                             pstVFrameInfo->stVFrame.u32Width, pstVFrameInfo->stVFrame.u32Height,
                             pstVFrameInfo->stVFrame.u32Stride[0], pstVFrameInfo->stVFrame.u32Stride[1] >> 1 );

    /* convert planar YUV420 to sem-planar YUV420 -----------------------------------------*/
    SAMPLE_COMM_VI_PlanToSemi(pstVFrameInfo->stVFrame.pVirAddr[0], pstVFrameInfo->stVFrame.u32Stride[0],
                              pstVFrameInfo->stVFrame.pVirAddr[1], pstVFrameInfo->stVFrame.u32Stride[1],
                              pstVFrameInfo->stVFrame.pVirAddr[2], pstVFrameInfo->stVFrame.u32Stride[1],
                              pstVFrameInfo->stVFrame.u32Width, pstVFrameInfo->stVFrame.u32Height);

    HI_MPI_SYS_Mmap(u32PhyAddr, u32Size);
    return 0;
}

HI_S32 SAMPLE_COMM_VI_ChangeCapSize(VI_CHN ViChn, HI_U32 u32CapWidth, HI_U32 u32CapHeight, HI_U32 u32Width, HI_U32 u32Height)
{
    VI_CHN_ATTR_S stChnAttr;
    HI_S32 S32Ret = HI_SUCCESS;
    S32Ret = HI_MPI_VI_GetChnAttr(ViChn, &stChnAttr);
    if (HI_SUCCESS != S32Ret)
    {
        SAMPLE_PRT( "HI_MPI_VI_GetChnAttr failed\n");
    }
    stChnAttr.stCapRect.u32Width = u32CapWidth;
    stChnAttr.stCapRect.u32Height = u32CapHeight;
    stChnAttr.stDestSize.u32Width = u32Width;
    stChnAttr.stDestSize.u32Height = u32Height;

    S32Ret = HI_MPI_VI_SetChnAttr(ViChn, &stChnAttr);
    if (HI_SUCCESS != S32Ret)
    {
        SAMPLE_PRT( "HI_MPI_VI_SetChnAttr failed\n");
    }

    return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_FPN_GetVBFromPool(HI_U32 u32VbSize, HI_U32 u32Width, HI_U32 u32Height, HI_U32 u32Stride, SAMPLE_VI_FRAME_INFO_S* pstVMstFrameInfo)
{
    VB_BLK VbBlk;
    HI_U32 u32PhyAddr;
    VIDEO_FRAME_INFO_S* pstVFrameInfo = &pstVMstFrameInfo->stVideoFrame;

    printf("===============FPN VB Size: %d\n", u32VbSize);
    /* alloc video buffer block ---------------------------------------------------------- */
    VbBlk = HI_MPI_VB_GetBlock(VB_INVALID_POOLID, u32VbSize, HI_NULL);
    if (VB_INVALID_HANDLE == VbBlk)
    {
        printf("HI_MPI_VB_GetBlock err! size:%d\n", u32VbSize);
        return HI_FAILURE;
    }
    pstVMstFrameInfo->u32FrmSize = u32VbSize;
    pstVMstFrameInfo->VbBlk = VbBlk;

    printf("VbBlk: 0x%x\n", VbBlk);

    u32PhyAddr = HI_MPI_VB_Handle2PhysAddr(VbBlk);
    if (0 == u32PhyAddr)
    {
        printf("HI_MPI_VB_Handle2PhysAddr err!\n");
        return HI_FAILURE;
    }

    pstVFrameInfo->u32PoolId = HI_MPI_VB_Handle2PoolId(VbBlk);
    if (VB_INVALID_POOLID == pstVFrameInfo->u32PoolId)
    {
        SAMPLE_COMM_VI_ExitMpp(pstVFrameInfo->u32PoolId);
        return -1;
    }

    pstVFrameInfo->stVFrame.u32PhyAddr[0] = u32PhyAddr;
    pstVFrameInfo->stVFrame.u32PhyAddr[1] = 0;
    pstVFrameInfo->stVFrame.u32PhyAddr[2] = 0;

    pstVFrameInfo->stVFrame.pVirAddr[0] = NULL;
    pstVFrameInfo->stVFrame.pVirAddr[1] = NULL;
    pstVFrameInfo->stVFrame.pVirAddr[2] = NULL;

    pstVFrameInfo->stVFrame.u32Width  = u32Width;
    pstVFrameInfo->stVFrame.u32Height = u32Height;
    pstVFrameInfo->stVFrame.u32Stride[0] = u32Stride;
    pstVFrameInfo->stVFrame.u32Stride[1] = 0;
    pstVFrameInfo->stVFrame.u32Stride[2] = 0;

    return HI_SUCCESS;
}



void SAMPLE_COMM_VI_SaveFpnData(ISP_FPN_FRAME_INFO_S* pVBuf, HI_U32 u32FpnMode, HI_U32 u32Nbit, FILE* pfd)
{
    HI_U8* pU8VBufVirt_Y;
    HI_U32 phy_addr, u32Size;
    HI_U8* pUserPageAddr[2];
    HI_BOOL bCompress;

    u32Size = pVBuf->u32FrmSize;
    printf("FPN data size: %d\n", u32Size);

    phy_addr =  pVBuf->stFpnFrame.stVFrame.u32PhyAddr[0];
    pUserPageAddr[0] = (HI_U8*) HI_MPI_SYS_Mmap(phy_addr, u32Size);
    if (NULL == pUserPageAddr[0])
    {
        printf("HI_MPI_SYS_Mmap null\n");
        return;
    }

    pU8VBufVirt_Y = (HI_U8*)pUserPageAddr[0];

    /* save Y ----------------------------------------------------------------*/
    fprintf(stderr, "saving......Raw data......u32Stride[0]: %d, width: %d, height: %d\n"
            , pVBuf->stFpnFrame.stVFrame.u32Stride[0]
            , pVBuf->stFpnFrame.stVFrame.u32Width
            , pVBuf->stFpnFrame.stVFrame.u32Height);
    //fprintf(stderr, "phy Addr: 0x%x\n", pVBuf->stFpnFrame.stVFrame.u32PhyAddr[0]);
    fflush(stderr);

    fwrite(pU8VBufVirt_Y, pVBuf->u32FrmSize, 1, pfd);

    /* save offset */
    fwrite(&pVBuf->u32Offset, 4, 1, pfd);

    /* save compress flag */
    bCompress = (COMPRESS_MODE_LINE == pVBuf->stFpnFrame.stVFrame.enCompressMode);
    fwrite(&bCompress, 4, 1, pfd);

    /* save fpn frame size */
    fwrite(&pVBuf->u32FrmSize, 4, 1, pfd);

    /* save ISO */
    fwrite(&pVBuf->u32Iso, 4, 1, pfd);
    fflush(pfd);

    //fprintf(stderr, "done u32TimeRef: %d!\n", pVBuf->stFpnFrame.stVFrame.u32TimeRef);
    fflush(stderr);

    HI_MPI_SYS_Munmap(pUserPageAddr[0], u32Size);
}


HI_S32 SAMPLE_COMM_VI_ReleaseVBToPool(SAMPLE_VI_FRAME_INFO_S* pstVMstFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_VB_ReleaseBlock(pstVMstFrameInfo->VbBlk);
    return s32Ret;
}

HI_S32 SAMPLE_COMM_VI_FPN_CALIBRATE_CONFIG(const char* fpn_file,    /* fpn file name */
        ISP_FPN_TYPE_E enFpnType, /* line/frame */
        PIXEL_FORMAT_E enPixelFormat,
        COMPRESS_MODE_E	enCompressMode,
        HI_U32 u32FrmNum,
        HI_U32 u32Threshold)
{
    VI_CHN ViChn = 0;
    VI_CHN_ATTR_S stTempChnAttr;
    ISP_FPN_CALIBRATE_ATTR_S stFpnCalAttr;
    HI_U32 u32Stride, u32VbSize;
    SAMPLE_VI_FRAME_INFO_S stVMstFrame = {0};
    HI_U32 u32Width, u32Height;
    HI_S32 s32Ret = HI_SUCCESS;

    ISP_DEV IspDev = 0;
    FILE* pFile;
    char fileName[FILE_NAME_LEN];

    s32Ret =  HI_MPI_VI_GetChnAttr(ViChn, &stTempChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("get vi chn attr failed!");
        return s32Ret;
    }
    u32Width = stTempChnAttr.stCapRect.u32Width;
    u32Height = stTempChnAttr.stCapRect.u32Height;

    /* alloc 16bit/pixel memory */
    u32Stride = ALIGN_BACK(stTempChnAttr.stCapRect.u32Width * 2, 16);
    printf("u32Stride: %d\n", u32Stride);
    stVMstFrame.stVideoFrame.stVFrame.enPixelFormat = enPixelFormat;
    stVMstFrame.stVideoFrame.stVFrame.enCompressMode = enCompressMode;
    stVMstFrame.stVideoFrame.stVFrame.u32Field = VIDEO_FIELD_FRAME;

    if (ISP_FPN_TYPE_LINE == enFpnType)
    {
        u32VbSize = u32Stride * 1;
    }
    else
    {
        u32VbSize = (u32Stride) * u32Height;
    }
    s32Ret = SAMPLE_COMM_VI_FPN_GetVBFromPool(u32VbSize, u32Width, u32Height, u32Stride, &stVMstFrame);
    if (HI_SUCCESS != s32Ret)
    {
        printf("alloc mem failed!");
        return s32Ret;
    }

    printf("==========let isp fly ====================\n");
    printf("\n please turn off camera aperture to start calibrate!\n");
    VI_PAUSE();

    s32Ret =  HI_MPI_VI_DisableChn(ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        printf("disable vi chn failed!");
        return s32Ret;
    }

    stFpnCalAttr.u32FrameNum  = u32FrmNum;
    stFpnCalAttr.u32Threshold = u32Threshold;
    stFpnCalAttr.enFpnType    = enFpnType;
    memcpy(&stFpnCalAttr.stFpnCaliFrame.stFpnFrame, &stVMstFrame.stVideoFrame, sizeof(VIDEO_FRAME_INFO_S));
    stFpnCalAttr.stFpnCaliFrame.u32Offset = 0;

    printf("compress mode: %d\n", stFpnCalAttr.stFpnCaliFrame.stFpnFrame.stVFrame.enCompressMode);
    s32Ret = HI_MPI_ISP_FPNCalibrate(IspDev, &stFpnCalAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("HI_MPI_ISP_FPNCalibrate err: 0x%x\n", s32Ret);
        return s32Ret;
    }
    //printf("out stVMstFrame.stVideoFrame.stVFrame.u32Stride[0]: %d\n", stVMstFrame.stVideoFrame.stVFrame.u32Stride[0]);
    /* save RAW data */
    snprintf(fileName, FILE_NAME_LEN, "./%s_%d_%d_%dbit.raw", fpn_file, u32Width, u32Height, 16);
    printf("\nafter calibrate, offset =0x%x,ISO = %d\n", stFpnCalAttr.stFpnCaliFrame.u32Offset,
           stFpnCalAttr.stFpnCaliFrame.u32Iso);

    s32Ret =  HI_MPI_VI_EnableChn(ViChn);
    if (HI_SUCCESS != s32Ret)
    {
        printf("enable vi chn failed!");
        return s32Ret;
    }

    printf("\nhit the Enter key,save dark frame file: %s!\n", fileName);
    getchar();

    pFile = fopen(fileName, "wb");
    if (NULL == pFile)
    {
        printf("open file %s err!\n", fileName);
        return HI_FAILURE;
    }
    else
    {
        HI_U32 u32FpnBitWidth = 10;

        SAMPLE_COMM_VI_SaveFpnData(&stFpnCalAttr.stFpnCaliFrame, enFpnType, u32FpnBitWidth, pFile);
        fclose(pFile);
    }
    printf("\nsaved dark frame! \n");

    s32Ret = SAMPLE_COMM_VI_ReleaseVBToPool(&stVMstFrame);
    if (HI_SUCCESS != s32Ret)
    {
        printf("SAMPLE_COMM_VI_ReleaseVBToPool err: 0x%x\n", s32Ret);
    }

    return HI_SUCCESS;
}

HI_S32 SAMPLE_COMM_VI_ReadOneFpnFrame(FILE* fp, HI_U8* pY, HI_U32* pu32Offset,
                        HI_U32* pu32FrmSize, COMPRESS_MODE_E* penCompressMode, HI_U32* pu32Iso)
{
    HI_U8* pDst;
    HI_U32 u32FrmSize;
    HI_BOOL bCompress;
    HI_S32 s32Ret;

    /*****************************************************************
    raw file storage layout:
    ///////////////////////////////////////////////////
    |-------------------------------------------------|
    |-------------------------------------------------|
    |-------------------------------------------------|
    |-------------------------------------------------|
    |-------------------------------------------------|
    |-------------------------------------------------|
    |-------------------|------|------|------|--------|
                        offset  comp   size    u32iso
    ****************************************************************/

    /* seek end of file */
    s32Ret = fseek(fp, -4, SEEK_END);
    if (0 != s32Ret)
    {
        printf("Func: %s(), line: [%d], get iso failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    /* get calibrate ISO */
    if (fread(pu32Iso, 4, 1, fp) != 1)
	{
        printf("Func: %s(), line: [%d], get iso failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }

    /* get fpn frame size */
    s32Ret = fseek(fp, -8, SEEK_END);
    if (0 != s32Ret)
    {
        printf("Func: %s(), line: [%d], get frame size failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }

    if (fread(&u32FrmSize, 4, 1, fp) != 1)
    {
        printf("Func: %s(), line: [%d], get frame size failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    *pu32FrmSize = u32FrmSize;

    /* get fpn frame compress flag */
    s32Ret = fseek(fp, -12, SEEK_END);
    if (0 != s32Ret)
    {
        printf("Func: %s(), line: [%d], get compress flag failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    if (fread(&bCompress, 4, 1, fp) != 1)
	{
        printf("Func: %s(), line: [%d], get compress flag failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }

    if (bCompress)
    {
        *penCompressMode = COMPRESS_MODE_LINE;
    }
    else
    {
        *penCompressMode = COMPRESS_MODE_NONE;
    }

    /* get fpn offset */
    s32Ret = fseek(fp, -16, SEEK_END);
    if (0 != s32Ret)
    {
        printf("Func: %s(), line: [%d], get fpn offset failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    if (fread(pu32Offset, 4, 1, fp) != 1)
    {
        printf("Func: %s(), line: [%d], get fpn offset failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }

    /* back to begin of file */
    fseek(fp, 0L, SEEK_SET);
    pDst = pY;
    if (fread(pDst, 1, u32FrmSize, fp) != u32FrmSize)
	{
        printf("Func: %s(), line: [%d], fread failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static inline HI_VOID SAMPLE_COMM_VI_GetBitWidthByPixFmt(PIXEL_FORMAT_E enPixelFormat, HI_U32 *pu32BitWidth)
{
    if( PIXEL_FORMAT_RGB_BAYER_8BPP == enPixelFormat)
    {
        *pu32BitWidth = 8;
    }
    else if( PIXEL_FORMAT_RGB_BAYER_10BPP == enPixelFormat)
    {
        *pu32BitWidth = 10;
    }
    else if( PIXEL_FORMAT_RGB_BAYER_12BPP == enPixelFormat)
    {
        *pu32BitWidth = 12;
    }
    else if( PIXEL_FORMAT_RGB_BAYER_14BPP == enPixelFormat)
    {
        *pu32BitWidth = 14;
    }
    else
    {
        *pu32BitWidth = 16;
    }
}

HI_S32 SAMPLE_COMM_VI_GetFPNFrame_FromRaw(FILE* pRawFile,
        HI_U32 u32Width, HI_U32 u32Height,
        SAMPLE_VI_FRAME_INFO_S* pstVMstFrameInfo,
        HI_U32* pu32Offset,
        HI_U32* pu32Iso)
{
    HI_U32 u32Size;
    VB_BLK VbBlk;
    HI_U32 u32PhyAddr;
    HI_U8* pVirAddr;
    HI_U32 u32Stride;
    HI_U32 u32BitWidth = 16;
    HI_S32 s32Ret;
    VIDEO_FRAME_INFO_S* pstVFrameInfo = &pstVMstFrameInfo->stVideoFrame;
    COMPRESS_MODE_E enCompressMode = COMPRESS_MODE_NONE;

    ////////////////////////////////////////////////////////
    /* seek end of file */
    s32Ret = fseek(pRawFile, -8, SEEK_END);
    if (0 != s32Ret)
    {
        printf("Func: %s(), line: [%d], get frame size failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    /* get fpn frame size */
    if (fread(&u32Size, 1, 4, pRawFile) != 4)
	{
        printf("Func: %s(), line: [%d], get frame size failed:  %s\n", __FUNCTION__, __LINE__, strerror(errno));
        return HI_FAILURE;
    }
    /* back to begin of file */
    fseek(pRawFile, 0L, SEEK_SET);
    ////////////////////////////////////////////////////////

    /* alloc video buffer block ---------------------------------------------------------- */
    VbBlk = HI_MPI_VB_GetBlock(VB_INVALID_POOLID, u32Size, HI_NULL);
    if (VB_INVALID_HANDLE == VbBlk)
    {
        printf("HI_MPI_VB_GetBlock err! size:%d\n", u32Size);
        SAMPLE_COMM_VI_ExitMpp(VbBlk);
        return HI_FAILURE;
    }
    pstVMstFrameInfo->VbBlk = VbBlk;

    u32PhyAddr = HI_MPI_VB_Handle2PhysAddr(VbBlk);
    if (0 == u32PhyAddr)
    {
        printf("HI_MPI_VB_Handle2PhysAddr err!\n");
        SAMPLE_COMM_VI_ExitMpp(u32PhyAddr);
        return HI_FAILURE;
    }
    pVirAddr = (HI_U8*) HI_MPI_SYS_Mmap(u32PhyAddr, u32Size);
    if (NULL == pVirAddr)
    {
        printf("HI_MPI_SYS_Mmap err!\n");
        SAMPLE_COMM_VI_ExitMpp((HI_S32)pVirAddr);
        return HI_FAILURE;
    }

    pstVFrameInfo->u32PoolId = HI_MPI_VB_Handle2PoolId(VbBlk);
    if (VB_INVALID_POOLID == pstVFrameInfo->u32PoolId)
    {
        HI_MPI_SYS_Munmap(pVirAddr, u32Size);
        SAMPLE_COMM_VI_ExitMpp(pstVFrameInfo->u32PoolId);
        return HI_FAILURE;
    }

    pstVFrameInfo->stVFrame.u32PhyAddr[0] = u32PhyAddr;
    pstVFrameInfo->stVFrame.u32PhyAddr[1] = 0;
    pstVFrameInfo->stVFrame.u32PhyAddr[2] = 0;

    pstVFrameInfo->stVFrame.pVirAddr[0] = pVirAddr;
    pstVFrameInfo->stVFrame.pVirAddr[1] = NULL;
    pstVFrameInfo->stVFrame.pVirAddr[2] = NULL;

    pstVFrameInfo->stVFrame.u32Width  = u32Width;
    pstVFrameInfo->stVFrame.u32Height = u32Height;
    pstVFrameInfo->stVFrame.u32Stride[0] = 0;
    pstVFrameInfo->stVFrame.u32Stride[1] = 0;
    pstVFrameInfo->stVFrame.u32Stride[2] = 0;
    pstVFrameInfo->stVFrame.u32Field = VIDEO_FIELD_FRAME;

    SAMPLE_COMM_VI_ReadOneFpnFrame(pRawFile, pstVFrameInfo->stVFrame.pVirAddr[0], pu32Offset,
                                   &pstVMstFrameInfo->u32FrmSize, &enCompressMode, pu32Iso);

    pstVFrameInfo->stVFrame.enCompressMode = enCompressMode;

    /* calculate the stride */
    u32Stride = u32Width * u32BitWidth;
    if (COMPRESS_MODE_LINE == enCompressMode)
    {
        SAMPLE_COMM_VI_GetBitWidthByPixFmt(pstVFrameInfo->stVFrame.enPixelFormat, &u32BitWidth);
        u32Stride += (16 * 8 + ((u32Width + 15) / 16 * 4));
    }
    u32Stride = ((u32Stride + 127) / 128 * 128) / 8;
    pstVFrameInfo->stVFrame.u32Stride[0] = u32Stride;

    HI_MPI_SYS_Munmap(pVirAddr, u32Size);
    return 0;
}



HI_S32 SAMPLE_COMM_VI_ReadOneRawFile(const char* file_name,
                                     HI_U32 u32Width, HI_U32 u32Height,
                                     SAMPLE_VI_FRAME_INFO_S* pstVMstFrameInfo,
                                     HI_U32* u32Offset,
                                     HI_U32* pu32Iso)
{
    FILE* pfd;
    HI_S32 s32Ret = HI_SUCCESS;

    /* open YUV file */
    printf("open dark frame file: %s. \n", file_name);
    pfd = fopen(file_name, "rb");
    if (!pfd)
    {
        printf("open file -> %s fail \n", file_name);
        return HI_FAILURE;
    }

    /* read frame information from YUV file */
    s32Ret = SAMPLE_COMM_VI_GetFPNFrame_FromRaw(pfd, u32Width, u32Height, pstVMstFrameInfo, u32Offset, pu32Iso);

    fclose(pfd);
    return s32Ret;
}


HI_S32 SAMPLE_COMM_VI_CORRECTION_CONFIG(const char* fpn_file,    /* fpn file name */
                                        ISP_FPN_TYPE_E enFpnType, /* line/frame */
                                        ISP_OP_TYPE_E  enOpType,  /* auto/manual */
                                        HI_U32 u32Strength,       /* strength */
                                        PIXEL_FORMAT_E enPixelFormat)
{
    VI_CHN ViChn = 0;
    VI_CHN_ATTR_S stTempChnAttr;
    ISP_FPN_ATTR_S stFPNAttr;
    SAMPLE_VI_FRAME_INFO_S stVMstFrame = {0};
    ISP_DEV IspDev = 0;
    ISP_FPN_FRAME_INFO_S* pstFpnFrmInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Iso = 0;

    s32Ret = HI_MPI_VI_GetChnAttr(ViChn, &stTempChnAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("get vi chn attr failed!");
        return HI_FAILURE;
    }

    stVMstFrame.stVideoFrame.stVFrame.enPixelFormat = enPixelFormat;
    stVMstFrame.stVideoFrame.stVFrame.enCompressMode = COMPRESS_MODE_NONE;
    pstFpnFrmInfo = &stFPNAttr.stFpnFrmInfo;

    printf("\nhit the Enter key,start read dark frame\n");
    VI_PAUSE();
    s32Ret = SAMPLE_COMM_VI_ReadOneRawFile(fpn_file,
                                           stTempChnAttr.stDestSize.u32Width,
                                           stTempChnAttr.stDestSize.u32Height,
                                           &stVMstFrame,
                                           &pstFpnFrmInfo->u32Offset,
                                           &u32Iso);

    if (HI_SUCCESS != s32Ret)
    {
        printf("read raw file failed!");
        return HI_FAILURE;
    }

    pstFpnFrmInfo->u32FrmSize = stVMstFrame.u32FrmSize;
    memcpy(&pstFpnFrmInfo->stFpnFrame, &stVMstFrame.stVideoFrame, sizeof(VIDEO_FRAME_INFO_S));
    stFPNAttr.bEnable  = HI_TRUE;
    stFPNAttr.enOpType = enOpType;
    stFPNAttr.enFpnType            = enFpnType;
    stFPNAttr.stFpnFrmInfo.u32Iso  = u32Iso;
    stFPNAttr.stManual.u32Strength = u32Strength;

    printf("\nread u32Offset  = 0x%x, u32iso = %d\n", stFPNAttr.stFpnFrmInfo.u32Offset , stFPNAttr.stFpnFrmInfo.u32Iso);
    printf("FrmSize: %d, stride: %d, compress mode: %d\n", stFPNAttr.stFpnFrmInfo.u32FrmSize,
                                        stFPNAttr.stFpnFrmInfo.stFpnFrame.stVFrame.u32Stride[0],
                                        stFPNAttr.stFpnFrmInfo.stFpnFrame.stVFrame.enCompressMode);

    printf("hit the Enter key,start correction\n");
    VI_PAUSE();

    s32Ret =  HI_MPI_ISP_SetFPNAttr(IspDev, &stFPNAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("fpn correction fail 0x%x\n", s32Ret);
        return HI_FAILURE;
    }

    VI_PAUSE();

    s32Ret = SAMPLE_COMM_VI_ReleaseVBToPool(&stVMstFrame);
    if (HI_SUCCESS != s32Ret)
    {
        printf("SAMPLE_COMM_VI_ReleaseVBToPool fail 0x%x\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/******************************************************************************
* funciton : Get enSize by diffrent sensor
******************************************************************************/
HI_S32 SAMPLE_COMM_VI_GetSizeBySensor(PIC_SIZE_E* penSize)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_VI_MODE_E enMode = SENSOR_TYPE;

    if (!penSize)
    {
        return HI_FAILURE;
    }

    switch (enMode)
    {
        case PANASONIC_MN34220_SUBLVDS_720P_120FPS:
        case PANASONIC_MN34220_MIPI_720P_120FPS:
        case SONY_IMX117_LVDS_720P_240FPS:
            *penSize = PIC_HD720;
            break;
        case APTINA_MT9P006_DC_1080P_30FPS:
        case PANASONIC_MN34220_SUBLVDS_1080P_30FPS:
        case PANASONIC_MN34220_MIPI_1080P_30FPS:
        case OMNIVISION_OV4689_MIPI_1080P_30FPS:
        case OMNIVISION_OV2718_MIPI_1080P_30FPS:
		case OMNIVISION_OV2718_2A_MIPI_1080P_30FPS:
	    case SONY_IMX323_CMOS_1080P_30FPS:
	    case APTINA_AR0237_LVDS_1080P_30FPS:
        case APTINA_AR0330_MIPI_1080P_30FPS:
        case SONY_IMX178_LVDS_1080P_30FPS:
        case SONY_IMX185_MIPI_1080P_30FPS:
        case SONY_IMX290_MIPI_1080P_30FPS:
        case SONY_IMX385_MIPI_1080P_30FPS:
        case SONY_IMX307_MIPI_1080P_30FPS:
        case JX_F22_MIPI_1080P_30FPS:
        case SMARTSENS_SC2235_CMOS_1080P_30FPS:
        case SONY_IMX117_LVDS_1080P_120FPS:
        case APTINA_AR0230_HISPI_1080P_30FPS:
            *penSize = PIC_HD1080;
            break;
        case APTINA_AR0330_MIPI_1536P_25FPS:
            *penSize = PIC_QXGA;
            break;
        case APTINA_AR0330_MIPI_1296P_25FPS:
            *penSize = PIC_2304x1296;
            break;
        case OMNIVISION_OV4689_MIPI_4M_30FPS:
            *penSize = PIC_2592x1520;
            break;
        case SONY_IMX178_LVDS_5M_30FPS:
        case OMNIVISION_OV5658_MIPI_5M_30FPS:
            *penSize = PIC_5M;
            break;
        case SONY_IMX226_LVDS_4K_30FPS:
        case SONY_IMX117_LVDS_4K_30FPS:
            *penSize = PIC_UHD4K;
            break;

        default:
            break;
    }

    return s32Ret;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
