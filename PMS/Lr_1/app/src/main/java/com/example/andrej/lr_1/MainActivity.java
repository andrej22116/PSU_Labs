package com.example.andrej.lr_1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toast.makeText(this, "onCreate()", Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPause() {
        Toast.makeText(this, "onPause()", Toast.LENGTH_LONG).show();
        super.onPause();
    }

    @Override
    protected void onRestart() {
        Toast.makeText(this, "onRestart()", Toast.LENGTH_LONG).show();
        super.onRestart();
    }

    @Override
    protected void onStart() {
        Toast.makeText(this, "onStart()", Toast.LENGTH_LONG).show();
        super.onStart();
    }
}
