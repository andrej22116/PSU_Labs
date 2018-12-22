package model;

import java.io.Serializable;

public class Athlete implements Serializable {
    public String getSurName() {
        return surName;
    }

    public void setSurName(String surName) {
        this.surName = surName;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMiddleName() {
        return middleName;
    }

    public void setMiddleName(String middleName) {
        this.middleName = middleName;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public boolean isFemale() {
        return isFemale;
    }

    public void setFemale(boolean female) {
        isFemale = female;
    }

    public String isFemaleString() {
        return isFemale ? "Дефка" : "Мужыг";
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    private String surName;
    private String name;
    private String middleName;

    int age;
    boolean isFemale;

    int id;

    public Athlete() {}

    public Athlete(int id, String surName, String name, String middleName, int age, boolean isFemale) {
        this.id = id;
        this.surName = surName;
        this.name = name;
        this.middleName = middleName;
        this.age = age;
        this.isFemale = isFemale;
    }
}
