package com.example.andrej.lr_3;

import android.app.ListActivity;
import android.database.Cursor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.example.andrej.lr_3.beans.DatabaseController;

public class DatabaseActivity extends ListActivity {

    ArrayAdapter<String> adapter;
    DatabaseController dbController;
    TextView newElementNameTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_database);

        dbController = new DatabaseController(this);
        updateList();

        newElementNameTextView = findViewById(R.id.newGameName);
        ListView listView = findViewById(android.R.id.list);
        registerForContextMenu(listView);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        super.onListItemClick(l, v, position, id);

        String elementName = (String) ((TextView) v).getText();
        Toast.makeText(this,
                "" + dbController.getElementIndex(elementName),
                Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        if ( v.getId() != android.R.id.list ) {
            return;
        }
        menu.add(1, 1, Menu.NONE, "Удалить");
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        if ( item.getItemId() == 1 ) {
            AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();
            String gameName = adapter.getItem(info.position);
            dbController.removeElement(gameName);

            Toast.makeText(this, "Игра \"" + gameName + "\" удалена!",
                    Toast.LENGTH_SHORT).show();
            updateList();

            return true;
        }
        else {
            return super.onContextItemSelected(item);
        }
    }

    public void addNewGame(View view) {
        dbController.insertNewElement(newElementNameTextView.getText().toString());
        newElementNameTextView.setText("");
        updateList();
    }

    private void updateList()
    {
        adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1,
                dbController.getAllGamesStr());
        setListAdapter(adapter);
    }
}
