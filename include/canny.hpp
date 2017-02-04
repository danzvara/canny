#ifndef CANNY_HPP
#define CANNY_HPP
#include <opencv2/core.hpp>

class Canny {
  public:

    Canny();

    Canny(int threshold);

    cv::Mat& detect(cv::Mat& image);

  private:
    cv::Mat& applyKernel(cv::Mat& image, int** kernel, int size, double k);

    void sobel(cv::Mat& image);

    void applyThreshold(cv::Mat& image);

    void nonMaxSuppression(cv::Mat& image);

    void dualThreshold(cv::Mat& image);

    void edgeTrack(cv::Mat &image);


    int threshold;
};
#endif
