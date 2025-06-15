#ifndef VITESSES_H
#define VITESSES_H

#include <ctime>

#include "consignes.h"
#include "temperatures.h"

class Vitesses
{
    
public:
    Vitesses();
    
    bool tempVitIntCa = false;
    bool tempVitExtFr = false;
    bool tempVitIntFr = false;
    bool tempVitExtCh = false;
    bool tempVitIntCh = false;
    
    unsigned long long departChronoTempVitessesExt = time(NULL);
    unsigned long long departChronoTempVitessesInt = time(NULL);
    
    void vitesseIntCa();
    void vitesseExtFroid();
    void vitesseIntFroid();
    void vitesseIntChauf();
    void vitesseExtChauf();

private:
    Consignes *m_vitessesConsignes;
    
    Temperatures *m_vitessesTemperatures;
    
    int tempoTempVitesses = 10;

    double hysteresisVentExtFr = 3;
};

#endif // VITESSES_H
