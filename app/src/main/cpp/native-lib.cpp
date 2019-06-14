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
#include "JavaHelp.h"

using std::string;
///////////////////////////////////////

JavaVM *javaVm=0;
////////////////////////////该方法在调用System.loadLibrary("native-lib");时候会执行/////////////////////////////////////
int JNI_OnLoad(JavaVM *vm, void *r) {
    LOGE("JNI_OnLoad:%s","运行了");
    javaVm = vm;
    return JNI_VERSION_1_6;
}

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
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_callJavaMe(JNIEnv *env, jobject instance, jbyteArray bytes_) {
    LOGE("callJavaMe");
    //jbyteArray 转为jbyte
    jsize size = env->GetArrayLength(bytes_);
    jbyte *bytes = env->GetByteArrayElements(bytes_, NULL);
    env->ReleaseByteArrayElements(bytes_, bytes, 0);
    LOGE("callJavaMe:%s", bytes);
    LOGE("size:%d", size);
    //jbyte 转为jbyteArray
    jbyteArray cpByteArray = env->NewByteArray(size);
    env->SetByteArrayRegion(cpByteArray,0,size,bytes);
    jbyte *jbyte1 = env->GetByteArrayElements(cpByteArray, JNI_FALSE);
    LOGE("cpByteArray:%s",jbyte1);
    env->ReleaseByteArrayElements(cpByteArray,jbyte1,JNI_COMMIT);
    LOGE("cpByteArray释放后:%s",jbyte1);
    JavaHelp *mJavaHelp=new  JavaHelp(javaVm,env,instance);
    mJavaHelp->callState(cpByteArray);
    delete (mJavaHelp);
    mJavaHelp=0;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_release(JNIEnv *env, jobject instance) {

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_callObj(JNIEnv *env, jobject instance, jobject use) {
    // TODO
    jclass    useClazz=env->GetObjectClass(use);
    jmethodID   getNameMId=env->GetMethodID(useClazz,"getName", "()Ljava/lang/String;");
    jobject jobject1=env->CallObjectMethod(use,getNameMId);
    jstring   jstring1= static_cast<jstring>(jobject1);
    const char *c=env->GetStringUTFChars(jstring1, 0);
    LOGE("callObj里面的Name:%s",c);
    env->DeleteLocalRef(useClazz);
    env->ReleaseStringUTFChars(jstring1,c);
}