package com.example.jnidata;

import android.util.Log;

import com.example.jnidata.bean.Use;

public class JniManage {

    static {
        System.loadLibrary("native-lib");
    }



    native  void  call();

    native  void  release();

    native  boolean   callBoolean(String string);

    native  void  callJavaMe(byte[] bytes);

    native  void  callObj(Use  use);

    /**
     * @param bytes   jni 调用时不能有static
     */
    private  final   void  callState(byte[] bytes){
        Log.e("ybb",new String(bytes));
    }

    native void  createThread();

    native void  threadAsy();

    native void  threadStop();

//    native void  threadThreadCallBack();

}
