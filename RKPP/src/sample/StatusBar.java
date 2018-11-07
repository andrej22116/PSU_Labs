package sample;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.control.Label;
import javafx.util.Duration;

public class StatusBar {
    private static StatusBar ourInstance = new StatusBar();

    public static StatusBar getInstance() {
        return ourInstance;
    }

    private Label label;

    private Timeline timer;

    private StatusBar() {}

    public void setLabel(Label label) { this.label = label; }

    public static void s_showMessage(String text) {
        getInstance().showMessage(text);
    }

    public static void s_showMessage(String text, double seconds) {
        getInstance().showMessage(text, seconds);
    }

    public void showMessage(String text) {
        label.setText(text);
        stopTimer();
    }

    public void showMessage(String text, double seconds) {
        label.setText(text);
        stopTimer();
        startTimerForCleanText(seconds);
    }

    void startTimerForCleanText(double seconds) {
        timer = new Timeline(
            new KeyFrame(
                Duration.seconds(seconds),
                ae -> {
                    if (StatusBar.this.label != null) {
                        StatusBar.this.showMessage("");
                    }
                }
            )
        );
        timer.setCycleCount(1);
        timer.play();
    }

    private void stopTimer() {
        if (timer != null) {
            timer.stop();
        }
    }
}
