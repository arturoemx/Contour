#include <Curvature.h>
#include <iostream>

float computeCurvature(cv::Point &p0, cv::Point &p1, cv::Point &p2)
{
   float dx, dy, dx2, dy2, dxb, dyb, dxf, dyf, Sb, Sf, iS2;

   dxb = p1.x - p0.x;
   dyb = p1.y - p0.y;
   Sb = sqrt(dxb * dxb + dyb * dyb);
   dxf = p2.x - p1.x;
   dyf = p2.y - p1.y;
   Sf = sqrt(dxf * dxf + dyf * dyf);
   assert(Sb != 0 && Sf !=0);
   dx = 0.5 * (dxb / Sb + dxf / Sf);
   dy = 0.5 * (dyb / Sb + dyf / Sf);
   iS2 = 2./((Sb + Sf)*Sb*Sf);
   dx2 = (Sb*dxf-Sf*dxb) * iS2;
   dy2 = (Sb*dyf-Sf*dyb) * iS2;
   return (dx * dy2 - dy * dx2) / pow(dx * dx + dy * dy, 1.5);
}

void computeCurvature(std::vector<cv::Point> &pts, std::vector<double> &K)
{
   unsigned int l = pts.size(), i;

   K = std::vector<double>(l, 0.);
   K[0] = computeCurvature(pts[l-1], pts[0], pts[1]);
   l--;
   for (i = 1; i < l;++i)
      K[i] = computeCurvature(pts[i-1], pts[i], pts[i+1]);
   K[l] = computeCurvature(pts[l-1], pts[l], pts[0]);
}

void plotCurvature(cv::Mat &frame, std::vector<cv::Point> &pts, std::vector<double> &K)
{
   double mn, mx, range, fact;
   unsigned int i, l, idx;
   cv::Mat gMap, cMap;
   cv::Mat_<uchar>::iterator itg;
   cv::Vec3b color;

   gMap = cv::Mat::zeros(1, 256, CV_8UC1);
   itg = gMap.begin<uchar>();
   for (int j = 255; j >= 0; --j, ++itg)
      *itg = (unsigned int)j;

   cv::applyColorMap(gMap, cMap, cv::COLORMAP_JET);

   l = K.size();
   mn = mx = fabs(K[0]);
   for (i = 1; i < l; ++i)
   {
      double val = fabs(K[i]);

      if (val < mn)
         mn = val;
      else
      {
         if (val > mx)
            mx = val;
      }
   }
   range = mx - mn;
   fact = 255 ;
   for (i = 1; i < l; ++i)
   {
      idx = (unsigned)(fabs(K[i]) * fact);
      if (idx > 255)
         idx = 255;
      color = cMap.at<cv::Vec3b>(idx);
      cv::line (frame, pts[i - 1], pts[i], color, 2);
   }
   idx = (unsigned)(fabs(K[i]) * fact);
   if (idx > 255)
      idx = 255;
   color = cMap.at<cv::Vec3b>(idx);
   cv::line (frame, pts[l - 1], pts[0], color, 2);
   std::cout << "[mn, mx, range] = [ " << mn << ", " << mx << ", "
             << range << " ]" << std::endl;
   for (i = 20, l = 0;i < 276; ++i, ++l)
   {
      color = cMap.at<cv::Vec3b>(l);
      cv::line(frame,cv::Point(i, 10), cv::Point(i, 30), color, 1);
   }
}
