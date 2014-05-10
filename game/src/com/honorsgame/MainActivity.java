package com.honorsgame;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

public class MainActivity extends Activity
{
    private GLSurfaceView view;

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);

	view = new GLSurfaceView(this);
	view.setEGLContextClientVersion(1);
	view.setRenderer(new GameRenderer());
	view.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
	setContentView(view);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
	float x = e.getX();
	float y = e.getY();
	NativeGame.touch(x, y);
	return super.onTouchEvent(e);
    }

    @Override
    protected void onPause() {
	super.onPause();
	view.onPause();
    }

    @Override
    protected void onResume() {
	super.onResume();
	view.onResume();
    }
}
