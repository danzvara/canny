#ifndef CANNY_HPP
#define CANNY_HPP
#include <opencv2/core.hpp>
#include <cmath>

class Canny {
  typedef cv::Vec<uint8_t, 1> Vec1b;
  typedef cv::Vec<uint8_t, 3> Vec3b;

  const int kernel[5][5] = {{2, 4, 5, 4, 2},
                      {4, 9, 12, 9, 4},
                      {5, 12, 15, 12, 5},
                      {4, 9, 12, 9, 4},
                      {2, 4, 5, 4, 2}};
  public:

    Canny();

    Canny(int threshold);

    cv::Mat& detect(cv::Mat& image);

  private:
    cv::Mat& applyKernel(cv::Mat& image, const int kernel[5][5], int size, double k);

    void sobel(cv::Mat& image);

    void applyThreshold(cv::Mat& image);

    void nonMaxSuppression(cv::Mat& image);

    void dualThreshold(cv::Mat& image);

    void edgeTrack(cv::Mat &image);


    int threshold;
};
#endif
