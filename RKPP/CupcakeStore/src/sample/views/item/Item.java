package sample.views.item;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.StackPane;
import sample.views.beans.Cupcake;

import java.io.IOException;

public class Item extends StackPane {

    @FXML
    public Label cupcakeName;

    @FXML
    public Label cupcakeInfo;

    @FXML
    public Label cost;

    @FXML
    public Label calories;

    private String cupcakeNameInitializer = "";
    private String cupcakeInfoInitializer = "";
    private String cupcakeCostInitializer = "";
    private String cupcakeColoriesInitializer = "";

    public Cupcake getCupcake() {
        return cupcake;
    }
    public void setCupcake(Cupcake cupcake) {
        this.cupcake = cupcake;
        initialize();
    }

    private Cupcake cupcake;

    public void onMouseClick(MouseEvent mouseEvent) {

    }

    public Item (Cupcake cupcake) {
        this.cupcake = cupcake;
        create();
    }

    private void create() {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("item.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        fxmlLoader.setClassLoader(getClass().getClassLoader());

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }

    @FXML
    public void initialize() {
        cupcakeName.setText(cupcake.getName());
        cupcakeInfo.setText(cupcake.getDimensions() + ", " +
                cupcake.getPastry() + " с " + cupcake.getStuffing() + " внутри! :3");
        cost.setText("$" + cupcake.getCost());
        calories.setText("" + cupcake.getCalories());
    }
}
