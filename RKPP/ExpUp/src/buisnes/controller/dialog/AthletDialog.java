package buisnes.controller.dialog;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Window;
import model.Athlete;

import java.net.URL;
import java.util.ResourceBundle;

public class AthletDialog extends CustomDialog<Athlete> {
    @FXML
    VBox dialog;

    @FXML
    private TextField surName;
    @FXML
    private TextField name;
    @FXML
    private TextField middleName;
    @FXML
    private TextField age;
    @FXML
    private CheckBox isFemale;
    @FXML
    private Button ok;
    @FXML
    private Button cancel;


    public AthletDialog(Window parent, Athlete model) {
        super(parent, "/view/dialog/athlete_dialog.fxml", model);
    }

    @FXML
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        //window = dialog.getScene().getWindow();

        if (getModel() != null) {
            surName.setText(getModel().getSurName());
            name.setText(getModel().getName());
            middleName.setText(getModel().getMiddleName());
            age.setText("" + getModel().getAge());
            isFemale.setSelected(getModel().isFemale());
        }

        surName.textProperty().addListener( event -> getModel().setSurName(surName.getText()) );
        name.textProperty().addListener( event -> getModel().setName(name.getText()) );
        middleName.textProperty().addListener( event -> getModel().setMiddleName(middleName.getText()) );
        age.textProperty().addListener( event -> getModel().setAge(Integer.parseInt(age.getText())) );
        isFemale.selectedProperty().addListener( event -> {
            getModel().setFemale(isFemale.isSelected());
        } );

        ok.setOnMouseClicked( event -> {
            dialog.getScene().getWindow().hide();
            AthletDialog.this.setResult(getModel());
        });
        cancel.setOnMouseClicked( event -> {
            dialog.getScene().getWindow().hide();
            AthletDialog.this.setResult(null);
        });
    }
}
