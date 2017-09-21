/*
 * Calibration.hpp
 *
 *  Created on: Mar 16, 2017
 *      Author: nico
 */

#ifndef CALIBRATION_HPP_
#define CALIBRATION_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Calibration
{
public:
	Calibration();
	virtual ~Calibration();
	void calibrate(const cv::Mat& img);
};

#endif /* CALIBRATION_HPP_ */
