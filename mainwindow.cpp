// mainwindow.cpp
#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Настройка главного окна
    setWindowTitle("Petri Net Editor");
    resize(1024, 768);

    // Создание сцены
    _scene = new PetriNetScene(this);
    //connect(_scene, &PetriNetScene::placeAdded, this, &MainWindow::onPlaceAdded);
    //connect(_scene, &PetriNetScene::transitionAdded, this, &MainWindow::onTransitionAdded);
    connect(_scene, &PetriNetScene::arcAdded, this, &MainWindow::onArcAdded);

    _simScene = new PetriNetScene(this);
    // Создание представления
    _view = new QGraphicsView(_scene, this);
    setCentralWidget(_view);

    // Создание панели инструментов
    createToolBar();

    // Создание док-виджетов
    createDockWidgets();

    // Создание меню
    createMenus();

    // Статус бар
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tools");
    QString iconsDir = QString(PROJECT_PATH) + "icons/";

    QAction *selectAction = new QAction(QIcon(iconsDir + "Image2.png"), "Select", this);
    selectAction->setCheckable(true);
    selectAction->setChecked(true);
    connect(selectAction, &QAction::triggered, [this]() { _scene->setCurrentTool(PetriNetScene::ToolSelect); });

    QAction *placeAction = new QAction(QIcon(":/icons/place.png"), "Place", this);
    placeAction->setCheckable(true);
    connect(placeAction, &QAction::triggered, [this]() { _scene->setCurrentTool(PetriNetScene::ToolPlace); });

    QAction *transitionAction = new QAction(QIcon(":/icons/transition.png"), "Transition", this);
    transitionAction->setCheckable(true);
    connect(transitionAction, &QAction::triggered, [this]() { _scene->setCurrentTool(PetriNetScene::ToolTransition); });

    QAction* arcAction = new QAction(QIcon(":/icons/arc.png"), "Arc", this);
    arcAction->setCheckable(true);
    connect(arcAction, &QAction::triggered, [this]() {
        _scene->setCurrentTool(PetriNetScene::ToolArc);
    });

    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(selectAction);
    toolGroup->addAction(placeAction);
    toolGroup->addAction(transitionAction);
    toolGroup->addAction(arcAction);

    toolBar->addActions(toolGroup->actions());
}

void MainWindow::createDockWidgets()
{
    // Панель свойств
    _propertyDock = new QDockWidget("Properties", this);
    _propertyEditor = new QTreeWidget(_propertyDock);
    _propertyDock->setWidget(_propertyEditor);
    addDockWidget(Qt::RightDockWidgetArea, _propertyDock);

    // Панель моделирования
    // _simulationDock = new QDockWidget("Simulation", this);
    // _simulationWidget = new SimulationWidget(_simulationDock);
    // _simulationDock->setWidget(_simulationWidget);
    // addDockWidget(Qt::LeftDockWidgetArea, _simulationDock);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *newAction = new QAction(QIcon(":/icons/Image2.png"), "New", this);
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAction);

    QAction *openAction = new QAction("Open...", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction(QIcon(":/icons/Image2.png"), "Save", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveAction);

    QAction *exportAction = new QAction("Export to JSON...", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportToJson);
    fileMenu->addAction(exportAction);

    QMenu *simMenu = menuBar()->addMenu("Simulation");

    QAction *startAction = new QAction(QIcon(":/icons/Image2.png"), "Switch editing/simulation", this);
    connect(startAction, &QAction::triggered, this, &MainWindow::onSimStart);
    simMenu->addAction(startAction);
}

void MainWindow::newFile()
{
    _scene->clear();
    statusBar()->showMessage("New file created", 2000);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Petri Net", "", "Petri Net Files (*.pn)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        statusBar()->showMessage("Could not open file", 2000);
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        statusBar()->showMessage("Invalid file format", 2000);
        return;
    }

    _scene->clear();
    //_scene->fromJson(doc.object());
    statusBar()->showMessage("File loaded", 2000);
}

void MainWindow::saveFile()
{
    // Реализация сохранения аналогична открытию, но в обратном порядке
}

void MainWindow::exportToJson()
{
    // QString fileName = QFileDialog::getSaveFileName(this, "Export to JSON", "", "JSON Files (*.json)");
    // if (fileName.isEmpty()) return;

    // QJsonDocument doc(_scene->toJson());
    // QFile file(fileName);
    // if (file.open(QIODevice::WriteOnly)) {
    //     file.write(doc.toJson());
    //     statusBar()->showMessage("Exported to JSON", 2000);
    // } else {
    //     statusBar()->showMessage("Could not export file", 2000);
    // }
}

void MainWindow::onPlaceAdded(PetriPlace *place)
{
    PetriPlace* tmp = new PetriPlace(nullptr, place->label());
    tmp->setPos(place->pos());
    tmp->setTokens(place->tokens());
    _simScene->addItem(tmp);
}

void MainWindow::onTransitionAdded(PetriTransition *transition)
{
    PetriTransition *tmp = new PetriTransition(nullptr);
    tmp->setPos(transition->pos());
    _simScene->addItem(tmp);
}

void MainWindow::onArcAdded(PetriArc *arc)
{
    const PetriPlace* place = arc->getPlace();
    PetriPlace* tmpPlace = new PetriPlace(nullptr, place->label());
    tmpPlace->setPos(place->pos());
    tmpPlace->setTokens(place->tokens());
    _simScene->addItem(tmpPlace);

    const PetriTransition* transition = arc->getTransition();
    PetriTransition *tmpTransition = new PetriTransition(nullptr);
    tmpTransition->setPos(transition->pos());
    _simScene->addItem(tmpTransition);

    PetriArc *tmpArc = new PetriArc(tmpPlace, tmpTransition, arc->isFromPlace(), 0);
    tmpArc->setPos(arc->pos());
    _simScene->addItem(tmpArc);
}

void MainWindow::onSimStart()
{
    if(!_isSim)
    {
        _view->setScene(_simScene);
    }
    else
    {
        _view->setScene(_scene);
    }
    _isSim = !_isSim;
}
