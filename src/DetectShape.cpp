/*
 * DetectShape.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: nico
 */

#include "DetectShape.hpp"

DetectShape::DetectShape(cv::Mat anImage) :
		image(anImage)
{

}

DetectShape::~DetectShape()
{
}
/*
 double DetectShape::calculateAngle(const cv::Point& anglePoint,
 const cv::Point& p1, const cv::Point& p2)
 {
 cv::Point line1 = anglePoint - p1;
 cv::Point line2 = anglePoint - p2;

 double a = (line1.x * line2.x + line1.y * line2.y);
 double b = (sqrt(pow(line1.x, 2) + pow(line1.y, 2))
 * sqrt(pow(line2.x, 2) + pow(line2.y, 2)));

 //std::cout<<"CALC ANGLE: "<<acos(a/b) *	180.0 / CV_PI<<std::endl;

 return acos(a / b) * 180.0 / CV_PI;
 }
 */

bool DetectShape::detectSquare(const std::vector<cv::Point>& contour)
{
	double peri = cv::arcLength(contour, true);
	std::vector<cv::Point> points;
	cv::approxPolyDP(contour, points, 0.04 * peri, true);
	std::cout<<points.size()<<std::endl;

	if (points.size() == 4)
	{
		//Create a minimal rect around the rectangle
		cv::RotatedRect rect = cv::minAreaRect(contour);

		cv::Point2f pts[4];
		//Get 4 cornor. Left bottom[0], clockwise
		rect.points(pts);

		//If they match, it could be a square
		if (fabs(1.0 - (rect.size.width / rect.size.height)) <= 0.03)
		{
			double computedArea = cv::contourArea(contour);
			double theoreticalArea = rect.size.width * rect.size.height;
			//Check if theoretical area matches the computed area
			if (fabs(1.0 - (computedArea / theoreticalArea)) <= 0.1)
			{
				debugDrawRect(pts);
				drawPoI(points);
				return true;
			}
		}
	}
	return false;
}

bool DetectShape::detectRect(const std::vector<cv::Point>& contour)
{
	double peri = cv::arcLength(contour, true);
	std::vector<cv::Point> points;
	cv::approxPolyDP(contour, points, 0.04 * peri, true);
	std::cout<<points.size()<<std::endl;

	if (points.size() == 4)
	{

		//Create a minimal rect around the rectangle
		cv::RotatedRect rect = cv::minAreaRect(contour);

		cv::Point2f pts[4];
		//Get 4 cornor. Left bottom[0], clockwise
		rect.points(pts);

		double computedArea = cv::contourArea(contour);
		double theoreticalArea = rect.size.width * rect.size.height;

		//If they match, it's hopefully a rectangle. This function doesn't want to detect that
		if (fabs(1.0 - (rect.size.width / rect.size.height)) >= 0.03)
		{
			//Check if theoretical area matches the computed area
			if (fabs(1.0 - (computedArea / theoreticalArea)) <= 0.1)
			{
				debugDrawRect(pts);
				drawPoI(points);
				return true;
			}
		}
	}
	return false;
}

bool DetectShape::detectCircle(const std::vector<cv::Point>& contour)
{
	double peri = cv::arcLength(contour, true);
	std::vector<cv::Point> points;
	cv::approxPolyDP(contour, points, 0.04 * peri, true);
	std::cout<<points.size()<<std::endl;

	if (points.size() > 4)
	{
		//Create a minimal rect around the rectangle
		cv::RotatedRect rect = cv::minAreaRect(contour);

		cv::Point2f pts[4];
		//Get 4 cornor. Left bottom[0], clockwise
		rect.points(pts);

		//The width and height of the rectange need to be equal (the diameter of a circle is the same everywhere.
		std::cout<<"C: "<<rect.size.width<<","<<rect.size.height<<std::endl;
		if (1.0 - (rect.size.width / rect.size.height) <= 0.1)
		{
			double area = cv::contourArea(points);
			double compArea = CV_PI * pow(rect.size.width / 2, 2);

			std::cout<<"C a: "<<area<<","<<compArea<<std::endl;

			if (fabs(1.0 - (area / compArea)) <= 0.2)
			{
				debugDrawRect(pts);
				drawPoI(points);
				return true;
			}
		}
	}
	return false;
}

bool DetectShape::detectHalfCircle(const std::vector<cv::Point>& contour)
{
	double peri = cv::arcLength(contour, true);
	std::vector<cv::Point> points;
	cv::approxPolyDP(contour, points, 0.04 * peri, true);
	std::cout<<points.size()<<std::endl;

	if (points.size() > 4 && points.size() < 7)
	{
		//Create a minimal rect around the half circle.
		cv::RotatedRect rect = cv::minAreaRect(contour);

		cv::Point2f pts[4];
		//Get 4 cornor. Left bottom[0], clockwise
		rect.points(pts);

		double ratio = rect.size.width / rect.size.height;

		//If width/height has a 2:1 or 1:2 ratio, the shape could be a half circle
		if ((ratio < 2.1 && ratio > 1.9) || (ratio < 0.6 && ratio > 0.4))
		{
			double computedArea = cv::contourArea(contour);
			double theoreticalArea = 0.5 * CV_PI
					* pow((rect.size.width / 2), 2);

			if (fabs(1.0 - (computedArea / theoreticalArea)) <= 0.1)
			{
				debugDrawRect(pts);
				drawPoI(points);
				return true;
			}

		}
	}
	return false;
}

bool DetectShape::detectTriangle(const std::vector<cv::Point>& contour)
{
	double peri = cv::arcLength(contour, true);
	std::vector<cv::Point> points;
	cv::approxPolyDP(contour, points, 0.04 * peri, true);

	std::cout<<points.size()<<std::endl;
	if (points.size() == 3)
	{
		//Create a minimal rect around the triangle
		cv::RotatedRect rect = cv::minAreaRect(contour);

		cv::Point2f pts[4];
		//Get 4 cornor. Left bottom[0], clockwise
		rect.points(pts);

		double computedArea = cv::contourArea(contour);
		double theoreticalArea = 0.5 * rect.size.width * rect.size.height;

		rect.boundingRect();

		//Check if theoretical area matches the computed area
		if (fabs(1.0 - (computedArea / theoreticalArea)) <= 0.1)
		{
			debugDrawRect(pts);
			drawPoI(points);
			return true;
		}
	}
	return false;

}

void DetectShape::debugDrawRect(cv::Point2f *pts)
{
	for (int j = 0; j < 4; j++)
	{
		cv::line(image, pts[j], pts[(j + 1) % 4], cv::Scalar(255, 255, 255), 1,
				8);
		cv::circle(image, pts[j], 2, cv::Scalar(0, 255, 255), -1, 8, 0);

	}
}

void DetectShape::drawContourAndCenter(const std::vector<cv::Point>& points,const std::vector<cv::Vec4i>& hierarchy)
{
	cv::Moments mu = moments(points, false);
	cv::Point mc;
	std::vector<std::vector<cv::Point>> temp;
	temp.push_back(points);
	mc = cv::Point(static_cast<int>(mu.m10 / mu.m00),
			static_cast<int>(mu.m01 / mu.m00));

	//This draws the outline
	//,hierarchy,0,cv::Point()
	cv::drawContours(image, temp, (int) 0, cv::Scalar(0, 255, 0), 1, 8);

	//This draws the dot
	cv::circle(image, mc,2,  cv::Scalar(0, 255, 0), -1, 8, 0);
	cv::putText(image, "("+std::to_string(mc.x) + ","+std::to_string(mc.y)+")", mc, CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255),
			1);
}

void DetectShape::drawPoI(const std::vector<cv::Point>& PoI)
{
	for (unsigned long i = 0; i < PoI.size(); ++i)
	{
		cv::circle(image, PoI.at(i), 1, cv::Scalar(0, 0, 255), -1, 8, 0);
	}
}

bool DetectShape::detectShape(const cv::Mat& input, shape theShape)
{
	//find contours in the thresholded image
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(input, contours, hierarchy, CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (size_t i = 0; i < contours.size(); i++)
	{
		//A contour are has to be bigger than 300 to be considered useful
		if (cv::contourArea(contours.at(i)) >= 300.0)
		{
			shape result;
			if (detectTriangle(contours.at(i)))
			{
				result = shape::TRIANGLE;
				drawContourAndCenter(contours.at(i),hierarchy);
			}
			else if (detectRect(contours.at(i)))
			{
				result = shape::RECTANGLE;
				drawContourAndCenter(contours.at(i),hierarchy);
			}
			else if (detectSquare(contours.at(i)))
			{
				result = shape::SQUARE;
				drawContourAndCenter(contours.at(i),hierarchy);
			}
			else if (detectCircle(contours.at(i)))
			{
				result = shape::CIRCLE;
				drawContourAndCenter(contours.at(i),hierarchy);
			}
			else if (detectHalfCircle(contours.at(i)))
			{
				result = shape::HALF_CIRCLE;
				drawContourAndCenter(contours.at(i),hierarchy);
			}

			if (theShape == result)
			{
				return true;
			}
		}
	}
	return false;
}

const cv::Mat& DetectShape::getImage() const
{
	return image;
}
