package sample;

import sample.pages.library.LibraryController;
import sample.pages.settings.SettingsController;
import sample.pages.store.StoreController;

import javafx.application.Application;
import javafx.geometry.*;
import javafx.scene.Scene;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;

public class Main extends Application {

    Label statusBar = new Label();
    BorderPane mainPane = new BorderPane();
    TilePane headPane = new TilePane();

    TabPane tabPane = new TabPane();

    @Override
    public void start(Stage primaryStage) throws Exception{
        BorderPane root = new BorderPane();
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

        Scene scene = new Scene(root, 800, 600);
        primaryStage.setScene(scene);
        primaryStage.setMinWidth(800);
        primaryStage.setMinHeight(600);
        primaryStage.show();
    }

    private void makeHeader()
    {
    }

    private void makeCenter()
    {
        statusBar.setText("Trololo!");

        castomizeTabPane();

        mainPane.setCenter(tabPane);

        tabPane.getTabs().add(makeTabForMainScene(new StoreController("МАГАЗИН ИГР"),
                null, "sample/images/icons/MarketIcon.png"));
        tabPane.getTabs().add(makeTabForMainScene(new LibraryController("БИБЛИОТЕКА ИГР"),
                null, "sample/images/icons/GamesIcon.png"));
        tabPane.getTabs().add(makeTabForMainScene(new SettingsController("НАСТРОЙКИ"),
                null, "sample/images/icons/OptionsIcon.png"));
    }

    private void castomizeTabPane()
    {
        tabPane.setSide(Side.LEFT);

        tabPane.setTabMinHeight(50);
        tabPane.setTabMaxHeight(50);
        tabPane.setTabMinWidth(60);
        tabPane.setTabMaxWidth(60);

        tabPane.setTabDragPolicy(TabPane.TabDragPolicy.FIXED);
        tabPane.setPadding(new Insets(0));
    }

    private Tab makeTabForMainScene(Tab tab, String text, String pathToImage)
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

        tab.setGraphic(content);

        return tab;
    }

    private String loadStyleSheetFromFile(String filename)
    {
        return getClass().getResource(filename).toExternalForm();
    }

    public static void main(String[] args) {
        System.setProperty("prism.lcdtext", "false");
        launch(args);
    }
}
