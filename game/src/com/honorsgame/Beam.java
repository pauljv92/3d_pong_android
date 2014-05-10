package com.honorsgame;

import android.app.Activity;
import android.content.Intent;
import android.nfc.NdefMessage;
import android.nfc.NdefRecord;
import android.nfc.NfcAdapter;
import android.nfc.NfcAdapter.CreateNdefMessageCallback;
import android.nfc.NfcAdapter.OnNdefPushCompleteCallback;
import android.nfc.NfcEvent;
import android.os.Bundle;
import android.os.Parcelable;
import android.widget.TextView;
import android.widget.Toast;
import java.nio.charset.Charset;
import android.net.wifi.WifiManager;
import android.text.format.Formatter;
import android.util.Log;

public class Beam extends Activity implements CreateNdefMessageCallback, OnNdefPushCompleteCallback
{
    NfcAdapter mNfcAdapter;
    TextView textView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.beam);
        TextView textView = (TextView) findViewById(R.id.textView);
       
        mNfcAdapter = NfcAdapter.getDefaultAdapter(this);
        if (mNfcAdapter == null) {
            Toast.makeText(this, "NFC is not available", Toast.LENGTH_LONG).show();
            finish();
            return;
        }

        mNfcAdapter.setNdefPushMessageCallback(this, this);
	mNfcAdapter.setOnNdefPushCompleteCallback(this, this);
    }

    @Override
    public NdefMessage createNdefMessage(NfcEvent event) {
	WifiManager wm = (WifiManager) getSystemService(WIFI_SERVICE);
	String ip = Formatter.formatIpAddress(wm.getConnectionInfo().getIpAddress());

	NdefMessage msg = new NdefMessage(new NdefRecord[] 
	    { 
		NdefRecord.createMime("application/com.honorsgame.beam", ip.getBytes()),
		NdefRecord.createApplicationRecord("com.honorsgame")
	    });

	return msg;
    }

    @Override
    public void onNdefPushComplete(NfcEvent event) {
        textView = (TextView) findViewById(R.id.textView);
        textView.setText("sent that shit");
    }
    

    @Override
    public void onResume() 
	{
        super.onResume();

        // Check to see that the Activity started due to an Android Beam
        if (NfcAdapter.ACTION_NDEF_DISCOVERED.equals(getIntent().getAction())) {
            processIntent(getIntent());
        }
    }

    @Override
    public void onNewIntent(Intent intent) {
        // onResume gets called after this to handle the intent
        setIntent(intent);
    }

    /**
     * Parses the NDEF Message from the intent and prints to the TextView
     */
    void processIntent(Intent intent) {
	    
        Parcelable[] rawMsgs = intent.getParcelableArrayExtra(
	    NfcAdapter.EXTRA_NDEF_MESSAGES);
        // only one message sent during the beam
        NdefMessage msg = (NdefMessage) rawMsgs[0];
        // record 0 contains the MIME type, record 1 is the AAR, if present
        textView = (TextView) findViewById(R.id.textView);
        textView.setText(new String(msg.getRecords()[0].getPayload()));
    }
}
