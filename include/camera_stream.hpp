#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

class CameraStream {
  public:
    CameraStream();

    CameraStream(int camera);

    int run();

  private:
    cv::Mat frame;
    int camera;
};
