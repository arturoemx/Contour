#ifndef __CONTOUR__
#define __CONTOUR__

#include <math.h>
#include "opencv2/opencv.hpp"
#include <vector>

struct contour 
{
   std::vector<cv::Point> contour;
   std::vector<cv::Point_<float>> smoothContour;
   std::vector<float> x;
   std::vector<float> y;
   std::vector<float> dx;
   std::vector<float> dy;
};

/*
\func float computeCurvature(Point &p0, Point &p1, Point &p2);
\brief Compute the curvature of a curve from three adyacent points
       in a contour. The curvature is computes as 
       \f$k = \frac{\dot(x)\ddot{y}-\ddot{x}\dot{y}}{(\dot{x}^2)+\dot{y}^2)^\frac{3}{2}}\f$
       where (\f$\dot{x}\f$,\f$\dot{y}\f$) and
             (\f$\ddot{x}\f$,\f$\ddot{y}\f$) are respectively the first and
             second derivatives with respect to arc length s.
      \param Point &p0, &p1, &p2. The plane coordinates of three adyacent
             contour points.
      \return The curvature measurement. It should be equal to the reciprocal
              radius of the circle tangent to the contour at point p.
*/
float computeCurvature(cv::Point &p0, cv::Point &p1, cv::Point &p2);

void computeCurvature(std::vector<cv::Point> &pts, std::vector<double> &K);

void plotCurvature(cv::Mat &frame, std::vector<cv::Point> &pts, std::vector<double> &K);

#endif

