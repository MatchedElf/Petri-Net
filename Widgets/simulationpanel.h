#ifndef SIMULATIONPANEL_H
#define SIMULATIONPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTimer>
#include "Scene/petrinetscene.h"
#include "Simulation/simulationsettings.h"

class SimulationPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SimulationPanel(QWidget *parent = nullptr);

    void setScene(PetriNetScene* scene);
    void setSettings(const SimulationSettings& settings);
    void addLog(const QString& message);
    void clearLogs();
    void startSimulation();

signals:
    void simulationStarted();
    void simulationPaused();
    void simulationReset();
    void simulationFinished();

public slots:
    void onStartClicked();
    void onPauseClicked();
    void onResetClicked();
    void onStepSimulation();

private:
    void updateButtonStates();
    void saveInitialState();
    void restoreInitialState();
    bool fireTransition(SimTransition& transition, QVector<SimPlace>& places);

    QPushButton* _startButton;
    QPushButton* _pauseButton;
    QPushButton* _resetButton;
    QPushButton* _stepButton;
    QTextEdit* _logArea;
    QTimer* _simulationTimer;

    PetriNetScene* _scene = nullptr;
    QVector<SimPlace> _places;
    QVector<SimTransition> _transitions;
    QVector<SimPlace> _initialPlaces;

    SimulationSettings _settings;
    bool _isRunning = false;
    bool _isPaused = false;
    int _stepCount = 0;
    int _maxIterations = -1;
};

#endif // SIMULATIONPANEL_H
