#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

namespace dnt {
  namespace cortex {
    class BallDetector {
      public:
        BallDetector() :
          file_opened(false),
          visualization(false),
          lower_bound(0, 0, 0, 0),
          upper_bound(255, 255, 255, 255) {}

        void set_color(const cv::Scalar& lower, const cv::Scalar& upper) {
          this->lower_bound = lower;
          this->upper_bound = upper;
        }

        void set_visualization(bool visualize) {
          this->visualization = visualize;
          cv::namedWindow("binary");
          cv::namedWindow("position");
        }

        void open_stream(int camera_id);
        void open_stream(const std::string& filename);

        std::tuple<unsigned /*x*/, unsigned /*y*/> operator()();

      protected:
        bool file_opened;
        bool visualization;
        cv::Scalar lower_bound;
        cv::Scalar upper_bound;
        cv::VideoCapture video_stream;

        bool read_video_frame(cv::Mat& frame);
        void video_stream_checks();
    };
  }
}
