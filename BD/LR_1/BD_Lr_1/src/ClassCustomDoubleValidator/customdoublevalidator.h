#ifndef CUSTOMDOUBLEVALIDATOR_H
#define CUSTOMDOUBLEVALIDATOR_H

#include <QDoubleValidator>

class CustomDoubleValidator : public QDoubleValidator
{
public:
    CustomDoubleValidator(QObject* parent = nullptr);
    CustomDoubleValidator(double min, double max, QObject* parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const override;
};

#endif // CUSTOMDOUBLEVALIDATOR_H
