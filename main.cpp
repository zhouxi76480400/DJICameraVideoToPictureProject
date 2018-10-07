#include <iostream>
#include "video_to_picture/video_to_picture.h"
#include <string>

using namespace std;

int main() {
    cout << "start convert nv12 file to jpg file" << endl;

    // set source file and new file path
    string file_path = "/Users/zhouxi/CLionProjects/DJICameraVideoToPictureProject/cmake-build-debug/raw_out.raw";
    string save_path = "/Users/zhouxi/CLionProjects/DJICameraVideoToPictureProject/cmake-build-debug/test_picture.bmp";

    // convert
    int status = convert_dji_camera_nv12_to_bmp(file_path,save_path);
    printf("the convert status is: %d\n",status);


    return 0;
}