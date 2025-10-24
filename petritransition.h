#ifndef PETRITRANSITION_H
#define PETRITRANSITION_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
class PetriTransition : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit PetriTransition(QGraphicsItem *parent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    int m_firingTime{0};
    int m_priority{0};
    QString m_label;

    QPair<int, int> m_timeInterval {0, 0};
signals:
    void positionChanged();
};

#endif // PETRITRANSITION_H
