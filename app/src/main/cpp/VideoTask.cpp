//
// Created by hachiadmin on 2019/6/17.
//

#include "VideoTask.h"

void *consumer(void *arg){
    LOGE("consumer()");
        VideoTask  *videoTask= static_cast<VideoTask *>(arg);
        videoTask->countReduce();
    return  0;
};

void *produce(void *arg){
    LOGE("produce()");
    VideoTask  *videoTask= static_cast<VideoTask *>(arg);
    videoTask->countPlus();
    return  0;
}

VideoTask::VideoTask() {
    LOGE("运行了VideoTask()");
    if (!isStart1){
        isStart1= true;
        pthread_create(&pthredID, 0, consumer, this);
        pthread_create(&pthreadID1, 0, produce, this);
    }else{
        LOGE("pthredID:%s","正在执行");
    }

}

VideoTask::~VideoTask() {

    LOGE("运行了VideoTask()销毁方法");
}

void VideoTask::countReduce() {
    LOGE("countReduse()");
     while (isStart1){
         sleep(0.5);
         i--;
         LOGE("i的值：%d",i);
     }
}

void VideoTask::countPlus() {
    while (isStart1){
        sleep(0.5);
        i++;
        LOGE("i的值：%d",i);
    }

}

