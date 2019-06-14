//
// Created by hachiadmin on 2019/6/13.
//
#ifndef JNI_JAVAHELP_H
#define JNI_JAVAHELP_H

#include <jni.h>

class JavaHelp {
public:
    //构造方法
    JavaHelp(JavaVM *vm, JNIEnv *env, jobject instance);

    void callState(jbyteArray bytes);

    //析构方法用来释放内存
    ~JavaHelp();

private :
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;

};

#endif
