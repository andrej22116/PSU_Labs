package buisnes;

import javafx.scene.control.ListCell;
import model.Payment;

public class PaymentItemCell extends ListCell<Payment> {
    @Override
    protected void updateItem(Payment item, boolean empty) {
        super.updateItem(item, empty);
        if (item != null && !empty) {
            PaymentItemController paymentItemController = new PaymentItemController(item);
            setGraphic(paymentItemController.getItem());
        }
        else {
            setGraphic(null);
        }
    }
}
