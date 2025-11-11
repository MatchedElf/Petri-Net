// petrinetscene.cpp
#include "petrinetscene.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include<QLineEdit>
#include<QPushButton>

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
            //QLineF tmpLine = QLineF(m_tempArcStartPlace ? m_tempArcStartPlace->pos() : m_tempArcStartTransition->pos(), event->scenePos());
            tempLine = new QGraphicsLineItem();
            tempLine->setPen(QPen(Qt::gray, 2, Qt::DashLine));
            addItem(tempLine);
            break;
        default:
            QGraphicsScene::mousePressEvent(event);
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        showContextMenu(event->screenPos(), item);

    }
    else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void PetriNetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_currentTool == ToolArc) {
        QList<QGraphicsItem*> tmp = items(event->scenePos());
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        removeItem(tempLine);

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
        tempLine = nullptr;
        update();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void PetriNetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_currentTool == ToolArc &&
        (m_tempArcStartPlace || m_tempArcStartTransition)) {
        // Отрисовка временной линии
        QLineF tmpLine = QLineF(m_tempArcStartPlace ? m_tempArcStartPlace->pos() : m_tempArcStartTransition->pos(), event->scenePos());
        tmpLine.setP2(QPointF(tmpLine.p2().x() - 5, tmpLine.p2().y() - 5));
        tempLine->setLine(tmpLine);
        //qDebug() << event->scenePos() << QPointF(tmpLine.p1().x() - 5, tmpLine.p1().y() - 5);
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

void PetriNetScene::addArc(PetriPlace *place, PetriTransition *transition, bool fromPlace, int weight)
{
    if (!place || !transition) return;

    PetriArc *arc = new PetriArc(place, transition, fromPlace, weight);
    if(fromPlace)
        transition->addPlace(place);
    addItem(arc);
    place->setParentItem(place);
    emit arcAdded(arc);
}

void PetriNetScene::showContextMenu(const QPointF &pos, QGraphicsItem* item)
{
    if(!item)
        return;
    QMenu contextMenu;

    // Создаем действия меню
    QAction *action1 = contextMenu.addAction("Удалить");
    QAction *action2;
    PetriPlace* place = dynamic_cast<PetriPlace*>(item);
    if (place)
    {
        action2 = contextMenu.addAction("Изменить количество фишек");
        connect(action2, &QAction::triggered, this, [place, this](){
            onTokensEdit(place);
        });
    }
    PetriArc* arc = dynamic_cast<PetriArc*>(item);
    if (arc)
    {
        action2 = contextMenu.addAction("Изменить количество стрелок");
        connect(action2, &QAction::triggered, this, [place, this](){
            onTokensEdit(place);
        });
    }
    contextMenu.addSeparator();
    QAction *action3 = contextMenu.addAction("Выход");

    // Подключаем действия к слотам
    connect(action1, &QAction::triggered, this, [item, this](){
        removeItem(item);
        update();
    });
    // connect(action3, &QAction::triggered, qApp, &QApplication::quit);

    // Показываем меню
    contextMenu.exec(pos.toPoint());

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

void PetriNetScene::onTokensEdit(PetriPlace* item)
{
    QDialog dialog;
    dialog.setWindowTitle("Ввод данных");
    dialog.resize(100, 70);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    // Поле для целых чисел
    QLabel *intLabel = new QLabel("Количество фишек для " + item->label() + ": ");
    QLineEdit *intEdit = new QLineEdit();
    QIntValidator* intVld = new QIntValidator(intEdit);
    intVld->setRange(0, 10);
    intEdit->setValidator(intVld);
    intEdit->setText(QString::number(item->tokens()));
    mainLayout->addWidget(intLabel);
    mainLayout->addWidget(intEdit);


    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Отмена");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    // Обработчики
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Показываем диалог
    if (dialog.exec() == QDialog::Accepted) {
        int newTokens = intEdit->text().toInt();
        item->setTokens(newTokens);
        update();
    }

}
