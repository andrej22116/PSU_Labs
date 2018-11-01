package com.example.andrej.lr_4;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final int SELECT_STATION_ACTIVITY_ID = 228;
    TextView tvSelectedStation;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvSelectedStation = findViewById(R.id.tvSelectedItem);
    }

    public void onSelectMetroStation(View view) {
        Intent intent = new Intent(this, MetroListActivity.class);
        startActivityForResult(intent, SELECT_STATION_ACTIVITY_ID);
    }

    public void onSelectMetroStationOther(View view) {
        Intent intent = new Intent();
        intent.setAction("android.intent.action.GET_STATION");
        startActivityForResult(intent, SELECT_STATION_ACTIVITY_ID);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case SELECT_STATION_ACTIVITY_ID: {
                if ( resultCode == Activity.RESULT_OK && data != null ) {
                    tvSelectedStation.setText(data.getStringExtra("station"));
                }
                else {
                    Toast.makeText(this,
                            "Станция метро не выбрана! Сохранён предыдущий выбор!",
                            Toast.LENGTH_SHORT).show();
                }
            } break;

            default: {
                Toast.makeText(this,
                        //"Станция метро не выбрана! Сохранён предыдущий выбор!",
                        "Неизвестное событие, лол.",
                        Toast.LENGTH_SHORT).show();
            } break;
        }
    }
}
