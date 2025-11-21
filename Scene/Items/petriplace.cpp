// petriplace.cpp

#include "petriplace.h"
#include "qpainter.h"


PetriPlace::PetriPlace(QGraphicsItem *parent, QString label)
    : QGraphicsEllipseItem(-40, -40, 80, 80, parent),
    m_tokens(0),
    m_queueMode(false),
    m_label(label)
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
    if (m_queueMode) {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawLine(-20, 0, 20, 0);
    }

    // Рисуем фишки
    if (m_tokens > 0) {
        if (m_tokens <= 7) {
            painter->setBrush(Qt::black);
            for (int i = 0; i < m_tokens; ++i) {
                double angle = 2 * M_PI * i / m_tokens;
                int x = 10 * cos(angle);
                int y = 10 * sin(angle);
                painter->drawEllipse(QPointF(x, y), 3, 3);
            }
        } else {
            painter->setFont(QFont("Arial", 10));
            painter->drawText(boundingRect(), Qt::AlignCenter, QString::number(m_tokens));
        }
    }

    // Рисуем метку
    painter->setFont(QFont("Arial", 10));
    QRectF labelRect(-20, -30, 40, 10);
    painter->drawText(labelRect, Qt::AlignCenter, m_label);
}

void PetriPlace::setTokens(int count)
{
    m_tokens = count;
    update();
}

int PetriPlace::tokens() const
{
    return m_tokens;
}

QString PetriPlace::label() const
{
    return m_label;
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
    m_tokens++;
    update();
}
