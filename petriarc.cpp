// petriarc.cpp
#include "petriarc.h"

PetriArc::PetriArc(PetriPlace *place, PetriTransition *transition, bool fromPlace, int weight)
    : QGraphicsLineItem(),
    m_place(place),
    m_transition(transition),
    _fromPlace(fromPlace),
    m_weight(weight)
{
    setPen(QPen(Qt::black, 2));
    updatePosition();

    QObject::connect(place, &PetriPlace::positionChanged, this, &PetriArc::updatePosition);
    QObject::connect(transition, &PetriTransition::positionChanged, this, &PetriArc::updatePosition);
}

void PetriArc::updatePosition()
{
    QLineF line;
    if(_fromPlace)
        line = QLineF(mapFromItem(m_place, 0, 0), mapFromItem(m_transition, 0, 0));
    else
        line = QLineF(mapFromItem(m_transition, 0, 0), mapFromItem(m_place, 0, 0));
    setLine(line);
}

void PetriArc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPointF start = line().p1();
    QPointF end = line().p2();

    // Рассчитываем точки пересечения с границами элементов
    QPointF intersectStart = _fromPlace ? calculateIntersection(start, end, m_place) : calculateIntersection(start, end, m_transition);
    QPointF intersectEnd = _fromPlace ? calculateIntersection(end, start, m_transition) : calculateIntersection(end, start, m_place);

    QLineF visibleLine(intersectStart, intersectEnd);
    setLine(visibleLine);

    // Рисуем линию
    painter->setPen(pen());
    painter->drawLine(visibleLine);

    // Рисуем стрелку или ингибитор
    // if (m_isInhibitor) {
    //     // Ингибитор - круг на конце
    //     painter->setBrush(Qt::white);
    //     painter->drawEllipse(intersectEnd, 5, 5);
    // } else {
    //     // Обычная стрелка
    //     double angle = std::atan2(visibleLine.dy(), visibleLine.dx());
    //     QPointF arrowP1 = intersectEnd - QPointF(sin(angle + M_PI / 3) * 10,
    //                                              cos(angle + M_PI / 3) * 10);
    //     QPointF arrowP2 = intersectEnd - QPointF(sin(angle + M_PI - M_PI / 3) * 10,
    //                                              cos(angle + M_PI - M_PI / 3) * 10);

    //     painter->setBrush(pen().color());
    //     painter->drawPolygon(QPolygonF() << intersectEnd << arrowP1 << arrowP2);
    // }

    // Обычная стрелка
    double angle = std::atan2(visibleLine.dy(), visibleLine.dx());
    QPointF arrowP1 = intersectEnd - QPointF(sin(angle + M_PI / 3) * 10,
                                             cos(angle + M_PI / 3) * 10);
    QPointF arrowP2 = intersectEnd - QPointF(sin(angle + M_PI - M_PI / 3) * 10,
                                             cos(angle + M_PI - M_PI / 3) * 10);

    painter->setBrush(pen().color());
    painter->drawPolygon(QPolygonF() << intersectEnd << arrowP1 << arrowP2);

    // Рисуем вес если > 1
    if (m_weight > 1) {
        painter->setFont(QFont("Arial", 8));
        QPointF textPos = (intersectStart + intersectEnd) / 2;
        painter->drawText(textPos, QString::number(m_weight));
    }
}

QPointF PetriArc::calculateIntersection(const QPointF &point1, const QPointF &point2, QGraphicsItem *item)
{
    // Упрощенный расчет пересечения с границей элемента
    QRectF rect = item->boundingRect();
    QPointF center = item->pos();
    rect.moveCenter(center);

    QLineF line(point1, point2);
    QPolygonF polygon;
    polygon << rect.topLeft() << rect.topRight()
            << rect.bottomRight() << rect.bottomLeft();

    QPointF intersectPoint;
    for (int i = 0; i < polygon.size(); ++i) {
        QLineF polyLine(polygon[i], polygon[(i + 1) % polygon.size()]);
        QLineF::IntersectionType type = line.intersects(polyLine, &intersectPoint);
        if (type == QLineF::BoundedIntersection) {
            return intersectPoint;
        }
    }

    return point2;
}
