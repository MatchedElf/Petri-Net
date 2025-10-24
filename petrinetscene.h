#ifndef PETRINETSCENE_H
#define PETRINETSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QTreeWidget>
#include <QActionGroup>

#include "petriplace.h"
#include "petritransition.h"
#include "petriarc.h"

class PetriNetScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Tool {
        ToolSelect,    // Режим выделения/перемещения объектов
        ToolPlace,     // Режим добавления позиций (окружностей)
        ToolTransition, // Режим добавления переходов (прямоугольников)
        ToolArc // Режим добавления стрелок
    };

    explicit PetriNetScene(QObject *parent = nullptr);

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    void addPlace(const QPointF &pos);
    void addTransition(const QPointF &pos);
    void addArc(PetriPlace *place, PetriTransition *transition, bool isInhibitor, int weight);

    void setCurrentTool(Tool tool);

    bool m_gridVisible;
    int m_gridSize;
    QColor m_gridColor{Qt::lightGray};
    Tool m_currentTool{ToolSelect};

    PetriPlace* m_tempArcStartPlace{nullptr};
    PetriTransition* m_tempArcStartTransition{nullptr};

    int placesCount{0};

signals:
    void transitionAdded(PetriTransition* transition);
    void arcAdded(PetriArc* arc);
    void placeAdded(PetriPlace* place);
};

#endif // PETRINETSCENE_H
