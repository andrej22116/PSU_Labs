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
import sample.StatusBar;

public class GameCell extends BorderPane {

    public static final double CELL_MAX_WIDTH = 750;
    public static final double CELL_MIN_WIDTH = 400;
    public static final double CELL_HEIGHT = 205;
    public static final double IMAGE_WIDTH = 205;
    public static final double IMAGE_HEIGHT = 205;
    public static final double IMAGE_VIEW_WIDTH = IMAGE_WIDTH;
    public static final double IMAGE_VIEW_HEIGHT = IMAGE_HEIGHT;

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
            StatusBar.s_showMessage("Game: " + label_name.getText(), 5);
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
