package sample.pages.store;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.SplitPane;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.VBox;
import sample.database.DataBaseController;
import sample.database.GamesQueries;
import sample.pages.BaseController;

import java.sql.ResultSet;

public class StoreController extends BaseController {
    private VBox storeContent = new VBox();
    private VBox gameInfoContent = new VBox();

    private ScrollPane scrollPaneStore = new ScrollPane(storeContent);
    private ScrollPane scrollPaneGameInfo = new ScrollPane(gameInfoContent);

    private SplitPane splitPane = new SplitPane(scrollPaneStore);

    private boolean needShowGameInfo = false;

    public StoreController(String name)
    {
        super(name);
        scrollPaneStore.setMaxWidth(Double.MAX_VALUE);
        scrollPaneStore.setFitToWidth(true);
        scrollPaneStore.setFitToHeight(true);
        scrollPaneStore.setStyle("   -fx-background-insets: 0;" +
                                 "   -fx-background-radius: 0;");

        scrollPaneStore.setMinWidth(GameCell.CELL_MIN_WIDTH + GameCell.CELL_MIN_WIDTH / 2);
        scrollPaneGameInfo.setMinWidth(400);

        initStoreContentPane();

        loadGamesList();
        initGameInfoPane();

        splitPane.widthProperty().addListener( e -> {
            choiceVisibleItems(needShowGameInfo);
        });

        content.setCenter(splitPane);
    }

    private void initStoreContentPane()
    {
        storeContent.setSpacing(10);
        storeContent.setMaxWidth(Double.MAX_VALUE);
        storeContent.setMinWidth(400);

        storeContent.setAlignment(Pos.BASELINE_CENTER);

        storeContent.setPadding(new Insets(10));
    }

    private void initGameInfoPane()
    {

    }

    public void loadGamesList()
    {
        if (DataBaseController.getInstance() == null) {
            return;
        }
        GamesQueries.init();

        ResultSet games = GamesQueries.getListOfGames();
        try {
            while (games.next()) {
                GameCell cell = new GameCell(
                        games.getInt("id_game"),
                        games.getInt("id_maker"),
                        games.getString("GameName"),
                        games.getString("GameDescription"),
                        games.getDate("DateOfReleaseGame").toString(),
                        games.getString("MakerName"),
                        games.getInt("GameCost"),
                        null);

                cell.addEventFilter(MouseEvent.MOUSE_PRESSED, e -> {
                    needShowGameInfo = true;
                    choiceVisibleItems(needShowGameInfo);
                });

                storeContent.getChildren().add(cell);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void choiceVisibleItems(boolean gameInfoShouldBeVisible)
    {
        double splitPaneWidth = splitPane.getWidth();
        double scrollPaneStoreMinWidth = scrollPaneStore.getMinWidth() + 5;
        double scrollPaneGameInfoMinWidth = scrollPaneGameInfo.getMinWidth() + 5;

        boolean splitPaneCanContainTwoPanes = false;
        if (splitPaneWidth >= scrollPaneStoreMinWidth + scrollPaneGameInfoMinWidth) {
            splitPaneCanContainTwoPanes = true;
        }

        if (gameInfoShouldBeVisible && splitPaneCanContainTwoPanes) {
            showGameInfoWithStore();
        }
        else if (gameInfoShouldBeVisible) {
            showGameInfo();
        }
        else {
            showStore();
        }
    }

    public void showGameInfoWithStore()
    {
        if (splitPane.getItems().size() == 2) {
            return;
        }

        if (!splitPane.getItems().contains(scrollPaneStore)) {
            splitPane.getItems().add(0, scrollPaneStore);
            SplitPane.setResizableWithParent(scrollPaneStore, false);
        }

        if (!splitPane.getItems().contains(scrollPaneGameInfo)) {
            splitPane.getItems().add(1, scrollPaneGameInfo);
        }

        splitPane.setDividerPosition(0, 0);
    }

    public void showGameInfo()
    {
        if (splitPane.getItems().contains(scrollPaneStore)) {
            splitPane.getItems().remove(scrollPaneStore);
        }
        if (!splitPane.getItems().contains(scrollPaneGameInfo)) {
            splitPane.getItems().add(0, scrollPaneGameInfo);
        }
    }

    public void showStore()
    {
        if (splitPane.getItems().contains(scrollPaneGameInfo)) {
            splitPane.getItems().add(0, scrollPaneGameInfo);
        }
        if (!splitPane.getItems().contains(scrollPaneStore)) {
            splitPane.getItems().remove(scrollPaneStore);
        }
    }

}
