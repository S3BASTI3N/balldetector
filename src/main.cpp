#include <iostream>
#include "ball_detector.h"
#include <opencv2/core/core.hpp>

int main1(int argc, char** argv) {
  /*
  if (argc <= 1) {
    std::cerr << "Need at least 1 argument" << std::endl;
    return -1;
  }
   */

  dnt::cortex::BallDetector b;
  b.set_visualization(true);
  b.set_color(cv::Scalar(0, 0, 170), cv::Scalar(100, 100, 255));

  b.open_stream(0);
  auto position = b();
  std::cout << std::get<0>(position) << " " << std::get<1>(position) << std::endl;
  while (1==1) {
    position = b();
    std::cout << std::get<0>(position) << " " << std::get<1>(position) << std::endl;
  }
  std::cout << "Exiting" << std::endl;
  return 0;
}


int main2(int argc, char** argv) {
  cv::VideoCapture video_stream(0);
  cv::Mat frame;
  std::cout << CV_VERSION << std::endl;

  if (!video_stream.isOpened())
  {
    std::cerr << "*** Failed to open stream" << std::endl;
    return 1;
  }

  while (cv::waitKey(100) != 'q') {
    if (!video_stream.read(frame)) {
      std::cerr << "*** Failed to read image" << std::endl;
      continue;
    }

    std::cout << frame.at<unsigned char>(0,0,0) << std::endl;
    cv::imshow("frame", frame);
  }
  return 0;
}


int main(int argc, char** argv) {
  return main1(argc, argv);
}
