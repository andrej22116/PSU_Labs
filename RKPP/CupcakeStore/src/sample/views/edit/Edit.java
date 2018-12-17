package sample.views.edit;

import javafx.animation.FadeTransition;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import javafx.scene.effect.GaussianBlur;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.util.Callback;
import javafx.util.Duration;
import sample.database.DataBaseController;
import sample.views.beans.Cupcake;
import sample.views.beans.IDialogListener;
import sample.views.beans.Ingredient;
import sample.views.edit.composition.Composition;

import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.Locale;

public class Edit extends GridPane {
    public Edit () {
        create();
    }

    private void create() {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("edit.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        fxmlLoader.setClassLoader(getClass().getClassLoader());

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }

    IDialogListener<Cupcake> listener;

    public void setListener(IDialogListener<Cupcake> listener) {
        this.listener = listener;
    }

    private void onStart() {
        if ( listener != null ) listener.onStart();
    }

    private void onEnd(Cupcake cupcake) {
        if ( listener != null ) listener.onFinish(cupcake);
    }


    private Cupcake oldCupcake;

    public void startCreateNew() {
        oldCupcake = null;
        title.setText(TITLE_NEW_ITEM);
        updateControls();
        onStart();
    }
    public void startEditOld(Cupcake oldCupcake) {
        this.oldCupcake = oldCupcake;
        title.setText(TITLE_EDIT_ITEM);

        updateControls();

        name.setText(oldCupcake.getName());
        cost.setText(String.format(Locale.US, "%f", oldCupcake.getCost()));
        comboboxPastry.getSelectionModel().select(findElementPosition(comboboxPastry, oldCupcake.getPastry()));
        comboboxStuffing.getSelectionModel().select(findElementPosition(comboboxStuffing, oldCupcake.getStuffing()));
        comboboxDimension.getSelectionModel().select(findElementPosition(comboboxDimension, oldCupcake.getDimensions()));
        comboboxTopping.getSelectionModel().select(findElementPosition(comboboxTopping, oldCupcake.getTopping()));

        onStart();
    }


    private enum EditIngredientTarget {
        EditPastry,
        EditStuffing,
        EditDimension,
        EditTopping
    }
    private EditIngredientTarget editIngredientTarget;


    public static final String TITLE_NEW_ITEM = "New cupcake :3";
    public static final String TITLE_EDIT_ITEM = "Edir cupcake :3";

    @FXML
    public Label title;

    @FXML
    public Button buttonCancel;

    @FXML
    public Button buttonOk;

    @FXML
    public ComboBox<Ingredient> comboboxPastry;
    @FXML
    public ComboBox<Ingredient> comboboxStuffing;
    @FXML
    public ComboBox<Ingredient> comboboxDimension;
    @FXML
    public ComboBox<Ingredient> comboboxTopping;

    @FXML
    public Label errorMsg;

    @FXML
    public TextField name;

    @FXML
    public TextField cost;

    @FXML
    public VBox blurTarget;

    @FXML
    public Button addPastry;
    @FXML
    public Button editPastry;
    @FXML
    public Button removePastry;
    @FXML
    public Button addStuffing;
    @FXML
    public Button editStuffing;
    @FXML
    public Button removeStuffing;
    @FXML
    public Button addDimension;
    @FXML
    public Button editDimension;
    @FXML
    public Button removeDimension;
    @FXML
    public Button addTopping;
    @FXML
    public Button editTopping;
    @FXML
    public Button removeTopping;

    private Composition composition = new Composition();

    @FXML
    public void initialize() {
        buttonCancel.setOnMouseClicked( e -> {
            onEnd(null);
        });

        buttonOk.setOnMouseClicked( e -> {
            errorMsg.setText("");

            if ( name.getText().length() == 0 ) {
                errorMsg.setText("Введите название кексика! :3");
                return;
            }
            if ( cost.getText().length() == 0 ) {
                errorMsg.setText("Введите стоимость кексика! :3");
                return;
            }

            if ( !cost.getText().matches("^[0-9]+(\\.[0-9]+){1,2}$") ) {
                errorMsg.setText("Введите правильную стоимость кексика! :3");
                return;
            }

            if ( comboboxPastry.getSelectionModel().getSelectedIndex() < 0 ) {
                errorMsg.setText("Выберите тесто для кексика! :3");
                return;
            }
            if ( comboboxStuffing.getSelectionModel().getSelectedIndex() < 0 ) {
                errorMsg.setText("Выберите начинку для кексика! :3");
                return;
            }
            if ( comboboxDimension.getSelectionModel().getSelectedIndex() < 0 ) {
                errorMsg.setText("Выберите размер кексика! :3");
                return;
            }
            if ( comboboxTopping.getSelectionModel().getSelectedIndex() < 0 ) {
                errorMsg.setText("Выберите посыпку для кексика! :3");
                return;
            }

            Cupcake cupcake = new Cupcake(
                    name.getText(),
                    Float.parseFloat(cost.getText()),
                    comboboxPastry.getSelectionModel().getSelectedItem().getCalories() +
                            comboboxStuffing.getSelectionModel().getSelectedItem().getCalories() +
                            comboboxDimension.getSelectionModel().getSelectedItem().getCalories() +
                            comboboxTopping.getSelectionModel().getSelectedItem().getCalories(),
                    comboboxStuffing.getSelectionModel().getSelectedItem().getName(),
                    comboboxDimension.getSelectionModel().getSelectedItem().getName(),
                    comboboxPastry.getSelectionModel().getSelectedItem().getName(),
                    comboboxTopping.getSelectionModel().getSelectedItem().getName()
                    );

            try {
                if ( oldCupcake == null ) {
                    DataBaseController.getInstance().addNewCupcake(cupcake);
                }
                else {
                    DataBaseController.getInstance().updateOldCupcake(oldCupcake.getName(), cupcake);
                }
                onEnd(cupcake);
            }
            catch (Exception ex) {
                errorMsg.setText(ex.getMessage());
                ex.printStackTrace();
            }
        });

        Callback<ListView<Ingredient>,ListCell<Ingredient>> adapter = new Callback<>(){

            @Override
            public ListCell<Ingredient> call(ListView<Ingredient> p) {

                final ListCell<Ingredient> cell = new ListCell<Ingredient>() {

                    @Override
                    protected void updateItem(Ingredient item, boolean empty) {
                        super.updateItem(item, empty);

                        if(item == null || empty){
                            setText(null);
                        }
                        else {
                            setText(item.getName() + " : " + item.getCalories());
                        }
                    }

                };

                return cell;
            }
        };

        comboboxPastry.setCellFactory(adapter);
        comboboxStuffing.setCellFactory(adapter);
        comboboxDimension.setCellFactory(adapter);
        comboboxTopping.setCellFactory(adapter);
        comboboxPastry.setButtonCell(adapter.call(null));
        comboboxStuffing.setButtonCell(adapter.call(null));
        comboboxDimension.setButtonCell(adapter.call(null));
        comboboxTopping.setButtonCell(adapter.call(null));

        composition.setListener(editIngredientListener);

        addPastry.setOnMouseClicked( e -> {
            composition.setEditPastry(null);
            editIngredientTarget = EditIngredientTarget.EditPastry;
            composition.show();
        });
        editPastry.setOnMouseClicked( e -> {
            if (comboboxPastry.getSelectionModel().getSelectedIndex() >= 0) {
                composition.setEditPastry(comboboxPastry.getSelectionModel().getSelectedItem());
                editIngredientTarget = EditIngredientTarget.EditPastry;
                composition.show();
            }
        });
        removePastry.setOnMouseClicked( e -> {
            if (comboboxPastry.getSelectionModel().getSelectedIndex() >= 0) {
               DataBaseController.getInstance().deletePastry(
                       comboboxPastry.getSelectionModel().getSelectedItem().getName());
               updateControlPastry();
            }
        });

        addStuffing.setOnMouseClicked( e -> {
            composition.setEditStuffing(null);
            editIngredientTarget = EditIngredientTarget.EditStuffing;
            composition.show();
        });
        editStuffing.setOnMouseClicked( e -> {
            if (comboboxStuffing.getSelectionModel().getSelectedIndex() >= 0) {
                composition.setEditStuffing(comboboxStuffing.getSelectionModel().getSelectedItem());
                editIngredientTarget = EditIngredientTarget.EditStuffing;
                composition.show();
            }
        });
        removeStuffing.setOnMouseClicked( e -> {
            if (comboboxStuffing.getSelectionModel().getSelectedIndex() >= 0) {
                DataBaseController.getInstance().deleteStuffing(
                        comboboxStuffing.getSelectionModel().getSelectedItem().getName());
                updateControlStuffing();
            }
        });

        addDimension.setOnMouseClicked( e -> {
            composition.setEditDimension(null);
            editIngredientTarget = EditIngredientTarget.EditDimension;
            composition.show();
        });
        editDimension.setOnMouseClicked( e -> {
            if (comboboxDimension.getSelectionModel().getSelectedIndex() >= 0) {
                composition.setEditDimension(comboboxDimension.getSelectionModel().getSelectedItem());
                editIngredientTarget = EditIngredientTarget.EditDimension;
                composition.show();
            }
        });
        removeDimension.setOnMouseClicked( e -> {
            if (comboboxDimension.getSelectionModel().getSelectedIndex() >= 0) {
                DataBaseController.getInstance().deleteDimensions(
                        comboboxDimension.getSelectionModel().getSelectedItem().getName());
                updateControlDimension();
            }
        });

        addTopping.setOnMouseClicked( e -> {
            composition.setEditTopping(null);
            editIngredientTarget = EditIngredientTarget.EditTopping;
            composition.show();
        });
        editTopping.setOnMouseClicked( e -> {
            if (comboboxTopping.getSelectionModel().getSelectedIndex() >= 0) {
                composition.setEditTopping(comboboxTopping.getSelectionModel().getSelectedItem());
                editIngredientTarget = EditIngredientTarget.EditTopping;
                composition.show();
            }
        });
        removeTopping.setOnMouseClicked( e -> {
            if (comboboxTopping.getSelectionModel().getSelectedIndex() >= 0) {
                DataBaseController.getInstance().deleteTopping(
                        comboboxTopping.getSelectionModel().getSelectedItem().getName());
                updateControlTopping();
            }
        });
    }

    private void updateControls() {
        updateControlPastry();
        updateControlStuffing();
        updateControlDimension();
        updateControlTopping();

        cost.setText("");
        name.setText("");
        errorMsg.setText("");
    }

    private void updateControlPastry() {
        comboboxPastry.getItems().clear();
        comboboxPastry.getItems().addAll(DataBaseController.getInstance().getAllPastry());
    }

    private void updateControlStuffing() {
        comboboxStuffing.getItems().clear();
        comboboxStuffing.getItems().addAll(DataBaseController.getInstance().getAllStuffing());
    }

    private void updateControlDimension() {
        comboboxDimension.getItems().clear();
        comboboxDimension.getItems().addAll(DataBaseController.getInstance().getAllDimensions());
    }

    private void updateControlTopping() {
        comboboxTopping.getItems().clear();
        comboboxTopping.getItems().addAll(DataBaseController.getInstance().getAllTopping());
    }


    private IDialogListener<Ingredient> editIngredientListener = new IDialogListener<Ingredient>() {
        public void onStart() {
            FadeTransition ft = new FadeTransition();
            ft.setNode(composition);
            ft.setDuration(new Duration(500));
            ft.setFromValue(0.0);
            ft.setToValue(1.0);
            ft.setCycleCount(1);
            ft.setAutoReverse(true);

            ft.play();
            Edit.this.getChildren().add(composition);
            blurTarget.setEffect(new GaussianBlur(12));
        }

        @Override
        public void onFinish(Ingredient result) {
            Edit.this.getChildren().remove(composition);
            blurTarget.setEffect(null);

            switch (editIngredientTarget) {
                case EditPastry: {
                    updateControlPastry();
                    comboboxPastry.getSelectionModel().select(findElementPosition(comboboxPastry,
                            result != null ? result.getName() : ""));
                } break;
                case EditTopping: {
                    updateControlTopping();
                    comboboxTopping.getSelectionModel().select(findElementPosition(comboboxTopping,
                            result != null ? result.getName() : ""));
                } break;
                case EditStuffing: {
                    updateControlStuffing();
                    comboboxStuffing.getSelectionModel().select(findElementPosition(comboboxStuffing,
                            result != null ? result.getName() : ""));
                } break;
                case EditDimension: {
                    updateControlDimension();
                    comboboxDimension.getSelectionModel().select(findElementPosition(comboboxDimension,
                            result != null ? result.getName() : ""));
                } break;
            }
        }
    };

    private int findElementPosition(ComboBox<Ingredient> combobox, String name) {
        List<Ingredient> list = combobox.getItems();
        int i = 0;
        for ( Ingredient ingredientOnList : list) {
            if (ingredientOnList.getName().equals(name)) {
                return i;
            }
            i++;
        }

        return -1;
    }
}
