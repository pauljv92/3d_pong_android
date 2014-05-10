package com.honorsgame;

public class NativeGame {
    static {
	System.loadLibrary("game");
    }
    public static native void init(int is_host, String host_ip);
    public static native void resize(int width, int height);
    public static native void touch(float x, float y);
    public static native void accelerometer(float x, float y, float z);
    public static native void render(float dt);
    public static native float playerx();
    public static native float playery();
}
