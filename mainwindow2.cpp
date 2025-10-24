#include "mainWindow2.h"
#include "ui_MainWindow2.h"

MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tools");

    QAction *selectAction = new QAction(QIcon(":/icons/select.png"), "Select", this);
    selectAction->setCheckable(true);
    selectAction->setChecked(true);
    connect(selectAction, &QAction::triggered, [this]() { m_scene->setCurrentTool(PetriNetScene::ToolSelect); });

    QAction *placeAction = new QAction(QIcon(":/icons/place.png"), "Place", this);
    placeAction->setCheckable(true);
    connect(placeAction, &QAction::triggered, [this]() { m_scene->setCurrentTool(PetriNetScene::ToolPlace); });

    QAction *transitionAction = new QAction(QIcon(":/icons/transition.png"), "Transition", this);
    transitionAction->setCheckable(true);
    connect(transitionAction, &QAction::triggered, [this]() { m_scene->setCurrentTool(PetriNetScene::ToolTransition); });

    QAction* arcAction = new QAction(QIcon(":/icons/arc.png"), "Arc", this);
    arcAction->setCheckable(true);
    connect(arcAction, &QAction::triggered, [this]() {
        m_scene->setCurrentTool(PetriNetScene::ToolArc);
    });

    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(selectAction);
    toolGroup->addAction(placeAction);
    toolGroup->addAction(transitionAction);
    toolGroup->addAction(arcAction);

    ui->menubar->addActions(toolGroup->actions());
    ui->statusbar->addActions(toolGroup->actions());
}

void MainWindow2::createDockWidgets()
{
    // Панель свойств
    m_propertyDock = new QDockWidget("Properties", this);
    m_propertyEditor = new QTreeWidget(ui->dockWidget);
    ui->dockWidget->setWidget(m_propertyEditor);
    //addDockWidget(Qt::RightDockWidgetArea, m_propertyDock);

    // Панель моделирования
    // m_simulationDock = new QDockWidget("Simulation", this);
    // m_simulationWidget = new SimulationWidget(m_simulationDock);
    // m_simulationDock->setWidget(m_simulationWidget);
    // addDockWidget(Qt::LeftDockWidgetArea, m_simulationDock);
}

void MainWindow2::createMenus()
{
    QMenu *fileMenu = ui->menubar->addMenu("File");

    QAction *newAction = new QAction("New", this);
    connect(newAction, &QAction::triggered, this, &MainWindow2::newFile);
    fileMenu->addAction(newAction);

    QAction *openAction = new QAction("Open...", this);
    connect(openAction, &QAction::triggered, this, &MainWindow2::openFile);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction("Save", this);
    connect(saveAction, &QAction::triggered, this, &MainWindow2::saveFile);
    fileMenu->addAction(saveAction);

    QAction *exportAction = new QAction("Export to JSON...", this);
    connect(exportAction, &QAction::triggered, this, &MainWindow2::exportToJson);
    fileMenu->addAction(exportAction);
}

void MainWindow2::newFile()
{
    m_scene->clear();
    statusBar()->showMessage("New file created", 2000);
}

void MainWindow2::openFile()
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

    m_scene->clear();
    //m_scene->fromJson(doc.object());
    statusBar()->showMessage("File loaded", 2000);
}

void MainWindow2::saveFile()
{
    // Реализация сохранения аналогична открытию, но в обратном порядке
}

void MainWindow2::exportToJson()
{
    // QString fileName = QFileDialog::getSaveFileName(this, "Export to JSON", "", "JSON Files (*.json)");
    // if (fileName.isEmpty()) return;

    // QJsonDocument doc(m_scene->toJson());
    // QFile file(fileName);
    // if (file.open(QIODevice::WriteOnly)) {
    //     file.write(doc.toJson());
    //     statusBar()->showMessage("Exported to JSON", 2000);
    // } else {
    //     statusBar()->showMessage("Could not export file", 2000);
    // }
}

void MainWindow2::onPlaceAdded(PetriPlace *place)
{
    // Обновляем список позиций и свойства
}

void MainWindow2::onTransitionAdded(PetriTransition *transition)
{
    // Обновляем список переходов и свойства
}

void MainWindow2::onArcAdded(PetriArc *arc)
{
    // Обновляем список дуг
}
