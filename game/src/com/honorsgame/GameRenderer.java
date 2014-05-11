package com.honorsgame;

import android.app.Activity;
import android.content.Intent;
import android.content.*;
import android.os.Bundle;
import android.opengl.*;
import android.util.Log;
import android.widget.*;
import android.os.*;
import android.content.*;
import android.util.*;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

public class GameRenderer implements GLSurfaceView.Renderer
{
    public static int GAME_DEAD = 4734;

    Handler handler;
    long lastTime = -1;
    int width;
    int height;
    String ip;
    boolean died;

    public GameRenderer(Handler handler, String ip) {
	this.handler = handler;
	this.ip = ip;
	this.died = false;
    }
    
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
	NativeGame.init(ip);
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
	this.width = width;
	this.height = height;
	NativeGame.resize(width, height);
    }

    public void onDrawFrame(GL10 gl) {
	long currentTime = System.currentTimeMillis();
	if (lastTime > 0) {
	    float dt = (currentTime - lastTime) * 0.001f;
	    draw(gl, dt);
	}
	lastTime = currentTime;

	String death = NativeGame.death();
	if (death != null && !died) {
	    Message message = handler.obtainMessage(GAME_DEAD);
	    message.obj = death;
	    handler.sendMessage(message);
	    died = true;
	}
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
