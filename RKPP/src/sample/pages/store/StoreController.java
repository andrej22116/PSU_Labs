package sample.pages.store;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.Border;
import javafx.scene.layout.VBox;
import sample.database.DataBaseController;
import sample.database.GamesQueries;
import sample.pages.BaseController;

import java.sql.ResultSet;

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

        if (DataBaseController.getInstance() == null) {
            return;
        }
        GamesQueries.init();

        ResultSet games = GamesQueries.getListOfGames();
        try {
            while (games.next()) {
                storeContent.getChildren().add(new GameCell(
                        games.getInt("id_game"),
                        games.getInt("id_maker"),
                        games.getString("GameName"),
                        games.getString("GameDescription"),
                        games.getDate("DateOfReleaseGame").toString(),
                        games.getString("MakerName"),
                        games.getInt("GameCost"),
                        null));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        content.setCenter(scrollPane);
    }
}
