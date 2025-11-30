#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H

class SimulationSettings
{
public:
    SimulationSettings();
    bool infinite = false;
    int iterations = 100;

    int stepTimeMs = 100;
};

#endif // SIMULATIONSETTINGS_H
