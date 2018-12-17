package sample.views.main;

import javafx.animation.FadeTransition;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.effect.GaussianBlur;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.util.Duration;
import sample.database.DataBaseController;
import sample.views.beans.Cupcake;
import sample.views.beans.IDialogListener;
import sample.views.edit.Edit;
import sample.views.info.Info;
import sample.views.item.Item;

public class Controller {

    @FXML
    public VBox content;

    @FXML
    public GridPane superParent;

    @FXML
    public StackPane blurTarget;

    @FXML
    public Button buttonAdd;

    @FXML
    public void initialize() {
        edit = new Edit();
        edit.setListener(editListener);

        info = new Info();
        info.setListener(infoListener);

        for (Cupcake cupcake : DataBaseController.getInstance().getAllCupcakes()) {
            addNewItem(new Item(cupcake));
        }

        buttonAdd.setOnMouseClicked( e -> {
            Controller.this.edit.startCreateNew();
        });
    }


    private void addNewItem(Item item) {
        content.getChildren().add(item);
        item.setOnMouseClicked( e -> {
            selectedItem = item;
            info.show(item);
        });
    }


    private Edit edit;
    private Info info;
    private Item selectedItem;

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
            superParent.getChildren().add(edit);
            blurTarget.setEffect(new GaussianBlur(12));
        }

        @Override
        public void onFinish(Cupcake result) {
            superParent.getChildren().remove(edit);
            blurTarget.setEffect(null);

            if ( result != null ) {
                addNewItem(new Item(result));
            }
        }
    };

    IDialogListener<Boolean> infoListener = new IDialogListener<Boolean>() {
        @Override
        public void onStart() {
            FadeTransition ft = new FadeTransition();
            ft.setNode(info);
            ft.setDuration(new Duration(500));
            ft.setFromValue(0.0);
            ft.setToValue(1.0);
            ft.setCycleCount(1);
            ft.setAutoReverse(true);

            ft.play();
            superParent.getChildren().add(info);
            blurTarget.setEffect(new GaussianBlur(12));
        }

        @Override
        public void onFinish(Boolean result) {
            superParent.getChildren().remove(info);
            blurTarget.setEffect(null);

            if (result == null) {
                content.getChildren().remove(selectedItem);
                DataBaseController.getInstance().removeCupcake(selectedItem.getCupcake().getName());
                selectedItem = null;
                return;
            }

            if ( result ) {
            }
        }
    };
}
