#include "simulations.h"
#include <QRandomGenerator>
#include <QDebug>

Simulations::Simulations(QObject *parent)
    : QObject(parent)
{
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &Simulations::onTimerTick);
}

void Simulations::setPlaces(const QVector<SimPlace>& places)
{
    _places = places;
    _initialPlaces = places;
}

void Simulations::setTransitions(const QVector<SimTransition>& transitions)
{
    _transitions = transitions;
}

void Simulations::setSettings(const SimulationSettings& settings)
{
    _settings = settings;
}

void Simulations::start()
{
    _running = true;
    _currentIteration = 0;

    if (_settings.stepTimeMs == 0) {
        // Мгновенное выполнение
        while (_running) {
            step();
            if (!_settings.infinite && _currentIteration >= _settings.iterations) {
                stop();
                break;
            }
        }
    } else {
        _timer->start(_settings.stepTimeMs);
    }
}

void Simulations::stop()
{
    _running = false;
    _timer->stop();
    emit simulationFinished();
}

void Simulations::reset()
{
    _places = _initialPlaces;
    _currentIteration = 0;
    _running = false;
    _timer->stop();

    QVector<int> tokens;
    for (const auto& place : _places) {
        tokens.append(place.tokens);
    }
    emit markingChanged(tokens);
}

void Simulations::step()
{
    QVector<int> enabled = getEnabledTransitions();

    if (enabled.isEmpty()) {
        qDebug() << "No enabled transitions - deadlock or end state";
        stop();
        return;
    }

    // Выбираем случайный переход из разрешённых
    int index = QRandomGenerator::global()->bounded(enabled.size());
    fire(enabled[index]);

    _currentIteration++;

    QVector<int> tokens;
    for (const auto& place : _places) {
        tokens.append(place.tokens);
    }
    emit markingChanged(tokens);
    emit stepCompleted(_currentIteration);

    qDebug() << "Step" << _currentIteration << "- Fired transition" << enabled[index];
}

void Simulations::onTimerTick()
{
    if (!_settings.infinite && _currentIteration >= _settings.iterations) {
        stop();
        return;
    }
    step();
}

bool Simulations::canFire(int transitionIndex) const
{
    const SimTransition& t = _transitions[transitionIndex];

    for (int i = 0; i < t.inputPlaces.size(); ++i) {
        int placeIdx = t.inputPlaces[i];
        int weight = t.inputWeights[i];
        if (_places[placeIdx].tokens < weight) {
            return false;
        }
    }
    return true;
}

void Simulations::fire(int transitionIndex)
{
    SimTransition& t = _transitions[transitionIndex];

    // Убираем фишки из входных позиций
    for (int i = 0; i < t.inputPlaces.size(); ++i) {
        int placeIdx = t.inputPlaces[i];
        int weight = t.inputWeights[i];
        _places[placeIdx].tokens -= weight;
    }

    // Добавляем фишки в выходные позиции
    for (int i = 0; i < t.outputPlaces.size(); ++i) {
        int placeIdx = t.outputPlaces[i];
        int weight = t.outputWeights[i];
        _places[placeIdx].tokens += weight;
    }
}

QVector<int> Simulations::getEnabledTransitions() const
{
    QVector<int> enabled;
    for (int i = 0; i < _transitions.size(); ++i) {
        if (canFire(i)) {
            enabled.append(i);
        }
    }
    return enabled;
}
