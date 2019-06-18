//
// Created by hachiadmin on 2019/6/17.
//

#include "VideoTask.h"

void *consumer(void *arg) {
    LOGE("consumer()");
    VideoTask *videoTask = static_cast<VideoTask *>(arg);
    videoTask->countReduce();
    return 0;
};

void *produce(void *arg) {
    LOGE("produce()");
    VideoTask *videoTask = static_cast<VideoTask *>(arg);
    videoTask->countPlus();
    return 0;
}

VideoTask::VideoTask() {
    LOGE("运行了VideoTask()");
    if (!isStart1) {
        i = 1000;
        isStart1 = true;
        pthread_create(&pthredID, 0, consumer, this);
        pthread_create(&pthreadID1, 0, produce, this);
        //初始化同步锁
        pthread_mutex_init(&mutex, NULL);
        //初始化条件变量用来，唤醒和等待
        pthread_cond_init(&cond, NULL);
        pthread_mutex_init(&mutex1, NULL);
        pthread_cond_init(&cond1, NULL);
    } else {
        LOGE("pthredID:%s", "正在执行");
    }

}

VideoTask::~VideoTask() {

    LOGE("运行了VideoTask()销毁方法");
    isStart1 = false;
//    int   a=pthread_join(pthredID,0);
//    LOGE("a:%d",a);
//    pthread_join(pthreadID1,0);
//    int   b=pthread_join(pthredID,0);
//    LOGE("b:%d",b);
    //在子线程执行完毕之后，一般子线程中有一些资源没有需要回收这用这个等待子线程回收完毕，如果子线程没有需要回收的资源，那么主线程也没有必要等待子线程回收完毕，所以调用这个pthread_detach()
    pthread_detach(pthredID);
    pthread_detach(pthreadID1);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond1);
    pthread_mutex_destroy(&mutex1);

//    pthread_exit((void*)1);
}


void VideoTask::countReduce() {
    LOGE("countReduse()");
    pthread_mutex_lock(&mutex);
    while (isStart1) {
        if (!isConsumed) {
            pthread_cond_wait(&cond, &mutex);
        } else {
            sleep(0.9);
            i--;
            isConsumed = false;
            LOGE("i的值：%d", i);
            pthread_cond_signal(&cond1);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void VideoTask::countPlus() {
    pthread_mutex_lock(&mutex1);
    while (isStart1) {
        if (!isConsumed) {
            sleep(0.9);
            i++;
            LOGE("i的值：%d", i);
            isConsumed = true;
            pthread_cond_signal(&cond);
        } else {
            pthread_cond_wait(&cond1, &mutex1);
        }
    }
    pthread_mutex_unlock(&mutex1);
}

