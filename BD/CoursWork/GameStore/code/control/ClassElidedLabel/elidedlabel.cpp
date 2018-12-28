#include "elidedlabel.h"
#include <QResizeEvent>
#include <QFontMetricsF>

ElidedLabel::ElidedLabel(QWidget* parent) : QLabel(parent)
{

}

void ElidedLabel::setElidedText(const QString& text)
{
    this->text = text;
    updateElidedText();

}

void ElidedLabel::resizeEvent(QResizeEvent* event)
{
    updateElidedText();
}

void ElidedLabel::updateElidedText()
{
    QFontMetricsF fontMetrics(this->font());
    this->setText(fontMetrics.elidedText(this->text, Qt::TextElideMode::ElideRight, this->width()));
}
