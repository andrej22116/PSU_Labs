package sample.CustomControls;

import javafx.scene.control.TextFormatter;

import java.util.function.UnaryOperator;

public class IntegerTextField extends BaseExtendsTextField {

    private int min = Integer.MIN_VALUE;
    public void setMin(int min) { this.min = min; }
    public int getMin() { return min; }

    private int max = Integer.MAX_VALUE;
    public void setMax(int max) { this.max = max; }
    public int getMax() { return max; }

    public void setRange(int min, int max) {
        this.min = min;
        this.max = max;
    }

    public IntegerTextField()
    {
        init();
    }

    public IntegerTextField(int min, int max)
    {
        setRange(min, max);
        init();
    }

    private void init()
    {
        setStyle("-fx-border-width: 3; -fx-border-color: red;");

        UnaryOperator<TextFormatter.Change> filter = new UnaryOperator<TextFormatter.Change>() {
            @Override
            public TextFormatter.Change apply(TextFormatter.Change change) {
                // Событие, не связанное с изменением текста.
                // Возвращается объект изменения.
                if (!change.isContentChange()) {
                    return change;
                }

                String newText = change.getControlNewText();
                boolean textLengthIsNotZero = newText.length() > 0;
                boolean textLengthIsOne= newText.length() == 1;
                boolean singleCharacterIsPlusOrMinus = textLengthIsOne
                        && (newText.charAt(0) == '-' || newText.charAt(0) == '+');

                // Проверка нового текста на соответствие шаблону.
                if (textLengthIsNotZero && !newText.matches("^(([\\+-]?)((0?)|([1-9][0-9]*)))$")) {
                    setLastChangeState(State.Invalid);
                    return null;
                }

                // Проверка числа на попадание в диапазон.
                if (singleCharacterIsPlusOrMinus) {
                    setLastChangeState(State.Middle);
                    setCurrentState(State.Middle);
                }
                else if (textLengthIsNotZero) {
                    try {
                        int num = Integer.parseInt(newText);
                        if (num < min || num > max){
                            setLastChangeState(State.Invalid);
                            return null;
                        }
                    }
                    catch (Exception ex) {
                        setLastChangeState(State.Invalid);
                        return null;
                    }
                }

                if (!textLengthIsNotZero) {
                    setLastChangeState(State.Invalid);
                    setCurrentState(State.Invalid);
                }
                else if (!singleCharacterIsPlusOrMinus){
                    setLastChangeState(State.Acceptable);
                    setCurrentState(State.Acceptable);
                }

                return change;
            }
        };

        this.setTextFormatter(new TextFormatter<>(filter));
    }


    @Override
    protected void onInvalidText() {
        setStyle("-fx-border-width: 3; -fx-border-color: red;");
    }
    @Override
    protected void onMiddleText() {
        setStyle("-fx-border-width: 3; -fx-border-color: orange;");
    }
    @Override
    protected void onAcceptText() {
        setStyle("-fx-border-width: 3; -fx-border-color: green;");
    }
}
