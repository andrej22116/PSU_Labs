package buisnes.database;

import model.Athlete;
import model.Visit;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class VisitsDatabaseTable {
    private static final String TABLE_NAME = "visits";
    private static final String getAllQueryTemplate = "select * from %s where id_athlete = %d;";
    private static final String insertQueryTemplate = "insert into %s" +
            "(id_athlete, visit_date, visit_time, visited) " +
            "values('%d', '%s', '%s', '%b');";
    private static final String updateQueryTemplate = "update %s set " +
            "visit_date = '%s', " +
            "visit_time = '%s', " +
            "visited = '%b' " +
            "where id = '%d';";
    private static final String deleteQueryTemplate = "delete from %s where id = '%d'";


    public static List<Visit> getAll(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        List<Visit> list = new ArrayList<>();

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(getAllQueryTemplate, TABLE_NAME, athlete.getId());
            ResultSet res = statement.executeQuery(query);
            while (res.next()) {
                Visit visit = new Visit(
                        res.getInt(1),
                        res.getInt(2),
                        res.getDate(3),
                        res.getTime(4),
                        res.getBoolean(5)
                );
                list.add(visit);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void insert(Visit visit) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, insertQueryTemplate, TABLE_NAME, visit.getIdAthlete(), visit.getDate(),
                    visit.getTime(), visit.isVisited());

            statement.execute(query);

            query = String.format("select max(id) as id from %s;", TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            if (res.next()) {
                visit.setId(res.getInt(1));
            }
            else {
                throw new RuntimeException("Invalid row insert!!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void update(Visit visit) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, updateQueryTemplate, TABLE_NAME, visit.getDate(),
                    visit.getTime(), visit.isVisited(), visit.getId());

            statement.execute(query);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void delete(Visit visit) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, deleteQueryTemplate, TABLE_NAME,  visit.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
