/*
 * Calibration.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#include "Calibration.hpp"

#include <iostream>

Calibration::Calibration()
{
	// TODO Auto-generated constructor stub

}

Calibration::~Calibration()
{
	// TODO Auto-generated destructor stub
}

void Calibration::calibrate(const cv::Mat& img)
{
	cv::Mat grey, grey2;
	cv::cvtColor(img, grey, CV_BGR2GRAY);

	cv::GaussianBlur(grey, grey, cv::Size(11, 11), 0);

	//cv::bilateralFilter(grey, grey,11, 17, 17);
	cv::Canny(grey, grey, 30, 200);

	cv::imshow("grey", grey);

	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(grey, contours, hierarchy, CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (int i = 0; i < contours.size(); ++i)
	{
		cv::drawContours(img, contours, (int) i, cv::Scalar(0, 0, 0), 2, 8,
				hierarchy, 0, cv::Point());

		double peri = cv::arcLength(contours.at(i), true);
		std::vector<cv::Point> approx;
		cv::approxPolyDP(contours.at(i), approx, 0.04 * peri, true);

		if (approx.size() == 4)
		{
			cv::Moments mu = moments(contours.at(i), false);
			cv::Point mc = cv::Point((mu.m10 / mu.m00), (mu.m01 / mu.m00));


			if (mc.x < img.rows && mc.x > 0 && mc.y > 0 && mc.y << img.cols)
			{
				cv::RotatedRect rect = cv::minAreaRect(contours.at(i));

				if (fabs(1 - rect.size.width / rect.size.height) <= 0.01)
				{
					std::cout<<"rect: "<<fabs(1 - rect.size.width / rect.size.height)<<std::endl;

					std::cout << "x" << mc.x << "|" << img.rows << std::endl;
								std::cout << "y" << mc.y << "|" << img.cols << std::endl;

					cv::Vec3b colour = img.at<cv::Vec3b>(mc.x, mc.y);
					std::cout << (int) colour.val[0] << ","
							<< (int) colour.val[1] << "," << (int) colour.val[2]
							<< std::endl;
					cv::circle(img, mc, 5, cv::Scalar(0, 255, 0), -1, 8, 0);
				}
			}

			//std::cout<<mc.x<<mc.y<<std::endl;

			//cv::Vec3f intensity = img.at<cv::Vec3f>(mc.y, mc.x);
			//cv::Vec3b intensity = img.at<cv::Vec3b>(mc.x, mc.y);
			//uchar blue = intensity.val[0];
			//uchar green = intensity.val[1];
			//uchar red = intensity.val[2];
			//float blue = intensity.val[0];
			//float green = intensity.val[1];
			//float red = intensity.val[2];
			//std::cout<<colour.val[0]<<","<<colour.val[1]<<","<< colour.val[2]<<std::endl;
		}
	}

}

