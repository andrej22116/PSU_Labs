package sample.pages.store;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.Border;
import javafx.scene.layout.VBox;
import sample.pages.BaseController;

public class StoreController extends BaseController {
    public VBox storeContent = new VBox();
    ScrollPane scrollPane = new ScrollPane(storeContent);

    public StoreController(String name)
    {
        super(name);
        scrollPane.setMaxWidth(Double.MAX_VALUE);
        scrollPane.setFitToWidth(true);
        scrollPane.setFitToHeight(true);
        scrollPane.setStyle("   -fx-background-insets: 0;" +
                            "   -fx-background-radius: 0;");


        storeContent.setSpacing(10);
        storeContent.setMaxWidth(Double.MAX_VALUE);

        storeContent.setAlignment(Pos.BASELINE_CENTER);

        storeContent.setPadding(new Insets(10));

        storeContent.getChildren().addAll(
                new GameCell("Игра 1", "Инфа об игре 1 daf sdf sadf asd!"),
                new GameCell("Игра 2", "Инфа об игре 2!"),
                new GameCell("Игра 3", "Инфа об игре 3!"),
                new GameCell("Игра 4", "Инфа об игре 4!"),
                new GameCell("Игра 5", "Инфа об игре 5!"),
                new GameCell("Игра 6", "Инфа об игре 6!"),
                new GameCell("Игра 7", "Инфа об игре 7!"),
                new GameCell("Игра 8", "Инфа об игре 8!"),
                new GameCell("Игра 1", "Инфа об игре 1!"),
                new GameCell("Игра 2", "Инфа об игре 2!"),
                new GameCell("Игра 3", "Инфа об игре 3!"),
                new GameCell("Игра 4", "Инфа об игре 4!"),
                new GameCell("Игра 5", "Инфа об игре 5!"),
                new GameCell("Игра 6", "Инфа об игре 6!"),
                new GameCell("Игра 7", "Инфа об игре 7!"),
                new GameCell("Игра 8", "Инфа об игре 8!"),
                new GameCell("Игра 1", "Инфа об игре 1!"),
                new GameCell("Игра 2", "Инфа об игре 2!"),
                new GameCell("Игра 3", "Инфа об игре 3!"),
                new GameCell("Игра 4", "Инфа об игре 4!"),
                new GameCell("Игра 5", "Инфа об игре 5!"),
                new GameCell("Игра 6", "Инфа об игре 6!"),
                new GameCell("Игра 7", "Инфа об игре 7!"),
                new GameCell("Игра 8", "Инфа об игре 8!"),
                new GameCell("Игра 1", "Инфа об игре 1!"),
                new GameCell("Игра 2", "Инфа об игре 2!"),
                new GameCell("Игра 3", "Инфа об игре 3!"),
                new GameCell("Игра 4", "Инфа об игре 4!"),
                new GameCell("Игра 5", "Инфа об игре 5!"),
                new GameCell("Игра 6", "Инфа об игре 6!"),
                new GameCell("Игра 7", "Инфа об игре 7!"),
                new GameCell("Игра 8", "Инфа об игре 8!"),
                new GameCell("Игра 1", "Инфа об игре 1!"),
                new GameCell("Игра 2", "Инфа об игре 2!"),
                new GameCell("Игра 3", "Инфа об игре 3!"),
                new GameCell("Игра 4", "Инфа об игре 4!"),
                new GameCell("Игра 5", "Инфа об игре 5!"),
                new GameCell("Игра 6", "Инфа об игре 6!"),
                new GameCell("Игра 7", "Инфа об игре 7!"),
                new GameCell("Игра 8", "Инфа об игре 8!"),
                new GameCell("Игра 9", "Инфа об игре 9!")
        );

        content.setCenter(scrollPane);
    }
}
