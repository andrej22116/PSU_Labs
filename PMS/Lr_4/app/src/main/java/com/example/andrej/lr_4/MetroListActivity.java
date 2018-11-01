package com.example.andrej.lr_4;

import android.app.ListActivity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MetroListActivity extends ListActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_metro_list);

        String[] listOfMetroStations =  getResources().getStringArray(R.array.stations);
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1,
                listOfMetroStations);
        setListAdapter(arrayAdapter);

        ListView listView = findViewById(android.R.id.list);
        listView.setOnItemClickListener( (parent, view, position, id) -> {
            TextView tvSelected = (TextView) view;
            Intent intent = new Intent();
            intent.putExtra("station", tvSelected.getText().toString());
            setResult(RESULT_OK, intent);
            finish();
        });
    }

    public void onClick(View view) {
        Toast.makeText(this, ((TextView) view).getText(), Toast.LENGTH_SHORT).show();
    }
}
