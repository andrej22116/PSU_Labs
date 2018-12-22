package buisnes;

import buisnes.database.VisitsDatabaseTable;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import model.Visit;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class VisitItemController implements Initializable {
    private Visit visit;

    @FXML
    private HBox item;
    @FXML
    private Label date;
    @FXML
    private Label time;
    @FXML
    private CheckBox checkbox;


    public HBox getItem() { return item; }


    public VisitItemController(Visit visit)
    {
        this.visit = visit;

        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/view/visit/visitItem.fxml"));
        fxmlLoader.setController(this);
        try
        {
            fxmlLoader.load();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        checkbox.selectedProperty().addListener( event -> {
            visit.setVisited(checkbox.isSelected());
            VisitsDatabaseTable.update(visit);
        });

        date.setText(visit.getDate().toString());
        time.setText(visit.getTime().toString());
        checkbox.setSelected(visit.isVisited());
    }
}
