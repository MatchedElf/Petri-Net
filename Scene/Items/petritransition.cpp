// petritransition.cpp

#include "petritransition.h"
#include "qpainter.h"


PetriTransition::PetriTransition(QGraphicsItem *parent, QString label = QString(""))
    : QGraphicsRectItem(-10, -40, 20, 80, parent),
    _firingTime(0),
    _priority(0),
    _label(label)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setBrush(Qt::black);
    setPen(QPen(Qt::black, 2));
}


void PetriTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    // Рисуем временные параметры
    painter->setPen(QPen(Qt::white));
    if (_firingTime > 0) {
        painter->setFont(QFont("Arial", 7));
        QString timeText = QString::number(_firingTime);
        if (_timeInterval.first > 0 || _timeInterval.second < std::numeric_limits<double>::max()) {
            timeText += QString(" [%1,%2]").arg(_timeInterval.first).arg(_timeInterval.second);
        }
        painter->drawText(QRectF(-15, -20, 30, 15), Qt::AlignCenter, timeText);
    }

    // Рисуем приоритет
    if (_priority > 0) {
        painter->setFont(QFont("Arial", 8, QFont::Bold));
        painter->drawText(QRectF(-15, 5, 30, 15), Qt::AlignCenter, QString::number(_priority));
    }

    // Рисуем метку
    painter->setFont(QFont("Arial", 10));
    QRectF labelRect(-20, -30, 40, 10);
    painter->drawText(labelRect, Qt::AlignCenter, _label);
}


QVariant PetriTransition::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        emit positionChanged();
    }
    return QGraphicsRectItem::itemChange(change, value);
}



void PetriTransition::addPlace(PetriPlace * place, bool from)
{
    if(from)
        _fromPlacesList.append(place);
    else
        _toPlacesList.append(place);
}

QString PetriTransition::label() const
{
    return _label;
}
