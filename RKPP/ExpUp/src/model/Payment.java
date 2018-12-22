package model;

import java.sql.Timestamp;

public class Payment {
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getIdAthlete() {
        return idAthlete;
    }

    public void setIdAthlete(int idAthlete) {
        this.idAthlete = idAthlete;
    }

    public Timestamp getPaymentDate() {
        return paymentDate;
    }

    public void setPaymentDate(Timestamp paymentDate) {
        this.paymentDate = paymentDate;
    }

    public double getAmountOfPayment() {
        return amountOfPayment;
    }

    public void setAmountOfPayment(double amountOfPayment) {
        this.amountOfPayment = amountOfPayment;
    }

    public int getDays() {
        return days;
    }

    public void setDays(int days) {
        this.days = days;
    }

    private int id;
    private int idAthlete;
    private Timestamp paymentDate;
    private double amountOfPayment;
    private int days;

    public Payment() {}

    public Payment(int id, int idAthlete, Timestamp paymentDate, double amountOfPayment, int days) {
        this.id = id;
        this.idAthlete = idAthlete;
        this.paymentDate = paymentDate;
        this.amountOfPayment = amountOfPayment;
        this.days = days;
    }
}
