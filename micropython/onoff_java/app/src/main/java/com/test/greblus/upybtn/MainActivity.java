package com.test.greblus.upybtn;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;
import android.widget.SeekBar;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {
    static int prev_val = 90;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final SeekBar pb = findViewById(R.id.seekBar);
        pb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                EditText e = findViewById(R.id.timeout);
                int v = Integer.valueOf(e.getText().toString()) + i-prev_val;
                if (v <= 0 || pb.getProgress() == 0)
                    v = 0;
                prev_val = i;
                long t = Math.round(v/5.0)*5;
                e.setText(String.valueOf(t));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

    }
    public void onClick(View v) {
        final URL url;
        try {
                url = new URL("http://10.0.1.60:8000/onoff");

            Thread thread = new Thread() {
                @Override
                public void run() {
                    HttpURLConnection urlConnection = null;
                    try {
                        urlConnection = (HttpURLConnection) url.openConnection();
                        InputStream in = new BufferedInputStream(urlConnection.getInputStream());
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                    finally {
                        urlConnection.disconnect();
                    }
                }
            };

            thread.start();
            Toast toast = Toast.makeText(MainActivity.this, "ON/OFF wysłane!", Toast.LENGTH_SHORT);
            toast.show();
        } catch (IOException ex) {}
    }

    public void setTimer(View v) {
        final URL url;
        try {
            EditText etxt = findViewById(R.id.timeout);
            url = new URL("http://10.0.1.60:8000/sleep="+etxt.getText());
            Thread thread = new Thread() {
                @Override
                public void run() {
                    HttpURLConnection urlConnection = null;
                    try {
                        urlConnection = (HttpURLConnection) url.openConnection();
                        InputStream in = new BufferedInputStream(urlConnection.getInputStream());
                    }
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                    finally {
                        urlConnection.disconnect();
                    }
                }
            };

            thread.start();
            Toast toast = Toast.makeText(MainActivity.this, "Timer ustawiony!", Toast.LENGTH_SHORT);
            toast.show();
        } catch (IOException ex) {}
    }
}
