//
// Created by zhouxi on 7/10/2018.
//

#include "video_to_picture.h"

#include <unistd.h>
#include <fstream>
#include "ConvertUtil.h"

bool isFileExist(string path);

int convert_nv12_to_bmp(int width_pixel, int height_pixel, string nv12_path, string save_path){
    int status = convert_nv_12_to_bmp_status_failed;
    int file_exist = isFileExist(nv12_path);
    if(true == file_exist) {
        // set buffer for nv12
        int file_size = width_pixel * height_pixel * 3 / 2;
        char * buffer = new char[file_size];
        // read file
        ifstream in_stream;
        in_stream.open(nv12_path.c_str(),std::ifstream::binary);
        bool file_is_open = in_stream.is_open();
        if(!file_is_open) {
            status = convert_nv_12_to_bmp_status_file_not_exist_or_not_permission;
        }else {
            in_stream.read(buffer,file_size);
            in_stream.close();
            cout << "input file size: " << strlen(buffer) << endl;
            char * yv12buffer = (char *) malloc(file_size);
            memcpy(yv12buffer,buffer,file_size);
            // convert NV12 to YV12
            convertNV12ToYV12((uint8_t *)buffer,(uint8_t *)yv12buffer,width_pixel,height_pixel);
            // convert I420 to BGR
            int bgr_size = width_pixel * height_pixel * 3;
            char * bgrbuffer = (char *) malloc(bgr_size);
            bool isSuccessToConvertBGR = convertYV12ToBGR24_Table((uint8_t *)yv12buffer,(uint8_t *)bgrbuffer,width_pixel,height_pixel);
            if(isSuccessToConvertBGR) {
                char * bmp_header_buffer = (char *) createBMPHeader(width_pixel,height_pixel,bgr_size);
                ofstream out_stream;
                out_stream.open(save_path, std::ofstream::binary);
                out_stream.write(bmp_header_buffer,Bmp_Info_Size + Bmp_FileHeader_Size);
                out_stream.write(bgrbuffer,bgr_size);
                out_stream.close();
                delete [] bgrbuffer;
                delete [] bmp_header_buffer;
                status = convert_nv_12_to_bmp_status_success;
            }else{
                status = convert_nv_12_to_bmp_status_failed;
            }
            delete [] yv12buffer;
        }
        delete [] buffer;

    }else{
        status = convert_nv_12_to_bmp_status_file_not_exist_or_not_permission;
    }
    return status;
}


int convert_dji_camera_nv12_to_bmp(string nv12_path, string save_path){
    int status = convert_nv12_to_bmp(1280,720,nv12_path,save_path);
    return status;
}

/**
 * check is file exists
 * @param path
 * @return
 */
bool isFileExist(string path) {
    bool status = false;
    int access_result = access(path.c_str(),F_OK);
    if(0 == access_result) {
        status = true;
    }
    return status;
}

