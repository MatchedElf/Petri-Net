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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createToolBar();
    void createDockWidgets();
    void createMenus();

    void newFile();
    void openFile();
    void saveFile();
    void exportToJson();

    void onPlaceAdded(PetriPlace *place);
    void onTransitionAdded(PetriTransition *transition);
    void onArcAdded(PetriArc *arc);

    PetriNetScene* m_scene;
    QGraphicsView* m_view;

    QDockWidget* m_propertyDock;
    QTreeWidget* m_propertyEditor;
};
#endif // MAINWINDOW_H
