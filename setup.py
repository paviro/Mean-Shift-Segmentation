#!/usr/bin/env python3

from setuptools import setup, Extension
import pybind11

mean_shift_module = Extension(
    'mean_shift_module',
    sources=['mean_shift_py.cpp', 'MeanShift.cpp'],
    include_dirs=[pybind11.get_include(), '/opt/homebrew/opt/opencv/include/opencv4'],
    library_dirs=['/opt/homebrew/opt/opencv/lib'],
    libraries=['opencv_core', 'opencv_imgproc', 'opencv_highgui'],
    extra_compile_args=['-std=c++11'],
    language='c++'
)

setup(
    name='mean_shift_module',
    version='0.1',
    description='Python bindings for custom MeanShift using pybind11',
    ext_modules=[mean_shift_module]
)
