package sample.database;

public class DataBaseController {
    private static DataBaseController ourInstance = new DataBaseController();

    public static DataBaseController getInstance() {
        return ourInstance;
    }

    private DataBaseController() {
    }
}
