package com.example.calljavamethodfromcexample;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		//When button is clicked, message is displayed
		Button btn = (Button) findViewById(R.id.btn);
		btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				CharSequence text = "JNI에서 TOAST 표시";
				displayToast(text);
			}
		});
	}

	public native void displayToast(CharSequence charseq);
	
	static {
		System.loadLibrary("jnitoast");
	}

}
