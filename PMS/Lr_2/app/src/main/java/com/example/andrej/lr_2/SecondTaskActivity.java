package com.example.andrej.lr_2;

import android.app.Application;
import android.content.Context;
import android.content.res.Resources;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TabHost;
import android.widget.TextView;
import android.widget.Toast;

public class SecondTaskActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second_task);

        initTabWidget();
        initWebView();
        initListView();
    }

    private void initTabWidget()
    {
        TabHost tabHost = findViewById(android.R.id.tabhost);
        tabHost.setup();

        TabHost.TabSpec tabSpec = tabHost.newTabSpec("tab1");
        tabSpec.setIndicator("Веб контент");
        tabSpec.setContent(R.id.tab1);
        tabHost.addTab(tabSpec);

        tabSpec = tabHost.newTabSpec("tab2");
        tabSpec.setIndicator("Список");
        tabSpec.setContent(R.id.listView);
        tabHost.addTab(tabSpec);
    }

    private void initWebView()
    {
        WebView webView = findViewById(R.id.webView);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.loadUrl("https://www.psu.by/faculty/fit");
    }

    private void initListView()
    {
        Resources r = getResources();

        String[] stationsArray = r.getStringArray(R.array.stations);
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<String>(this,
                R.layout.list_item,
                stationsArray);

        ListView listView = findViewById(R.id.listView);
        listView.setAdapter(arrayAdapter);

        listView.setOnItemClickListener( (parent, view, position, id) -> {
            CharSequence text = ((TextView) view).getText();
            Context context = getApplicationContext();
            Toast.makeText(context, text, Toast.LENGTH_SHORT).show();
        });
    }
}
