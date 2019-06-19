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
//c++的线程
#include "pthread.h"
#include "VideoTask.h"

using std::string;
///////////////////////////////////////

JavaVM *javaVm = 0;
VideoTask *videoTask = 0;
////////////////////////////该方法在调用System.loadLibrary("native-lib");时候会执行/// 静态注册需要这方法//////////////////////////////////
//int JNI_OnLoad(JavaVM *vm, void *r) {
//    LOGE("JNI_OnLoad:%s","运行了");
//    javaVm = vm;
//    return JNI_VERSION_1_6;
//}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_call(JNIEnv *env, jobject instance) {
    LOGE("call:%s", "调用了call");

}extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnidata_JniManage_callBoolean(JNIEnv *env, jobject instance, jstring string_) {
    const char *strings = env->GetStringUTFChars(string_, 0);
    env->ReleaseStringUTFChars(string_, strings);
    LOGE("callBoolean:%s", strings);
    string str1 = strings;
    LOGE("释放内存后的str1:%s", str1.data());
    const char *str2 = "abc";
    if (!strcmp(strings, str2)) {
        return true;
    } else {
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
    env->SetByteArrayRegion(cpByteArray, 0, size, bytes);
    jbyte *jbyte1 = env->GetByteArrayElements(cpByteArray, JNI_FALSE);
    LOGE("cpByteArray:%s", jbyte1);
    env->ReleaseByteArrayElements(cpByteArray, jbyte1, JNI_COMMIT);
    LOGE("cpByteArray释放后:%s", jbyte1);
    JavaHelp *mJavaHelp = new JavaHelp(javaVm, env, instance);
    mJavaHelp->callState(cpByteArray);
    delete (mJavaHelp);
    mJavaHelp = 0;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_release(JNIEnv *env, jobject instance) {

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_callObj(JNIEnv *env, jobject instance, jobject use) {
    jclass useClazz = env->GetObjectClass(use);
    //获取use类里面的name
    jmethodID getNameMId = env->GetMethodID(useClazz, "getName", "()Ljava/lang/String;");
    jobject jobject1 = env->CallObjectMethod(use, getNameMId);
    jstring jstring1 = static_cast<jstring>(jobject1);
    const char *c = env->GetStringUTFChars(jstring1, 0);
    LOGE("callObj里面的Name:%s", c);
    jmethodID getAgeMID = env->GetMethodID(useClazz, "getAge", "()I");
    jint age = env->CallIntMethod(use, getAgeMID);
    LOGE("age的值为：%d", age);
    jmethodID getMoneyMid = env->GetMethodID(useClazz, "getMoney", "()F");
    jfloat money = env->CallFloatMethod(use, getMoneyMid);
    LOGE("money的值为：%f", money);
    jmethodID getDataMid = env->GetMethodID(useClazz, "getData", "()S");
    jshort data = env->CallShortMethod(use, getDataMid);
    LOGE("data的值：%d", data);
    jfieldID ageFid = env->GetFieldID(useClazz, "age", "I");
    jint ageField = env->GetIntField(use, ageFid);
    LOGE("ageField值：%d", ageField);
    jfieldID nameFieldId = env->GetFieldID(useClazz, "name", "Ljava/lang/String;");
    jobject nameFieldObj = env->GetObjectField(use, nameFieldId);
    jstring nameField = static_cast<jstring>(nameFieldObj);
    const char *name1 = env->GetStringUTFChars(nameField, JNI_FALSE);
    LOGE("name1的值是：%s", name1);
    env->DeleteLocalRef(useClazz);
    env->ReleaseStringUTFChars(jstring1, c);
}

void *pthreadTask(void *arg) {
    LOGE("pthreadTask:%s", "线程开始运行了");
    return 0;
};

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_createThread(JNIEnv *env, jobject instance) {
    pthread_t pthreadId;
    int pi = 100;
    pthread_create(&pthreadId, 0, pthreadTask, &pi);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_threadAsy(JNIEnv *env, jobject instance) {
    LOGE("threadAsy运行了");
    if (!videoTask) {
        videoTask = new VideoTask();
    } else {

        LOGE("已经有一个videoTask对象");
    }

//   delete(videoTask);
//   videoTask=0;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidata_JniManage_threadStop(JNIEnv *env, jobject instance) {
    LOGE("threadStop运行了");
    if (videoTask) {
        LOGE("videoTask不为空");
        delete (videoTask);
        videoTask = 0;
    } else {
        LOGE("videoTask为空");
    }
}

//C++：动态注册
void aa(JNIEnv *env, jobject instance) {
    LOGE("aa 动态注册");
}

jstring bb(JNIEnv *env, jobject instance, jint i) {
    LOGE("bb方法里面：%d", i);
    return env->NewStringUTF("我是动态注册的getString方法");
}

//需要动态注册的方法数组
static const JNINativeMethod mMethods[] = {
        {"getName",   "()V",                   (void *) aa},
        {"getString", "(I)Ljava/lang/String;", (jstring *) bb}
};

//需要动态注册native方法的类名
static const char *mClassName = "com/example/jnidata/NativeClass";

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGE("JNI_OnLoad");
    JNIEnv *env = NULL;
    //获得 JniEnv
    int r = vm->GetEnv((void **) &env, JNI_VERSION_1_4);
    if (r != JNI_OK) {
        LOGE("获取env失败");
        return -1;
    }
    LOGE("获取env成功");
    javaVm = vm;
    jclass mainActivityCls = env->FindClass(mClassName);
    // 注册 如果小于0则注册失败  sizeof(mMethods) / sizeof(JNINativeMethod)替换2也行
    r = env->RegisterNatives(mainActivityCls, mMethods, sizeof(mMethods) / sizeof(JNINativeMethod));
    if (r != JNI_OK) {
        LOGE("注册失败");
        return -1;
    }
    LOGE("注册成功");
    return JNI_VERSION_1_4;
}