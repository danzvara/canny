#include "canny.hpp"

Canny::Canny() : threshold(0) {};

Canny::Canny(int threshold) : threshold(threshold) {};

cv::Mat& Canny::detect(cv::Mat& src)
{
  const int n = 5;
  const double k = 0.0629;
  uchar kernelData[n][n] = {{2, 4, 5, 4, 2},
                      {4, 9, 12, 9, 4},
                      {5, 12, 15, 12, 5},
                      {4, 9, 12, 9, 4},
                      {2, 4, 5, 4, 2}};
  cv::Mat kernel = cv::Mat(n, n, CV_8UC1, kernelData);

  cv::Mat frame = applyKernel(src, kernel, n, k);
  sobel(src);
  return src;
}

/* Applies given kernel on the image. Assumes the kernel is of dimension size x size */
cv::Mat& Canny::applyKernel(cv::Mat& src, cv::Mat& kernel, const int size, const double k)
{
  if (kernel.rows < 1 || kernel.cols < 1 || size < 1)
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
        Vec1b* kernel_row = kernel.ptr<Vec1b>(y + half);
        for (int x = -half; x <= half; x++)
        {
          sum += k * (int) src_row[j + x][0] * kernel_row[x + half][0];
        }
      }

      sum = std::abs(sum);
      dest_row[j] = (uint8_t) (sum / (size * size));
    }
  }

  return *dest;
}

void Canny::sobel(cv::Mat& src)
{
  const int n = 3;
  const int k = 1;
  int kernel_dataGY[n][n] = {{-1, -2, -1},
                                {0, 0, 0},
                                {1, 2, 1}};
  int kernel_dataGX[n][n] = {{-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}};
  cv::Mat kernelGX = cv::Mat(n, n, CV_32SC1, kernel_dataGX);
  cv::Mat kernelGY = cv::Mat(n, n, CV_32SC1, kernel_dataGY);

  cv::Mat& gradX = applyKernel(src, kernelGX, n, k);
  cv::Mat& gradY = applyKernel(src, kernelGY, n, k);

  for (int i = 1; i < src.rows - 1; i++)
  {
    Vec1i* gx_row = gradX.ptr<Vec1i>(i);
    Vec1i* gy_row = gradY.ptr<Vec1i>(i);
    cv::Vec3b* src_row = src.ptr<cv::Vec3b>(i);
    for (int j = 1; j < src.cols - 1; j++)
    {
      int GX = gx_row[j][0];
      int GY = gy_row[j][0];
      uchar G = (uchar) std::round(std::hypot(GX, GY));
      src_row[j][0] = G;
      src_row[j][1] = G;
      src_row[j][2] = G;
    }
  }
}

void Canny::applyThreshold(cv::Mat& src)
{
}

void Canny::nonMaxSuppression(cv::Mat& src)
{
}

void Canny::dualThreshold(cv::Mat& src)
{
}

void Canny::edgeTrack(cv::Mat &src)
{
}
