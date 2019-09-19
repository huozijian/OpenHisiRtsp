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
}H264Data,*PH264Data;

class H264DataQueue
{
public :
	int size;
	std::vector<PH264Data> datas;
	H264DataQueue()
	{
		size=0;
		//mMutex=Mutex::createNew();
	}
	~H264DataQueue()
	{
		//delete mMutex;
	}
	void push(PH264Data pData)
	{
		//MutexLockGuard mutexLockGuard(mMutex);
		datas.push_back(pData);
	}
	void pop(PH264Data &pData)
	{
		//MutexLockGuard mutexLockGuard(mMutex);
		//printf("datas====%d\r\n",datas.size());
		if(datas.size()<=0)
		{
			pData=NULL;
		}
		else
		{
			pData=datas[0];
			datas.erase(datas.begin());
		}
	}
//private:
	//Mutex* mMutex;
};
class VencThreadCtrl
{
public:
	bool bThreadStart;
	pthread_t hnd;
	Mutex* mMutex;
	H264DataQueue h264Queue;
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
    bool videoInit();
    bool videoExit();
    bool h264Init();
    bool h264Exit();
    void getFrameFromH264Queue(uint8_t* frame, int &size);

private:
    UsageEnvironment* mEnv;
    std::string mDev;
    struct Hisi_buf* mHisiBuf;
    struct Hisi_buf_unit* mHisiBufUnit;

    SAMPLE_VI_CONFIG_S stViConfig ;
    VencThreadCtrl vencThreadCtrl;
    int mCsp;
    int mPts;
};

#endif //_Hisi_MEDIA_SOURCE_H_
