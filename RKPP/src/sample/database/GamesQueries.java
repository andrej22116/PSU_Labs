package sample.database;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class GamesQueries {
    private static GamesQueries ourInstance = new GamesQueries();

    public static GamesQueries getInstance() {
        return ourInstance;
    }

    private static Statement listOfGamesStatement = null;

    private GamesQueries() {
    }

    public static void init() {
        try {
            listOfGamesStatement = DataBaseController.getInstance()
                    .connection.createStatement();
        } catch (Exception e) {
            e.printStackTrace();
            listOfGamesStatement = null;
        }
    }

    public static ResultSet getListOfGames() {
        return getListOfGames(0, Integer.MAX_VALUE);
    }

    public static ResultSet getListOfGames(int offset, int amount) {
        try {
            return listOfGamesStatement.executeQuery("select * from public.getgameslistwithauthors(" +
                    offset + "," + amount + ");");
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return null;
    }


    private final static String getGamesListWithDevelopersQuery =
            "select * from public.getgameslistwithauthors(?, ?);";
}
