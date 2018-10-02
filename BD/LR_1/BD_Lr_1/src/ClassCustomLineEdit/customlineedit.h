#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>

class CustomLineEdit : public QLineEdit
{
public:
    enum CustomLineEditType {
        EditType_Integer = 0,
        EditType_Double = 1,
        EditType_String = 2
    };


private:
    CustomLineEditType _currentType = EditType_String;

public:
    explicit CustomLineEdit(QWidget* parent = nullptr);
    explicit CustomLineEdit(CustomLineEditType type, QWidget* parent = nullptr);
    ~CustomLineEdit() = default;

    CustomLineEdit* setType(CustomLineEditType type = EditType_String);
    CustomLineEdit* setInterval(double min, double max);

private slots:
    void onTextEdited(const QString & text);

private:
    void init();

    void setIntegerEditor();
    void setDoubleEditor();
    void setStringEditor();
};

#endif // CUSTOMLINEEDIT_H
