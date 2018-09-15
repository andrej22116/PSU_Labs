package sample.settings;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.Tab;
import javafx.scene.layout.BorderPane;
import javafx.scene.text.Font;
import javafx.scene.text.TextAlignment;

public class SettingsController extends Tab {
    private BorderPane content = new BorderPane();

    public SettingsController()
    {
        content.setTop(makeHeader());

        this.setContent(content);
    }

    private Label makeHeader()
    {
        Label headLabel = new Label("НАСТРОЙКИ");
        headLabel.setTextAlignment(TextAlignment.CENTER);
        headLabel.setAlignment(Pos.CENTER);
        headLabel.setFont(new Font("Arial", 36));
        headLabel.setStyle("-fx-border-width: 0 0 1 0; -fx-border-color: #e0e0e0;");
        headLabel.setMaxWidth(Double.MAX_VALUE);

        return headLabel;
    }
}
