package model;

import java.sql.Date;

public class BodyCheck {
    public BodyCheck() {}

    public BodyCheck(int id, int idAthlete, Date fixationDate, boolean therapist, boolean surgeon,
                     boolean oculist, boolean endDoctor, boolean dopingTest, String conclusion) {
        this.id = id;
        this.idAthlete = idAthlete;
        this.fixationDate = fixationDate;
        this.therapist = therapist;
        this.surgeon = surgeon;
        this.oculist = oculist;
        this.endDoctor = endDoctor;
        this.dopingTest = dopingTest;
        this.conclusion = conclusion;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Date getFixationDate() {
        return fixationDate;
    }

    public void setFixationDate(Date fixationDate) {
        this.fixationDate = fixationDate;
    }

    public boolean isTherapist() {
        return therapist;
    }

    public void setTherapist(boolean therapist) {
        this.therapist = therapist;
    }

    public boolean isSurgeon() {
        return surgeon;
    }

    public void setSurgeon(boolean surgeon) {
        this.surgeon = surgeon;
    }

    public boolean isOculist() {
        return oculist;
    }

    public void setOculist(boolean oculist) {
        this.oculist = oculist;
    }

    public boolean isEndDoctor() {
        return endDoctor;
    }

    public void setEndDoctor(boolean endDoctor) {
        this.endDoctor = endDoctor;
    }

    public boolean isDopingTest() {
        return dopingTest;
    }

    public void setDopingTest(boolean dopingTest) {
        this.dopingTest = dopingTest;
    }

    public String getConclusion() {
        return conclusion;
    }

    public void setConclusion(String conclusion) {
        this.conclusion = conclusion;
    }

    public int getIdAthlete() {
        return idAthlete;
    }

    public void setIdAthlete(int idAthlete) {
        this.idAthlete = idAthlete;
    }

    private int id;
    private int idAthlete;
    private Date fixationDate;     // Дата прохождения
    private boolean therapist;          // Терапевт
    private boolean surgeon;            // Хирург
    private boolean oculist;            // Окулсит
    private boolean endDoctor;          // Лор
    private boolean dopingTest;         // Тест на допинг
    private String conclusion;          // Заключение
}
