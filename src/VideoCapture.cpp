/*
 * VideoCapture.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#include "VideoCapture.hpp"

#include <iostream>

/*static*/VideoCapture& VideoCapture::getInstance()
{
	static VideoCapture c(1);
	return c;
}

VideoCapture::VideoCapture(unsigned char camID) :
		cap(camID)
{
	// TODO Auto-generated constructor stub

}

void VideoCapture::capture()
{
	if (!cap.isOpened())
	{
		throw std::runtime_error(
				"Oops, it wasn't possible to open the video stream");
	}
	while (key != 27)
	{
		//cv::Mat frame, processedFrame;

		cap >> frame;


		//Convert BGR image to HSV

		cv::imshow("Webcam", frame);

		//If esc key has not been pressed you can check for the key and wait the waitkey time. Function close will also
		//change the key if needed to close the program
		if(key != 27)
		{
			key = cv::waitKey(30);
		}
	}
	cv::destroyAllWindows();
}

VideoCapture::~VideoCapture()
{
	// TODO Auto-generated destructor stub
}

void VideoCapture::close()
{
	std::cout<<"Closing videostream"<<std::endl;
	//Key 27 is the escape key, which is a shortkey for closing the application
	key = 27;
}

cv::Mat VideoCapture::getFrame()
{
	return frame;
}
