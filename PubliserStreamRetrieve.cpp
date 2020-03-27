#ifdef __unix__
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif
#include "PubliserStreamRetrieve.h"
#include "GenICam/Frame.h"
#include<Media/ImageConvert.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<ros/ros.h>
#include<opencv2/highgui/highgui.hpp>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>
#include<string>
#include<time.h>

double lastClockTime,t_start,t_end;

void imageCallback(uint8_t* image,int image_size){

}

PubliserStreamRetrieve::PubliserStreamRetrieve(IStreamSourcePtr& streamSptr,ros::NodeHandle nh)
	: CThread("PubliserStreamRetrieve")
	, m_isLoop(false)
	, m_streamSptr(streamSptr)
{
    image_transport::ImageTransport it(nh);
    pub = it.advertise("camera/leftRaw",1);
}

bool PubliserStreamRetrieve::start()
{
	m_isLoop = true;
	return createThread();
}

bool PubliserStreamRetrieve::stop()
{
	m_isLoop = false;
	m_streamSptr.reset();
	return destroyThread();
}

void PubliserStreamRetrieve::threadProc()
{
	
	while (m_isLoop)
	{
		t_start = clock();
		std::cout<<"-------------------------------------------------------------"<<std::endl;
		CFrame frame;

		//获取一帧
		if (!m_streamSptr)
		{
			printf("m_streamPtr is NULL.\n");
			return;
		}
		bool isSuccess = m_streamSptr->getFrame(frame, 300);
		
		if (!isSuccess)
		{
			printf("getFrame  fail.\n");
			continue;
		}

		//判断帧的有效性
		bool isValid = frame.valid();
		if (!isValid)
		{
			printf("frame is invalid!\n");
			continue;
		}
		
		IMGCNV_SOpenParam conv_param;
		conv_param.width = frame.getImageWidth();
		conv_param.height = frame.getImageHeight();
		if (conv_param.width%4 != 0){
			conv_param.paddingX = 4 - conv_param.width%4;
		}else
		{
			conv_param.paddingX = 0;
		}
		
		if (conv_param.height%2 != 0){
			conv_param.paddingY = 2 - conv_param.height%2;
		}else
		{
			conv_param.paddingY = 0;
		}

		//转换图片格式
		int nRgbBufferSize = 0;
		nRgbBufferSize = conv_param.height*conv_param.width*3;
		uint8_t* imgBuff =   (uint8_t*)frame.getImage();
		uint8_t* img_out = (uint8_t*)malloc(nRgbBufferSize);
		conv_param.dataSize =frame.getImageSize(); 
		conv_param.pixelForamt = frame.getImagePixelFormat();
		IMGCNV_EErr status =  IMGCNV_ConvertToBGR24_Ex(imgBuff,&conv_param,img_out,&nRgbBufferSize,IMGCNV_DEMOSAIC_BILINEAR);
		
		
		 if (IMGCNV_SUCCESS != status)
			{
				/* 释放内存 */
				printf("IMGCNV_ConvertToBGRA24_Ex failed.\n");
				free(imgBuff);
				free(img_out);
				return;
			}

		std::cout<<"[Time]Time stamp:"<<frame.getImageTimeStamp()<<std::endl;
		std::cout<<"[Size]Source image size: "<<frame.getImageSize()<<std::endl;
		std::cout<<"[Size]CV image size: "<<nRgbBufferSize<<std::endl;
		

		cv::Mat Image(conv_param.height,conv_param.width,CV_8UC3,img_out);
		//cv::imshow("view",Image);
		//cv::waitKey(10);

		/*pub*/
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",Image).toImageMsg();
        pub.publish(msg);
        //ros::spinOnce();


		//打印FrameID
		t_end = clock();
		std::cout<<"[Time]pub total time:"<<(t_end-t_start)/CLOCKS_PER_SEC<<std::endl;
		printf("[INFO]get frame %lld successfully thread ID :%d\n", frame.getBlockId(), CThread::getCurrentThreadID());
		std::cout<<"[INFO]Press ctrl+z to stop"<<std::endl;
		/* 释放内存 */
		//free(imgBuff);
		free(img_out);
	}
	cv::destroyAllWindows();
}


