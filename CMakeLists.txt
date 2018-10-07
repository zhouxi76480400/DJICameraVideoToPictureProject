cmake_minimum_required(VERSION 3.12)
project(DJICameraVideoToPictureProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(DJICameraVideoToPictureProject
        main.cpp
        video_to_picture/video_to_picture.cpp
        video_to_picture/video_to_picture.h
        video_to_picture/ConvertUtil.cpp
        video_to_picture/ConvertUtil.h
        )