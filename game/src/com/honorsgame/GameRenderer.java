package com.honorsgame;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.*;
import android.util.Log;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

public class GameRenderer implements GLSurfaceView.Renderer
{
    boolean initialized;
    long lastTime = -1;
    int width;
    int height;
    
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	initialized = false;
    }

    public void init(String host_ip) {
	if (host_ip == null) {
	    NativeGame.init(1, null);
	} else {
	    NativeGame.init(0, host_ip);
	}
	NativeGame.resize(width, height);
	initialized = true;
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
	width = w;
	height = h;
	if (initialized) {
	    NativeGame.resize(width, height);
	}
    }

    public void onDrawFrame(GL10 gl) {
	long currentTime = System.currentTimeMillis();
	if (lastTime > 0) {
	    float dt = (currentTime - lastTime) * 0.001f;
	    draw(gl, dt);
	}
	lastTime = currentTime;
    }

    protected void draw(GL10 gl, float dt) {
	gl.glMatrixMode(GL10.GL_PROJECTION);
	gl.glLoadIdentity();
	GLU.gluPerspective(gl, 45.0f, (float)width / height, 0.1f, 50);

	gl.glMatrixMode(GL10.GL_MODELVIEW);
	gl.glLoadIdentity();

	float playerx = NativeGame.playerx();
	float playery = NativeGame.playery();
	GLU.gluLookAt(gl, 0.5f * playerx, 0.5f * playery, 2.0f, 
		      playerx/4, playery/4, 0, 0, 1.0f, 0);

	NativeGame.render(dt);
    }
}
