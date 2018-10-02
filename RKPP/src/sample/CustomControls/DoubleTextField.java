package sample.CustomControls;

import javafx.scene.control.TextFormatter;

import java.util.function.UnaryOperator;

public class DoubleTextField extends BaseExtendsTextField {


    private double min = -Double.MAX_VALUE;
    public void setMin(double min) { this.min = min; }
    public double getMin() { return min; }

    private double max = Double.MAX_VALUE;
    public void setMax(double max) { this.max = max; }
    public double getMax() { return max; }

    public void setRange(double min, double max) {
        this.min = min;
        this.max = max;
    }

    public DoubleTextField()
    {
        init();
    }

    public DoubleTextField(double min, double max)
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
                boolean dotIsLastSymbol = textLengthIsNotZero && newText.charAt(newText.length() - 1) == '.';

                // Проверка нового текста на соответствие шаблону.
                if (textLengthIsNotZero && !newText.matches("^([\\+-]?)(((0)|([1-9][0-9]*))([\\.,][0-9]*)?)?$")) {
                    setLastChangeState(State.Invalid);
                    return null;
                }

                // Проверка числа на попадание в диапазон.
                if (singleCharacterIsPlusOrMinus || dotIsLastSymbol) {
                    setLastChangeState(State.Middle);
                    setCurrentState(State.Middle);
                }
                else if (textLengthIsNotZero) {
                    try {
                        double num = Double.parseDouble(newText);
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
                else if (!singleCharacterIsPlusOrMinus && !dotIsLastSymbol){
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
