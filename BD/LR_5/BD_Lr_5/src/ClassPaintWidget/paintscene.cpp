#include "paintscene.h"
#include <QPoint>
#include <QImage>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QtMath>

PaintScene::PaintScene(QObject* parent) : QGraphicsScene(parent)
{
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if ( _currentPaintMode == Line ) {
        beginDrawLine(event->scenePos());
    } else {
        beginDrawFigure(event->scenePos());
    }
}


void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if ( !onPaint ) { return; }

    (this->*_drawingController)(event->scenePos());
}


void PaintScene::beginDrawLine(const QPointF& beginPoint)
{
    onPaint = true;
    addEllipse(beginPoint.x() - 5,
               beginPoint.y() - 5,
               10,
               10,
               QPen(Qt::NoPen),
               QBrush(Qt::red));

    _beginPoint = beginPoint;
}


void PaintScene::drawLine(const QPointF& endPoint)
{
    addLine(_beginPoint.x(),
            _beginPoint.y(),
            endPoint.x(),
            endPoint.y(),
            QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));

    _beginPoint = endPoint;
}


void PaintScene::endDrawLine()
{
    onPaint = false;
}


void PaintScene::beginDrawFigure(const QPointF& beginPoint)
{
    onPaint = true;
    _beginPoint = beginPoint;

    switch(_currentPaintMode) {
    case Square: case Rectangle: {
        _drawingItem = addRect(_beginPoint.x(),
                               _beginPoint.y(),
                               1, 1,
                               QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
    } break;
    case Circle: case Ellipse: {
        _drawingItem = addEllipse(_beginPoint.x(),
                                  _beginPoint.y(),
                                  1, 1,
                                  QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap));
    } break;
    }

    switch(_currentPaintMode) {
    case Line: { _drawingController = &PaintScene::drawLine; } break;
    case Square: { _drawingController = &PaintScene::drawSquare; } break;
    case Rectangle: { _drawingController = &PaintScene::drawRectangle; } break;
    case Circle: { _drawingController = &PaintScene::drawCircle; } break;
    case Ellipse: { _drawingController = &PaintScene::drawEllipse; } break;
    }
}


void PaintScene::drawSquare(const QPointF& endPoint)
{
    auto item = dynamic_cast<QGraphicsRectItem*>(_drawingItem);
    item->setRect(getFigureSquare(endPoint));
}


void PaintScene::drawRectangle(const QPointF& endPoint)
{
    auto item = dynamic_cast<QGraphicsRectItem*>(_drawingItem);
    item->setRect(getFigureRect(endPoint));
}


void PaintScene::drawCircle(const QPointF& endPoint)
{
    auto item = dynamic_cast<QGraphicsEllipseItem*>(_drawingItem);
    item->setRect(getFigureSquare(endPoint));
}


void PaintScene::drawEllipse(const QPointF& endPoint)
{
    auto item = dynamic_cast<QGraphicsEllipseItem*>(_drawingItem);
    item->setRect(getFigureRect(endPoint));
}


void PaintScene::endDrawFigure()
{
    onPaint = false;
    _drawingItem = nullptr;
    _drawingController = nullptr;
}


QRectF PaintScene::getFigureRect(const QPointF& endPoint)
{
    QRectF rect;

    if (_beginPoint.x() < endPoint.x()) {
        rect.setX(_beginPoint.x());
        rect.setWidth(endPoint.x() - rect.x());
    } else {
        rect.setX(endPoint.x());
        rect.setWidth(_beginPoint.x() - rect.x());
    }

    if (_beginPoint.y() < endPoint.y()) {
        rect.setY(_beginPoint.y());
        rect.setHeight(endPoint.y() - rect.y());
    } else {
        rect.setY(endPoint.y());
        rect.setHeight(_beginPoint.y() - rect.y());
    }

    return rect;
}


QRectF PaintScene::getFigureSquare(const QPointF& endPoint)
{
    QRectF rect = getFigureRect(endPoint);

    qreal subX = endPoint.x() - _beginPoint.x();
    qreal subY = endPoint.y() - _beginPoint.y();

    if ( rect.width() < rect.height() ) {
        if (subY < 0) {
            rect.setY(rect.y() + rect.height() - rect.width());
        }
        rect.setHeight(rect.width());
    } else {
        if (subX < 0) {
            rect.setX(rect.x() + rect.width() - rect.height());
        }
        rect.setWidth(rect.height());
    }

    return rect;
}
