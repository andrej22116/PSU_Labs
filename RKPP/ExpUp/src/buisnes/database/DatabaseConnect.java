package buisnes.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnect {
    private static Connection connection = null;

    private DatabaseConnect() {}

    public static Connection getConnection() {
        if ( connection != null ) {
            return connection;
        }

        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            System.err.println("PostgreSQL JDBC Driver is not found. Include it in your library path ");
            return null;
        }

        String url = "jdbc:postgresql://127.0.0.1:5432/rkpp";
        try {
            connection = DriverManager.getConnection(url, "postgres", "andrej22116");

        } catch (SQLException e) {
            System.out.println("Connection Failed");
            e.printStackTrace();
            return null;
        }

        if (connection == null) {
            System.err.println("Failed to make connection to database");
        }

        return connection;
    }
}
