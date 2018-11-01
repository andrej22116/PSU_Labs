package com.example.andrej.lr_3.beans;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.HashMap;

public class DatabaseHelper extends SQLiteOpenHelper {

    public DatabaseHelper(Context context) {
        super(context, "database", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table games (" +
                "id integer primary key autoincrement," +
                "name text not null);");


        ContentValues contentValues = new ContentValues();
        contentValues.put("name", "Left 4 dead");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Mass Effect");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Minecraft");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Terraria");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Read dead redemption");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Magicka");
        db.insert("games", null, contentValues);

        contentValues.put("name", "Grand theft auto");
        db.insert("games", null, contentValues);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
