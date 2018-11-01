package com.example.andrej.lr_2;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import java.time.Instant;

public class FirstTaskActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_first_task);
    }

    public void closePage(View view) {
        Intent instant = new Intent(this, MainActivity.class);
        startActivity(instant);
    }

    public void nextPage(View view) {
        Intent instant = new Intent(this, SecondTaskActivity.class);
        startActivity(instant);
    }
}
