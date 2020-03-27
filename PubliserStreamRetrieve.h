#include "Infra/Thread.h"
#include "GenICam/StreamSource.h"
#include<ros/ros.h>
#include<image_transport/image_transport.h>

using namespace Dahua::GenICam;
using namespace Dahua::Infra;


class PubliserStreamRetrieve : public CThread
{
public:
	PubliserStreamRetrieve(IStreamSourcePtr& streamSpt,ros::NodeHandle nh);
	bool start();
	bool stop();
	ros::NodeHandle nh;
	image_transport::Publisher pub;

private:
	void threadProc();
	bool m_isLoop;
	IStreamSourcePtr m_streamSptr;
};
