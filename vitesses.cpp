#include "vitesses.h"

#include <QDebug>

Vitesses::Vitesses()
{
	m_vitessesConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    
    m_vitessesTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
}

void Vitesses::vitesseIntFroid()
{
    if (time(NULL) - departChronoTempVitessesInt >= tempoTempVitesses) { 
        m_vitessesConsignes ->lireConsignesGainable();
        m_vitessesTemperatures ->lireTemperatureUniteInt();
        if (m_vitessesTemperatures ->temperatureUnitInt >= m_vitessesConsignes ->consignePeVitIntFr) { // si la temperature unité interieur est comprise entre
            tempVitIntFr = true; // grande vitesse
        } else {
            tempVitIntFr = false; // petite vitesse
        }
        departChronoTempVitessesInt = time(NULL);
    }
}

void Vitesses::vitesseIntChauf()
{
    if (time(NULL) - departChronoTempVitessesInt >= tempoTempVitesses) {
        m_vitessesConsignes ->lireConsignesGainable();
        m_vitessesTemperatures ->lireTemperatureUniteInt();
        if (m_vitessesTemperatures ->temperatureUnitInt <= m_vitessesConsignes ->consignePeVitIntCh) { // si la temperature unité interieur est comprise entre 21.5 et 25.5 (aspiration)
            tempVitIntCh = true;
        } else {
            tempVitIntCh = false;
        }
        departChronoTempVitessesInt = time(NULL);
    }
}

void Vitesses::vitesseIntCa()
{
    if (time(NULL) - departChronoTempVitessesInt >= tempoTempVitesses) {
        m_vitessesTemperatures ->lireTemperatureUniteInt();
        m_vitessesTemperatures ->lireTemperatureExt();
        m_vitessesConsignes ->lireConsigneVentIntCanicule();
        if (m_vitessesTemperatures ->temperatureUnitInt >= m_vitessesConsignes ->consigneVentIntCanicule) {
            tempVitIntCa = true;
        } else {
            tempVitIntCa = false;
        }
        departChronoTempVitessesInt = time(NULL);
    }
}

void Vitesses::vitesseExtFroid()
{
    if (time(NULL) - departChronoTempVitessesExt >= tempoTempVitesses) {
        m_vitessesConsignes ->lireConsignesGainable();
        m_vitessesTemperatures ->lireTemperatureUniteExt();
        if (m_vitessesTemperatures ->temperatureUnitExt >= m_vitessesConsignes ->consigneGrVitExtFr) {
            tempVitExtFr = true;
        } else {
            if (m_vitessesTemperatures ->temperatureUnitExt <= (m_vitessesConsignes ->consigneGrVitExtFr - hysteresisVentExtFr)) {
                tempVitExtFr = false;
            }
            departChronoTempVitessesExt = time(NULL);
        }
        departChronoTempVitessesExt = time(NULL);
    }
}

void Vitesses::vitesseExtChauf()
{
    if (time(NULL) - departChronoTempVitessesExt >= tempoTempVitesses) {
        m_vitessesConsignes ->lireConsignesGainable();
        m_vitessesTemperatures ->lireTemperatureUniteExt();
        if (m_vitessesTemperatures ->temperatureUnitExt <= m_vitessesConsignes ->consigneGrVitExtCh) {
            tempVitExtCh = true;
        } else {
            tempVitExtCh = false;
        }
        departChronoTempVitessesExt = time(NULL);
    }
}
