package buisnes.database;

import model.Athlete;
import model.BodyCheck;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class BodyCheckDatabaseTable {
    private static final String TABLE_NAME = "body_checks";
    private static final String getAllQueryTemplate = "select * from %s where id_athlete = %d;";
    private static final String insertQueryTemplate = "insert into %s" +
            "(id_athlete, fixation_date, therapist, surgeon, oculist, endDoctor, dopingTest, conclusion) " +
            "values('%d', '%s', '%b', '%b', '%b', '%b', '%b', '%s');";
    private static final String updateQueryTemplate = "update %s set " +
            "fixation_date = '%s', " +
            "therapist = '%b', " +
            "surgeon = '%b', " +
            "oculist = '%b', " +
            "endDoctor = '%b', " +
            "dopingTest = '%b', " +
            "conclusion = '%s' " +
            "where id = '%d';";
    private static final String deleteQueryTemplate = "delete from %s where id = '%d'";


    public static List<BodyCheck> getAll(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        List<BodyCheck> list = new ArrayList<>();

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, getAllQueryTemplate, TABLE_NAME, athlete.getId());
            ResultSet res = statement.executeQuery(query);
            while (res.next()) {
                BodyCheck bodyCheck = new BodyCheck(
                        res.getInt(1),
                        res.getInt(2),
                        res.getDate(3),
                        res.getBoolean(4),
                        res.getBoolean(5),
                        res.getBoolean(6),
                        res.getBoolean(7),
                        res.getBoolean(8),
                        res.getString(9)
                );
                list.add(bodyCheck);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void insert(BodyCheck bodyCheck) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, insertQueryTemplate, TABLE_NAME, bodyCheck.getIdAthlete(),
                    bodyCheck.getFixationDate(), bodyCheck.isTherapist(), bodyCheck.isSurgeon(), bodyCheck.isOculist(),
                    bodyCheck.isEndDoctor(), bodyCheck.isDopingTest(), bodyCheck.getConclusion());

            statement.execute(query);

            query = String.format("select max(id) as id from %s;", TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            if (res.next()) {
                bodyCheck.setId(res.getInt(1));
            }
            else {
                throw new RuntimeException("Invalid row insert!!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void update(BodyCheck bodyCheck) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, updateQueryTemplate, TABLE_NAME,
                    bodyCheck.getFixationDate(), bodyCheck.isTherapist(), bodyCheck.isSurgeon(), bodyCheck.isOculist(),
                    bodyCheck.isEndDoctor(), bodyCheck.isDopingTest(), bodyCheck.getConclusion(), bodyCheck.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void delete(BodyCheck bodyCheck) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(deleteQueryTemplate, TABLE_NAME,  bodyCheck.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
