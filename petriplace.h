#ifndef PETRIPLACE_H
#define PETRIPLACE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>

class PetriPlace : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit PetriPlace(QGraphicsItem *parent, QString label);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setTokens(int count);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void positionChanged();
private:
    QString m_label;
    int m_tokens{0};
    bool m_queueMode{false};

};

#endif // PETRIPLACE_H
