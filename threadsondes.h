#ifndef THREADSONDES_H
#define THREADSONDES_H

#include <QThread>

#include "temperatures.h"

class ThreadSondes: public QThread
{
	Q_OBJECT
	
public:
    ThreadSondes();
    
    double tempExtLue;
    double tempUnitExtLue;
    double tempEcExtLue;
    double tempUnitIntLue;
    double tempEcIntLue;

private:
    Temperatures *m_threadSondesTemperatures;
    
    QTimer *m_timerEcritTemperatures;
    
    int timerEcrit = 15000;
    
    void ecritToutesTemperaturesLue();
    
    void run();
    
};

#endif //THREADSONDES
