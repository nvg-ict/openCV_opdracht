/*
 * ColorDetection.hpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#ifndef COLORDETECTION_HPP_
#define COLORDETECTION_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <array>
#include <map>

enum class colors {RED, GREEN, BLUE, YELLOW, BLACK, WHITE};

static std::map<colors,std::string> colorTypeTostring
{
	{colors::RED,"rood"},
	{colors::GREEN,"groen"},
	{colors::BLUE,"blauw"},
	{colors::YELLOW,"geel"},
	{colors::BLACK,"zwart"},
	{colors::WHITE,"wit"}
};

static std::map<std::string,colors> stringTocolor
{
	{"rood",colors::RED},
	{"groen",colors::GREEN},
	{"blauw",colors::BLUE},
	{"geel",colors::YELLOW},
	{"zwart",colors::BLACK},
	{"wit",colors::WHITE}
};

struct ColorRange
{
	ColorRange(const cv::Scalar& aLow, const cv::Scalar& aHigh)
	:low(aLow), high(aHigh)
	{
	}

	cv::Scalar low;
	cv::Scalar high;
};

class ColorDetection {
public:
	ColorDetection(const std::array<ColorRange,7>& list);
	virtual ~ColorDetection();
	void getColorRange(const cv::Mat& input, colors color, cv::Mat& output);

private:
	ColorRange redLRange;
	ColorRange redHRange;
	ColorRange greenRange;
	ColorRange blueRange;
	ColorRange yellowRange;
	ColorRange blackRange;
	ColorRange whiteRange;
};

#endif /* COLORDETECTION_HPP_ */



