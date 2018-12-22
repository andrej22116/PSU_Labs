package buisnes;

import javafx.scene.control.ListCell;
import model.Visit;

public class VisitItemCell extends ListCell<Visit> {
    @Override
    protected void updateItem(Visit item, boolean empty) {
        super.updateItem(item, empty);
        if (item != null && !empty) {
            VisitItemController visitItemController = new VisitItemController(item);
            setGraphic(visitItemController.getItem());
        }
        else {
            setGraphic(null);
        }
    }
}
