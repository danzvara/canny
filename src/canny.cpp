#include "canny.hpp"

Canny::Canny() : threshold(0) {};

Canny::Canny(int threshold) : threshold(threshold) {};

cv::Mat& Canny::detect(cv::Mat& image)
{
return image;
}

cv::Mat& Canny::applyKernel(cv::Mat& image, int** kernel, int size, double k)
{
return image;
}

void Canny::sobel(cv::Mat& image)
{
}

void Canny::applyThreshold(cv::Mat& image)
{
}

void Canny::nonMaxSuppression(cv::Mat& image)
{
}

void Canny::dualThreshold(cv::Mat& image)
{
}

void Canny::edgeTrack(cv::Mat &image)
{
}
