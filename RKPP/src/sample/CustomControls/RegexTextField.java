package sample.CustomControls;

import javafx.scene.control.TextFormatter;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.List;
import java.util.function.UnaryOperator;

public class RegexTextField extends BaseExtendsTextField {
    private List<Pair<String, State>> regStateList = new ArrayList<Pair<String, State>>();

    public RegexTextField()
    {
        init();
    }

    public void addState(String regex, State state) {
        regStateList.add(new Pair<String, State>(regex, state));
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

                // Проверка нового текста на соответствие шаблону.
                for (Pair<String, State> pair : regStateList) {
                    if (newText.matches(pair.getKey())) {
                        setLastChangeState(pair.getValue());
                        setCurrentState(pair.getValue());
                        return change;
                    }
                }

                setLastChangeState(State.Invalid);
                return null;
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
