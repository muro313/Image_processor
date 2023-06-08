cmake_minimum_required(VERSION 3.24)
project(image)

set(CMAKE_CXX_STANDARD 20)

add_executable(image main.cpp lib/in_out/Read.cpp lib/bmp/FILE_INFO.cpp lib/bmp/FILE_INFO.h lib/ColorPanel/ColorPanel.cpp lib/ColorPanel/ColorPanel.h lib/in_out/Write.cpp lib/in_out/Write.h lib/Parser/parser.cpp lib/Parser/parser.h lib/filters/facroty.cpp lib/filters/facroty.h lib/filters/Crop.cpp lib/filters/Crop.h lib/filters/Grayscale.cpp lib/filters/Grayscale.h lib/filters/Negative.cpp lib/filters/Negative.h lib/filters/Sharpening.cpp lib/filters/Sharpening.h lib/filters/EdgeDetection.cpp lib/filters/EdgeDetection.h)
