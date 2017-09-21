/*
 * VideoCapture.hpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#ifndef VIDEOCAPTURE_HPP_
#define VIDEOCAPTURE_HPP_

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

class VideoCapture
{
public:
	/**
	 * @brief Get instance of singleton class
	 * @return A reference to the Videocapture class
	 */
	static VideoCapture& getInstance();
	/**
	 * @brief Destructor
	 */
	virtual ~VideoCapture();
	/**
	 * @brief Function that captures the webcam
	 * It will show a constant stream of the webcam feed in a while loop. Ideally used in for example a thread
	 */
	void capture();
	/**
	 * @brief Function will close the webcam feed.
	 * In this case it will change the key value to 27, simulating the ecs key being pressed
	 */
	void close();
	/**
	 * @brief Function to get the current frame capture by the webcam feed
	 * @return A hard copy of the image, it will be used as a "photo" by the color/shape algorithms.
	 */
	cv::Mat getFrame();
private:
	VideoCapture(unsigned char camID);
	cv::Mat frame;
	cv::VideoCapture cap;
	char key = 0;
};

#endif /* VIDEOCAPTURE_HPP_ */
