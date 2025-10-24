// petritransition.cpp
#include "petritransition.h"
#include "qpainter.h"


PetriTransition::PetriTransition(QGraphicsItem *parent)
    : QGraphicsRectItem(-10, -40, 20, 80, parent),
    m_firingTime(0),
    m_priority(0),
    m_label("t0")
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
    if (m_firingTime > 0) {
        painter->setFont(QFont("Arial", 7));
        QString timeText = QString::number(m_firingTime);
        if (m_timeInterval.first > 0 || m_timeInterval.second < std::numeric_limits<double>::max()) {
            timeText += QString(" [%1,%2]").arg(m_timeInterval.first).arg(m_timeInterval.second);
        }
        painter->drawText(QRectF(-15, -20, 30, 15), Qt::AlignCenter, timeText);
    }

    // Рисуем приоритет
    if (m_priority > 0) {
        painter->setFont(QFont("Arial", 8, QFont::Bold));
        painter->drawText(QRectF(-15, 5, 30, 15), Qt::AlignCenter, QString::number(m_priority));
    }

    // Рисуем метку
    painter->setFont(QFont("Arial", 8));
    QRectF labelRect(-15, -40, 30, 10);
    painter->drawText(labelRect, Qt::AlignCenter, m_label);
}

QVariant PetriTransition::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        emit positionChanged();
    }
    return QGraphicsRectItem::itemChange(change, value);
}
