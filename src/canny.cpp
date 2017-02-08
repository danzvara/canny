#include "canny.hpp"

Canny::Canny() : threshold(0) {};

Canny::Canny(int threshold) : threshold(threshold) {};

cv::Mat& Canny::detect(cv::Mat& src)
{
  const int n = 5;
  const double k = 0.00629;
  int kernelData[n][n] = {{2, 4, 5, 4, 2},
                      {4, 9, 12, 9, 4},
                      {5, 12, 15, 12, 5},
                      {4, 9, 12, 9, 4},
                      {2, 4, 5, 4, 2}};
  cv::Mat kernel = cv::Mat(n, n, CV_32SC1, kernelData);
  cv::cvtColor(src, src, cv::COLOR_RGB2GRAY, 0);
  cv::Mat& frame = applyKernel(src, kernel, n, k);
  sobel(frame);
  //applyThreshold(frame, 240);
  return frame;
}

/* Applies given kernel on the image. Assumes the kernel is of dimension size x size.
 *
 * src - uchar, single channel
 * kernel - 32bit signed integer, single channel */
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
        Vec1b* src_row = src.ptr<Vec1b>(i + y);
        Vec1i* kernel_row = kernel.ptr<Vec1i>(y + half);
        for (int x = -half; x <= half; x++)
        {
          sum += ((int) src_row[j + x][0]) * kernel_row[x + half][0];
        }
      }

      sum = (k * (double) std::abs(sum));
      dest_row[j] = (uint8_t) (sum);
    }
  }

  return *dest;
}

/* Applies sobel filter on the source image.
 *
 * src - uchar single channel */
void Canny::sobel(cv::Mat& src)
{
  const int n = 3;
  const double k = 1;
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
    Vec1b* gx_row = gradX.ptr<Vec1b>(i);
    Vec1b* gy_row = gradY.ptr<Vec1b>(i);
    Vec1b* src_row = src.ptr<Vec1b>(i);
    for (int j = 1; j < src.cols - 1; j++)
    {
      uchar GX = gx_row[j][0];
      uchar GY = gy_row[j][0];
      int G = 0.5 * (int) std::round(std::hypot((double) GX, (double) GY));
      src_row[j][0] = G > 255 ? 100 : ((uchar) G);
    }
  }

  delete &gradX, &gradY;
}

/* Applies given threshold to the src image.
 * Everything with the value < t will be set to 0.
 *
 * src - uchar, single channel */
void Canny::applyThreshold(cv::Mat& src, uchar t)
{
  for (int i = 0; i < src.rows; i++)
  {
    Vec1b* src_row = src.ptr<Vec1b>(i);
    for (int j = 0; j < src.cols; j++)
    {
        src_row[j][0] = src_row[j][0] < t ? 0 : src_row[j][0];
    }
  }
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
