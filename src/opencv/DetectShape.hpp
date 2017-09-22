/*
 * DetectShape.hpp
 *
 *  Created on: Mar 13, 2017
 *      Author: nico
 */

#ifndef DETECTSHAPE_HPP_
#define DETECTSHAPE_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <vector>
#include <map>

enum class shape {CIRCLE,HALF_CIRCLE,SQUARE,RECTANGLE,TRIANGLE};

static std::map<shape,std::string> shapeTypeTostring
{
	{shape::CIRCLE,"circel"},
	{shape::HALF_CIRCLE,"halve circel"},
	{shape::SQUARE,"vierkant"},
	{shape::RECTANGLE,"rechthoek"},
	{shape::TRIANGLE,"driehoek"}
};

static std::map<std::string,shape> stringToshape
{
	{"circel",shape::CIRCLE},
	{"halve circel",shape::HALF_CIRCLE},
	{"vierkant",shape::SQUARE},
	{"rechthoek",shape::RECTANGLE},
	{"driehoek",shape::TRIANGLE}
};

class DetectShape
{
public:
	DetectShape(cv::Mat anImage);
	virtual ~DetectShape();
	/**
	 * @brief Function will detect a square
	 * The function will first check if height is equal to width. If that is not the case the function will return false
	 * Then the function will compare the computed area with the theoretical area. If that is not within the margin it will return false.
	 * Then the function will calculate every corner. If a corner is not ~90 degrees it will return false.
	 * If all above applies, the shape is assumed to be a square and true will be returned
	 * @param contour The contour of the shape
	 * @return True if the shape is a square
	 */
	bool detectSquare(const std::vector<cv::Point>& contour);
	/**
	 * @brief Function will detect a rectangle
	 * The function will first check if height is not equal to width. If that is not the case the function will return false
	 * Then the function will compare the computed area with the theoretical area. If that is not within the margin it will return false.
	 * Then the function will calculate every corner. If a corner is not ~90 degrees it will return false.
	 * If all above applies, the shape is assumed to be a rectangle and true will be returned
	 * @param contour The contour of the shape
	 * @return True if the shape is a rectangle
	 */
	bool detectRect(const std::vector<cv::Point>& contour);
	/**
	 * @brief Function that will detect the full circle
	 * Function will calculate the diameter and then the theoretical surface of the circle. Then it will be checked
	 * if it roughly matches the contour area.
	 * After that, every point gets validated with the function of a circle: (x-cx)²+(y-cy)²=d
	 * If one of the points doesn't meet the condition of the math function, the function will return false.
	 * @param contour The points needed to compute the circle (~8 are given by the approxPolyDP function)
	 * @return True if a circle is detected
	 */
	bool detectCircle(const std::vector<cv::Point>& contour);
	/**
	 * @brief Function that will detect half a circle
	 * First a check will be made if the width is twice the height (of the min area rect). If this is not the case, the function returns false
	 * Secondly a check will be done if the contour area matches the theoretical area of the half circle. If not, false is returned
	 * Once the points of the diameter are known, every point computed by the approxPolyDP will be validated by
	 * calculating every angle, whose have to be ~90 degrees everywhere.
	 * If one of the angles is not ~90 degrees the function will return false.
	 * @param contour All the points of the contour
	 * @return True if half a circle is detected
	 */
	bool detectHalfCircle(const std::vector<cv::Point>& contour);
	/**
	 * @brief Function will detect a triangle, given the three important points, computed by approxPolyDP.
	 * First the theoretical area is calculated and compared to the computed area. If they don't rougly match the function returns false
	 * Function then makes use of the property that a all angles of a triangle are 180 degrees.
	 * If the sum of angles is not ~180 degrees it will return false
	 * @param contour The points needed to compute the triangle (3 are needed for a triangle
	 * @return True if a triangle is detected
	 */
	bool detectTriangle(const std::vector<cv::Point>& contour);
	/**
	 * @brief Function will draw the Points of Interest (the points that were used to determine the shape.
	 * @param PoI The points of interest
	 */
	void drawPoI(const std::vector<cv::Point>& PoI);
	/**
	 * @brief Function that can draw the rotatedrect
	 * @param pts A pointer containing the 4 vertices of the rotatedrect
	 */
	void debugDrawRect(cv::Point2f *pts);
	/**
	 *
	 */
	void drawContourAndCenter(const std::vector<cv::Point>& points,const std::vector<cv::Vec4i>& hierarchy);

	bool detectShape(const cv::Mat& input, shape theShape);
	const cv::Mat& getImage() const;

private:
	/**
	 * @brief Function calculates the angle of a point, given two other points to create two intersecting vectors
	 * The function creates two "vectors" between anglePoint and p1, and between anglePoint and p2.
	 * Then the dotproduct will be calculated between the two lines.
	 * @param anglePoint The angle on which the lines need to intersect
	 * @param p1 A point which will be used to create the first vector
	 * @param p2 A point which will be used to create the second vector
	 * @return The angle calculated by the dotproduct
	 */
	//double calculateAngle(const cv::Point& anglePoint, const cv::Point& p1, const cv::Point& p2);

	cv::Mat image;
};

#endif /* DETECTSHAPE_HPP_ */
