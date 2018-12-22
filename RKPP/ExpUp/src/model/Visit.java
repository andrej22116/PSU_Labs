package model;

import java.sql.Date;
import java.sql.Time;

public class Visit {
    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public Time getTime() {
        return time;
    }

    public void setTime(Time time) {
        this.time = time;
    }

    public boolean isVisited() {
        return visited;
    }

    public void setVisited(boolean visited) {
        this.visited = visited;
    }

    public int getIdAthlete() {
        return idAthlete;
    }

    public void setIdAthlete(int idAthlete) {
        this.idAthlete = idAthlete;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Visit() {}

    public Visit(int id, int idAthlete, Date date, Time time, boolean visited) {
        this.id = id;
        this.idAthlete = idAthlete;
        this.date = date;
        this.time = time;
        this.visited = visited;
    }


    private int id;
    private int idAthlete;
    private Date date;
    private Time time;
    private boolean visited;
}
