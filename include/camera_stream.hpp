#ifndef CAMERA_STREAM_HPP
#define CAMERA_STREAM_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "canny.hpp"

class CameraStream {
  public:
    CameraStream();

    CameraStream(int camera);

    void useCanny(Canny& canny);

    int run();

  private:
    cv::Mat frame;
    Canny* canny;
    int camera;
};
#endif
