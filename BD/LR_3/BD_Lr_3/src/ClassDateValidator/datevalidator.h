#ifndef DATEVALIDATOR_H
#define DATEVALIDATOR_H

#include <QValidator>

class DateValidator : public QValidator
{
    QChar _punct;

public:
    DateValidator(QObject* parent = nullptr);
    DateValidator(QChar punct, QObject* parent = nullptr);

    State validate(QString& input, int& pos) const override;
};

#endif // DATEVALIDATOR_H
