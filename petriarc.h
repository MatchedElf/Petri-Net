#ifndef PETRIARC_H
#define PETRIARC_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QtMath>
#include <QObject>
#include <QGraphicsItem>

#include "petriplace.h"
#include "petritransition.h"

class PetriArc : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit PetriArc(PetriPlace *place, PetriTransition *transition, bool fromPlace, int weight);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPointF calculateIntersection(const QPointF &point1, const QPointF &point2, QGraphicsItem *item);

    PetriPlace* m_place;
    PetriTransition* m_transition;
    bool _fromPlace;
    int m_weight;
public slots:
    void updatePosition();

};

#endif // PETRIARC_H
