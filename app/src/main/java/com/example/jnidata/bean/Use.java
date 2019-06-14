package com.example.jnidata.bean;

import android.util.Log;

public class Use {
    private  String  name;
    private  int   age;
    private  float  money;
    private  short  data;

    public Use(String name, int age, float money, short data) {
        this.name = name;
        this.age = age;
        this.money = money;
        this.data = data;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public float getMoney() {
        return money;
    }

    public void setMoney(float money) {
        this.money = money;
    }

    public short getData() {
        return data;
    }

    public void setData(short data) {
        this.data = data;
    }

    public  static  void  callUs(){
        Log.e("ybb","调用了静态方法");

    }

    @Override
    public String toString() {
        return "Use{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", money=" + money +
                ", data=" + data +
                '}';
    }
}
