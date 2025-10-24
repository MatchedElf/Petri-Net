#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "petriplace.h"
#include "petritransition.h"
#include "petriarc.h"
#include "petrinetscene.h"

#include <QToolBar>
#include <QAction>
#include <QGraphicsView>
#include <QDockWidget>
#include <QStatusBar>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

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

private:
    Ui::MainWindow2 *ui;
};

#endif // MAINWINDOW2_H
