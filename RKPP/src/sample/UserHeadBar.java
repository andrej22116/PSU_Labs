package sample;

import javafx.scene.control.Label;

public class UserHeadBar extends Label {
    private static UserHeadBar ourInstance = new UserHeadBar();

    public static UserHeadBar getInstance() {
        return ourInstance;
    }

    private UserHeadBar() {
    }
}
