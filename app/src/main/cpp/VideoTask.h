//
// Created by hachiadmin on 2019/6/17.
//

#ifndef JNI_VIDEOTASK_H
#define JNI_VIDEOTASK_H

#endif //JNI_VIDEOTASK_H

#include "jni.h"
//////////////////////////
#include <android/log.h>
//Android 低层封装了c++的log，这个是属于宏定义
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"FFMPEG",__VA_ARGS__)

class VideoTask {

public:
    VideoTask();

    ~VideoTask();

private:


};
