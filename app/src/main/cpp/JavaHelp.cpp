//
// Created by hachiadmin on 2019/6/13.
//


#include "JavaHelp.h"

JavaHelp::JavaHelp(JavaVM *vm, JNIEnv *env, jobject instance) {
    this->vm = vm;
    this->env = env;
    //注意由于instance 是jobject类型不是指针所以这个方法执行完这个变量就没有了，但是现在想要间这个作为全局变量所以需要用到NewGlobalRef
    this->instance = env->NewGlobalRef(instance);
}

JavaHelp::~JavaHelp() {
    //创建完注意释放这个对象
    env->DeleteGlobalRef(instance);
}

void JavaHelp::callState(jbyteArray bytes) {
    jclass zls = env->GetObjectClass(instance);
    jmethodID callStateId = env->GetMethodID(zls, "callState", "([B)V");
    env->CallVoidMethod(instance, callStateId, bytes);

}

