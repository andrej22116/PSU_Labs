package sample.database;

import sample.views.beans.Cupcake;
import sample.views.beans.Ingredient;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.List;
import java.util.ArrayList;
import java.util.Locale;

public class DataBaseController {
    private static DataBaseController ourInstance = new DataBaseController();

    public static DataBaseController getInstance() {
        return ourInstance;
    }

    private Connection connection = PostgresDatabaseConnection.getConnection(
            "postgres",
            "andrej22116",
            "rkpp",
            "localhost",
            "5432"
            );

    private DataBaseController()
    {
    }


    private static final String TABLE_CUPCAKE = "cupcake";
    private static final String TABLE_STUFFING = "stuffing";
    private static final String TABLE_DIMENSIONS = "dimensions";
    private static final String TABLE_PASTRY = "pastry";
    private static final String TABLE_TOPPING = "topping";


    public List<Ingredient> getAllStuffing() {
        return getIngredient(TABLE_STUFFING);
    }

    public List<Ingredient> getAllDimensions() {
        return getIngredient(TABLE_DIMENSIONS);
    }

    public List<Ingredient> getAllPastry() {
        return getIngredient(TABLE_PASTRY);
    }

    public List<Ingredient> getAllTopping() {
        return getIngredient(TABLE_TOPPING);
    }

    private List<Ingredient> getIngredient(String tableName) {
        List<Ingredient> ingredients = new ArrayList<>();

        try {
            Statement statement = connection.createStatement();
            ResultSet queryRes = statement.executeQuery("select name, calories from " + tableName + ";");

            while (queryRes.next()) {
                ingredients.add(new Ingredient(queryRes.getString(1), queryRes.getFloat(2)));
            }
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }

        return ingredients;
    }


    public void addNewStuffing(String name, float calories) throws SQLException {
        addNewIngredient(TABLE_STUFFING, name, calories);
    }
    public void updateOldStuffing(String oldName, String newName, float calories) throws SQLException {
        updateOldIngredient(TABLE_STUFFING, oldName,  newName, calories);
    }
    public void deleteStuffing(String name) {
        deleteIngredient(TABLE_STUFFING, name);
    }

    public void addNewDimensions(String name, float calories) throws SQLException {
        addNewIngredient(TABLE_DIMENSIONS, name, calories);
    }
    public void updateOldDimensions(String oldName, String newName, float calories) throws SQLException {
        updateOldIngredient(TABLE_DIMENSIONS, oldName,  newName, calories);
    }
    public void deleteDimensions(String name) {
        deleteIngredient(TABLE_DIMENSIONS, name);
    }

    public void addNewPastry(String name, float calories) throws SQLException {
        addNewIngredient(TABLE_PASTRY, name, calories);
    }
    public void updateOldPastry(String oldName, String newName, float calories) throws SQLException {
        updateOldIngredient(TABLE_PASTRY, oldName,  newName, calories);
    }
    public void deletePastry(String name) {
        deleteIngredient(TABLE_PASTRY, name);
    }

    public void addNewTopping(String name, float calories) throws SQLException {
        addNewIngredient(TABLE_TOPPING, name, calories);
    }
    public void updateOldTopping(String oldName, String newName, float calories) throws SQLException {
        updateOldIngredient(TABLE_TOPPING, oldName,  newName, calories);
    }
    public void deleteTopping(String name) {
        deleteIngredient(TABLE_TOPPING, name);
    }

    private void addNewIngredient(String table, String name, float calories) throws SQLException {
        Statement statement = connection.createStatement();
        statement.execute(String.format(Locale.US, "insert into %s (name, calories) values('%s', '%f');",
                table, name, calories));
    }
    private void updateOldIngredient(String table, String oldName, String newName, float calories) throws SQLException {
        Statement statement = connection.createStatement();
        statement.execute(String.format(Locale.US, "update %s set name = '%s', calories = '%f' where name = '%s'",
                table, newName, calories, oldName));
    }
    private void deleteIngredient(String table, String name) {
        try {
            Statement statement = connection.createStatement();
            statement.execute(String.format("delete from %s where name = '%s';", table, name));
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }


    public void addNewCupcake(Cupcake cupcake) throws SQLException {
        Statement statement = connection.createStatement();
        String query = String.format(Locale.US,
                "select * from add_cupcake('%s', '%s', '%s', '%s', '%s', '%.2f');",
                cupcake.getStuffing(), cupcake.getDimensions(), cupcake.getPastry(),
                cupcake.getTopping(), cupcake.getName(), cupcake.getCost());
        statement.execute(query);
    }

    public void updateOldCupcake(String oldName, Cupcake cupcake) throws SQLException {
        Statement statement = connection.createStatement();
        String query = String.format(Locale.US,
                "select * from update_cupcake('%s', '%s', '%s', '%s', '%s', '%s', '%.2f');",
                oldName, cupcake.getStuffing(), cupcake.getDimensions(), cupcake.getPastry(),
                cupcake.getTopping(), cupcake.getName(), cupcake.getCost());
        statement.execute(query);
    }

    public List<Cupcake> getAllCupcakes() {
        List<Cupcake> cupcakes = new ArrayList<>();

        try {
            Statement statement = connection.createStatement();
            ResultSet queryRes = statement.executeQuery("select * from get_cupcakes();");

            while (queryRes.next()) {
                cupcakes.add(
                        new Cupcake(
                                queryRes.getString(1),
                                queryRes.getFloat(2),
                                queryRes.getFloat(3),
                                queryRes.getString(4),
                                queryRes.getString(5),
                                queryRes.getString(6),
                                queryRes.getString(7)));
            }
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }

        return cupcakes;
    }

    public void removeCupcake(String name) {
        try {
            Statement statement = connection.createStatement();
            statement.execute(String.format("delete from %s where name = '%s'", TABLE_CUPCAKE, name));
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
