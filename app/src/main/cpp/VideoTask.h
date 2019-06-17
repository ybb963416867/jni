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
//c++线程
#include "pthread.h"
//sleep的头文件
#include <unistd.h>

class VideoTask {

public:
    VideoTask();
    void  countReduce();
    void  countPlus();
    ~VideoTask();

private:
     int  i=1000;
     bool isStart1= false;
     pthread_t pthredID ;
     pthread_t pthreadID1;
};
