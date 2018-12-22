package buisnes.controller.dialog;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Dialog;
import javafx.stage.Modality;
import javafx.stage.Window;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public abstract class CustomDialog<T> extends Dialog<T> implements Initializable {
    private T model;
    public T getModel() { return model; }

    public CustomDialog(Window owner, String url, T model) {
        this.model = model;

        initOwner(owner);
        initModality(Modality.APPLICATION_MODAL);

        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource(url));
            loader.setController(this);
            Parent root = loader.load();
            getDialogPane().setContent(root);

            //setResultConverter(buttonType -> model);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @FXML
    @Override
    public void initialize(URL location, ResourceBundle resources) {}
}
