#ifndef HYSTERESISVITESSES_H
#define HYSTERESISVITESSES_H

#include "consignes.h"
#include "temperatures.h"

class HysteresisVitesses
{

public:
    HysteresisVitesses();
    
    bool tempVitIntCa = false;
    bool tempVitExtFr = false;
    bool tempVitIntFr = false;
    bool tempVitExtCh = false;
    bool tempVitIntCh = false;
    
    void hysteresisTempVitesseIntCa();
    void hysteresisTempVitesseExtFroid();
    void hysteresisTempVitesseIntFroid();
    void hysteresisTempVitesseIntChauf();
    void hysteresisTempVitesseExtChauf();

private:
    Consignes *m_hysteresisConsignes;
    
    Temperatures *m_hysteresisTemperatures;

    double hysteresis = 0.5;
    double hysteresis1 = 1.0;
    double hysteresisVentExtFr = 3;
};

#endif // HYSTERESISVITESSES_H
