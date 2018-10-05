package sample.database;

import java.sql.Connection;

public class DataBaseController {
    private static DataBaseController ourInstance = new DataBaseController();

    public static DataBaseController getInstance() {
        return ourInstance;
    }

    Connection connection = PostgresDatabaseConnection.getConnection(
            "postgres",
            "andrej22116",
            "GameStore",
            "localhost",
            "5432"
            );

    private DataBaseController()
    {
    }

    /// BEGIN GAMES




    /// END GAMES
}
