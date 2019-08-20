/******************************************************************************
  A simple program of Hisilicon Hi35xx rtspServer.
  Lingtu Technology Co., Ltd.
 ******************************************************************************
    Modification:  2018-12-12 Created
    Author:				Jason
******************************************************************************/

#include <iostream>
#include "debugComm.h"
#include "base/Logging.h"
#include "net/UsageEnvironment.h"
#include "base/ThreadPool.h"
#include "net/EventScheduler.h"
#include "net/Event.h"
#include "net/RtspServer.h"
#include "net/MediaSession.h"
#include "net/InetAddress.h"
#include "net/HisiMediaSource.h"
#include "net/H264RtpSink.h"
using namespace std;

int main(int argc, char *argv[])
{
	Logger::setLogLevel(Logger::LogWarning);

	EventScheduler* scheduler = EventScheduler::createNew(EventScheduler::POLLER_SELECT);
	ThreadPool* threadPool = ThreadPool::createNew(2);
	UsageEnvironment* env = UsageEnvironment::createNew(scheduler, threadPool);

	Ipv4Address ipAddr("0.0.0.0", 8554);
	RtspServer* server = RtspServer::createNew(env, ipAddr);
	MediaSession* session = MediaSession::createNew("live");
	MediaSource* mediaSource = HisiMediaSource::createNew(env,"hisi");
	RtpSink* rtpSink = H264RtpSink::createNew(env, mediaSource);

	session->addRtpSink(MediaSession::TrackId0, rtpSink);
	//session->startMulticast(); //多播
	server->addMeidaSession(session);
	server->start();
	std::cout<<"Play the media using the URL \""<<server->getUrl(session)<<"\""<<std::endl;
	env->scheduler()->loop();
	return 0;
}
