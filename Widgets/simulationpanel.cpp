#include "simulationpanel.h"
#include <QDateTime>
#include <QGroupBox>
#include <QLabel>

SimulationPanel::SimulationPanel(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Группа кнопок управления
    QGroupBox* controlGroup = new QGroupBox("Управление симуляцией");
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    _startButton = new QPushButton("▶ Запустить");
    _pauseButton = new QPushButton("⏸ Пауза");
    _resetButton = new QPushButton("⟲ Сбросить");
    _stepButton = new QPushButton("⏭ Шаг");

    _pauseButton->setEnabled(false);

    buttonLayout->addWidget(_startButton);
    buttonLayout->addWidget(_pauseButton);
    controlLayout->addLayout(buttonLayout);

    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    buttonLayout2->addWidget(_stepButton);
    buttonLayout2->addWidget(_resetButton);
    controlLayout->addLayout(buttonLayout2);

    mainLayout->addWidget(controlGroup);

    // Область логов
    QGroupBox* logGroup = new QGroupBox("Логи симуляции");
    QVBoxLayout* logLayout = new QVBoxLayout(logGroup);

    _logArea = new QTextEdit();
    _logArea->setReadOnly(true);
    _logArea->setPlaceholderText("Логи симуляции будут отображаться здесь...");
    logLayout->addWidget(_logArea);

    mainLayout->addWidget(logGroup, 1);

    // Таймер для автоматической симуляции
    _simulationTimer = new QTimer(this);

    // Подключение сигналов
    connect(_startButton, &QPushButton::clicked, this, &SimulationPanel::onStartClicked);
    connect(_pauseButton, &QPushButton::clicked, this, &SimulationPanel::onPauseClicked);
    connect(_resetButton, &QPushButton::clicked, this, &SimulationPanel::onResetClicked);
    connect(_stepButton, &QPushButton::clicked, this, &SimulationPanel::onStepSimulation);
    connect(_simulationTimer, &QTimer::timeout, this, &SimulationPanel::onStepSimulation);
}

void SimulationPanel::setScene(PetriNetScene* scene)
{
    _scene = scene;
}

void SimulationPanel::setSettings(const SimulationSettings& settings)
{
    _settings = settings;
    _maxIterations = settings.infinite ? -1 : settings.iterations;
    
    // Устанавливаем интервал таймера
    if (settings.stepTimeMs > 0) {
        _simulationTimer->setInterval(settings.stepTimeMs);
    } else {
        _simulationTimer->setInterval(1); // Минимальный интервал для "мгновенной" симуляции
    }
    
    addLog(QString("Настройки: итераций=%1, время шага=%2мс")
           .arg(settings.infinite ? "∞" : QString::number(settings.iterations))
           .arg(settings.stepTimeMs));
}

void SimulationPanel::startSimulation()
{
    // Сбрасываем состояние и запускаем
    onResetClicked();
    onStartClicked();
}

void SimulationPanel::addLog(const QString& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    _logArea->append(QString("[%1] %2").arg(timestamp, message));
}

void SimulationPanel::clearLogs()
{
    _logArea->clear();
}

void SimulationPanel::onStartClicked()
{
    if (!_scene) return;

    if (!_isRunning) {
        // Первый запуск - извлекаем данные сети
        _scene->extractNetData(_places, _transitions);
        saveInitialState();
        _stepCount = 0;
        clearLogs();
        addLog("Симуляция запущена");
        addLog(QString("Загружено %1 позиций и %2 переходов")
                   .arg(_places.size())
                   .arg(_transitions.size()));
    } else if (_isPaused) {
        addLog("Симуляция возобновлена");
    }

    _isRunning = true;
    _isPaused = false;
    _simulationTimer->start();
    updateButtonStates();
    emit simulationStarted();
}

void SimulationPanel::onPauseClicked()
{
    _isPaused = true;
    _simulationTimer->stop();
    addLog("Симуляция приостановлена");
    updateButtonStates();
    emit simulationPaused();
}

void SimulationPanel::onResetClicked()
{
    _simulationTimer->stop();
    _isRunning = false;
    _isPaused = false;
    _stepCount = 0;

    restoreInitialState();
    addLog("Симуляция сброшена в начальное состояние");
    updateButtonStates();
    emit simulationReset();
}

void SimulationPanel::onStepSimulation()
{
    if (!_scene || _places.isEmpty()) {
        if (_scene) {
            _scene->extractNetData(_places, _transitions);
            saveInitialState();
        }
        return;
    }

    // Проверяем лимит итераций
    if (_maxIterations > 0 && _stepCount >= _maxIterations) {
        addLog(QString("Достигнут лимит итераций (%1)").arg(_maxIterations));
        _simulationTimer->stop();
        _isRunning = false;
        updateButtonStates();
        emit simulationFinished();
        return;
    }

    _stepCount++;
    addLog(QString("--- Шаг %1 ---").arg(_stepCount));

    // Находим активные переходы
    QVector<int> enabledTransitions;
    for (int i = 0; i < _transitions.size(); ++i) {
        SimTransition& t = _transitions[i];
        bool enabled = true;

        for (int j = 0; j < t.inputPlaces.size(); ++j) {
            int placeIdx = t.inputPlaces[j];
            int weight = t.inputWeights[j];
            if (_places[placeIdx].tokens < weight) {
                enabled = false;
                break;
            }
        }

        if (enabled && !t.inputPlaces.isEmpty()) {
            enabledTransitions.append(i);
        }
    }

    if (enabledTransitions.isEmpty()) {
        addLog("Нет активных переходов. Симуляция завершена.");
        _simulationTimer->stop();
        _isRunning = false;
        updateButtonStates();
        emit simulationFinished();
        return;
    }

    // Выбираем случайный активный переход
    int selectedIdx = enabledTransitions[rand() % enabledTransitions.size()];
    SimTransition& selectedTransition = _transitions[selectedIdx];

    addLog(QString("Срабатывает переход: %1").arg(selectedTransition.id));

    // Выполняем переход
    if (fireTransition(selectedTransition, _places)) {
        // Выводим состояние позиций
        QString state = "Состояние: ";
        for (int i = 0; i < _places.size(); ++i) {
            state += QString("%1=%2 ").arg(_places[i].id).arg(_places[i].tokens);
        }
        addLog(state);

        // Обновляем визуальное представление на сцене
        for (QGraphicsItem* item : _scene->items()) {
            if (PetriPlace* place = dynamic_cast<PetriPlace*>(item)) {
                for (const SimPlace& sp : _places) {
                    if (sp.id == place->label()) {
                        place->setTokens(sp.tokens);
                        break;
                    }
                }
            }
        }
        _scene->update();
    }
}

bool SimulationPanel::fireTransition(SimTransition& transition, QVector<SimPlace>& places)
{
    // Забираем токены из входных позиций
    for (int i = 0; i < transition.inputPlaces.size(); ++i) {
        int placeIdx = transition.inputPlaces[i];
        int weight = transition.inputWeights[i];
        places[placeIdx].tokens -= weight;
        addLog(QString("  %1: -%2 токенов").arg(places[placeIdx].id).arg(weight));
    }

    // Добавляем токены в выходные позиции
    for (int i = 0; i < transition.outputPlaces.size(); ++i) {
        int placeIdx = transition.outputPlaces[i];
        int weight = transition.outputWeights[i];
        places[placeIdx].tokens += weight;
        addLog(QString("  %1: +%2 токенов").arg(places[placeIdx].id).arg(weight));
    }

    return true;
}

void SimulationPanel::updateButtonStates()
{
    _startButton->setEnabled(!_isRunning || _isPaused);
    _pauseButton->setEnabled(_isRunning && !_isPaused);
    _stepButton->setEnabled(!_isRunning || _isPaused);
}

void SimulationPanel::saveInitialState()
{
    _initialPlaces = _places;
}

void SimulationPanel::restoreInitialState()
{
    _places = _initialPlaces;

    // Восстанавливаем визуальное состояние
    if (_scene) {
        for (QGraphicsItem* item : _scene->items()) {
            if (PetriPlace* place = dynamic_cast<PetriPlace*>(item)) {
                for (const SimPlace& sp : _initialPlaces) {
                    if (sp.id == place->label()) {
                        place->setTokens(sp.tokens);
                        break;
                    }
                }
            }
        }
        _scene->update();
    }
}
