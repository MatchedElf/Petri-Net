// petrinetscene.cpp
#include "petrinetscene.h"

PetriNetScene::PetriNetScene(QObject *parent)
    : QGraphicsScene(parent),
    m_gridVisible(true),
    m_gridSize(20),
    m_gridColor(Qt::lightGray),
    m_currentTool(Tool::ToolSelect)
{
    // Настройка сцены
    setSceneRect(-1000, -1000, 2000, 2000);
}

void PetriNetScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);

    if (m_gridVisible) {
        painter->setPen(QPen(m_gridColor, 1));

        qreal left = int(rect.left()) - (int(rect.left()) % m_gridSize);
        qreal top = int(rect.top()) - (int(rect.top()) % m_gridSize);

        for (qreal x = left; x < rect.right(); x += m_gridSize) {
            painter->drawLine(x, rect.top(), x, rect.bottom());
        }

        for (qreal y = top; y < rect.bottom(); y += m_gridSize) {
            painter->drawLine(rect.left(), y, rect.right(), y);
        }
    }
}

void PetriNetScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        switch (m_currentTool) {
        case ToolPlace:
            addPlace(event->scenePos());
            break;
        case ToolTransition:
            addTransition(event->scenePos());
            break;
        case ToolArc:
            if (PetriPlace* place = dynamic_cast<PetriPlace*>(item)) {
                m_tempArcStartPlace = place;
                m_tempArcStartTransition = nullptr;
            }
            else if (PetriTransition* transition = dynamic_cast<PetriTransition*>(item)) {
                m_tempArcStartTransition = transition;
                m_tempArcStartPlace = nullptr;
            }
            break;
        default:
            QGraphicsScene::mousePressEvent(event);
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void PetriNetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_currentTool == ToolArc) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

        if (m_tempArcStartPlace && dynamic_cast<PetriTransition*>(item)) {
            // Создаем дугу от Place к Transition
            addArc(m_tempArcStartPlace, static_cast<PetriTransition*>(item), true, 1);
        }
        else if (m_tempArcStartTransition && dynamic_cast<PetriPlace*>(item)) {
            // Создаем дугу от Transition к Place
            addArc(static_cast<PetriPlace*>(item), m_tempArcStartTransition, false, 1);
        }

        m_tempArcStartPlace = nullptr;
        m_tempArcStartTransition = nullptr;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void PetriNetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_currentTool == ToolArc &&
        (m_tempArcStartPlace || m_tempArcStartTransition)) {
        // Отрисовка временной линии
        QLineF tmpLine = QLineF(m_tempArcStartPlace ? m_tempArcStartPlace->pos() : m_tempArcStartTransition->pos(), event->scenePos());
        QGraphicsLineItem* tempLine = new QGraphicsLineItem(tmpLine);
        tempLine->setPen(QPen(Qt::gray, 2, Qt::DashLine));
        addItem(tempLine);
        update();
        delete tempLine;
    }
    update();
    QGraphicsScene::mouseMoveEvent(event);
}

void PetriNetScene::addPlace(const QPointF &pos)
{
    PetriPlace *place = new PetriPlace(nullptr, "p" + QString::number(placesCount));
    placesCount++;
    place->setPos(pos);
    addItem(place);
    emit placeAdded(place);
}

void PetriNetScene::addTransition(const QPointF &pos)
{
    PetriTransition *transition = new PetriTransition(nullptr);
    transition->setPos(pos);
    addItem(transition);
    emit transitionAdded(transition);
}

void PetriNetScene::addArc(PetriPlace *place, PetriTransition *transition, bool isInhibitor, int weight)
{
    if (!place || !transition) return;

    PetriArc *arc = new PetriArc(place, transition, isInhibitor, weight);
    addItem(arc);
    emit arcAdded(arc);
}

void PetriNetScene::setCurrentTool(Tool tool)
{
    m_currentTool = tool;

    // Обновляем курсор
    // switch (tool) {
    // case ToolSelect:
    //     setCursor(Qt::ArrowCursor);
    //     break;
    // case ToolPlace:
    //     setCursor(QPixmap(":/icons/place_cursor.png"));
    //     break;
    // case ToolTransition:
    //     setCursor(QPixmap(":/icons/transition_cursor.png"));
    //     break;
    // }
}
