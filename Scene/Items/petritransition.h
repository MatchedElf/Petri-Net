/**
 * @file petritransition.h
 * @brief Заголовочный файл класса PetriTransition - графического представления перехода сети Петри
 * @ingroup GraphicsItems
 */
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

 /**
  * @class PetriTransition
  * @brief Класс, представляющий переход в графической модели сети Петри
  * Наследуется от QGraphicsRectItem для отображения в виде прямоугольника и QObject для поддержки сигналов/слотов.
  * Переход может иметь временные параметры, приоритет и связанные позиции.
  */
class PetriTransition : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор перехода сети Петри
     * 
     * @details Создает графический элемент в виде вертикального прямоугольника размером 20x80 пикселей
     * с центром в точке (0,0). Устанавливает начальные свойства и флаги взаимодействия.
     * @param parent Родительский графический элемент
     */
    explicit PetriTransition(QGraphicsItem *parent);

    /**
     * @brief Отрисовка перехода на графической сцене
     * 
     * @details Выполняет отрисовку в следующем порядке:
     * 1. Базовая отрисовка прямоугольника
     * 2. Временные параметры (время срабатывания и интервал)
     * 3. Приоритет перехода
     * 4. Текстовая метка
     * 
     * @param painter Объект painter для отрисовки
     * @param option Стиль отрисовки элемента
     * @param widget Виджет, в котором происходит отрисовка
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @brief Обработчик изменения свойств элемента
     * @details Перехватывает изменения позиции элемента и испускает сигнал positionChanged
     * для уведомления связанных элементов (дуг) о необходимости обновления их позиций.
     * @param change Тип изменения
     * @param value Новое значение
     * @emit positionChanged() при изменении позиции элемента
     * @return Результат обработки изменения
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /**
     * @brief Добавление позиции, связанной с переходом
     * @details Добавляет позицию в соответствующий список в зависимости от направления связи.
     * @param place Указатель на добавляемую позицию
     * @param from Направление связи: true - входная позиция, false - выходная позиция
     */
    void addPlace(PetriPlace*, bool from);
signals:
    /**
    * @brief Сигнал об изменении позиции элемента на сцене
    * @signal Испускается при перемещении перехода
    */
    void positionChanged();

private:
    int _firingTime{ 0 };                   ///< Время срабатывания перехода
    int _priority{ 0 };                     ///< Приоритет перехода
    QPair<int, int> _timeInterval{ 0, 0 };  ///< Временной интервал срабатывания
    QString _label;                         ///< Текстовая метка перехода

    QList<PetriPlace*> _fromPlacesList;      ///< Список входных позиций (источники фишек)
    QList<PetriPlace*> _toPlacesList;        ///< Список выходных позиций (приемники фишек)
};

#endif // PETRITRANSITION_H
