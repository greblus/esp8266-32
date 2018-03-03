package com.test.greblus.button;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {

    boolean on = true;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }
    public void onClick(View v) {
        final URL url;
        try {
            if (on)
                url = new URL("http://10.0.1.60/gpio/0");
            else
                url = new URL("http://10.0.1.60/gpio/1");
            on = !on;

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
            Toast toast = Toast.makeText(MainActivity.this, "ON/OFF sent!", Toast.LENGTH_SHORT);
            toast.show();
        } catch (IOException ex) {}
    }

    public void setTimer(View v) {
        final URL url;
        try {
            EditText etxt = findViewById(R.id.timeout);
            url = new URL("http://10.0.1.60/timer/"+etxt.getText()+"&");

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
            Toast toast = Toast.makeText(MainActivity.this, "Timer set!", Toast.LENGTH_SHORT);
            toast.show();
        } catch (IOException ex) {}
    }
}
