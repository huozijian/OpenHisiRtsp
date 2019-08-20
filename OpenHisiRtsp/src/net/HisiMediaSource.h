#ifndef _HISI_MEDIA_SOURCE_H_
#define _HISI_MEDIA_SOURCE_H_
#include <string>
#include <queue>
#include <stdint.h>
#include "net/UsageEnvironment.h"
#include "net/MediaSource.h"
#include "base/ThreadPool.h"
#include "hisiComm/sample_comm.h"
#include "base/Mutex.h"
#include <pthread.h>
typedef struct __H264_DATA__
{
	unsigned char *pData;
	int dataSize;
}H264Data;
class VencThreadCtrl
{
public:
	bool bThreadStart;
	pthread_t hnd;
	Mutex* mMutex;
	H264Data h264Data;
};




class HisiMediaSource : public MediaSource
{
public:
    static HisiMediaSource* createNew(UsageEnvironment* env, std::string dev);
    virtual ~HisiMediaSource();

protected:
    HisiMediaSource(UsageEnvironment* env, std::string& dev);
    virtual void readFrame();

private:
    struct Nalu
    {
        Nalu(uint8_t* data, int size) : mData(data), mSize(size)
        { }

        uint8_t* mData;
        int mSize;
    };

    bool videoInit();
    bool videoExit();
    bool h264Init();
    bool h264Exit();
    void getFrameFromH264Mem(uint8_t* frame, int &size);

private:
    UsageEnvironment* mEnv;
    std::string mDev;
    struct Hisi_buf* mHisiBuf;
    struct Hisi_buf_unit* mHisiBufUnit;

    SAMPLE_VI_CONFIG_S stViConfig ;
    VencThreadCtrl vencThreadCtrl;
    int mCsp;
    int mPts;

    std::queue<Nalu> mNaluQueue;
};

#endif //_Hisi_MEDIA_SOURCE_H_
