#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "net/HisiMediaSource.h"
#include "debugComm.h"
#include "base/Logging.h"


HisiMediaSource* HisiMediaSource::createNew(UsageEnvironment* env, std::string dev)
{
    return new HisiMediaSource(env, dev);
}

HisiMediaSource::HisiMediaSource(UsageEnvironment* env, std::string& dev) :
    MediaSource(env),
    mEnv(env),
    mDev(dev),
    mPts(0)
{
	vencThreadCtrl.mMutex = Mutex::createNew();
    bool ret;

    setFps(22);

    ret = videoInit();
    assert(ret == true);

    ret = h264Init();
    assert(ret == true);

    for(int i = 0; i < DEFAULT_FRAME_NUM; ++i)
        mEnv->threadPool()->addTask(mTask);
}

HisiMediaSource::~HisiMediaSource()
{
	delete vencThreadCtrl.mMutex;
    h264Exit();
    videoExit();
}

static inline int startCode3(uint8_t* buf)
{
    if(buf[0] == 0 && buf[1] == 0 && buf[2] == 1)
        return 1;
    else
        return 0;
}

void HisiMediaSource::readFrame()
{
    MutexLockGuard mutexLockGuard(mMutex);

    if(mAVFrameInputQueue.empty())
        return;

    AVFrame* frame = mAVFrameInputQueue.front();
    frame->mFrameSize=0;
    while(frame->mFrameSize==0)
    	getFrameFromH264Mem(frame->mBuffer, frame->mFrameSize);
    if(frame->mFrameSize < 0)
        return;

    if(startCode3(frame->mBuffer))
    {
        frame->mFrame = frame->mBuffer+3;
        frame->mFrameSize -= 3;
    }
    else
    {
        frame->mFrame = frame->mBuffer+4;
        frame->mFrameSize -= 4;
    }

    mAVFrameInputQueue.pop();
    mAVFrameOutputQueue.push(frame);
}

bool HisiMediaSource::videoInit()
{

	PAYLOAD_TYPE_E enPayLoad[2]= {PT_H264, PT_H264};
	PIC_SIZE_E enSize[2] = {PIC_HD1080, PIC_HD1080};
	HI_U32 u32Profile = 0;

	VB_CONF_S stVbConf;
	VPSS_GRP VpssGrp;
	VPSS_CHN VpssChn;
	VPSS_GRP_ATTR_S stVpssGrpAttr = {0};
	VPSS_CHN_ATTR_S stVpssChnAttr = {HI_FALSE};
	VPSS_CHN_MODE_S stVpssChnMode;

	VENC_CHN VencChn;
	SAMPLE_RC_E enRcMode= SAMPLE_RC_CBR;
	HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 u32BlkSize;
	SIZE_S stSize;


	/******************************************
	 step  1: init sys variable
	******************************************/
	memset(&stVbConf,0,sizeof(VB_CONF_S));

	SAMPLE_COMM_VI_GetSizeBySensor(&enSize[0]);

	stVbConf.u32MaxPoolCnt = 128;
	u32BlkSize = SAMPLE_COMM_SYS_CalcPicVbBlkSize(VIDEO_ENCODING_MODE_NTSC,enSize[0], SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);
	stVbConf.astCommPool[0].u32BlkSize = u32BlkSize;
	stVbConf.astCommPool[0].u32BlkCnt = 5;


	/******************************************
	 step 2: mpp system init.
	******************************************/
	s32Ret = SAMPLE_COMM_SYS_Init(&stVbConf);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("system init failed with %d!\n", s32Ret);
		goto END_VENC_1080P_CLASSIC_0;
	}

	/******************************************
	 step 3: start vi dev & chn to capture
	******************************************/
	stViConfig.enViMode   = SENSOR_TYPE;
	stViConfig.enRotate   = ROTATE_NONE;
	stViConfig.enNorm     = VIDEO_ENCODING_MODE_AUTO;
	stViConfig.enViChnSet = VI_CHN_SET_NORMAL;
	stViConfig.enWDRMode  = WDR_MODE_NONE;
	s32Ret = SAMPLE_COMM_VI_StartVi(&stViConfig);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("start vi failed!\n");
		goto END_VENC_1080P_CLASSIC_1;
	}

	/******************************************
	 step 4: start vpss and vi bind vpss
	******************************************/
	s32Ret = SAMPLE_COMM_SYS_GetPicSize(VIDEO_ENCODING_MODE_NTSC, enSize[0], &stSize);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("SAMPLE_COMM_SYS_GetPicSize failed!\n");
		goto END_VENC_1080P_CLASSIC_1;
	}


	VpssGrp = 0;
	stVpssGrpAttr.u32MaxW = stSize.u32Width;
	stVpssGrpAttr.u32MaxH = stSize.u32Height;
	stVpssGrpAttr.bIeEn = HI_FALSE;
	stVpssGrpAttr.bNrEn = HI_TRUE;
	stVpssGrpAttr.bHistEn = HI_FALSE;
	stVpssGrpAttr.bDciEn = HI_FALSE;
	stVpssGrpAttr.enDieMode = VPSS_DIE_MODE_NODIE;
	stVpssGrpAttr.enPixFmt = SAMPLE_PIXEL_FORMAT;
	stVpssGrpAttr.bSharpenEn = HI_FALSE;

	s32Ret = SAMPLE_COMM_VPSS_StartGroup(VpssGrp, &stVpssGrpAttr);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("Start Vpss failed!\n");
		goto END_VENC_1080P_CLASSIC_2;
	}

	s32Ret = SAMPLE_COMM_VI_BindVpss(stViConfig.enViMode);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("Vi bind Vpss failed!\n");
		goto END_VENC_1080P_CLASSIC_3;
	}

	VpssChn = 0;
	stVpssChnMode.enChnMode      = VPSS_CHN_MODE_USER;
	stVpssChnMode.bDouble        = HI_FALSE;
	stVpssChnMode.enPixelFormat  = SAMPLE_PIXEL_FORMAT;
	stVpssChnMode.u32Width       = stSize.u32Width;
	stVpssChnMode.u32Height      = stSize.u32Height;
	stVpssChnMode.enCompressMode = COMPRESS_MODE_SEG;
	memset(&stVpssChnAttr, 0, sizeof(stVpssChnAttr));
	stVpssChnAttr.s32SrcFrameRate = -1;
	stVpssChnAttr.s32DstFrameRate = -1;
	s32Ret = SAMPLE_COMM_VPSS_EnableChn(VpssGrp, VpssChn, &stVpssChnAttr, &stVpssChnMode, HI_NULL);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("Enable vpss chn failed!\n");
		goto END_VENC_1080P_CLASSIC_4;
	}


	/******************************************
	 step 5: start stream venc
	******************************************/

	enRcMode = SAMPLE_RC_CBR;
	VpssGrp = 0;
	VpssChn = 0;
	VencChn = 0;

	s32Ret = SAMPLE_COMM_VENC_Start(VencChn, enPayLoad[0],VIDEO_ENCODING_MODE_NTSC, enSize[0], enRcMode,u32Profile,ROTATE_NONE);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("Start Venc failed!\n");
		goto END_VENC_1080P_CLASSIC_5;
	}

	s32Ret = SAMPLE_COMM_VENC_BindVpss(VencChn, VpssGrp, VpssChn);
	if (HI_SUCCESS != s32Ret)
	{
		RTSP_SYS_DEBUG("Start Venc failed!\n");
		goto END_VENC_1080P_CLASSIC_5;
	}
	return true;
END_VENC_1080P_CLASSIC_5:

	VpssGrp = 0;
	VpssChn = 0;
	VencChn = 0;
	SAMPLE_COMM_VENC_UnBindVpss(VencChn, VpssGrp, VpssChn);
	SAMPLE_COMM_VENC_Stop(VencChn);
	SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);

END_VENC_1080P_CLASSIC_4:	//vpss stop

	VpssGrp = 0;
	VpssChn = 0;
	SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);


END_VENC_1080P_CLASSIC_3:    //vpss stop
	SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
END_VENC_1080P_CLASSIC_2:    //vpss stop
	SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
END_VENC_1080P_CLASSIC_1:	//vi stop
	SAMPLE_COMM_VI_StopVi(&stViConfig);
END_VENC_1080P_CLASSIC_0:	//system exit
	SAMPLE_COMM_SYS_Exit();
	return false;

    
}

bool HisiMediaSource::videoExit()
{
	VPSS_GRP VpssGrp;
	VPSS_CHN VpssChn;
	VENC_CHN VencChn;

	VpssGrp = 0;
	VpssChn = 0;
	VencChn = 0;
	SAMPLE_COMM_VENC_UnBindVpss(VencChn, VpssGrp, VpssChn);
	SAMPLE_COMM_VENC_Stop(VencChn);
	SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);


	VpssGrp = 0;
	VpssChn = 0;
	SAMPLE_COMM_VPSS_DisableChn(VpssGrp, VpssChn);


	SAMPLE_COMM_VI_UnBindVpss(stViConfig.enViMode);
	SAMPLE_COMM_VPSS_StopGroup(VpssGrp);
	SAMPLE_COMM_VI_StopVi(&stViConfig);
	SAMPLE_COMM_SYS_Exit();
    return true;
}

static void flushVencStreamToMem(H264Data *h264Data, VENC_STREAM_S* pstStream)
{
    if(h264Data->pData!=NULL)
    {
    	free(h264Data->pData);
    	h264Data->dataSize=0;
    }
    //计算当前视频包的大小
    for (unsigned int i = 0; i < pstStream->u32PackCount; i++)
    {
    	h264Data->dataSize+=pstStream->pstPack[i].u32Len - pstStream->pstPack[i].u32Offset;
    }
    h264Data->pData=(unsigned char *)malloc(h264Data->dataSize);
    unsigned char *pData = h264Data->pData;
    //填充数据
    for (unsigned int i = 0; i < pstStream->u32PackCount; i++)
    {
    	int len =pstStream->pstPack[i].u32Len - pstStream->pstPack[i].u32Offset;
    	memcpy(pData,pstStream->pstPack[i].pu8Addr + pstStream->pstPack[i].u32Offset,len);
    	pData+=len;
    }
}

void* vencStreamProcess(void* p)
{
    HI_S32 i;
    HI_S32 s32Ret;
    HI_S32 s32ChnTotal=1;

    HI_S32 maxfd = 0;
    fd_set read_fds;
    HI_S32 VencFd[VENC_MAX_CHN_NUM];

    VENC_CHN VencChn;
    VENC_CHN_STAT_S stStat;
    VENC_STREAM_S stStream;
    VENC_CHN_ATTR_S stVencChnAttr;
    VencThreadCtrl* pstPara;
    VENC_STREAM_BUF_INFO_S stStreamBufInfo[VENC_MAX_CHN_NUM];
    struct timeval TimeoutVal;

    prctl(PR_SET_NAME, "hi_getstream", 0, 0, 0);
    pstPara = (VencThreadCtrl*)p;

    /******************************************
     step 1:  check & prepare save-file & venc-fd
    ******************************************/
    if (s32ChnTotal >= VENC_MAX_CHN_NUM)
    {
        RTSP_SYS_DEBUG("input count invaild\n");
        return NULL;
    }
    for (i = 0; i < s32ChnTotal; i++)
    {
        /* decide the stream file name, and open file to save stream */
        VencChn = i;
        s32Ret = HI_MPI_VENC_GetChnAttr(VencChn, &stVencChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            RTSP_SYS_DEBUG("HI_MPI_VENC_GetChnAttr chn[%d] failed with %#x!\n", \
                       VencChn, s32Ret);
            return NULL;
        }
        VencFd[i] = HI_MPI_VENC_GetFd(i);
        if (VencFd[i] < 0)
        {
            RTSP_SYS_DEBUG("HI_MPI_VENC_GetFd failed with %#x!\n",
                       VencFd[i]);
            return NULL;
        }
        if (maxfd <= VencFd[i])
        {
            maxfd = VencFd[i];
        }

        s32Ret = HI_MPI_VENC_GetStreamBufInfo (i, &stStreamBufInfo[i]);
        if (HI_SUCCESS != s32Ret)
        {
            RTSP_SYS_DEBUG("HI_MPI_VENC_GetStreamBufInfo failed with %#x!\n", s32Ret);
            return (void *)HI_FAILURE;
        }
    }

    /******************************************
     step 2:  Start to get streams of each channel.
     ******************************************/
    while (true == pstPara->bThreadStart)
    {
        FD_ZERO(&read_fds);
        for (i = 0; i < s32ChnTotal; i++)
        {
            FD_SET(VencFd[i], &read_fds);
        }
        TimeoutVal.tv_sec  = 2;
        TimeoutVal.tv_usec = 0;
        s32Ret = select(maxfd + 1, &read_fds, NULL, NULL, &TimeoutVal);
        if (s32Ret < 0)
        {
            RTSP_SYS_DEBUG("select failed!\n");
            break;
        }
        else if (s32Ret == 0)
        {
            RTSP_SYS_DEBUG("get venc stream time out, exit thread\n");
            continue;
        }
        else
        {
            for (i = 0; i < s32ChnTotal; i++)
            {
                if (FD_ISSET(VencFd[i], &read_fds))
                {
                    /*******************************************************
                    step 2.1 : query how many packs in one-frame stream.
                    *******************************************************/
                    memset(&stStream, 0, sizeof(stStream));
                    s32Ret = HI_MPI_VENC_Query(i, &stStat);
                    if (HI_SUCCESS != s32Ret)
                    {
                        RTSP_SYS_DEBUG("HI_MPI_VENC_Query chn[%d] failed with %#x!\n", i, s32Ret);
                        break;
                    }
                    /*******************************************************
					step 2.2 :suggest to check both u32CurPacks and u32LeftStreamFrames at the same time,for example:					 if(0 == stStat.u32CurPacks || 0 == stStat.u32LeftStreamFrames)
					 {						RTSP_SYS_DEBUG("NOTE: Current  frame is NULL!\n");
						continue;
					 }
					 *******************************************************/
                    if (0 == stStat.u32CurPacks)
                    {
                        RTSP_SYS_DEBUG("NOTE: Current  frame is NULL!\n");
                        continue;
                    }
                    /*******************************************************
                     step 2.3 : malloc corresponding number of pack nodes.
                    *******************************************************/
                    stStream.pstPack = (VENC_PACK_S*)malloc(sizeof(VENC_PACK_S) * stStat.u32CurPacks);
                    if (NULL == stStream.pstPack)
                    {
                        RTSP_SYS_DEBUG("malloc stream pack failed!\n");
                        break;
                    }
                    /*******************************************************
                     step 2.4 : call mpi to get one-frame stream
                    *******************************************************/
                    stStream.u32PackCount = stStat.u32CurPacks;
                    s32Ret = HI_MPI_VENC_GetStream(i, &stStream, HI_TRUE);
                    if (HI_SUCCESS != s32Ret)
                    {
                        free(stStream.pstPack);
                        stStream.pstPack = NULL;
                        RTSP_SYS_DEBUG("HI_MPI_VENC_GetStream failed with %#x!\n", \
                                   s32Ret);
                        break;
                    }
                    /*******************************************************
                     step 2.5 : save frame to file
                    *******************************************************/
                    {
                        MutexLockGuard mutexLockGuard(pstPara->mMutex);
                        flushVencStreamToMem(&pstPara->h264Data,&stStream);
                    }


                    /*******************************************************
                     step 2.6 : release stream
                     *******************************************************/
                    s32Ret = HI_MPI_VENC_ReleaseStream(i, &stStream);
                    if (HI_SUCCESS != s32Ret)
                    {
                        free(stStream.pstPack);
                        stStream.pstPack = NULL;
                        break;
                    }
                    /*******************************************************
                     step 2.7 : free pack nodes
                    *******************************************************/
                    free(stStream.pstPack);
                    stStream.pstPack = NULL;
                }
            }
        }
    }

    return NULL;
}
void HisiMediaSource::getFrameFromH264Mem(uint8_t* frame, int& size)
{
	MutexLockGuard mutexLockGuard(vencThreadCtrl.mMutex);
	if(vencThreadCtrl.h264Data.dataSize>FRAME_MAX_SIZE)
	{
		RTSP_SYS_DEBUG("getFrameFromH264Mem failed,vencThreadCtrl.h264Data.dataSize>FRAME_MAX_SIZE\n");
		size=0;
		return;
	}
	if(vencThreadCtrl.h264Data.dataSize==0)
	{
		size=0;
		return;
	}
	memcpy(frame,vencThreadCtrl.h264Data.pData,vencThreadCtrl.h264Data.dataSize);
	size = vencThreadCtrl.h264Data.dataSize;
}
bool HisiMediaSource::h264Init()
{

	vencThreadCtrl.bThreadStart=true;
	pthread_create(&vencThreadCtrl.hnd,NULL, vencStreamProcess, (void*)&vencThreadCtrl);
    return true;
}

bool HisiMediaSource::h264Exit()
{
    if (true == vencThreadCtrl.bThreadStart)
    {
    	vencThreadCtrl.bThreadStart = false;
        pthread_join(vencThreadCtrl.hnd, 0);
    }
    return true;
}
