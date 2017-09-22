/*
 * MainApplication.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: root
 */

#include "MainApplication.hpp"

MainApplication::MainApplication(shape aShape, colors aColor) :
		shape_(aShape), colour_(aColor), c_start(std::clock()), c_end(0)
{

}

MainApplication::~MainApplication()
{
	std::cout << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
			<< std::endl;
}

bool MainApplication::run(const cv::Mat& image)
{
	bool shapeFound = false;
	cv::Mat processedImage;

	std::cout<<"Image"<<std::endl;

	DetectShape d(image);

	cv::GaussianBlur(image, processedImage, cv::Size(3, 3), 0);

	//BEST ZOU ZIJN ALS DIT OOK INSTELBAAR WAS HEB GEPROBEERD OM DIT ALS DEFAULT IN TE STELLEN
	//MAAR IS TE VEEL WERK... kut gekloot dat ik std::array geen default waarde kan geven
	//en dat je ColorDetection geen default contstructor heeft. Beetje kut om dan een instatie te maken zonder argumenten.
	ColorDetection c(
			std::array<ColorRange, 7>
			{ ColorRange(cv::Scalar(0, 100, 100), cv::Scalar(20, 255, 255)),
					ColorRange(cv::Scalar(160, 100, 100),
							cv::Scalar(179, 255, 255)), ColorRange(
							cv::Scalar(43, 100, 100), cv::Scalar(74, 255, 255)),
					ColorRange(cv::Scalar(83, 100, 100),
							cv::Scalar(140, 255, 255)), ColorRange(
							cv::Scalar(17, 50, 50), cv::Scalar(40, 255, 255)),
					ColorRange(cv::Scalar(0, 0, 0), cv::Scalar(179, 255, 60)),
					ColorRange(cv::Scalar(0, 0, 160), cv::Scalar(179, 225, 255)) });

	cv::Mat colourMask;

	c.getColorRange(processedImage, colour_, colourMask);

	std::cout<<"colourrange"<<std::endl;

	cv::GaussianBlur(colourMask, colourMask, cv::Size(5, 5), 0);

	std::cout<<"try to detect"<<std::endl;

	shapeFound = d.detectShape(colourMask, shape_);

	std::cout<<"detected"<<std::endl;

	//cv::namedWindow("Processed Image RAW", CV_WINDOW_AUTOSIZE);
	//cv::namedWindow("Processed Image", CV_WINDOW_AUTOSIZE);

	imshow("Processed Image RAW", colourMask);
	imshow("Processed Image", d.getImage());

	//imshow("Color filter raw", colourMask);
	//cv::imshow("Webcam", processedFrame);

	c_end = std::clock();
	return shapeFound;
}

