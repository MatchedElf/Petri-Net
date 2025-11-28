#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <QTimer>
#include "simulationsettings.h"

struct SimPlace {
    QString id;
    int tokens;
};

struct SimTransition {
    QString id;
    QVector<int> inputPlaces;   // индексы входных позиций
    QVector<int> outputPlaces;  // индексы выходных позиций
    QVector<int> inputWeights;  // веса входных дуг
    QVector<int> outputWeights; // веса выходных дуг
};


class Simulations : public QObject
{
    Q_OBJECT
public:
    explicit Simulations(QObject *parent = nullptr);

    void setPlaces(const QVector<SimPlace>& places);
    void setTransitions(const QVector<SimTransition>& transitions);
    void setSettings(const SimulationSettings& settings);

    void start();
    void stop();
    void step();
    void reset();

    bool isRunning() const { return _running; }
    const QVector<SimPlace>& places() const { return _places; }

signals:
    void stepCompleted(int iteration);
    void simulationFinished();
    void markingChanged(const QVector<int>& tokens);

private slots:
    void onTimerTick();

private:
    bool canFire(int transitionIndex) const;
    void fire(int transitionIndex);
    QVector<int> getEnabledTransitions() const;

    QVector<SimPlace> _places;
    QVector<SimPlace> _initialPlaces; // для сброса
    QVector<SimTransition> _transitions;
    SimulationSettings _settings;

    QTimer* _timer;
    bool _running{false};
    int _currentIteration{0};
};

#endif // SIMULATIONS_H
