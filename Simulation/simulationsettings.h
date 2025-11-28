#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H

class SimulationSettings
{
public:
    SimulationSettings();
    bool infinite;
    int iterations;

    int stepTimeMs;
};

#endif // SIMULATIONSETTINGS_H
