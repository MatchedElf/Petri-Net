// petriplace.cpp

#include "petriplace.h"
#include "qpainter.h"
#include <cmath>


PetriPlace::PetriPlace(QGraphicsItem *parent, QString label)
    : QGraphicsEllipseItem(-40, -40, 80, 80, parent),
    _tokens(0),
    _queueMode(false),
    _label(label)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setBrush(Qt::white);
    setPen(QPen(Qt::black, 2));
}


void PetriPlace::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);

    // Рисуем разделение для режима очереди
    if (_queueMode) {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(-20, 0, 20, 0);
    }

    // Рисуем фишки
    if (_tokens > 0) {
        if (_tokens <= 7) {
            painter->setBrush(Qt::black);
            for (int i = 0; i < _tokens; ++i) {
                double angle = 2 * M_PI * i / _tokens;
                int x = 10 * cos(angle);
                int y = 10 * sin(angle);
                painter->drawEllipse(QPointF(x, y), 3, 3);
            }
        } else {
            painter->setFont(QFont("Arial", 10));
            painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(_tokens));
        }
    }

    // Рисуем метку
    painter->setFont(QFont("Arial", 10));
    QRectF labelRect(-20, -30, 40, 10);
    painter->drawText(labelRect, Qt::AlignCenter, _label);
}

void PetriPlace::setTokens(int count)
{
    _tokens = count;
    update();
}

int PetriPlace::tokens() const
{
    return _tokens;
}

QString PetriPlace::label() const
{
    return _label;
}

QVariant PetriPlace::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        emit positionChanged();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void PetriPlace::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    _tokens++;
    update();
}
