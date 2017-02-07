#include <iostream>
#include "camera_stream.hpp"

int main (int argc, char** argv)
{
  CameraStream cameraStream;
  Canny canny;
  cameraStream.useCanny(&canny);
  cameraStream.run();

  return 0;
}
