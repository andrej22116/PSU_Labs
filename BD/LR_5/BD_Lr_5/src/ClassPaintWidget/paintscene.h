#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QGraphicsScene>

class QImage;
class QGraphicsItem;

class PaintScene : public QGraphicsScene
{
public:
    enum PaintMode {
        Line,
        Square,
        Rectangle,
        Circle,
        Ellipse
    };

    enum FillMode {
        Full,
        VerticalLines,
        HorizontalLines
    };


private:
    bool onPaint = false;
    PaintMode _currentPaintMode = Circle;
    QPointF _beginPoint;
    QGraphicsItem* _drawingItem = nullptr;

    QBrush _fillBrush;
    QColor _fillColor;

    Q_OBJECT
public:
    explicit PaintScene(QObject *parent = nullptr);

    void setPaintMode(PaintMode newPaintMode);

    void setFillColor(QColor newColor);
    void setFillMode(FillMode newFillMode);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void beginDrawFigure(const QPointF& beginPoint);
    void drawLine(const QPointF& endPoint);
    void drawSquare(const QPointF& endPoint);
    void drawRectangle(const QPointF& endPoint);
    void drawCircle(const QPointF& endPoint);
    void drawEllipse(const QPointF& endPoint);
    void endDrawFigure();

    QRectF getFigureRect(const QPointF& endPoint);
    QRectF getFigureSquare(const QPointF& endPoint);

    using DrawingController = decltype(&PaintScene::drawSquare);
    DrawingController _drawingController = nullptr;
};

#endif // PAINTWIDGET_H
