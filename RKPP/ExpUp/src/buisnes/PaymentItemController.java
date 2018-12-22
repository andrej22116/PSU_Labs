package buisnes;

import buisnes.database.VisitsDatabaseTable;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import model.Payment;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class PaymentItemController implements Initializable {
    private Payment payment;

    @FXML
    private HBox itemPayment;
    @FXML
    private Label datetime;
    @FXML
    private Label cost;
    @FXML
    private Label days;

    public HBox getItem() { return itemPayment; }


    public PaymentItemController(Payment payment)
    {
        this.payment = payment;

        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/view/payment/paymentItem.fxml"));
        fxmlLoader.setController(this);
        try
        {
            fxmlLoader.load();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        datetime.setText(payment.getPaymentDate().toString());
        cost.setText("" + payment.getAmountOfPayment());
        days.setText("" + payment.getDays());
    }
}
