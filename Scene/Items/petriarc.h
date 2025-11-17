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

//test
class PetriArc : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit PetriArc(PetriPlace *place, PetriTransition *transition, bool fromPlace, int weight);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


public slots:
    void updatePosition();

private:
    QPointF calculateIntersection(const QPointF &point1, const QPointF &point2, const QGraphicsItem *item);

    const PetriPlace* m_place;
    const PetriTransition* m_transition;
    bool _fromPlace;
    int m_weight;

};

#endif // PETRIARC_H
