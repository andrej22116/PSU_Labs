package sample.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class PostgresDatabaseConnection{
    public static Connection getConnection(String login, String password, String db_name,
                                                 String db_addres, String db_port)
    {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            System.err.println("PostgreSQL JDBC Driver is not found. Include it in your library path ");
            return null;
        }

        Connection connection = null;
        String url = "jdbc:postgresql://" + db_addres + ":" + db_port + "/" + db_name;
        try {
            connection = DriverManager.getConnection(url, login, password);

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
