#ifndef PETRITRANSITION_H
#define PETRITRANSITION_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "petriplace.h"

class PetriTransition : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PetriTransition(QGraphicsItem *parent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void addPlace(PetriPlace*);
signals:
    void positionChanged();

private:
    int m_firingTime{0};
    int m_priority{0};
    QPair<int, int> m_timeInterval {0, 0};
    QString m_label;
    QList<PetriPlace*> _placesList;
};

#endif // PETRITRANSITION_H
