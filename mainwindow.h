#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Scene/Items/petriplace.h"
#include "Scene/Items/petritransition.h"
#include "Scene/Items/petriarc.h"
#include "Scene/petrinetscene.h"

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QDockWidget>
#include <QStatusBar>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
/**
 * @class MainWindow
 * @brief Главное окно приложения для редактирования сетей Петри
 *
 * Наследуется от QMainWindow и предоставляет:
 * - Графическую сцену для редактирования сети
 * - Панели инструментов для работы с элементами
 * - Док-виджеты для свойств и моделирования
 * - Меню для работы с файлами
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    /**
     * @brief Конструктор главного окна
     *
     * @details Инициализирует все компоненты интерфейса:
     * - Создает графическую сцену и представление
     * - Настраивает панель инструментов
     * - Создает док-виджеты и меню
     * - Устанавливает соединения между сигналами и слотами
     *
     * @param parent Родительский виджет
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Создание панели инструментов для редактирования
     *
     * @details Создает группу взаимоисключающих действий для выбора инструментов:
     * - Выбор/перемещение элементов
     * - Добавление позиций
     * - Добавление переходов
     * - Добавление дуг
     *
     * Каждый инструмент представлен иконкой и проверяемой кнопкой.
     */
    void createToolBar();

    /**
     * @brief Создание док-виджетов для дополнительных панелей
     *
     * @details Создает и размещает док-виджеты по краям главного окна:
     * - Правая панель: свойства элементов (реализована)
     */
    void createDockWidgets();

    /**
     * @brief Создание главного меню приложения
     *
     * @details Создает меню "File" со следующими пунктами:
     * - New: создание новой сети
     * - Open: открытие существующей сети
     * - Save: сохранение текущей сети
     * - Export to JSON: экспорт в JSON формат
     */
    void createMenus();

    /**
     * @brief Создание новой пустой сети
     *
     * @details Очищает текущую сцену и показывает сообщение о создании нового файла
     *
     * @see PetriNetScene::clear()
     */
    void newFile();

    /**
     * @brief Открытие сети из файла
     *
     * @details Открывает диалог выбора файла, загружает и парсит JSON данные,
     * затем восстанавливает сеть на сцене.
     *
     * @see PetriNetScene::fromJson()
     */
    void openFile();

    /**
     * @brief Сохранение текущей сети в файл
     *
     * @details Сохраняет текущее состояние сети в файловом формате.
     */
    void saveFile();

    /**
     * @brief Экспорт сети в JSON формат
     *
     * @details Экспортирует текущее состояние сети в JSON файл для
     * последующего использования или анализа.
     */
    void exportToJson();

    /**
     * @brief Обработчик добавления позиции на сцену
     *
     * @details Вызывается при добавлении новой позиции на сцену.
     * Может использоваться для обновления списка позиций и свойств.
     *
     * @param place Указатель на добавленную позицию
     *
     */
    void onPlaceAdded(PetriPlace *place);

    /**
     * @brief Обработчик добавления перехода на сцену
     *
     * @details Вызывается при добавлении нового перехода на сцену.
     * Может использоваться для обновления списка переходов и свойств.
     *
     * @param transition Указатель на добавленный переход
     *
     */
    void onTransitionAdded(PetriTransition *transition);

    /**
     * @brief Обработчик добавления дуги на сцену
     *
     * @details Вызывается при добавлении новой дуги на сцену.
     * Может использоваться для обновления списка дуг.
     *
     * @param arc Указатель на добавленную дугу
     * 
     */
    void onArcAdded(PetriArc *arc);

    PetriNetScene* m_scene;
    QGraphicsView* m_view;

    QDockWidget* m_propertyDock;
    QTreeWidget* m_propertyEditor;
};
#endif // MAINWINDOW_H
