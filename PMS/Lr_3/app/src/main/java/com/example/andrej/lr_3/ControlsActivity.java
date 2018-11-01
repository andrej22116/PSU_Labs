package com.example.andrej.lr_3;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

public class ControlsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controls);
    }

    public void onButtonClicked(View view) {
        Toast.makeText(this, "Кнопка нажата", Toast.LENGTH_SHORT).show();
    }

    public void onCheckboxClicked(View view) {
        if (((CheckBox) view).isChecked()) {
            Toast.makeText(this, "Чекбокс: Отмечено", Toast.LENGTH_SHORT).show();
        }
        else {
            Toast.makeText(this, "Чекбокс: Не отмечено", Toast.LENGTH_SHORT).show();
        }
    }

    public void onToggleClicked(View view) {
        if (((ToggleButton) view).isChecked()) {
            Toast.makeText(this, "Переключатель: Включено", Toast.LENGTH_SHORT).show();
        }
        else {
            Toast.makeText(this, "Переключатель: Выключено", Toast.LENGTH_SHORT).show();
        }
    }

    public void onRadioButtonClicked(View view) {
        RadioButton rb = (RadioButton) view;
        Toast.makeText(this, "Выбрано животное: " + rb.getText(),
                Toast.LENGTH_SHORT).show();
    }

    public void onClearText(View view) {
        TextView textView = findViewById(R.id.userText);
        textView.setText("");
    }
}
