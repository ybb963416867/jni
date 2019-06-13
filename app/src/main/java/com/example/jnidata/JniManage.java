package com.example.jnidata;

public class JniManage {

    static {
        System.loadLibrary("native-lib");
    }



    native  void  call();

    native  boolean   callBoolean(String string);
}
