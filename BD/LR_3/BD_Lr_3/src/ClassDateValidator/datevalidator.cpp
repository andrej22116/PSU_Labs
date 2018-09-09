#include <utility>

#include "datevalidator.h"

DateValidator::DateValidator(QObject* parent)
    : QValidator(parent), _punct('/')
{
}


DateValidator::DateValidator(QChar punct, QObject* parent)
    : QValidator(parent), _punct(punct)
{
}


QValidator::State DateValidator::validate(QString& input, int& pos) const
{
    if ( input.length() > 10 ) { return Invalid; }

    for (const auto ch : input) {
        if (ch == _punct) { continue; }
        if (ch < '0' || ch > '9') { return Invalid; }
    }

    auto tokens = input.split(QString(_punct));
    if ( tokens.size() > 3 ) { return Invalid; }
    if ( tokens.empty() ) { return Intermediate; }



    qint32 day = tokens[0].toUInt();
    if ( tokens[0].length() == 0 ) { return Intermediate; }
    if ( tokens[0].length() > 2 ) { return Invalid; }
    if ( day == 0 || day > 31) { return Invalid; }


    if ( tokens.size() < 2 ) { return Intermediate; }


    static const char amountDaysOnMonth[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    qint32 month = tokens[1].toUInt();
    if ( tokens[1].length() == 0 ) { return Intermediate; }
    if ( tokens[1].length() > 2 ) { return Invalid; }
    if ( month == 0 || month > 12 ) { return Invalid; }
    if ( day > amountDaysOnMonth[month] ) { return Invalid; }


    if ( tokens.size() < 3 ) { return Intermediate; }


    qint32 year = tokens[2].toUInt();
    if ( tokens[2].length() == 0 ) { return Intermediate; }
    if ( tokens[2].length() > 4 ) { return Invalid; }
    if ( month == 2 && day > 28
         && (year % 4 != 0
             || (year % 4 == 0
                 && year % 100 == 0
                 && year % 400 != 0)) ) { return Intermediate; }

    return Acceptable;
}
