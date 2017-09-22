/*
 * ColorDetection.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#include "ColorDetection.hpp"

ColorDetection::ColorDetection(const std::array<ColorRange, 7>& list) :
		redLRange(list[0]), redHRange(list[1]), greenRange(list[2]), blueRange(
				list[3]), yellowRange(list[4]), blackRange(list[5]), whiteRange(
				list[6])
{
}

ColorDetection::~ColorDetection()
{
	// TODO Auto-generated destructor stub
}

void ColorDetection::getColorRange(const cv::Mat& input,
		colors color, cv::Mat& output)
{
	cv::Mat mask1, mask2, frameHSV;

	cv::cvtColor(input, frameHSV, CV_BGR2HSV);

	switch (color)
	{
	case colors::RED:
		cv::inRange(frameHSV, redHRange.low, redHRange.high, mask1);
		cv::inRange(frameHSV, redLRange.low, redLRange.high, mask2);
		output = mask1 | mask2;
		break;
	case colors::GREEN:
		cv::inRange(frameHSV, greenRange.low, greenRange.high, output);
		break;
	case colors::BLUE:
		cv::inRange(frameHSV, blueRange.low, blueRange.high, output);
		break;
	case colors::YELLOW:
		cv::inRange(frameHSV, yellowRange.low, yellowRange.high, output);
		break;
	case colors::BLACK:
		cv::inRange(frameHSV, blackRange.low, blackRange.high, output);
		break;
	case colors::WHITE:
		cv::inRange(frameHSV, whiteRange.low, whiteRange.high, output);
		break;
	default:
		output = input;
		break;
	}
}

