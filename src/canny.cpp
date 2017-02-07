#include "canny.hpp"

Canny::Canny() : threshold(0) {};

Canny::Canny(int threshold) : threshold(threshold) {};

cv::Mat& Canny::detect(cv::Mat& image)
{
  return applyKernel(image, kernel, 5, 0.0629);
}

/* Applies given kernel on the image. Assumes the kernel is of dimension size x size */
cv::Mat& Canny::applyKernel(cv::Mat& src, const int kernel[5][5], int size, double k)
{
  if (kernel == nullptr || size < 1)
    return src;

  cv::Mat* dest = new cv::Mat(src.size(), CV_8UC1);
  int half = size / 2;
  for (int i = half; i < (src.rows - half); i++)
  {
    Vec1b* dest_row = dest->ptr<Vec1b>(i);
    for (int j = half; j < (src.cols - half); j++)
    {
      int sum = 0;
      for (int y = -half; y <= half; y++)
      {
        Vec3b* src_row = src.ptr<Vec3b>(i + y);
        for (int x = -half; x <= half; x++)
        {
          sum += k * (int) src_row[j + x][0] * kernel[y + half][x + half];
        }
      }

      sum = std::abs(sum);
      dest_row[j] = (uint8_t) (sum / (size * size));
    }
  }

  return *dest;
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
