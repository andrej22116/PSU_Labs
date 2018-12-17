package sample.views.info;

import javafx.animation.FadeTransition;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.effect.GaussianBlur;
import javafx.scene.layout.StackPane;
import javafx.util.Duration;
import sample.database.DataBaseController;
import sample.views.beans.Cupcake;
import sample.views.beans.IDialogListener;
import sample.views.edit.Edit;
import sample.views.item.Item;

import java.io.IOException;

public class Info extends StackPane {
    private Item selectedItem;

    public Info() {
        create();
    }

    private void create() {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("info.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        fxmlLoader.setClassLoader(getClass().getClassLoader());

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }


    IDialogListener<Boolean> listener;

    public void setListener(IDialogListener<Boolean> listener) {
        this.listener = listener;
    }


    @FXML
    public Label name;
    @FXML
    public Label pastry;
    @FXML
    public Label stuffing;
    @FXML
    public Label dimensions;
    @FXML
    public Label topping;
    @FXML
    public Label cost;
    @FXML
    public Label calories;

    @FXML
    public Button buttonOk;

    @FXML
    public Button buttonEdit;

    @FXML
    public Button buttonDelete;

    @FXML
    public StackPane blurTarget;

    @FXML
    public void initialize() {
        name.setText("");
        pastry.setText("");
        stuffing.setText("");
        dimensions.setText("");
        topping.setText("");
        cost.setText("");
        calories.setText("");

        buttonOk.setOnMouseClicked( e -> {
            if ( listener != null ) listener.onFinish(false);
        });

        buttonDelete.setOnMouseClicked( e -> {
            if ( listener != null ) listener.onFinish(null);
        });

        edit.setListener(editListener);
        buttonEdit.setOnMouseClicked( e -> {
            edit.startEditOld(selectedItem.getCupcake());
        });
    }

    public void show(Item item) {
        selectedItem = item;
        Cupcake cupcake = item.getCupcake();

        setInfo(cupcake);

        if ( listener != null ) listener.onStart();
    }

    private void setInfo(Cupcake cupcake)
    {
        name.setText(cupcake.getName());
        pastry.setText(cupcake.getPastry());
        stuffing.setText(cupcake.getStuffing());
        dimensions.setText(cupcake.getDimensions());
        topping.setText(cupcake.getTopping());
        cost.setText("" + cupcake.getCost());
        calories.setText("" + cupcake.getCalories());
    }


    Edit edit = new Edit();
    IDialogListener<Cupcake> editListener = new IDialogListener<Cupcake>() {
        @Override
        public void onStart() {
            FadeTransition ft = new FadeTransition();
            ft.setNode(edit);
            ft.setDuration(new Duration(300));
            ft.setFromValue(0.0);
            ft.setToValue(1.0);
            ft.setCycleCount(1);
            ft.setAutoReverse(true);

            ft.play();
            Info.this.getChildren().add(edit);
            blurTarget.setEffect(new GaussianBlur(12));
        }

        @Override
        public void onFinish(Cupcake result) {
            Info.this.getChildren().remove(edit);
            blurTarget.setEffect(null);

            if ( result != null ) {
                selectedItem.setCupcake(result);
                setInfo(result);
            }
        }
    };
}
