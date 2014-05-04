package com.honorsgame;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

public class MainActivity extends Activity implements SensorEventListener
{
    private GLSurfaceView view;
    private SensorManager sensorManager;
    private Sensor accelerometer;

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	
	sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
	accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);

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
	sensorManager.unregisterListener(this);
    }

    @Override
    protected void onResume() {
	super.onResume();
	view.onResume();
	sensorManager.registerListener(this, accelerometer, 
				       SensorManager.SENSOR_DELAY_NORMAL);
    }

    public void onAccuracyChanged(Sensor sensor, int accuracy) {
	// ignore
    }

    public void onSensorChanged(SensorEvent event) {
//	Log.i("hgame", "sensor: " + event.values[0] + " " + event.values[1] + " " + event.values[2]);
	NativeGame.accelerometer(
	    event.values[0], event.values[1], event.values[2]);
    }
}
