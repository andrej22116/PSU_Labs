#include "customdoublevalidator.h"

CustomDoubleValidator::CustomDoubleValidator(QObject* parent) : QDoubleValidator(parent)
{
}

CustomDoubleValidator::CustomDoubleValidator(double min, double max, QObject* parent)
    : QDoubleValidator(min, max, 1000, parent)
{
}


QValidator::State CustomDoubleValidator::validate(QString &input, int &pos) const
{
    if ( ((input.length() == 1) && (input[0] == ','))
         || ((input.length() > 1) && (input[0] == '0')
             && (input[1] != '.') && (input[1] != ',')) ) {
        return State::Invalid;
    }

    return QDoubleValidator::validate(input, pos);
}
