package buisnes.database;

import model.Athlete;
import model.PhysicalCharacteristics;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class PhysicalCharacteristicsDatabaseTable {
    private static final String TABLE_NAME = "physicals_characteristics";
    private static final String getAllQueryTemplate = "select * from %s where id_athlete = %d;";
    private static final String insertQueryTemplate = "insert into %s" +
            "(id_athlete, mass, biceps_girth, chest_girth, waist_girth, leg_girth, weight_on_biceps, weight_on_chest," +
            "weight_on_foot, weight_on_back, back_width, mass_and_fat_ratio, fixation_date) " +
            "values('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%s');";
    private static final String updateQueryTemplate = "update %s set " +
            "mass = '%f', " +
            "biceps_girth = '%f', " +
            "chest_girth = '%f', " +
            "waist_girth = '%f', " +
            "leg_girth = '%f', " +
            "weight_on_biceps = '%f', " +
            "weight_on_chest = '%f', " +
            "weight_on_foot = '%f', " +
            "weight_on_back = '%f', " +
            "back_width = '%f', " +
            "mass_and_fat_ratio = '%f', " +
            "fixation_date = '%s' " +
            "where id = '%d';";
    private static final String deleteQueryTemplate = "delete from %s where id = '%d'";

    public static List<PhysicalCharacteristics> getAll(Athlete athlete) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        List<PhysicalCharacteristics> list = new ArrayList<>();

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, getAllQueryTemplate, TABLE_NAME, athlete.getId());
            ResultSet res = statement.executeQuery(query);
            while (res.next()) {
                PhysicalCharacteristics physicalCharacteristics = new PhysicalCharacteristics(
                        res.getInt(1),
                        res.getInt(2),
                        res.getFloat(3),
                        res.getFloat(4),
                        res.getFloat(5),
                        res.getFloat(6),
                        res.getFloat(7),
                        res.getFloat(8),
                        res.getFloat(9),
                        res.getFloat(10),
                        res.getFloat(11),
                        res.getFloat(12),
                        res.getFloat(13),
                        res.getDate(14)
                );
                list.add(physicalCharacteristics);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return list;
    }

    public static void insert(PhysicalCharacteristics physicalCharacteristics) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, insertQueryTemplate, TABLE_NAME, physicalCharacteristics.getIdAthlete(),
                    physicalCharacteristics.getMass(), physicalCharacteristics.getBicepsGirth(),
                    physicalCharacteristics.getChestGirth(), physicalCharacteristics.getWaistGirth(),
                    physicalCharacteristics.getLegGirth(), physicalCharacteristics.getWeightOnBiceps(),
                    physicalCharacteristics.getWeightOnChest(), physicalCharacteristics.getWeightOnFoot(),
                    physicalCharacteristics.getWeightOnBack(), physicalCharacteristics.getBackWidth(),
                    physicalCharacteristics.getMassAndFatRatio(), physicalCharacteristics.getFixationDate());

            System.out.println(query);

            statement.execute(query);

            query = String.format("select max(id) as id from %s;", TABLE_NAME);
            ResultSet res = statement.executeQuery(query);
            if (res.next()) {
                physicalCharacteristics.setId(res.getInt(1));
            }
            else {
                throw new RuntimeException("Invalid row insert!!");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void update(PhysicalCharacteristics physicalCharacteristics) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, updateQueryTemplate, TABLE_NAME,
                    physicalCharacteristics.getMass(), physicalCharacteristics.getBicepsGirth(),
                    physicalCharacteristics.getChestGirth(), physicalCharacteristics.getWaistGirth(),
                    physicalCharacteristics.getLegGirth(), physicalCharacteristics.getWeightOnBiceps(),
                    physicalCharacteristics.getWeightOnChest(), physicalCharacteristics.getWeightOnFoot(),
                    physicalCharacteristics.getWeightOnBack(), physicalCharacteristics.getBackWidth(),
                    physicalCharacteristics.getMassAndFatRatio(), physicalCharacteristics.getFixationDate(),
                    physicalCharacteristics.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void delete(PhysicalCharacteristics physicalCharacteristics) {
        if ( DatabaseConnect.getConnection() == null ) throw new RuntimeException("No connection!");

        try (Statement statement = DatabaseConnect.getConnection().createStatement()){
            String query = String.format(Locale.US, deleteQueryTemplate, TABLE_NAME,  physicalCharacteristics.getId());

            statement.execute(query);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
