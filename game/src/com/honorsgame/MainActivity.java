package com.honorsgame;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.os.Parcelable;

public class MainActivity extends Activity
{
    private GLSurfaceView view;
    private GameRenderer renderer;

    @Override
    public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);

	renderer = new GameRenderer();
	view = new GLSurfaceView(this);
	view.setEGLContextClientVersion(1);
	view.setRenderer(renderer);
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

	if (!renderer.initialized) {
	    Intent intent = getIntent();

	    // Host Intent
	    // todo

	    // Client Intent
	    if (NfcAdapter.ACTION_NDEF_DISCOVERED.equals(
		    intent.getAction())) {
		Parcelable[] rawMsgs = intent.getParcelableArrayExtra(
		    NfcAdapter.EXTRA_NDEF_MESSAGES);
		NdefMessage msg = (NdefMessage) rawMsgs[0];
		String ip = new String(msg.getRecords()[0].getPayload());
		Log.i("honorsgame", "received ip of " + ip);
		renderer.init(ip);
	    }
	}

	view.onResume();
    }

    @Override
    public void onNewIntent(Intent intent) {
        // onResume gets called after this to handle the intent
        setIntent(intent);
    }
}
