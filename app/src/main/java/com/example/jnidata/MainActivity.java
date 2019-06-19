package com.example.jnidata;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.example.jnidata.bean.Use;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private String TAG = "MainActivity";
    private JniManage jniManage;
    private NativeClass nativeClass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.call).setOnClickListener(this);
        findViewById(R.id.callObj).setOnClickListener(this);
        findViewById(R.id.thread).setOnClickListener(this);
        findViewById(R.id.threadAsy).setOnClickListener(this);
        findViewById(R.id.threadStop).setOnClickListener(this);
        findViewById(R.id.btn_register).setOnClickListener(this);
        jniManage = new JniManage();
        nativeClass = new NativeClass();
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.call:
                jniManage.call();
                boolean abc = jniManage.callBoolean("abc");
                Log.e(TAG, abc + "");
                String var1 = "中华人民共和国";
                byte[] bytes = var1.getBytes();
                jniManage.callJavaMe(bytes);
                break;

            case R.id.callObj:
                Use ybb = new Use("ybb", 30, 333, (short) 1);
                jniManage.callObj(ybb);
                break;

            case R.id.thread:
                jniManage.createThread();
                break;

            case R.id.threadAsy:
                jniManage.threadAsy();
                break;
            case R.id.threadStop:
                new  Thread(new Runnable() {
                    @Override
                    public void run() {
                        jniManage.threadStop();
                    }
                }).start();
                break;
            case R.id.btn_register:
                nativeClass.getName();
                nativeClass.getString(5);
                break;
        }
    }
}
