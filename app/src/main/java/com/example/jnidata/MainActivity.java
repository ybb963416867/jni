package com.example.jnidata;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private  String  TAG="MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.call).setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.call:
                JniManage jniManage = new JniManage();
                jniManage.call();
                boolean abc = jniManage.callBoolean("abc");
                Log.e(TAG,abc+"");
                String   var1="中华人民共和国";
                byte[] bytes = var1.getBytes();
                jniManage.callJavaMe(bytes);
                break;
        }
    }
}
