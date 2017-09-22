/*
 * MainApplication.hpp
 *
 *  Created on: Mar 16, 2017
 *      Author: root
 */

#ifndef MAINAPPLICATION_HPP_
#define MAINAPPLICATION_HPP_

#include "ColorDetection.hpp"
#include "DetectShape.hpp"
#include <ctime>
#include <chrono>

class MainApplication
{
public:
	MainApplication(shape aShape, colors aColor);
	virtual ~MainApplication();
	bool run(const cv::Mat& image);
private:
	shape shape_;
	colors colour_;
	std::clock_t c_start;
	std::clock_t c_end;
};

#endif /* MAINAPPLICATION_HPP_ */
