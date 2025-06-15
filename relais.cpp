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
    
    m_relaisVitesses.vitesseIntFroid();
    m_relaisVitesses.vitesseExtFroid();
    
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVentInt, ON);
    
    if (m_relaisVitesses.tempVitExtFr == true) { // si la temperature unité exterieur est supperieur a 20°C
        digitalWrite (relaiVitesseVentExt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseVentExt, OFF); // petite vitesse
    }
    if (forceVentIntDegFr == true) {
        digitalWrite (relaiVitesseInt, ON);
    } else if (m_relaisVitesses.tempVitIntFr == true) { // si la temperature unité interieur est supperieur a 23°C (aspiration)
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseInt, OFF); // petite vitesse
    }
}

void Relais::activeRelaisVentIntChauffage() 
{
    qDebug() << "activeRelaisVentIntChauffage()";
    
    m_relaisVitesses.vitesseIntChauf();
    
    digitalWrite (relaiVentInt, ON);
    
    if (m_relaisVitesses.tempVitIntCh == true) { // si la temperature unité interieur est inferieur est comprise entre 21.5 et 25.5 (aspiration)
        digitalWrite (relaiVitesseInt, ON); // grande vitesse
    } else {
        digitalWrite (relaiVitesseInt, OFF); // petite vitesse
    }
}

void Relais::activeRelaisVentExtChauffage() 
{
    qDebug() << "activeRelaisVentExtChauffage()";
    
    m_relaisVitesses.vitesseExtChauf();
    
    digitalWrite (relaiVentExt, ON);
    
    if (m_relaisVitesses.tempVitExtCh == true) { // si la temperature unité exterieur est supperieur a 5°c
        digitalWrite (relaiVitesseVentExt, OFF); // petite vitesse
    } else {
        digitalWrite (relaiVitesseVentExt, ON); // grande vitesse
    }
}

void Relais::activeRelaisVentCanicule() 
{
    qDebug() << "activeRelaisVentCanicule()";
    
    m_relaisVitesses.vitesseIntCa();
    
    digitalWrite (relaiVentExt, ON);
    digitalWrite (relaiVitesseVentExt, ON);
    
    digitalWrite (relaiVentInt, ON);
    
    if (m_relaisVitesses.tempVitIntCa == true) { // si la temperature de unite interieur est supperieur a la consigne int canicule + 4°C
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

void Relais::desactiveRelaisVentilationInt() 
{    
    digitalWrite (relaiVentInt, OFF);
    digitalWrite (relaiVitesseInt, OFF);
}

void Relais::desactiveRelaisVentilationExt()
{
    digitalWrite (relaiVitesseVentExt, OFF);
    digitalWrite (relaiVentExt, OFF);
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
