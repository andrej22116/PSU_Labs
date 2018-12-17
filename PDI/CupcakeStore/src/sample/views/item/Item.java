package sample.views.item;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.StackPane;

import java.io.IOException;

public class Item extends StackPane {

    @FXML
    public Label cupcakeName;

    @FXML
    public Label cupcakeInfo;


    private String cupcakeNameInitializer = "";
    private String cupcakeInfoInitializer = "";



    public void onMouseClick(MouseEvent mouseEvent) {

    }

    public Item () {
        create();
    }

    public Item (String name, String info) {
        cupcakeNameInitializer = name;
        cupcakeInfoInitializer = info;

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
        cupcakeName.setText(cupcakeNameInitializer);
        cupcakeInfo.setText(cupcakeInfoInitializer);
    }
}
