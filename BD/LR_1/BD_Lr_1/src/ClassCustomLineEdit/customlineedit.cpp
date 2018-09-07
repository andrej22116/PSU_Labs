#include "customlineedit.h"
#include "src/ClassCustomIntValidator/customintvalidator.h"
#include <src/ClassCustomDoubleValidator/customdoublevalidator.h>

#include <QStyle>
#include <iostream>

CustomLineEdit::CustomLineEdit(QWidget* parent) : QLineEdit(parent)
{
    init();
}


CustomLineEdit::CustomLineEdit(CustomLineEditType type, QWidget* parent) : QLineEdit(parent)
{
    init();
    setType(type);
}



void CustomLineEdit::onTextEdited(const QString & text)
{
    auto validator = this->validator();
    if (!validator) {
        return;
    }

    int pos = 0;
    auto state = validator->validate(const_cast<QString&>(text), pos);
    setProperty("status", int(state));

    if (styleSheet().length() > 0) {
        this->style()->unpolish(this);
        this->style()->polish(this);
    }
}



void CustomLineEdit::init()
{
    connect(this, &QLineEdit::textChanged, this, &CustomLineEdit::onTextEdited);

    setObjectName("CustomLineEdit");
    setProperty("status", 1);

    setStyleSheet("QLineEdit#CustomLineEdit[status=\"0\"] { border: 2px solid red; }\n"
                  "QLineEdit#CustomLineEdit[status=\"1\"] { border: 2px solid orange; }\n"
                  "QLineEdit#CustomLineEdit[status=\"2\"] { border: 2px solid green; }");
}


void CustomLineEdit::setIntegerEditor()
{
    _currentType = EditType_Integer;
    this->setValidator(new CustomIntValidator());
}


void CustomLineEdit::setDoubleEditor()
{
    _currentType = EditType_Double;
    this->setValidator(new CustomDoubleValidator());
}


void CustomLineEdit::setStringEditor()
{
    _currentType = EditType_String;
    this->setValidator(nullptr);
}


CustomLineEdit* CustomLineEdit::setType(CustomLineEditType type)
{
    switch(type) {
    case EditType_Integer: { setIntegerEditor(); } break;
    case EditType_Double: { setDoubleEditor(); } break;
    case EditType_String: { setStringEditor(); } break;
    }

    return this;
}

CustomLineEdit* CustomLineEdit::setInterval(double min, double max)
{
    switch(_currentType) {
    case EditType_Integer: { setValidator(new CustomIntValidator(int(min), int(max))); } break;
    case EditType_Double: { setValidator(new CustomDoubleValidator(min, max)); } break;
    }

    return this;
}
