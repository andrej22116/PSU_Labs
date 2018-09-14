package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Orientation;
import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;
import javafx.geometry.Side;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.event.ActionEvent;

public class Main extends Application {

    Label statusBar = new Label();
    GridPane mainPane = new GridPane();
    TilePane headPane = new TilePane();

    TabPane tabPane = new TabPane();

    @Override
    public void start(Stage primaryStage) throws Exception{
        BorderPane root = new BorderPane();//FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("Hello World");

        root.setTop(headPane);
        root.setCenter(mainPane);
        root.setBottom(statusBar);

        statusBar.setMaxSize(Double.MAX_VALUE, 30);
        statusBar.getStylesheets().add(loadStyleSheetFromFile("StatusBarStyle.css"));

        tabPane.setTabClosingPolicy(TabPane.TabClosingPolicy.UNAVAILABLE);
        tabPane.getStylesheets().add(loadStyleSheetFromFile("TabBarStyleSheet"));

        makeHeader();
        makeCenter();

        primaryStage.setScene(new Scene(root, 800, 600));
        primaryStage.setMinWidth(800);
        primaryStage.setMinHeight(600);
        primaryStage.show();
    }

    private void makeHeader()
    {
        //headPane.setOrientation(Orientation.HORIZONTAL);
        //headPane.set
    }

    private void makeCenter()
    {
        tabPane.setSide(Side.LEFT);
        statusBar.setText("Trololo!");

        Button button = new Button("Press me!");
        button.setOnAction((e) -> {
            statusBar.setText(e.toString());
        });

        //mainPane.add(button, 0, 0);
        mainPane.add(tabPane, 0, 1);


        tabPane.setTabMinHeight(50);
        tabPane.setTabMaxHeight(50);
        tabPane.setTabMinWidth(60);
        tabPane.setTabMaxWidth(60);
        Tab tab = makeTabForMainScene("pinus", "sample/images/icons/MarketIcon.png");
        button.setMaxWidth(Double.MAX_VALUE);
        tab.setContent(button);
        /*
        //tab.setText("TROLOLO");
        tab.setContent(button);

        VBox content = new VBox();
        ImageView icon = new ImageView(new Image(".\\images\\icons\\MarketIcon.png"));
        tab.setGraphic(icon);
        */
        tabPane.getTabs().add(tab);

        tab = new Tab();
        tab.setText("AZAZAZA");
        tabPane.getTabs().add(tab);
    }

    private Tab makeTabForMainScene(String text, String pathToImage)
    {
        VBox content = new VBox();
        if (pathToImage != null) {
            Image image = new Image(pathToImage, 50, 50, true, true);
            ImageView icon = new ImageView(image);
            icon.setFitWidth(40); icon.setFitHeight(40);

            content.getChildren().add(icon);
        }

        if (text != null) {
            Label textLabel = new Label(text);
            textLabel.setAlignment(Pos.BOTTOM_CENTER);
            textLabel.setMaxSize(40, 20);

            content.getChildren().add(textLabel);
        }

        Tab tab = new Tab();
        tab.setGraphic(content);

        return tab;
    }

    private String loadStyleSheetFromFile(String filename)
    {
        return getClass().getResource(filename).toExternalForm();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
