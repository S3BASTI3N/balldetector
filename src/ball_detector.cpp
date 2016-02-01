#include <iostream>
#include "ball_detector.h"

namespace dnt {
namespace cortex {

std::tuple<unsigned, unsigned> BallDetector::operator()() {
  cv::Mat frame, binary_img;
  unsigned x = 0;
  unsigned y = 0;
  unsigned count = 0;
  std::tuple<unsigned, unsigned> result(0, 0);

  if (!this->read_video_frame(frame)) {
    std::cerr << "oh no!\n";
  }

  cv::inRange(frame, this->lower_bound, this->upper_bound, binary_img);

  cv::Mat f2 = frame.clone();

  std::cout << binary_img.type() << " "
      << binary_img.depth() << " "
      << binary_img.channels() << std::endl;

  for (int i = 0; i < binary_img.rows; i++) {
    for (int j = 0; j < binary_img.cols; j++) {
      if (binary_img.at<unsigned char>(i, j, 0) != 0) {
        x += i;
        y += j;
        count++;
      }
    }
  }

  if (count != 0) {
    result = std::make_tuple(x / count, y / count);
  }

  if (this->visualization) {
    cv::circle(binary_img,
        cv::Point(std::get<0>(result), std::get<1>(result)),
        10,
        cv::Scalar(255, 255, 255));
    cv::imshow("binary", binary_img);
    cv::waitKey(1);

    cv::circle(f2,
        cv::Point(std::get<0>(result), std::get<1>(result)),
        10,
        cv::Scalar(0, 0, 255));
    cv::putText(f2,
        "(" + std::to_string(std::get<0>(result)) + ", " + std::to_string(std::get<1>(result)) + ")",
        cv::Point(20, 100),
        1,
        2,
        cv::Scalar(0, 0, 255));
    cv::imshow("position", f2);
    cv::waitKey(1);
  }
  return result;
}

void BallDetector::open_stream(int camera_id) {
  video_stream = cv::VideoCapture(camera_id);
  this->video_stream_checks();
}


void BallDetector::open_stream(const std::string& filename) {
  video_stream = cv::VideoCapture(filename);
  this->video_stream_checks();
}


void BallDetector::video_stream_checks() {
  if (!video_stream.isOpened())
  {
    std::cerr << "*** Failed to open video stream" << std::endl;
    file_opened = false;
  }
  else {
    file_opened = true;
  }
}


bool BallDetector::read_video_frame(cv::Mat& frame) {
  if (this->file_opened && video_stream.read(frame)) {
    return true;
  }
  else {
    if (!this->file_opened) {
      std::cerr << "file not opened\n";
    }
    if (!video_stream.read(frame)) {
      std::cerr << "cannot read stream\n";
    }
    return false;
  }
}

}
}
