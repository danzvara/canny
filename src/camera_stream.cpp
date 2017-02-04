#include "camera_stream.hpp"

CameraStream::CameraStream() : camera(0) {}

CameraStream::CameraStream(int camera) : camera(camera) {}

int CameraStream::run()
{
  cv::VideoCapture capture(camera);
  if (!capture.isOpened()) {
    return -1;
  }

  cv::namedWindow("edges", 1);
  for(;;)
  {
    capture >> frame;
    cv::imshow("edges", frame);
    if (cv::waitKey(30) >= 0)
      return 0;
  }

  return 0;
}


