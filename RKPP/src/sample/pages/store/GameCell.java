package sample.pages.store;

import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

public class GameCell extends VBox {
    private Image icon;
    private Label name = new Label();
    private Label info = new Label();

    private static Font headerTextFont = new Font("Arial", 14);
    private static Font footerTextFont = new Font("Arial", 10);
    private static String css =
                    "-fx-padding: 5;" +
                    "-fx-background-color: #e0e0e0;"
                    ;

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

    public GameCell(String gameName, String gameInfo, Image gameIcon)
    {
        name.setText(gameName);
        info.setText(gameInfo);
        icon = gameIcon;

        makeBox();
    }

    private void makeBox()
    {
        this.setStyle(css);

        if (icon != null) {
            this.getChildren().add(new ImageView(icon));
        }

        name.setFont(headerTextFont);
        info.setFont(footerTextFont);

        name.setStyle("-fx-color: black; -fx-border-width: 0 0 1 0; -fx-border-color: black;");
        name.setStyle("-fx-color: gray;");

        name.setMaxWidth(Double.MAX_VALUE);
        name.setTextAlignment(TextAlignment.CENTER);
        name.setAlignment(Pos.CENTER);

        this.getChildren().add(name);
        this.getChildren().add(info);

        this.setMaxSize(150, 500);
        this.setMinSize(150, 100);
    }
}
