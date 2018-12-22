package buisnes;

import buisnes.controller.dialog.AthletDialog;
import buisnes.database.*;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldListCell;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.util.Callback;
import javafx.util.StringConverter;
import model.*;

import java.net.URL;
import java.sql.Date;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Optional;
import java.util.ResourceBundle;

public class MainController implements Initializable {
    @FXML
    public StackPane window;
    @FXML
    public TableView athleteTable;
    @FXML
    public Button buttonAddToAthleteTable;
    @FXML
    public Button buttonEditInAthleteTable;
    @FXML
    public Button buttonRemoveOnAthleteTable;
    @FXML
    public ListView listPhysicalDates;
    @FXML
    public Button buttonAddToPhysicalList;
    @FXML
    public Button buttonRemoveFromPhysicalList;
    @FXML
    public Label labelPhysicalMass;
    @FXML
    public Label labelPhysicalBicepsGirth;
    @FXML
    public Label labelPhysicalChestGirth;
    @FXML
    public Label labelPhysicalWaistGirth;
    @FXML
    public Label labelPhysicalLegGirth;
    @FXML
    public Label labelPhysicalWeightOnBiceps;
    @FXML
    public Label labelPhysicalWeightOnChest;
    @FXML
    public Label labelPhysicalWeightOnFoot;
    @FXML
    public Label labelPhysicalWeightOnBack;
    @FXML
    public Label labelPhysicalBackWidth;
    @FXML
    public Label labelPhysicalMassAndFatRatio;
    @FXML
    public Label labelPhysicalFixationDate;
    @FXML
    public ListView listBodyCheckDates;
    @FXML
    public Button buttonAddToBodyCheckList;
    @FXML
    public Button buttonRemoveFromBodyCheckList;
    @FXML
    public CheckBox checkboxBodyCheckTherapist;
    @FXML
    public CheckBox checkboxBodyCheckSurgeon;
    @FXML
    public CheckBox checkboxBodyCheckOculist;
    @FXML
    public CheckBox checkboxBodyCheckEndDoctor;
    @FXML
    public CheckBox checkboxBodyCheckDopingTest;
    @FXML
    public Label labelBodyCheckConclusion;
    @FXML
    public ListView listVisits;
    @FXML
    public Button buttonAddToVisitsList;
    @FXML
    public Button buttonRemoveFromVisitsList;
    @FXML
    public ListView listPayment;
    @FXML
    public Button buttonAddToPaymentList;
    @FXML
    public Button buttonRemoveFromPaymentList;
    @FXML
    public GridPane infoPhysical;
    @FXML
    public VBox infoBodyCheck;
    @FXML
    public Button buttonEditInPaymentList;
    @FXML
    public Button buttonEditInVisitsList;
    @FXML
    public Button buttonRicardo;
    @FXML
    public ImageView ricardo;

    @FXML @Override
    public void initialize(URL location, ResourceBundle resources) {
        initAthlete();
        initPhysicalCharacteristics();
        initBodyCheck();
        initVisits();
        initPayment();

        buttonRicardo.setOnMouseClicked( event -> {
            ricardo.setVisible(!ricardo.isVisible());
        });
    }

    ////////////////

    private void initAthlete() {
        initAthleteTable();
        initAthleteActions();
    }

    private void initAthleteTable() {
        athleteTable.setItems(athleteList);
        ObservableList<TableColumn> columns = athleteTable.getColumns();
        TableColumn<Athlete, Integer> columnSurName = columns.get(0);
        columnSurName.setCellValueFactory(new PropertyValueFactory<>("surName"));
        TableColumn<Athlete, String> columnName = columns.get(1);
        columnName.setCellValueFactory(new PropertyValueFactory<>("name"));
        TableColumn<Athlete, String> columnMiddleNamee = columns.get(2);
        columnMiddleNamee.setCellValueFactory(new PropertyValueFactory<>("middleName"));
        TableColumn<Athlete, Integer> columnAge = columns.get(3);
        columnAge.setCellValueFactory(new PropertyValueFactory<>("age"));
        TableColumn<Athlete, String> columnSex = columns.get(4);
        columnSex.setCellValueFactory(cell -> new SimpleStringProperty(cell.getValue().isFemale() ? "Дефка" : "Мужыг"));

        athleteTable.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        loadAllAthletes();
    }

    private void initAthleteActions() {
        buttonRemoveOnAthleteTable.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                deleteSelectedAthleteFromTable();
            }
        });

        athleteTable.getSelectionModel().selectedItemProperty().addListener( (event) -> {
            if (athleteTable.getSelectionModel().getSelectedIndex() < 0) {

            }
            else {
                Athlete athlete = getSelectedAthleteFromTable();
                loadAllPhysicalCharacteristics(athlete);
                loadAllBodyChecks(athlete);
                loadAllVisits(athlete);
                loadAllPayments(athlete);
            }
        });

        buttonAddToAthleteTable.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                AthletDialog dialog = new AthletDialog(buttonAddToAthleteTable.getScene().getWindow(), new Athlete());
                Optional<Athlete> dialogResult = dialog.showAndWait();
                dialogResult.ifPresent(AthleteDatabaseTable::insert);
            }
        });

        buttonEditInAthleteTable.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                Athlete athlete = getSelectedAthleteFromTable();
                if (athlete == null) return;

                AthletDialog dialog = new AthletDialog(buttonAddToAthleteTable.getScene().getWindow(), athlete);
                Optional<Athlete> dialogResult = dialog.showAndWait();
                dialogResult.ifPresent(AthleteDatabaseTable::update);
            }
        });
    }


    //////////////////

    private void initPhysicalCharacteristics() {
        initPhysicalCharacteristicsList();
        initPhysicalCharacteristicsActions();

        hidePhysicalCharacteristics();
    }

    private void initPhysicalCharacteristicsList() {
        listPhysicalDates.setItems(physicalCharacteristicsList);
        listPhysicalDates.setEditable(true);

        listPhysicalDates.setCellFactory(lv -> {
            TextFieldListCell<PhysicalCharacteristics> cell = new TextFieldListCell<>();
            cell.setConverter(new StringConverter<PhysicalCharacteristics>() {
                @Override
                public String toString(PhysicalCharacteristics client) {
                    return client.getFixationDate().toString();
                }

                @Override
                public PhysicalCharacteristics fromString(String string) {
                    PhysicalCharacteristics client = cell.getItem();
                    try {
                        client.setFixationDate(
                                new Date( new SimpleDateFormat("yyyy-MM-dd").parse(string).getTime()) );
                        PhysicalCharacteristicsDatabaseTable.update(client);
                    }
                    catch (ParseException e) {
                        e.printStackTrace();
                    }

                    return client;
                }

            });
            return cell ;
        });
    }

    private void initPhysicalCharacteristicsActions() {
        listPhysicalDates.getSelectionModel().selectedItemProperty().addListener( event -> {
            if (listPhysicalDates.getSelectionModel().getSelectedIndex() < 0) {
                hidePhysicalCharacteristics();
            }
            else {
                PhysicalCharacteristics physicalCharacteristics = getSelectedPhysicalCharacteristics();
                showPhysicalCharacteristics(physicalCharacteristics);
            }
        });

        buttonRemoveFromPhysicalList.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                deleteSelectedPhysicalCharacteristics();
            }
        });

        buttonAddToPhysicalList.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                Athlete athlete = getSelectedAthleteFromTable();
                if ( athlete == null ) {
                    return;
                }

                PhysicalCharacteristics physicalCharacteristics = new PhysicalCharacteristics();
                physicalCharacteristics.setFixationDate(new java.sql.Date(new java.util.Date().getTime()));
                physicalCharacteristics.setIdAthlete(athlete.getId());

                PhysicalCharacteristicsDatabaseTable.insert(physicalCharacteristics);
                if (physicalCharacteristics.getId() > 0) {
                    physicalCharacteristicsList.add(physicalCharacteristics);
                }
            }
        });
    }

    //////////////////

    private void initBodyCheck() {
        initBodyCheckList();
        initBodyCheckActions();

        hideBodyCheck();
    }

    private void initBodyCheckList() {
        listBodyCheckDates.setItems(bodyCheckList);
        listBodyCheckDates.setEditable(true);

        listBodyCheckDates.setCellFactory(lv -> {
            TextFieldListCell<BodyCheck> cell = new TextFieldListCell<>();
            cell.setConverter(new StringConverter<BodyCheck>() {
                @Override
                public String toString(BodyCheck client) {
                    return client.getFixationDate().toString();
                }

                @Override
                public BodyCheck fromString(String string) {
                    BodyCheck client = cell.getItem();
                    try {
                        client.setFixationDate(
                                new Date( new SimpleDateFormat("yyyy-MM-dd").parse(string).getTime()) );
                        BodyCheckDatabaseTable.update(client);
                    }
                    catch (ParseException e) {
                        e.printStackTrace();
                    }

                    return client;
                }

            });
            return cell ;
        });
    }

    private void initBodyCheckActions() {
        listBodyCheckDates.getSelectionModel().selectedItemProperty().addListener( event -> {
            if (listBodyCheckDates.getSelectionModel().getSelectedIndex() < 0) {
                hideBodyCheck();
            }
            else {
                BodyCheck bodyCheck = getSelectedBodyCheck();
                showBodyCheck(bodyCheck);
            }
        });

        buttonRemoveFromBodyCheckList.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                deleteSelectedBodyCheck();
            }
        });

        buttonAddToBodyCheckList.setOnMouseClicked( event -> {
            if (event.getButton() == MouseButton.PRIMARY) {
                Athlete athlete = getSelectedAthleteFromTable();
                if ( athlete == null ) {
                    return;
                }

                BodyCheck bodyCheck = new BodyCheck();
                bodyCheck.setFixationDate(new java.sql.Date(new java.util.Date().getTime()));
                bodyCheck.setIdAthlete(athlete.getId());

                BodyCheckDatabaseTable.insert(bodyCheck);
                if (bodyCheck.getId() > 0) {
                    bodyCheckList.add(bodyCheck);
                }
            }
        });

        checkboxBodyCheckDopingTest.selectedProperty().addListener(
                event -> getSelectedBodyCheck().setDopingTest(checkboxBodyCheckDopingTest.isSelected())
        );
        checkboxBodyCheckEndDoctor.selectedProperty().addListener(
                event -> getSelectedBodyCheck().setEndDoctor(checkboxBodyCheckEndDoctor.isSelected())
        );
        checkboxBodyCheckOculist.selectedProperty().addListener(
                event -> getSelectedBodyCheck().setOculist(checkboxBodyCheckOculist.isSelected())
        );
        checkboxBodyCheckSurgeon.selectedProperty().addListener(
                event -> getSelectedBodyCheck().setSurgeon(checkboxBodyCheckSurgeon.isSelected())
        );
        checkboxBodyCheckTherapist.selectedProperty().addListener(
                event -> getSelectedBodyCheck().setTherapist(checkboxBodyCheckTherapist.isSelected())
        );
    }

    //////////////////

    private void initVisits() {
        listVisits.setItems(visitList);
        listVisits.setCellFactory((Callback<ListView<Visit>, ListCell<Visit>>) listView -> new VisitItemCell());
    }

    //////////////////

    private void initPayment() {
        listPayment.setItems(paymentList);
        listPayment.setCellFactory((Callback<ListView<Payment>, ListCell<Payment>>) listView -> new PaymentItemCell());
    }

    /////////////////////////////////////////////////////

    private ObservableList<Athlete> athleteList = FXCollections.observableArrayList();

    private void loadAllAthletes() {
        List<Athlete> list = AthleteDatabaseTable.getAll();
        athleteList.clear();
        athleteList.addAll(list);
    }

    private void addAthleteToTable(Athlete athlete) {
        athleteList.add(athlete);
        AthleteDatabaseTable.insert(athlete);
    }

    private void updateSelectedAthleteInDatabase() {
        Athlete athlete = getSelectedAthleteFromTable();
        if (athlete == null) {
            return;
        }

        AthleteDatabaseTable.update(athlete);
    }

    private Athlete getSelectedAthleteFromTable() {
        return (Athlete)athleteTable.getSelectionModel().getSelectedItem();
    }

    private void deleteSelectedAthleteFromTable() {
        Athlete athlete = getSelectedAthleteFromTable();
        if (athlete == null) {
            return;
        }

        AthleteDatabaseTable.delete(athlete);
        athleteList.remove(athlete);
    }

    /////////////////////////////////////////////////////
    private ObservableList<PhysicalCharacteristics> physicalCharacteristicsList = FXCollections.observableArrayList();

    private void loadAllPhysicalCharacteristics(Athlete athlete) {
        List<PhysicalCharacteristics> list = PhysicalCharacteristicsDatabaseTable.getAll(athlete);
        physicalCharacteristicsList.clear();
        physicalCharacteristicsList.setAll(list);
    }

    private void deleteSelectedPhysicalCharacteristics() {
        PhysicalCharacteristics physicalCharacteristics = getSelectedPhysicalCharacteristics();
        if (physicalCharacteristics == null) {
            return;
        }

        physicalCharacteristicsList.remove(physicalCharacteristics);
        PhysicalCharacteristicsDatabaseTable.delete(physicalCharacteristics);
    }

    private PhysicalCharacteristics getSelectedPhysicalCharacteristics() {
        return (PhysicalCharacteristics)listPhysicalDates.getSelectionModel().getSelectedItem();
    }

    private void hidePhysicalCharacteristics() {
        infoPhysical.setVisible(false);
    }

    private void showPhysicalCharacteristics(PhysicalCharacteristics physicalCharacteristics) {
        infoPhysical.setVisible(true);
        labelPhysicalMass.setText("" + physicalCharacteristics.getMass());
        labelPhysicalBackWidth.setText("" + physicalCharacteristics.getBackWidth());
        labelPhysicalBicepsGirth.setText("" + physicalCharacteristics.getBicepsGirth());
        labelPhysicalChestGirth.setText("" + physicalCharacteristics.getChestGirth());
        labelPhysicalLegGirth.setText("" + physicalCharacteristics.getLegGirth());
        labelPhysicalMassAndFatRatio.setText("" + physicalCharacteristics.getMassAndFatRatio());
        labelPhysicalWaistGirth.setText("" + physicalCharacteristics.getWaistGirth());
        labelPhysicalWeightOnBack.setText("" + physicalCharacteristics.getWeightOnBack());
        labelPhysicalWeightOnBiceps.setText("" + physicalCharacteristics.getWeightOnBiceps());
        labelPhysicalWeightOnChest.setText("" + physicalCharacteristics.getWeightOnChest());
        labelPhysicalWeightOnFoot.setText("" + physicalCharacteristics.getWeightOnFoot());
    }


    /////////////////////////////////////////////////////
    private ObservableList<BodyCheck> bodyCheckList = FXCollections.observableArrayList();
    private ChangeListener<Boolean> bodyCheckChangeListener = (observable, oldValue, newValue) ->
            BodyCheckDatabaseTable.update(getSelectedBodyCheck());

    private void loadAllBodyChecks(Athlete athlete) {
        List<BodyCheck> list = BodyCheckDatabaseTable.getAll(athlete);
        bodyCheckList.clear();
        bodyCheckList.setAll(list);
    }

    private BodyCheck getSelectedBodyCheck() {
        return (BodyCheck)listBodyCheckDates.getSelectionModel().getSelectedItem();
    }

    private void deleteSelectedBodyCheck() {
        BodyCheck bodyCheck = getSelectedBodyCheck();
        if (bodyCheck == null) {
            return;
        }

        BodyCheckDatabaseTable.delete(bodyCheck);
        bodyCheckList.remove(bodyCheck);
    }

    private void hideBodyCheck() {
        infoBodyCheck.setVisible(false);
    }

    private void showBodyCheck(BodyCheck bodyCheck) {
        infoBodyCheck.setVisible(true);
        removeBodyCheckUpdateEvents();
        checkboxBodyCheckDopingTest.setSelected(bodyCheck.isDopingTest());
        checkboxBodyCheckEndDoctor.setSelected(bodyCheck.isEndDoctor());
        checkboxBodyCheckOculist.setSelected(bodyCheck.isOculist());
        checkboxBodyCheckSurgeon.setSelected(bodyCheck.isSurgeon());
        checkboxBodyCheckTherapist.setSelected(bodyCheck.isTherapist());
        labelBodyCheckConclusion.setText(bodyCheck.getConclusion());
        addBodyCheckUpdateEvents();
    }

    private void addBodyCheckUpdateEvents() {
        checkboxBodyCheckDopingTest.selectedProperty().addListener(bodyCheckChangeListener);
        checkboxBodyCheckEndDoctor.selectedProperty().addListener(bodyCheckChangeListener);
        checkboxBodyCheckOculist.selectedProperty().addListener(bodyCheckChangeListener);
        checkboxBodyCheckSurgeon.selectedProperty().addListener(bodyCheckChangeListener);
        checkboxBodyCheckTherapist.selectedProperty().addListener(bodyCheckChangeListener);
    }

    private void removeBodyCheckUpdateEvents() {
        checkboxBodyCheckDopingTest.selectedProperty().removeListener(bodyCheckChangeListener);
        checkboxBodyCheckEndDoctor.selectedProperty().removeListener(bodyCheckChangeListener);
        checkboxBodyCheckOculist.selectedProperty().removeListener(bodyCheckChangeListener);
        checkboxBodyCheckSurgeon.selectedProperty().removeListener(bodyCheckChangeListener);
        checkboxBodyCheckTherapist.selectedProperty().removeListener(bodyCheckChangeListener);
    }



    /////////////////////////////////////////////////////
    private ObservableList<Visit> visitList = FXCollections.observableArrayList();

    private void loadAllVisits(Athlete athlete) {
        List<Visit> list = VisitsDatabaseTable.getAll(athlete);
        visitList.clear();
        visitList.setAll(list);
    }

    /////////////////////////////////////////////////////
    private ObservableList<Payment> paymentList = FXCollections.observableArrayList();

    private void loadAllPayments(Athlete athlete) {
        List<Payment> list = PaymentDatabaseTable.getAll(athlete);
        paymentList.clear();
        paymentList.setAll(list);
    }
}
