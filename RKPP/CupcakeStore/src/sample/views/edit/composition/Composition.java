package sample.views.edit.composition;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import sample.database.DataBaseController;
import sample.views.beans.IDialogListener;
import sample.views.beans.Ingredient;

import java.io.IOException;
import java.sql.SQLException;
import java.util.Locale;

public class Composition extends GridPane {
    public Composition() {
        create();
    }

    private void create() {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("composition.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        fxmlLoader.setClassLoader(getClass().getClassLoader());

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }


    IDialogListener<Ingredient> listener;

    public void setListener(IDialogListener<Ingredient> listener) {
        this.listener = listener;
    }

    @FXML
    public Button buttonOk;
    @FXML
    public Button buttonCancel;

    @FXML
    public Label title;
    @FXML
    public TextField name;
    @FXML
    public TextField calories;
    @FXML
    public Label errorMsg;


    private enum EditCompositionTarget {
        EditPastry {
            public void onCancelEdit(Ingredient oldIngredient, Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().updateOldPastry(oldIngredient.getName(),
                        newIngredient.getName(), newIngredient.getCalories());
            }
            public void onCancelEdit(Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().addNewPastry(newIngredient.getName(), newIngredient.getCalories());
            }
        },
        EditStuffing {
            public void onCancelEdit(Ingredient oldIngredient, Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().updateOldStuffing(oldIngredient.getName(),
                        newIngredient.getName(), newIngredient.getCalories());
            }
            public void onCancelEdit(Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().addNewStuffing(newIngredient.getName(), newIngredient.getCalories());
            }
        },
        EditDimension {
            public void onCancelEdit(Ingredient oldIngredient, Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().updateOldDimensions(oldIngredient.getName(),
                        newIngredient.getName(), newIngredient.getCalories());
            }
            public void onCancelEdit(Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().addNewDimensions(newIngredient.getName(), newIngredient.getCalories());
            }
        },
        EditTopping {
            public void onCancelEdit(Ingredient oldIngredient, Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().updateOldTopping(oldIngredient.getName(),
                        newIngredient.getName(), newIngredient.getCalories());
            }
            public void onCancelEdit(Ingredient newIngredient) throws SQLException {
                DataBaseController.getInstance().addNewTopping(newIngredient.getName(), newIngredient.getCalories());
            }
        };

        public abstract void onCancelEdit(Ingredient oldIngredient, Ingredient newIngredient) throws SQLException;
        public abstract void onCancelEdit(Ingredient newIngredient) throws SQLException;
    }
    private EditCompositionTarget editCompositionTarget;
    private Ingredient oldIngredient;

    @FXML
    public void initialize() {
        title.setText("");
        name.setText("");
        calories.setText("");

        buttonOk.setOnMouseClicked( e -> {
            errorMsg.setText("");

            if ( name.getText().length() == 0 ) {
                errorMsg.setText("Установите название ингредиента! :3");
                return;
            }
            if ( !calories.getText().matches("^[0-9]+(\\.[0-9]+)*$") ) {
                errorMsg.setText("Установите цифровое значение калорийности ингредиента! :3");
                return;
            }

            try {
                Ingredient ingredient = new Ingredient(name.getText(), Float.parseFloat(calories.getText()));

                if (oldIngredient != null) {
                    editCompositionTarget.onCancelEdit(oldIngredient, ingredient);
                }
                else {
                    editCompositionTarget.onCancelEdit(ingredient);
                }

                if ( listener != null ) {
                    listener.onFinish(ingredient);
                }
            }
            catch (Exception ex) {
                errorMsg.setText(ex.getMessage());
                ex.printStackTrace();
            }
        });

        buttonCancel.setOnMouseClicked( e -> {
            if ( listener != null ) listener.onFinish(null);
        });
    }

    public void setEditPastry(Ingredient ingredient) {
        setEditParams(ingredient, "Add pastry :3", "Edit pastry :3");
        editCompositionTarget = EditCompositionTarget.EditPastry;
    }
    public void setEditStuffing(Ingredient ingredient) {
        setEditParams(ingredient, "Add stuffing :3", "Edit stuffing :3");
        editCompositionTarget = EditCompositionTarget.EditStuffing;
    }
    public void setEditDimension(Ingredient ingredient) {
        setEditParams(ingredient, "Add dimension :3", "Edit dimension :3");
        editCompositionTarget = EditCompositionTarget.EditDimension;
    }
    public void setEditTopping(Ingredient ingredient) {
        setEditParams(ingredient, "Add topping :3", "Edit topping :3");
        editCompositionTarget = EditCompositionTarget.EditTopping;
    }
    private void setEditParams(Ingredient ingredient, String add, String edit) {
        this.oldIngredient = ingredient;
        errorMsg.setText("");

        if (ingredient == null) {
            this.title.setText(add);
            name.setText("");
            calories.setText("");
        }
        else {
            this.title.setText(edit);
            name.setText(ingredient.getName());
            calories.setText(String.format(Locale.US, "%f", ingredient.getCalories()));
        }
    }

    public void show() {
        if ( listener != null ) listener.onStart();
    }
}
