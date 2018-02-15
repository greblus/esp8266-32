package com.test.greblus.button;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {

    boolean on = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }
    public void onClick(View v) {
        final URL url;
        Button button = findViewById(R.id.button);
        try {
            if (on) {
                url = new URL("http://192.168.1.7/gpio/0");
                button.setText(R.string.but_off);
            }
            else
                {
                url = new URL("http://192.168.1.7/gpio/1");
                button.setText(R.string.but_on);
            }
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
            Toast toast = Toast.makeText(MainActivity.this, "Wysłano!", Toast.LENGTH_SHORT);
            toast.show();
        } catch (IOException ex) {}
    }
}
