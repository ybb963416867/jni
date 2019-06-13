//
// Created by hachiadmin on 2019/6/13.
//这个是linux 下jni的头文件，而java下也有jni.h头文件但是他是windows平台下的，有些地方不一样
#include <jni.h>
//////////////////////////
#include <android/log.h>
//Android 低层封装了c++的log，这个是属于宏定义
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"FFMPEG",__VA_ARGS__)
////使用c++里面封装的string是要加这两
#include <string>
using std::string;
///////////////////////////////////////


extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_call(JNIEnv *env, jobject instance) {
    LOGE("call:%s","调用了call");
    // TODO

}extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnidata_JniManage_callBoolean(JNIEnv *env, jobject instance, jstring string_) {
    const char *strings = env->GetStringUTFChars(string_, 0);
    env->ReleaseStringUTFChars(string_, strings);
    LOGE("callBoolean:%s",strings);
    string  str1=strings;
    LOGE("释放内存后的str1:%s",str1.data());
    const char *str2="abc";
    if (!strcmp(strings,str2)){
        return true;
    }else {
        return false;
    }
//    if (!str1.compare(str2)){
//        return true;
//    } else{
//        return false;
//    }
}