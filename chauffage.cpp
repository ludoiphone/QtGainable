#include "chauffage.h"

#include <QDebug>
#include <ctime>

#include "gpioPin.hpp"
#include "gainable.h"
#include "froid.h"

#define OFF HIGH
#define ON LOW

const int thermostats = 17; 
const int capteurFiltre = 27;

Gainable m_chauffageGainable;

Froid m_chauffageFroid;

Chauffage::Chauffage()
{
    qDebug() << "Chauffage";
	
    pinMode (capteurFiltre, INPUT_PULLUP);
    pinMode (thermostats, INPUT_PULLUP);
    
    m_chauffageConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    
    m_chauffageTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_chauffageFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
}

void Chauffage::arretChauffage()
{
    qDebug() << "arretChauffage()";
}

void Chauffage::froidChauffage()
{
    //etatsGainableChauffage = TEMPO_COMPRESSEUR_CHAUFFAGE;
}

void Chauffage::modeChauffage()
{
    m_chauffageConsignes ->lireConsignesGainable();
    m_chauffageFiltre ->lireChronos();
    
    switch (etatsGainableChauffage) {
	
	case COMMANDE_CHAUFFAGE:
        
        qDebug() << "COMMANDE_CHAUFFAGE";
	
	if (time(NULL) - departTempoVoletsCh >= tempoVoletsCh) {
	    if (time(NULL) - departTempoVentilationCh >= tempoVentilationCh) { // tempo de 3 minutes
		m_chauffageTemperatures ->lireTemperatureUniteInt();
		if (m_chauffageTemperatures ->temperatureUnitInt < m_chauffageConsignes ->consigneDepartChauffageEnChauffage) { // si la temperature unite interieur est inferieur a 22°C
		    m_chauffageTemperatures ->lireTemperatureUniteExt();
		    if (m_chauffageTemperatures ->temperatureUnitExt <= m_chauffageConsignes ->consigneBlocChauf) { // si la temperature unite exterieur est inferieur a 11°C
			departTempoCompCh = time(NULL);
			//m_relais.desactiveRelaisVentIntCh();
			gifVentilationChauffage = false;
			etatsGainableChauffage = TEMPO_COMPRESSEUR_CHAUFFAGE; // production de chauffage
		    } else {
			departTempoVentilationCh = time(NULL);
		    }
		} else if (m_chauffageTemperatures ->temperatureUnitInt > m_chauffageConsignes ->consigneDepartFroidEnChauffage) { // si non si la temperature unite interieur est superieur a 24°C
		    m_chauffageRelais.desactiveRelaiEteHiver(); // relai étéHiver mode froid
		    labelModeChauffage = false;
		    //labelModeFroid = true;
		    departTempoVentilationCh = time(NULL);
		    //etatsGainable = COMMANDE_FROID; // passe en froid///////////////////////////////////////////////////////////////////////
		} else {
		    departTempoVentilationCh = time(NULL);
		}
	    } else {
		gifVentilationChauffage = true;
		m_chauffageRelais.activeRelaisVentilationInt(); // active les relais ventilateur interieur en grande vitesse
	    }
	} else {
	    departTempoVentilationCh = time(NULL);
	}

        break;

        case TEMPO_COMPRESSEUR_CHAUFFAGE:
    
        qDebug() << "TEMPO_COMPRESSEUR_CHAUFFAGE";
        
	if (time(NULL) - departTempoCompCh >= tempoCompCh) {
            departChronoFiltreCh = time(NULL);
            departTempoDegCh = time(NULL);
            qDebug() << "departTempoDegCh 2" << departTempoDegCh;
            //compteurCompCh++;
            etatsGainableChauffage = TEMPO_DEGIVRAGE;
	} else {
	     gifVentilationExtChauffage = true;
	     m_chauffageRelais.desactiveRelaisVentIntCh();
	     m_chauffageRelais.activeRelaisVentExtChauffage();
	}

        break;

        case TEMPO_DEGIVRAGE:
        
        qDebug() << "TEMPO_DEGIVRAGE";
	
	if (time(NULL) - departTempoDegCh >= tempoDegCh) {
            etatsGainableChauffage = MODE_DEGIVRAGE;
        } else {
	    m_chauffageTemperatures ->lireTemperatureEcInt();
            if (m_chauffageTemperatures ->temperatureEcInt >= m_chauffageConsignes ->consigneDepartVentIntCh && gifChauffage == true) {
		gifVentilationIntChauffage = true;
                m_chauffageRelais.activeRelaisVitesseVentIntChauffage();
                m_chauffageRelais.activeRelaisVentExtChauffage();
            } else {
                gifChauffage = true;
                m_chauffageRelais.activeRelaiComp();
                m_chauffageRelais.activeRelaisVentExtChauffage();
            }
        }
        
        break;

        case MODE_DEGIVRAGE:
        
        qDebug() << "MODE_DEGIVRAGE";
	
	m_chauffageTemperatures ->lireTemperatureUniteExt();
	if (m_chauffageTemperatures ->temperatureUnitExt <= m_chauffageConsignes ->consigneModeDegCh) {
	    finChronoFiltreCh = time(NULL);
            //m_chauffageParametres ->chronoFiltre = (finChronoFiltre - departChronoFiltre) + m_chauffageParametres ->chronoFiltre;
            //m_chauffageParametres ->ecritChronoFiltre();
            departTempoV4VDegElec = time(NULL);
            //compteurDegElec++;
            gifVentilationExtChauffage = false;
            gifVentilationIntChauffage = false;
            gifChauffage = false;
            etatsGainableChauffage = TEMPO_DEG_V4V;
         } else {
            finChronoFiltreCh = time(NULL);
            //m_chauffageParametres ->chronoFiltre = (finChronoFiltre - departChronoFiltre) + m_chauffageParametres ->chronoFiltre;
            //m_chauffageParametres ->ecritChronoFiltre();
            departTempoDegNat = time(NULL);
            //compteurDegNat++;
            gifVentilationExtChauffage = false;
            gifVentilationIntChauffage = false;
            gifChauffage = false;
            etatsGainableChauffage = DEGIVRAGE_NATUREL;
        }
    
        break;

        case DEGIVRAGE_NATUREL:
    
        qDebug() << "DEGIVRAGE_NATUREL";
    
        if (time(NULL) - departTempoDegNat >= tempoDegNat) {
            departTempoEgouttageCh = time(NULL);
	    gifDegivrageChauffage = false;
            //compteurEgouttageNat++;
            etatsGainableChauffage = EGOUTTAGE_NATUREL;
        } else {
            m_chauffageRelais.desactiveTousRelais();
            gifDegivrageChauffage = true;
        }

        break;

        case EGOUTTAGE_NATUREL:
    
        qDebug() << "EGOUTTAGE_NATUREL";
	
	if (time(NULL) - departTempoEgouttageCh >= tempoEgouttageCh) {
            departTempoFinEgouttageCh = time(NULL);
            //compteurFinEgouttageNat++;
            etatsGainableChauffage = FIN_EGOUTTAGE_NATUREL;
        } else {
            gifEgouttageChauffage = true;
            m_chauffageRelais.activeRelaisVentEgouttageCh();
        }

        break;

        case FIN_EGOUTTAGE_NATUREL:
    
        qDebug() << "FIN_EGOUTTAGE_NATUREL";
    
        if (time(NULL) - departTempoFinEgouttageCh >= tempoFinEgouttageCh) {
	    gifEgouttageChauffage = false;
            arretChauffage();
        } else {
            m_chauffageRelais.desactiveTousRelais();
        }

        break;

        case TEMPO_DEG_V4V:
        
        qDebug() << "TEMPO_DEG_V4V";
    
        if (time(NULL) - departTempoV4VDegElec >= tempoV4VDegElec) {
            departTempoCompDegElec = time(NULL);
            //compteurV4VDegElec++;
            etatsGainableChauffage = TEMPO_DEG_COMPRESSEUR;
        } else {
            m_chauffageRelais.desactiveTousRelais();
            gifDegivrageChauffage = true;
        }

        break;

        case TEMPO_DEG_COMPRESSEUR:
        
        qDebug() << "TEMPO_DEG_COMPRESSEUR";
    
        if (time(NULL) - departTempoCompDegElec >= tempoCompDegElec) {
            departTempoTempDegElec = time(NULL);
            //compteurCompDegElec++;
            etatsGainableChauffage = DEGIVRAGE_ELECTRIC;
        } else {
            m_chauffageRelais.activeRelaiV4V();
            gifElectriqueChauffage = true;
        }

        break;

        case DEGIVRAGE_ELECTRIC:
    
        qDebug() << "DEGIVRAGE_ELECTRIC";
	
	m_chauffageTemperatures ->lireTemperatureEcExt();
        if (m_chauffageTemperatures ->temperatureEcExt >= m_chauffageConsignes ->consigneFinDegCh) {
            departTempoEgouttageCh = time(NULL);
            //compteurEgouttageCh++;
            //compteurFinDegTemperature++;
            gifDegivrageChauffage = false;
            gifElectriqueChauffage = false;
            etatsGainableChauffage = EGOUTTAGE_CHAUFFAGE;
        } else if (time(NULL) - departTempoTempDegElec >= tempoTempDegElec) {
            departTempoEgouttageCh = time(NULL);
            //compteurEgouttageCh++;
            //compteurFinDegTemps++;
            gifDegivrageChauffage = false;
            gifElectriqueChauffage = false;
            etatsGainableChauffage = EGOUTTAGE_CHAUFFAGE;
        } else {
            m_chauffageRelais.activeRelaiComp();
        }

        break;

        case EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "EGOUTTAGE_CHAUFFAGE";
	
	if (time(NULL) - departTempoEgouttageCh >= tempoEgouttageCh) {
            departTempoFinEgouttageCh = time(NULL);
            //compteurFinEgouttageCh++;
            etatsGainableChauffage = FIN_EGOUTTAGE_CHAUFFAGE;
        } else {
            gifEgouttageChauffage = true;
            m_chauffageRelais.desactiveTousRelais();
        }
        break;

        case FIN_EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "FIN_EGOUTTAGE_CHAUFFAGE";
	
	if (time(NULL) - departTempoFinEgouttageCh >= tempoFinEgouttageCh) {
	    departTempoVoletsCh = time(NULL);
            m_chauffageRelais.desactiveTousRelais();
            gifEgouttageChauffage = false;
            arretChauffage();
        } else {
            m_chauffageRelais.activeRelaisVentEgouttageCh();
        }

        break;
    }
}
