import buisnes.controller.dialog.AthletDialog;
import buisnes.database.AthleteDatabaseTable;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import model.Athlete;

import java.util.List;
import java.util.Optional;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("view/main/main.fxml"));
        primaryStage.setTitle("ExpUp - Лучшая качалка!");
        primaryStage.setScene(new Scene(root, 800, 600));
        primaryStage.setMinWidth(800);
        primaryStage.setMinHeight(600);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
