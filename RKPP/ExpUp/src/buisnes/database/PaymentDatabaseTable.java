package buisnes.database;

import model.Athlete;
import model.Payment;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class PaymentDatabaseTable {
    private static final String TABLE_NAME = "payment";
    private static final String getAllQueryTemplate = "select * from %s where id_athlete = %d;";
    private static final String insertQueryTemplate = "insert into %s" +
            "(id_athlete, payment_date, amount_of_payment, days) " +
            "values('%d', '%s', '%f', '%d');";
    private static final String updateQueryTemplate = "update %s set " +
            "payment_date = '%s', " +
            "amount_of_payment = '%f', " +
            "days = '%d' " +
            "where id = '%d';";
    private static final String deleteQueryTemplate = "delete from %s where id = '%d'";


    public static List<Payment> getAll(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        List<Payment> list = new ArrayList<>();

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(getAllQueryTemplate, TABLE_NAME, athlete.getId());
            ResultSet res = statement.executeQuery(query);
            while (res.next()) {
                Payment payment = new Payment(
                        res.getInt(1),
                        res.getInt(2),
                        res.getTimestamp(3),
                        res.getDouble(4),
                        res.getInt(5)
                );
                list.add(payment);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void insert(Payment payment) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, insertQueryTemplate, TABLE_NAME, payment.getIdAthlete(),
                    payment.getPaymentDate(), payment.getAmountOfPayment(), payment.getDays());

            statement.execute(query);

            query = String.format("select max(id) as id from %s;", TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            if (res.next()) {
                payment.setId(res.getInt(1));
            }
            else {
                throw new RuntimeException("Invalid row insert!!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void update(Payment payment) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, updateQueryTemplate, TABLE_NAME,
                    payment.getPaymentDate(), payment.getAmountOfPayment(), payment.getDays(), payment.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void delete(Payment payment) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, deleteQueryTemplate, TABLE_NAME,  payment.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
