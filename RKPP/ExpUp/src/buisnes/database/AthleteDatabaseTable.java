package buisnes.database;

import model.Athlete;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class AthleteDatabaseTable {
    private static final String TABLE_NAME = "athletes";
    private static final String getAllQueryTemplate = "select * from %s;";
    private static final String insertQueryTemplate = "insert into %s" +
            "(surname, name, middle_name, age, is_female) " +
            "values('%s', '%s', '%s', '%d', '%b');";
    private static final String updateQueryTemplate = "update %s set " +
            "surname = '%s', " +
            "name = '%s', " +
            "middle_name = '%s', " +
            "age = '%d', " +
            "is_female = '%b' " +
            "where id = '%d';";
    private static final String deleteQueryTemplate = "delete from %s where id = '%d'";


    public static List<Athlete> getAll() {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        List<Athlete> list = new ArrayList<>();

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, getAllQueryTemplate, TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            while (res.next()) {
                Athlete athlete = new Athlete(
                        res.getInt(1),
                        res.getString(2),
                        res.getString(3),
                        res.getString(4),
                        res.getInt(5),
                        res.getBoolean(6)
                );
                list.add(athlete);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void insert(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, insertQueryTemplate, TABLE_NAME, athlete.getSurName(), athlete.getName(),
                    athlete.getMiddleName(), athlete.getAge(), athlete.isFemale());

            statement.execute(query);

            query = String.format("select max(id) as id from %s;", TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            if (res.next()) {
                athlete.setId(res.getInt(1));
            }
            else {
                throw new RuntimeException("Invalid row insert!!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void update(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, updateQueryTemplate, TABLE_NAME, athlete.getSurName(), athlete.getName(),
                    athlete.getMiddleName(), athlete.getAge(), athlete.isFemale(), athlete.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void delete(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(deleteQueryTemplate, TABLE_NAME,  athlete.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
