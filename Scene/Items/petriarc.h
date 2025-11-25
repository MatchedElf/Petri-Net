/**
 * @file petriarc.h
 * @brief Заголовочный файл класса petriarc - графического представления дуги сети Петри
 * @ingroup GraphicsItems
 */

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

 /**
  * @class PetriArc
  * @brief Класс, представляющий дугу в графической модели сети Петри
  *
  * Наследуется от QGraphicsLineItem для отображения линии и QObject.
  * Обеспечивает визуальное соединение между позицией (PetriPlace) и переходом (PetriTransition).
  */
class PetriArc : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор дуги сети Петри
    * @param place Указатель на позицию сети Петри
    * @param transition Указатель на переход сети Петри
    * @param fromPlace Направление дуги: true - от позиции к переходу, false - от перехода к позиции
    * @param weight Вес дуги 
    *
    * @note Дуга автоматически подписывается на сигналы изменения позиции связанных элементов
    * @warning Переданные указатели должны быть валидными в течение всего времени жизни дуги
    */
    explicit PetriArc(PetriPlace *place, PetriTransition *transition, bool fromPlace, int weight);
    /**
    * @brief Отрисовка дуги
    * @param painter Объект painter для отрисовки
    * @param option Стиль отрисовки элемента
    * @param widget Виджет, в котором происходит отрисовка 
    *
    * @details Метод рисует:
    * - Линию между элементами
    * - Стрелку на конце дуги
    * - Вес дуги (если больше 1)
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    const PetriPlace* getPlace();

    const PetriTransition* getTransition();

    bool isFromPlace();

public slots:
    /**
    * @brief Обновление позиции дуги при перемещении связанных элементов
    *
    * @slot Вызывается автоматически при изменении позиции или перехода
    * @see PetriPlace::positionChanged
    * @see PetriTransition::positionChanged
    */
    void updatePosition();

private:

    /**
    * @brief Расчет точки пересечения линии с границей графического элемента
    * @param point1 Начальная точка линии
    * @param point2 Конечная точка линии
    * @param item Графический элемент, с границей которого ищется пересечение
    * @return Точка пересечения линии с boundingRect элемента
    *
    * @details Используется для корректного отображения дуги от границы элемента, а не из его центра
    */
    QPointF calculateIntersection(const QPointF &point1, const QPointF &point2, const QGraphicsItem *item);

    const PetriPlace* _place;
    const PetriTransition* _transition;
    bool _fromPlace;
    int _weight;

};

#endif // PETRIARC_H
