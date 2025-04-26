#include "relais.h"

#include "gpioPin.hpp"

#include <QDebug>

#define OFF HIGH
#define ON LOW

// pins relais
const int relaiComp = 5;
const int relaiV4V = 6;
const int relaiVentExt = 13;
const int relaiVitesseVentExt = 16;
const int relaiVentInt = 19;
const int relaiVitesseInt = 20;
const int relaiEteHiver = 26;

Relais::Relais()
{
    pinMode (relaiComp, OUTPUT);
    digitalWrite (relaiComp, OFF);
    pinMode (relaiV4V, OUTPUT);
    digitalWrite (relaiV4V, OFF);
    pinMode (relaiVentExt, OUTPUT);
    digitalWrite (relaiVentExt, OFF);
    pinMode (relaiVitesseVentExt, OUTPUT);
    digitalWrite (relaiVitesseVentExt, OFF);
    pinMode (relaiVentInt, OUTPUT);
    digitalWrite (relaiVentInt, OFF);
    pinMode (relaiVitesseInt, OUTPUT);
    digitalWrite (relaiVitesseInt, OFF);
    pinMode (relaiEteHiver, OUTPUT);
    digitalWrite (relaiEteHiver, OFF);
}

void Relais::activeRelaiEteHiver()
{
    digitalWrite (relaiEteHiver, ON);
    qDebug() << "relai Ete Hiver = ON";
}
void Relais::desactiveRelaiEteHiver()
{
    digitalWrite (relaiEteHiver, OFF);
}

void Relais::activeRelaiV4V()
{
    digitalWrite (relaiV4V, ON);
    qDebug() << "relai V4V = ON";
}
void Relais::desactiveRelaiV4V()
{
    digitalWrite (relaiV4V, OFF);
}

void Relais::activeRelaiComp()
{
    digitalWrite (relaiComp, ON);
    qDebug() << "relai Compresseur = ON";
}
void Relais::desactiveRelaiComp()
{
    digitalWrite (relaiComp, OFF);
}

void Relais::activeRelaisVentilationInt()
{
    qDebug() << "activeRelaisVentilationInt()";
    
    digitalWrite (relaiVentInt, ON);
    digitalWrite (relaiVitesseInt, ON);
}

void Relais::activeRelaisVentFroid() 
{
    qDebug() << "activeRelaisVentFroid()";
    
    m_relaisHysteresis.hysteresisTempVitesseIntFroid();
    m_relaisHysteresis.hysteresisTempVitesseExtFroid();
    
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVentInt, ON);
    
    if (m_relaisHysteresis.tempVitExtFr) { // si la temperature unité exterieur est supperieur a 20°C
        digitalWrite (relaiVitesseVentExt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseVentExt, OFF); // petite vitesse
    }
    if (forceVentIntDegFr == true) {
        digitalWrite (relaiVitesseInt, ON);
    } else if (m_relaisHysteresis.tempVitIntFr) { // si la temperature unité interieur est supperieur a 23°C (aspiration)
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseInt, OFF); // petite vitesse
    }
}

void Relais::activeRelaisVitesseVentIntChauffage() 
{
    m_relaisHysteresis.hysteresisTempVitesseIntChauf();
    
    digitalWrite (relaiVentInt, ON);
    
    if (m_relaisHysteresis.tempVitIntCh) { // si la temperature unité interieur est supperieur a 23°C (aspiration)
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseInt, OFF); // petite vitesse
    }
}

void Relais::activeRelaisVentExtChauffage() 
{
    m_relaisHysteresis.hysteresisTempVitesseExtChauf();
    
    digitalWrite (relaiVentExt, ON);
    
    if (m_relaisHysteresis.tempVitExtCh) { // si la temperature unité exterieur est supperieur a 5°c
        digitalWrite (relaiVitesseVentExt, OFF); // petite vitesse
    } else {
        digitalWrite (relaiVitesseVentExt, ON); // grande vitesse
    }
}

void Relais::activeRelaisVentExtCanicule() 
{
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVitesseVentExt, ON);
}

void Relais::activeRelaisVentIntCanicule() 
{
    m_relaisHysteresis.hysteresisTempVitesseIntCa();
    
    digitalWrite (relaiVentInt, ON);
    
    if (forceVentIntDegFr == true) { // si la temperature de l'echangeur interieur est pendant 1 minute a -5°C force grande vitesse
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else if (m_relaisHysteresis.tempVitIntCa) { // si la temperature de unite interieur est supperieur a la consigne int canicule + 2°C
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseInt, OFF); // petite vitesse
    }
}

void Relais::activeRelaisVentEgouttageFr() 
{
    digitalWrite (relaiVentInt, ON);
    digitalWrite (relaiVitesseInt, ON); // petite vitesse
}

void Relais::activeRelaisVentEgouttageCh() 
{
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVitesseVentExt, ON); // grande vitesse
}

void Relais::desactiveRelaisVentIntCh() 
{
    digitalWrite (relaiVentInt, OFF);
    digitalWrite (relaiVitesseInt, OFF);
}

void Relais::desactiveTousRelais() 
{
    digitalWrite (relaiVitesseVentExt, OFF);
    digitalWrite (relaiVentExt, OFF);
    digitalWrite (relaiVentInt, OFF);
    digitalWrite (relaiVitesseInt, OFF);
    digitalWrite (relaiVitesseInt, OFF);
    digitalWrite (relaiComp, OFF);
    digitalWrite (relaiV4V, OFF);
}

void Relais::testRelais()
{
    digitalWrite (relaiComp, ON);
    digitalWrite (relaiV4V, ON);
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVentInt, ON);
    digitalWrite (relaiVitesseVentExt, ON);
    digitalWrite (relaiVitesseInt, ON);
    digitalWrite (relaiEteHiver, ON);
    
}
