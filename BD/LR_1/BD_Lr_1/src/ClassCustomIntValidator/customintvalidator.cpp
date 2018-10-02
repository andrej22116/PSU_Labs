#include "customintvalidator.h"

CustomIntValidator::CustomIntValidator(QObject* parent) : QIntValidator(parent)
{
}

CustomIntValidator::CustomIntValidator(int min, int max, QObject* parent)
    : QIntValidator(min, max, parent)
{
}

QValidator::State CustomIntValidator::validate(QString &input, int &pos) const
{
    if ( (input.length() > 1 && input[0] == '0')
         || (input.length() > 1 && input[0] == '-' && input[1] == '0') ) {
        return State::Invalid;
    }

    return QIntValidator::validate(input, pos);
}
