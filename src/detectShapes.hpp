/*
 * centerShapes.hpp
 *
 *  Created on: Feb 21, 2017
 *      Author: nico
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

cv::Mat imageRAW, image;

std::string detectSquare(const std::vector<cv::Point>& c);

short detectShapes()
{
	imageRAW = cv::imread("/home/nico/workspace/OpenCV/Debug/shapes.png",
			CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!imageRAW.data)                              // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::cvtColor(imageRAW, image, CV_BGR2GRAY);
	cv::GaussianBlur(image, image, cv::Size(5, 5), 0, 0);

	//find contours in the thresholded image
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(image, contours, hierarchy, CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::RNG rng(12345);
	std::vector<cv::Moments> mu(contours.size());
	std::vector<cv::Point2f> mc(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{

		cv::Moments mu = moments(contours.at(i), false);

		std::string shape = detectSquare(contours.at(i));
		mc[i] = cv::Point2f(static_cast<float>(mu.m10 / mu.m00),
				static_cast<float>(mu.m01 / mu.m00));

		cv::Scalar color = cv::Scalar(255, 255, 255);
		//This draws the outline
		cv::drawContours(imageRAW, contours, (int) i, color, 2, 8, hierarchy, 0,
				cv::Point());
		//This draws the dot
		cv::circle(imageRAW, mc[i], 1, color, -1, 8, 0);
		cv::putText(imageRAW, shape, cv::Point(mc[i].x-(shape.length()*4), mc[i].y), CV_FONT_HERSHEY_SIMPLEX, 0.5, color,
				2);

	}

	/// Show in a window
	cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", imageRAW);

	cv::namedWindow("Image Used to detect", CV_WINDOW_AUTOSIZE);
	imshow("Image Used to detect", image);

	cv::waitKey(0);                        // Wait for a keystroke in the window
	cv::destroyAllWindows();

	return 0;
}

std::string detectSquare(const std::vector<cv::Point>& c)
{
	std::string shape;

	double peri = cv::arcLength(c, true);
	std::vector<cv::Point> approx;
	cv::approxPolyDP(c, approx, 0.04 * peri, true);

	switch (approx.size())
	{
	case 3:
		shape = "triangle";
		break;
	case 4:
	{
		cv::Rect rect = cv::boundingRect(approx);
		double ar = rect.width / float(rect.height);

		// a square will have an aspect ratio that is approximately
		// equal to one, otherwise, the shape is a rectangle
		if (ar >= 0.95 && ar <= 1.05)
		{
			shape = "square";
		}
		else
		{
			shape = "rectangle";
		}
		break;
	}
	case 5:
		shape = "pentagon";
		break;
	case 6:
		shape = "hexagon";
		break;

	default:
		shape = "circle";
		break;
	}
	std::stringstream ss;
	ss<<shape<<" "<<approx.size();
	return ss.str();
}

