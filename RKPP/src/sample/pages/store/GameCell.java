package sample.pages.store;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;
import sample.Main;

public class GameCell extends HBox {

    private static final double CELL_MAX_WIDTH = 750;
    private static final double CELL_MIN_WIDTH = 400;
    private static final double CELL_HEIGHT = 205;
    private static final double IMAGE_WIDTH = 200;
    private static final double IMAGE_HEIGHT = 200;
    private static final double IMAGE_BORDER_WIDTH = 5;
    private static final double IMAGE_VIEW_WIDTH = IMAGE_WIDTH + IMAGE_BORDER_WIDTH;
    private static final double IMAGE_VIEW_HEIGHT = IMAGE_HEIGHT;

    private Image image;
    private Label name = new Label();
    private Label info = new Label();

    private static Image noImage = new Image("sample/images/other/NoImage.png",
            IMAGE_WIDTH, IMAGE_HEIGHT, true, true);

    private static Font headerTextFont = new Font("Arial", 24);
    private static Font footerTextFont = new Font("Arial", 14);
    private static String css =
                    "-fx-border-width: 0 0 5 0;" +
                    "-fx-border-color: #e4e4e4;" +
                    "-fx-background-color: #eaeaea;" +
                    "-fx-effect: dropshadow(gaussian, rgba(0,0,0,0.2), 7, -7, 2, 7);";
    private static String cssHover = css + "-fx-background-color: #f0f0f0;";
    private static String cssPressed = css +
            "-fx-background-color: #e0e0e0;" +
            "-fx-border-width: 2 0 3 0;" +
            "-fx-border-color: #f4f4f4 black #d0d0d0 black;" +
            "-fx-effect: dropshadow(gaussian, rgba(0,0,0,0.2), 5, -5, 2, 5);";

    public GameCell(String gameName)
    {
        name.setText(gameName);

        makeBox();
    }

    public GameCell(String gameName, String gameInfo)
    {
        name.setText(gameName);
        info.setText(gameInfo);

        makeBox();
    }

    public GameCell(String gameName, String gameInfo, Image gameImage)
    {
        name.setText(gameName);
        info.setText(gameInfo);
        image = gameImage;

        makeBox();
    }

    private void makeBox()
    {
        this.setMaxSize(CELL_MAX_WIDTH, CELL_HEIGHT);
        this.setMinSize(CELL_MIN_WIDTH, CELL_HEIGHT);
        this.setStyle(css);
        this.setOnMouseEntered( e -> {
            this.setStyle(cssHover);
        });
        this.setOnMouseExited( e -> {
            this.setStyle(css);
        });
        this.setOnMousePressed( e -> {
            if (e.isPrimaryButtonDown()) {
                this.setStyle(cssPressed);
            }
        });
        this.setOnMouseReleased( e -> {
            this.setStyle(css);
        });
        this.setOnMouseClicked( e -> {
            Main.statusBar.setText("Game: " + name.getText());
        });

        name.setFont(headerTextFont);
        info.setFont(footerTextFont);

        name.setStyle("-fx-color: black; -fx-background-color: #0001;");
        info.setStyle("-fx-color: gray;");

        name.setMaxWidth(Double.MAX_VALUE);
        info.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        name.setTextAlignment(TextAlignment.CENTER);

        VBox imgBox = new VBox();
        imgBox.setStyle("-fx-background-color: #0001");
        imgBox.setMinSize(IMAGE_VIEW_WIDTH, IMAGE_VIEW_HEIGHT);
        imgBox.setMaxSize(IMAGE_VIEW_WIDTH, IMAGE_VIEW_HEIGHT);
        imgBox.setStyle("-fx-border-width: 0 " + (int)IMAGE_BORDER_WIDTH + " 0 0;" +
                        "-fx-border-color: d0d0d088;");
        ImageView imgView = new ImageView();
        imgView.setFitWidth(200); imgView.setFitHeight(200);

        if (image != null) {
            imgView.setImage(image);
        } else {
            imgView.setImage(noImage);
        }
        imgBox.getChildren().add(imgView);

        VBox box = new VBox(name, info);
        box.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        //box.setFillWidth(true);
        box.setStyle("-fx-border-width: 0 5 0 0;" +
                "-fx-border-color: black;");
        box.setAlignment(Pos.TOP_CENTER);
        this.getChildren().addAll(imgBox, box);
    }
}
