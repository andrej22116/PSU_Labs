package sample.CustomControls;

import javafx.scene.control.TextField;

public abstract class BaseExtendsTextField extends TextField {
    public enum State {
        Invalid,
        Middle,
        Acceptable
    }

    private State lastTextChangeState = State.Invalid;
    private State currentTextState = State.Invalid;

    public State getState() { return currentTextState; }
    protected void setCurrentState(State state) { currentTextState = state; }
    protected void setLastChangeState(State state) { lastTextChangeState = state; }

    public BaseExtendsTextField() {
        textProperty().addListener((observer, oldValue, newValue) -> {
            switch (lastTextChangeState) {
                case Invalid: { onInvalidTextChange(); } break;
                case Middle: { onMiddleTextChange(); } break;
                case Acceptable: { onAcceptTextChange(); } break;
            }

            switch (currentTextState) {
                case Invalid: { onInvalidText(); } break;
                case Middle: { onMiddleText(); } break;
                case Acceptable: { onAcceptText(); } break;
            }
        });
    }

    protected void onInvalidTextChange() {}
    protected void onMiddleTextChange() {}
    protected void onAcceptTextChange() {}

    protected void onInvalidText() {}
    protected void onMiddleText() {}
    protected void onAcceptText() {}
}
