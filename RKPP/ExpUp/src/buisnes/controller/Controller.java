package buisnes.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;

import java.io.IOException;
import java.net.URL;

public abstract class Controller implements Initializable {
    private static FXMLLoader loader = new FXMLLoader();

    public Controller(String sourceURL) {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource(sourceURL));
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

    @FXML
    public abstract void initialize();

    public static <T> T get(String srcUrl) {
        try
        {
            return FXMLLoader.<T>load(Controller.class.getResource(srcUrl));
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    public static <T, C> T get(String srcUrl, C controller) {
        loader.setLocation(Controller.class.getResource(srcUrl));
        loader.setRoot(null);
        loader.setController(controller);

        try
        {
            return loader.load();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }

    public static <T, C, R> T get(String srcUrl, C controller, R root) {
        loader.setLocation(Controller.class.getResource(srcUrl));
        loader.setRoot(root);
        loader.setController(controller);

        try
        {
            return loader.load();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }
}
