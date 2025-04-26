#include "hysteresisvitesses.h"

#include <QDebug>
#include <ctime>

HysteresisVitesses::HysteresisVitesses()
{
	m_hysteresisConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    
    m_hysteresisTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
}

void HysteresisVitesses::hysteresisTempVitesseIntCa()
{
    m_hysteresisTemperatures ->lireTemperatureUniteExt();
    m_hysteresisConsignes ->lireConsignesGainable();
    
    if (tempVitIntCa) {
        tempVitIntCa = m_hysteresisTemperatures ->temperatureUnitInt >= (m_hysteresisConsignes ->consigneVentIntCa - hysteresis);
    } else {
        tempVitIntCa = m_hysteresisTemperatures ->temperatureUnitInt >= (m_hysteresisConsignes ->consigneVentIntCa + hysteresis);
    }
}

void HysteresisVitesses::hysteresisTempVitesseExtFroid()
{
    m_hysteresisTemperatures ->lireTemperatureUniteExt();
    m_hysteresisConsignes ->lireConsignesGainable();

    if (tempVitExtFr) {
        tempVitExtFr = m_hysteresisTemperatures ->temperatureUnitExt >= (m_hysteresisConsignes ->consigneGrVitExtFr - hysteresisVentExtFr);
    } else {
        tempVitExtFr = m_hysteresisTemperatures ->temperatureUnitExt >= (m_hysteresisConsignes ->consigneGrVitExtFr);
    }
}

void HysteresisVitesses::hysteresisTempVitesseIntFroid()
{
    m_hysteresisTemperatures ->lireTemperatureUniteInt();
    m_hysteresisConsignes ->lireConsignesGainable();
    
    if (tempVitIntFr) {
        tempVitIntFr = m_hysteresisTemperatures ->temperatureUnitInt >= (m_hysteresisConsignes ->consignePeVitIntFr - hysteresis);
    } else {
        tempVitIntFr = m_hysteresisTemperatures ->temperatureUnitInt >= (m_hysteresisConsignes ->consignePeVitIntFr + hysteresis);
    }
}

void HysteresisVitesses::hysteresisTempVitesseIntChauf()
{
    m_hysteresisTemperatures ->lireTemperatureUniteInt();
    m_hysteresisConsignes ->lireConsignesGainable();

    if (tempVitIntCh) {
        tempVitIntCh = m_hysteresisTemperatures ->temperatureUnitInt <= (m_hysteresisConsignes ->consignePeVitIntCh + hysteresis);
    } else {
        tempVitIntCh = m_hysteresisTemperatures ->temperatureUnitInt <= (m_hysteresisConsignes ->consignePeVitIntCh - hysteresis);
    }
}

void HysteresisVitesses::hysteresisTempVitesseExtChauf()
{
    m_hysteresisTemperatures ->lireTemperatureUniteExt();
    m_hysteresisConsignes ->lireConsignesGainable();

    if (tempVitExtCh) {
        tempVitExtCh = m_hysteresisTemperatures ->temperatureUnitExt >= (m_hysteresisConsignes ->consigneGrVitExtCh - hysteresis);
    } else {
        tempVitExtCh = m_hysteresisTemperatures ->temperatureUnitExt >= (m_hysteresisConsignes ->consigneGrVitExtCh + hysteresis);
    }
}
