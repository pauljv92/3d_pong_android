package com.honorsgame;

import android.app.Activity;
import android.content.Intent;
import android.nfc.*;
import android.nfc.NfcAdapter.*;
import android.os.*;
import android.content.*;
import android.widget.*;
import android.util.*;
import java.nio.charset.Charset;
import android.net.wifi.WifiManager;
import android.text.format.Formatter;

public class Beam extends Activity implements CreateNdefMessageCallback, 
				   OnNdefPushCompleteCallback,
				   Handler.Callback
{
    final int MESSAGE_SENT = 69;
    final int MESSAGE_RECEIVED = 96;

    TextView textView;
    NfcAdapter nfcAdapter;
    Handler handler;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

	// Set up UI
        setContentView(R.layout.beam);
        textView = (TextView)findViewById(R.id.textView);
       
	// Set up NFC
        nfcAdapter = NfcAdapter.getDefaultAdapter(this);
        if (nfcAdapter == null) {
            Toast.makeText(this, "NFC is not available", 
			   Toast.LENGTH_LONG).show();
            finish();
            return;
        }
        nfcAdapter.setNdefPushMessageCallback(this, this);
	nfcAdapter.setOnNdefPushCompleteCallback(this, this);

	// Set up message handler
	handler = new Handler(Looper.getMainLooper(), this);
    }

    public void startGame(String ip) {
	Intent intent = new Intent();
	intent.putExtra("ip", ip);
	intent.setComponent(
	    new ComponentName("com.honorsgame",
			      "com.honorsgame.MainActivity"));
	startActivity(intent);
    }
    
    @Override
    public boolean handleMessage(Message message) {
	switch (message.what) {
	case MESSAGE_SENT:
	    startGame(null);
	case MESSAGE_RECEIVED:
	    startGame((String) message.obj);
	}
	return true;
    }

    String getIPAddress() {
	WifiManager wm = (WifiManager) getSystemService(WIFI_SERVICE);
	return Formatter.formatIpAddress(
	    wm.getConnectionInfo().getIpAddress());
    }

    @Override
    public NdefMessage createNdefMessage(NfcEvent event) {
	NdefMessage msg = new NdefMessage(
	    new NdefRecord[] {
		NdefRecord.createMime("application/com.honorsgame.beam", 
				      getIPAddress().getBytes()),
		NdefRecord.createApplicationRecord("com.honorsgame")
	    });
	return msg;
    }

    @Override
    public void onNdefPushComplete(NfcEvent event) {
	handler.sendEmptyMessage(MESSAGE_SENT);
    }

    public String getNdefString(Intent intent) {
        Parcelable[] rawMsgs = intent.getParcelableArrayExtra(
	    NfcAdapter.EXTRA_NDEF_MESSAGES);
        NdefMessage msg = (NdefMessage) rawMsgs[0];
	return new String(msg.getRecords()[0].getPayload());
    }

    @Override
    public void onNewIntent(Intent intent) {
        setIntent(intent);
    }

    @Override
    public void onResume() {
	super.onResume();

	Intent intent = getIntent();
	if (NfcAdapter.ACTION_NDEF_DISCOVERED.equals(intent.getAction())) {

	    Message message = handler.obtainMessage(MESSAGE_RECEIVED);
	    message.obj = getNdefString(intent);
	    handler.sendMessage(message);
	}
    }
}
