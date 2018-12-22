package model;

import java.io.Serializable;
import java.sql.Date;

public class PhysicalCharacteristics implements Serializable {
    public float getMass() {
        return mass;
    }

    public void setMass(float mass) {
        this.mass = mass;
    }

    public float getBicepsGirth() {
        return bicepsGirth;
    }

    public void setBicepsGirth(float bicepsGirth) {
        this.bicepsGirth = bicepsGirth;
    }

    public float getChestGirth() {
        return chestGirth;
    }

    public void setChestGirth(float chestGirth) {
        this.chestGirth = chestGirth;
    }

    public float getWaistGirth() {
        return waistGirth;
    }

    public void setWaistGirth(float waistGirth) {
        this.waistGirth = waistGirth;
    }

    public float getLegGirth() {
        return legGirth;
    }

    public void setLegGirth(float legGirth) {
        this.legGirth = legGirth;
    }

    public float getWeightOnBiceps() {
        return weightOnBiceps;
    }

    public void setWeightOnBiceps(float weightOnBiceps) {
        this.weightOnBiceps = weightOnBiceps;
    }

    public float getWeightOnChest() {
        return weightOnChest;
    }

    public void setWeightOnChest(float weightOnChest) {
        this.weightOnChest = weightOnChest;
    }

    public float getWeightOnFoot() {
        return weightOnFoot;
    }

    public void setWeightOnFoot(float weightOnFoot) {
        this.weightOnFoot = weightOnFoot;
    }

    public float getWeightOnBack() {
        return weightOnBack;
    }

    public void setWeightOnBack(float weightOnBack) {
        this.weightOnBack = weightOnBack;
    }

    public float getBackWidth() {
        return backWidth;
    }

    public void setBackWidth(float backWidth) {
        this.backWidth = backWidth;
    }

    public float getMassAndFatRatio() {
        return massAndFatRatio;
    }

    public void setMassAndFatRatio(float massAndFatRatio) {
        this.massAndFatRatio = massAndFatRatio;
    }

    public Date getFixationDate() {
        return fixationDate;
    }

    public void setFixationDate(Date fixationDate) {
        this.fixationDate = fixationDate;
    }

    public int getIdAthlete() {
        return idAthlete;
    }

    public void setIdAthlete(int idAthlet) {
        this.idAthlete = idAthlet;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    private int id;

    private int idAthlete;

    private float mass;

    private float bicepsGirth;  // Обхват бицепса
    private float chestGirth;   // Обхват груди
    private float waistGirth;   // Обхват талии
    private float legGirth;     // Обхват ноги

    private float weightOnBiceps;   // Вес на бицепс
    private float weightOnChest;    // Вес на грудь
    private float weightOnFoot;     // Вес на ноги
    private float weightOnBack;     // Вес на спину

    private float backWidth;            // Ширина спины
    private float massAndFatRatio;      // Соотношение жира и массы ( МассаЖира / Масса )
    private Date fixationDate;     // Дата фиксации

    public PhysicalCharacteristics() {}

    public PhysicalCharacteristics(int id, int idAthlete, float mass, float bicepsGirth, float chestGirth, float waistGirth,
                                   float legGirth, float weightOnBiceps, float weightOnChest, float weightOnFoot,
                                   float weightOnBack, float backWidth, float massAndFatRatio, Date fixationDate) {
        this.id = id;
        this.idAthlete = idAthlete;
        this.mass = mass;
        this.bicepsGirth = bicepsGirth;
        this.chestGirth = chestGirth;
        this.waistGirth = waistGirth;
        this.legGirth = legGirth;
        this.weightOnBiceps = weightOnBiceps;
        this.weightOnChest = weightOnChest;
        this.weightOnFoot = weightOnFoot;
        this.weightOnBack = weightOnBack;
        this.backWidth = backWidth;
        this.massAndFatRatio = massAndFatRatio;
        this.fixationDate = fixationDate;
    }
}
