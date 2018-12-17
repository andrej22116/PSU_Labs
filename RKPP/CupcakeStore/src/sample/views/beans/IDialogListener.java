package sample.views.beans;

public interface IDialogListener<T> {
    void onStart();
    void onFinish(T result);
}
