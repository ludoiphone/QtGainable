#ifndef RELAIS_H
#define RELAIS_H

#include "hysteresisvitesses.h"

class Relais
{
    
public:
    Relais();

    bool forceVentIntDegFr = false;
    
    void activeRelaiEteHiver();
    void activeRelaiV4V();
    void desactiveRelaiV4V();
    void activeRelaiComp();
    void desactiveRelaiComp();
    void desactiveRelaiEteHiver();
    void activeRelaisVentilationInt();
    void activeRelaisVentFroid();
    void activeRelaisVentExtChauffage();
    void desactiveRelaisVentIntCh();
    void activeRelaisVitesseVentIntChauffage();
    void activeRelaisVentExtCanicule();
    void activeRelaisVentIntCanicule();
    void activeRelaisVentEgouttageFr();
    void activeRelaisVentEgouttageCh();
    void desactiveTousRelais();
    
    void testRelais();

private:
    HysteresisVitesses m_relaisHysteresis;
    
    double hysteresis = 0.5;
    double hysteresis1 = 1.0;
    double hysteresisVentExtFr = 3;
};

#endif
