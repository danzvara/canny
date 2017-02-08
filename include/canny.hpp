#ifndef CANNY_HPP
#define CANNY_HPP
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

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

    void applyThreshold(cv::Mat& src, uchar t);

    void nonMaxSuppression(cv::Mat& src);

    void dualThreshold(cv::Mat& src);

    void edgeTrack(cv::Mat &src);


    int threshold;

    typedef cv::Vec<uint8_t, 1> Vec1b;
    typedef cv::Vec<uint8_t, 3> Vec3b;
    typedef cv::Vec<int, 1> Vec1i;
    typedef uint8_t uchar;
};
#endif
