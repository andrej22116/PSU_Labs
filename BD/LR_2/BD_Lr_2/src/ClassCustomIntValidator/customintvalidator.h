#ifndef CUSTOMINTVALIDATOR_H
#define CUSTOMINTVALIDATOR_H

#include <QIntValidator>

class CustomIntValidator : public QIntValidator
{
public:
    CustomIntValidator(QObject* parent = nullptr);
    CustomIntValidator(int min, int max, QObject* parent = nullptr);

    QValidator::State validate(QString &input, int &pos) const override;
};

#endif // CUSTOMINTVALIDATOR_H
