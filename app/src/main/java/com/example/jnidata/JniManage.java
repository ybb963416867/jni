package com.example.jnidata;

import android.util.Log;

public class JniManage {

    static {
        System.loadLibrary("native-lib");
    }



    native  void  call();

    native  void  release();

    native  boolean   callBoolean(String string);

    native  void  callJavaMe(byte[] bytes);

    /**
     * @param bytes   jni 调用时不能有static
     */
    private  final   void  callState(byte[] bytes){
        Log.e("ybb",new String(bytes));
    }

}
