package com.example.andrej.lr_3.beans;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class DatabaseController {
    private static final String TABLE_NAME = "games";

    DatabaseHelper databaseHelper;
    SQLiteDatabase database;
    ContentValues contentValues = new ContentValues();

    public DatabaseController(Context context) {
        databaseHelper = new DatabaseHelper(context);
        database = databaseHelper.getWritableDatabase();
    }

    public Cursor getAllGames()
    {
        return database.query(true,
                TABLE_NAME,
                new String[]{"name"},
                null,
                null,
                null,
                null,
                null,
                null
        );
    }

    public String[] getAllGamesStr()
    {
        Cursor cursor = getAllGames();

        String[] array = new String[cursor.getCount()];
        if ( !cursor.moveToFirst() ) {
            return array;
        }

        int i = 0;
        int columnIndex = cursor.getColumnIndex("name");
        do {
            array[i] = cursor.getString(columnIndex);
            i++;
        } while ( cursor.moveToNext() );

        return array;
    }

    public int getElementIndex(String elementName)
    {
        Cursor cursor = database.query(true,
                TABLE_NAME,
                new String[]{"id"},
                "name = ?",
                new String[] { elementName },
                null,
                null,
                "id",
                "1"
        );

        int columnIndex = cursor.getColumnIndex("id");
        if ( cursor.moveToFirst() ) {
            return cursor.getInt(columnIndex);
        }
        else {
            return -1;
        }
    }

    public long insertNewElement(String elementName)
    {
        contentValues.put("name", elementName);
        return database.insert(TABLE_NAME, null, contentValues);
    }

    public int removeElement(String elementName)
    {
        return database.delete(TABLE_NAME,
                "name = ?",
                new String[] { elementName }
                );
    }

    public int removeElement(int elementId)
    {
        return database.delete(TABLE_NAME,
                "id = ?",
                new String[] { "" + elementId }
        );
    }
}
