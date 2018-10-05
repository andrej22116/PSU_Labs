package sample.pages.store;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;
import sample.Main;

public class GameCell extends BorderPane {

    private static final double CELL_MAX_WIDTH = 750;
    private static final double CELL_MIN_WIDTH = 400;
    private static final double CELL_HEIGHT = 205;
    private static final double IMAGE_WIDTH = 205;
    private static final double IMAGE_HEIGHT = 205;
    private static final double IMAGE_VIEW_WIDTH = IMAGE_WIDTH;
    private static final double IMAGE_VIEW_HEIGHT = IMAGE_HEIGHT;

    private Image image;
    private Label label_name = new Label();
    private Label label_info = new Label();
    private Label label_dateOfCreate = new Label();
    private Label label_author = new Label();
    private Label label_cost = new Label();

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

    public GameCell(int gameId, int authorId, String gameName, String gameInfo,
                    String dateOfCreate, String author, Integer gameCost, Image gameImage)
    {
        setHandlers();
        setPropertyes();
        if (gameName != null) { label_name.setText(gameName); }
        if (gameInfo != null) { label_info.setText(gameInfo); }
        if (dateOfCreate != null) { label_dateOfCreate.setText(dateOfCreate); }
        if (author != null) { label_author.setText(author); }
        if (gameCost != null) { label_cost.setText(gameCost != 0 ? ("$" + gameCost) : ("Free")); }
        if (gameImage != null) { image = gameImage; }

        BorderPane rightContent = new BorderPane();
        {
            BorderPane rightContent_head = new BorderPane();
            {
                rightContent_head.getStyleClass().add("cell-head");
                rightContent_head.setLeft(label_name);
                rightContent_head.setRight(label_cost);
            }
            rightContent.setTop(rightContent_head);

            rightContent.getStyleClass().add("cell-center");
            rightContent.setCenter(label_info);

            BorderPane rightContent_base = new BorderPane();
            {
                rightContent_base.getStyleClass().add("cell-base");
                rightContent_base.setLeft(label_author);
                rightContent_base.setRight(label_dateOfCreate);
            }
            rightContent.setBottom(rightContent_base);
        }

        VBox imgBox = new VBox();
        {
            imgBox.setStyle("-fx-background-color: #0001");
            imgBox.setMinSize(IMAGE_VIEW_WIDTH, IMAGE_VIEW_HEIGHT);
            imgBox.setMaxSize(IMAGE_VIEW_WIDTH, IMAGE_VIEW_HEIGHT);
            ImageView imgView = new ImageView();
            imgView.setFitWidth(200);
            imgView.setFitHeight(200);

            if (image != null) {
                imgView.setImage(image);
            } else {
                imgView.setImage(noImage);
            }
            imgBox.getChildren().add(imgView);
        }

        this.setLeft(imgBox);
        this.setRight(rightContent);
    }

    private void setHandlers() {
        this.setOnMouseClicked( e -> {
            Main.statusBar.setText("Game: " + label_name.getText());
        });
    }

    private void setPropertyes() {
        this.setMaxSize(CELL_MAX_WIDTH, CELL_HEIGHT);
        this.setMinSize(CELL_MIN_WIDTH, CELL_HEIGHT);

        this.getStyleClass().add("cell");
        label_name.getStyleClass().add("name");
        label_info.getStyleClass().add("info");
        label_dateOfCreate.getStyleClass().add("date");
        label_author.getStyleClass().add("author");
        label_cost.getStyleClass().add("cost");

        label_info.setWrapText(true);

        this.getStylesheets().add(getClass().getClassLoader().getResource("sample/pages/store/style/GameCell.css").toExternalForm());
    }
}
