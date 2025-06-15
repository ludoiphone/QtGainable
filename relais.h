#ifndef RELAIS_H
#define RELAIS_H

#include "vitesses.h"

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
    void desactiveRelaisVentilationInt();
    void activeRelaisVentFroid();
    void activeRelaisVentExtChauffage();
    void desactiveRelaisVentilationExt();
    void activeRelaisVentIntChauffage();
    void activeRelaisVentCanicule();
    void activeRelaisVentEgouttageFr();
    void activeRelaisVentEgouttageCh();
    void desactiveTousRelais();
    
    void testRelais();

private:
    Vitesses m_relaisVitesses;

    double hysteresisVentExtFr = 3;
};

#endif
