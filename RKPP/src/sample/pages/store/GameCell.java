package sample.store;

import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;

public class GameCell extends Button {
    private VBox box = new VBox();
    private Image icon;
    private Label name = new Label();
    private Label info = new Label();

    public GameCell(String gameName)
    {
        name.setText(gameName);
    }

    public GameCell(String gameName, String gameInfo)
    {
        name.setText(gameName);
        info.setText(gameInfo);
    }

    public GameCell(String gameName, String gameInfo, Image gameIcon)
    {
        name.setText(gameName);
        info.setText(gameInfo);
        icon = gameIcon;
    }

    private void makeBox()
    {

    }
}
