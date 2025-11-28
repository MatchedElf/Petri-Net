/**
 * @file petrinetscene.h
 * @brief Заголовочный файл класса PetriNetScene - сцена для редактирования сетей Петри
 * @ingroup GraphicsScene
 */
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

#include "Items/petriplace.h"
#include "Items/petritransition.h"
#include "Items/petriarc.h"

#include "Simulation/simulations.h"

 /**
  * @class PetriNetScene
  * @brief Графическая сцена для создания и редактирования сетей Петри
  *
  * Наследуется от QGraphicsScene и предоставляет функциональность для:
  * - Добавления позиций, переходов и дуг
  * - Визуального редактирования сети
  * - Отображения сетки
  * - Контекстного меню для управления элементами
  */
class PetriNetScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @enum Tool
     * @brief Режимы редактирования сцены
     */
    enum Tool {
        ToolSelect,     // Режим выделения/перемещения объектов
        ToolPlace,      // Режим добавления позиций (окружностей)
        ToolTransition, // Режим добавления переходов (прямоугольников)
        ToolArc         // Режим добавления стрелок
    };

    /**
     * @brief Конструктор сцены сети Петри
     *
     * @details Инициализирует сцену с настройками по умолчанию:
     * - Видимая сетка с размером ячейки 20px
     * - Режим выбора как начальный инструмент
     * - Большая область сцены для работы
     *
     * @param parent Родительский объект
     */
    PetriNetScene(QObject *parent = nullptr);

    /**
     * @brief Отрисовка фона сцены с сеткой
     *
     * @details Рисует сетку поверх стандартного фона, если включена видимость сетки.
     * Сетка выравнивается по границам ячеек для точного позиционирования элементов.
     *
     * @param painter Объект для отрисовки
     * @param rect Область для перерисовки 
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    /**
     * @brief Обработчик нажатия кнопки мыши
     *
     * @details В зависимости от текущего инструмента:
     * - ToolPlace/ToolTransition: добавляет новый элемент в позиции клика
     * - ToolArc: начинает создание дуги от выбранного элемента
     * - ToolSelect: стандартная обработка для выделения/перемещения
     *
     * Правая кнопка мыши всегда показывает контекстное меню.
     *
     * @param event Событие мыши
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Обработчик отпускания кнопки мыши
     *
     * @details Для режима ToolArc завершает создание дуги, соединяя начальный
     * и конечный элементы. Удаляет временную линию и создает постоянную дугу.
     *
     * @param event Событие мыши
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Обработчик перемещения мыши
     *
     * @details В режиме ToolArc обновляет позицию временной линии для визуальной
     * обратной связи при создании дуги.
     *
     * @param event Событие мыши
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Добавление позиции на сцену
     *
     * @details Создает новую позицию с автоматическим именем (p0, p1, p2, ...)
     * и размещает ее в указанной позиции.
     *
     * @param pos Координаты для размещения позиции
     *
     * @emit placeAdded(PetriPlace*) после успешного добавления
     */
    void addPlace(const QPointF &pos);

    /**
     * @brief Добавление перехода на сцену
     *
     * @details Создает новый переход и размещает его в указанной позиции.
     *
     * @param pos Координаты для размещения перехода
     *
     * @emit transitionAdded(PetriTransition*) после успешного добавления
     */
    void addTransition(const QPointF &pos);

    /**
     * @brief Добавление дуги между позицией и переходом
     *
     * @details Создает дугу с указанными параметрами и связывает элементы.
     * Также добавляет связь в соответствующий список перехода.
     *
     * @param place Позиция для связи
     * @param transition Переход для связи
     * @param isInhibitor Направление: true - от позиции к переходу (входная дуга),
     *                  false - от перехода к позиции (выходная дуга)
     * @param weight Вес дуги (количество переносимых фишек)
     *
     * @warning Проверяет валидность указателей перед созданием дуги
     *
     * @emit arcAdded(PetriArc*) после успешного добавления
     */
    void addArc(PetriPlace *place, PetriTransition *transition, bool isInhibitor, int weight);

    /**
     * @brief Показать контекстное меню для элемента
     *
     * @details Создает контекстно-зависимое меню с действиями:
     * - Удаление элемента
     * - Для позиций: изменение количества фишек
     * - Для дуг: изменение веса (заглушка)
     *
     * @param pos Экранная позиция для отображения меню
     * @param item Элемент, для которого создается меню (может быть nullptr)
     */
    void showContextMenu(const QPointF &pos, QGraphicsItem* item);

    /**
     * @brief Установка текущего инструмента редактирования
     *
     * @param tool Выбранный инструмент из перечисления Tool
     */
    void setCurrentTool(Tool tool);

    /**
     * @brief Извлечение данных сети для симуляции
     * @param places Выходной вектор позиций
     * @param transitions Выходной вектор переходов
     */
    void extractNetData(QVector<SimPlace>& places, QVector<SimTransition>& transitions);


    bool _gridVisible;
    int _gridSize;
    QColor _gridColor{Qt::lightGray};
    Tool _currentTool{ToolSelect};

    PetriPlace* _tempArcStartPlace{nullptr};
    PetriTransition* _tempArcStartTransition{nullptr};

    QGraphicsLineItem* tempLine;

    int placesCount{0};

protected slots:

    /**
     * @brief "Диалог" редактирования количества фишек в позиции
     *
     * @details Создает модальный диалог с валидацией ввода для установки
     * количества фишек в указанной позиции.
     *
     * @param item Позиция для редактирования
     *
     * @note Использует QIntValidator с диапазоном 0-10 для ограничения ввода
     */
    void onTokensEdit(PetriPlace* item);

signals:
    /**
    * @brief Сигнал о добавлении перехода
    * @param transition Добавленный переход
    */
    void transitionAdded(PetriTransition* transition);

    /**
   * @brief Сигнал о добавлении дуги
   * @param arc Добавленная дуга
   */
    void arcAdded(PetriArc* arc);

    /**
     * @brief Сигнал о добавлении позиции
     * @param place Добавленная позиция
     */
    void placeAdded(PetriPlace* place);
};


#endif // PETRINETSCENE_H
