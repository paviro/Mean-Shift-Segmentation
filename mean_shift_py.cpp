#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include "MeanShift.h"

namespace py = pybind11;

cv::Mat numpy_uint8_3c_to_cv_mat(py::array_t<unsigned char>& input) {
  if (input.ndim() != 3 || input.shape(2) != 3)
    throw std::runtime_error("3-channel color image must be 3 dimensions");

  py::buffer_info buf_info = input.request();
  cv::Mat mat(buf_info.shape[0], buf_info.shape[1], CV_8UC3, (unsigned char*)buf_info.ptr);
  return mat;
}

class PyMeanShift {
public:
    PyMeanShift(float spatial_radius, float color_radius) : ms(spatial_radius, color_radius) {}

    void filter(py::array_t<unsigned char>& input) {
        cv::Mat img = numpy_uint8_3c_to_cv_mat(input);
        ms.MSFiltering(img);
    }

    void segment(py::array_t<unsigned char>& input) {
        cv::Mat img = numpy_uint8_3c_to_cv_mat(input);
        ms.MSSegmentation(img);
    }

private:
    MeanShift ms;
};

PYBIND11_MODULE(mean_shift_module, m) {
    py::class_<PyMeanShift>(m, "MeanShift")
        .def(py::init<float, float>())
        .def("filter", &PyMeanShift::filter)
        .def("segment", &PyMeanShift::segment);
}
