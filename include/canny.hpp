#ifndef CANNY_HPP
#define CANNY_HPP
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

#define PI 3.1415926536

class Canny {
  public:

    Canny();

    Canny(int threshold);

    cv::Mat& detect(cv::Mat& src);

  private:
    cv::Mat&
    applyKernel(cv::Mat& src, cv::Mat& kernel, const int size, const double k);

    cv::Mat&
    sobel(cv::Mat& gradientX, cv::Mat& gradientY);

    cv::Mat&
    nonMaxSuppression(cv::Mat& gradientX, cv::Mat& gradientY, cv::Mat& gradientMag);

    void applyThreshold(cv::Mat& src, uchar t);

    void dualThreshold(cv::Mat& src);

    void 
    dualThreshold(cv::Mat& src, int low, int high);

    void
    suppress(cv::Vec<uchar, 1>* row, int j, int a, int b, int c);

    void
    edgeTrack (cv::Mat &src);

    int threshold;

    typedef cv::Vec<uint8_t, 1> Vec1b;
    typedef cv::Vec<uint8_t, 3> Vec3b;
    typedef cv::Vec<int, 1> Vec1i;
    typedef uint8_t uchar;
};
#endif
