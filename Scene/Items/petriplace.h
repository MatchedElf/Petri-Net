/**
 * @file petriplace.h
 * @brief Заголовочный файл класса PetriPlace - графического представления позиции сети Петри
 * @ingroup GraphicsItems
 */
#ifndef PETRIPLACE_H
#define PETRIPLACE_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QObject>

 /**
  * @class PetriPlace
  * @brief Класс, представляющий позицию (место) в графической модели сети Петри
  *
  * Наследуется от QGraphicsEllipseItem для отображения в виде круга и QObject для поддержки сигналов/слотов.
  * Позиция может содержать метки (фишки) и имеет режим очереди.
  */

class PetriPlace : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор позиции сети Петри
    * 
    * @details Создает графический элемент в виде эллипса размером 80x80 пикселей
    * с центром в точке (0,0). Устанавливает начальные свойства и флаги взаимодействия.
    * 
    * @param parent Родительский графический элемент
    * @param label Текстовая метка позиции
    */
    explicit PetriPlace(QGraphicsItem *parent, QString label);

    /**
    * @brief Отрисовка позиции на графической сцене
    * 
    * @details Выполняет отрисовку в следующем порядке:
    * 1. Базовая отрисовка эллипса
    * 2. Разделительная линия
    * 3. Фишки
    * 4. Текстовая метка
    * @param painter Объект painter для отрисовки
    * @param option Стиль отрисовки элемента
    * @param widget Виджет, в котором происходит отрисовка
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    /**
     * @brief Установка количества фишек в позиции
     * @param count Количество фишек 
     */
    void setTokens(int count);
    /**
     * @brief Получение текущего количества фишек
     * @return Текущее количество фишек в позиции
     */
    int tokens() const;
    /**
    * @brief Получение текстовой метки позиции
    * @return Текстовая метка позиции
    */
    QString label() const;
    /**
   * @brief Обработчик изменения свойств элемента
   * @param change Тип изменения
   * @param value Новое значение
   * @return Результат обработки изменения
   */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    /**
    * @brief Обработчик двойного клика 
    * @param event Событие мыши
    */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    /**
   * @brief Сигнал об изменении позиции элемента
   * @signal При перемещении позиции
   */
    void positionChanged();
private:
    QString _label{""};      ///< Текстовая метка позиции
    int _tokens{0};          ///< Количество фишек в позиции
    bool _queueMode{false};  ///< Флаг режима очереди (отображает разделительную линию)

};

#endif // PETRIPLACE_H
