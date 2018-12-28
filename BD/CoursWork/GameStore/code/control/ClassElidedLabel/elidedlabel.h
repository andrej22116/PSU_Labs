#ifndef ELIDEDLABEL_H
#define ELIDEDLABEL_H

#include <QLabel>

class QResizeEvent;

class ElidedLabel : public QLabel
{
    QString text;
public:
    ElidedLabel(QWidget* parent);

    void setElidedText(const QString& text);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void updateElidedText();
};

#endif // ELIDEDLABEL_H
