package sample.pages.store;

import javafx.geometry.Insets;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.FlowPane;
import sample.pages.BaseController;

public class StoreController extends BaseController {
    public FlowPane storeContent = new FlowPane();
    ScrollPane scrollPane = new ScrollPane(storeContent);

    public StoreController(String name)
    {
        super(name);
        scrollPane.setMaxWidth(Double.MAX_VALUE);
        scrollPane.setFitToWidth(true);
        scrollPane.setFitToHeight(true);
        storeContent.setMaxWidth(Double.MAX_VALUE);

        storeContent.setVgap(10);
        storeContent.setHgap(10);
        storeContent.setPadding(new Insets(10));

        storeContent.getChildren().addAll(
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
