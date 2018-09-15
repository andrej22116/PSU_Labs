package sample.pages;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.layout.BorderPane;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

public abstract class BaseController extends Tab {
    protected BorderPane content = new BorderPane();
    protected Label headLabel;

    public BaseController(String name) {
        headLabel = new Label(name);
        headLabel.setTextAlignment(TextAlignment.CENTER);
        headLabel.setAlignment(Pos.CENTER);
        headLabel.setFont(new Font("Arial", 36));
        headLabel.setStyle("-fx-border-width: 0 0 1 0; -fx-border-color: #e0e0e0;");
        headLabel.setMaxWidth(Double.MAX_VALUE);

        content.setTop(headLabel);

        this.setContent(content);
    }
}
