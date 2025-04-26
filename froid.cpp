#include "froid.h"

#include <QDebug>

#include "gpioPin.hpp"
#include "chauffage.h"

#define OFF HIGH
#define ON LOW

const int thermostats = 17; 

Chauffage m_froidChauffage;

Froid::Froid()
{
    qDebug() << "Froid";
	
    pinMode (thermostats, INPUT_PULLUP);
    
    m_froidConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    //m_froidParametres ->setAtomicSyncRequired(false);
    m_froidTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_froidFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
    
    departTempoVoletsFr = time(NULL);
}

void Froid::arretFroid()
{
    qDebug() << "arretFroid()";
    
    if (gifFroid == true) {
	finChronoFiltreFr = time(NULL);
	chronoNettoyageFiltreFr = (finChronoFiltreFr - departChronoFiltreFr) + chronoNettoyageFiltreFr;
	m_froidFiltre ->chronoNettoyageFiltre = chronoNettoyageFiltreFr;
        m_froidFiltre ->ecritChronoNettoyageFiltre();
    }
    departTempoVoletsFr = time(NULL);
    etatsGainableFroid = TEMPO_VOLETS_FROID;
}

void Froid::chauffageFroid()
{
    qDebug() << "chauffageFroid()";
    
}

void Froid::modeFroid()
{
    switch (etatsGainableFroid) {

	case TEMPO_VOLETS_FROID:
		
	qDebug() << "TEMPO_VOLETS_FROID";
	
	if (time(NULL) - departTempoVoletsFr >= tempoVoletsFr) { // tempo de 10 secondes ventilation pour l'initialisation des volets
	    departTempoVentilationFr = time(NULL);
	    gifVentilationFroid = true;
	    m_froidRelais.activeRelaisVentilationInt();
	    etatsGainableFroid = TEMPO_VENTILATION_FROID;
	}
	
	break;
	
	case TEMPO_VENTILATION_FROID:
	
	qDebug() << "TEMPO_VENTILATION_FROID";
	
	if (time(NULL) - departTempoVentilationFr >= tempoVentilationFr) { // tempo de 3 minutes
	    m_froidTemperatures ->lireTemperatureUniteInt();
	    m_froidConsignes ->lireConsignesGainable();
	    if (m_froidTemperatures ->temperatureUnitInt > m_froidConsignes ->consigneDepartFroidEnFroid) { // si la temperature unite interieur est supperieur (reglable) 
		departTempoV4VFr = time(NULL);
		gifVentilationFroid = false;
		gifVentilationIntFroid = true;
		gifVentilationExtFroid = true;
		etatsGainableFroid = TEMPO_V4V_FROID; // passe en prodution de froid
	    } else if (m_froidTemperatures ->temperatureUnitInt < m_froidConsignes ->consigneDepartChauffageEnFroid) { // si non si la temperature unite interieur est inferieur as 22°C
		departTempoCompresseurFr = time(NULL);
		m_froidRelais.activeRelaiEteHiver();//relai étéHiver (mode chauffage)
		//labelModeFroid = false;
		//m_froidChauffage.labelModeChauffage = true;
		//m_froidChauffage.froidChauffage(); // passe en mode chauffage
	    } else {
		departTempoVentilationFr = time(NULL);
		etatsGainableFroid = TEMPO_VOLETS_FROID;
	    }
	}
	
	break;
		
	case TEMPO_V4V_FROID:
        
        qDebug() << "TEMPO_V4V_FROID";
	
	if (time(NULL) - departTempoV4VFr >= tempoV4VFr) {
	    departTempoCompresseurFr = time(NULL);
            m_froidRelais.activeRelaiV4V();
            //compteurV4V++;
            etatsGainableFroid = TEMPO_COMPRESSEUR_FROID;
        } else {
            m_froidRelais.activeRelaisVentFroid();
        }
        
        break;

        case TEMPO_COMPRESSEUR_FROID:
        
        qDebug() << "TEMPO_COMPRESSEUR_FROID";
        
	if (time(NULL) - departTempoCompresseurFr >= tempoCompresseurFr) {
	    departTempoTempsDegivrageFr = time(NULL);
	    departChronoFiltreFr = time(NULL);
            //compteurComp++;
	    gifFroid = true;
	    m_froidRelais.activeRelaiComp();
            etatsGainableFroid = TEMPO_VENTILATION_DEGIVRAGE_FROID;
        } else {
            m_froidRelais.activeRelaisVentFroid();
        }

        break;

        case TEMPO_VENTILATION_DEGIVRAGE_FROID:
        
        qDebug() << "TEMPO_DEGIVRAGE_FROID";
	
	if (time(NULL) - departTempoTempsDegivrageFr >= tempoTempsDegivrageFr) { // tempo 20 minutes
	    m_froidTemperatures ->lireTemperatureEcInt();
	    m_froidConsignes ->lireConsignesGainable();
            if (m_froidTemperatures ->temperatureEcInt < m_froidConsignes ->consigneDegFr) { // si temperature echangeur interieur est inferieur as -3°C (reglable)
                m_froidRelais.forceVentIntDegFr = true; // ventilation interieur grande vitesse
		etatsGainableFroid = TEMPO_DEGIVRAGE_FROID;
	    } else {
		departTempoTempsDegivrageFr = time(NULL);
	    }
	} else {
	    departTempoDegivrageFr = time(NULL);
	    m_froidRelais.activeRelaisVentFroid();
	}
			
	break;
                
	case TEMPO_DEGIVRAGE_FROID:
	
	qDebug() << "TEMPO_DEGIVRAGE_FROID";
	
	if (time(NULL) - departTempoDegivrageFr >= tempoDegivrageFr) { // tempo 2 minutes
	    m_froidTemperatures ->lireTemperatureEcInt();
	    m_froidConsignes ->lireConsignesGainable();
	    if (m_froidTemperatures ->temperatureEcInt < m_froidConsignes ->consigneDegFr) { // si la temperature echangeur est toujours a -3°C 
		departTempoFinDegivrageFr = time(NULL);
		finChronoFiltreFr = time(NULL);
		/*m_froidParametres ->chronoFiltre = (m_froidFiltre.finChronoFiltre - m_froidFiltre.departChronoFiltre) + m_froidParametres ->chronoFiltre;
		m_froidParametres ->ecritChronoFiltre();*/
		//m_froidGainable.finChronoFiltre = time(NULL);
		//m_froidParametres ->chronoNettoyageFiltre = (m_froidGainable.finChronoFiltre - m_froidGainable.departChronoFiltre) + m_froidParametres ->chronoNettoyageFiltre;
		//m_froidParametres ->ecritChronoNettoyageFiltre();
		gifFroid = false;
		m_froidRelais.forceVentIntDegFr = false;
		gifVentilationExtFroid = false;
		gifVentilationIntFroid = false;
		gifDegivrageFroid = true;
		degivrageFroid = true;
		m_froidRelais.desactiveTousRelais();
		//compteurDegFr++;
		etatsGainableFroid = DEGIVRAGE_FROID; // passe en degivrage
	    } else {
		departTempoDegivrageFr = time(NULL);
		//etatsGainableFroid = TEMPO_VENTILATION_DEGIVRAGE_FROID;
	    }
	} else {
	    m_froidRelais.activeRelaisVentFroid();
	}
    
        break;

        case DEGIVRAGE_FROID:
        
        qDebug() << "DEGIVRAGE_FROID";
	
	//m_froidTemperatures ->lireTemperatureEcInt();
	//m_froidParametres ->lireConsignesGainable();
        if (time(NULL) - departTempoFinDegivrageFr >= tempoFinDegivrageFr) {
	    qDebug() << "tempoFinDegivrage" << departTempoFinDegivrageFr;
	    m_froidTemperatures ->lireTemperatureEcInt();
	    m_froidConsignes ->lireConsignesGainable();
	    if (m_froidTemperatures ->temperatureEcInt >= m_froidConsignes ->consigneFinDegFr) {
		departTempoEgouttageFr = time(NULL);
		gifDegivrageFroid = false;
		gifVentilationDegFroid = true;
		gifEgouttageFroid = true;
		//compteurEgouttageFr++;
		m_froidRelais.activeRelaisVentEgouttageFr();
		etatsGainableFroid = EGOUTTAGE_FROID;
	    } else {
		departTempoFinDegivrageFr = time(NULL);
	    }
	}

        break;

        case EGOUTTAGE_FROID:
    
        qDebug() << "EGOUTTAGE_FROID";
        
        if (time(NULL) - departTempoEgouttageFr >= tempoEgouttageFr) {
	    departTempoFinEgouttageFr = time(NULL);
            gifVentilationDegFroid = false;
	    gifEgouttageFroid = false;
            //compteurFinEgouttageFr++;
            etatsGainableFroid = FIN_EGOUTTAGE_FROID;
        } else {
	    
        }

        break;

        case FIN_EGOUTTAGE_FROID:
        
        qDebug() << "FIN_EGOUTTAGE_FROID";
	
        if (time(NULL) - departTempoFinEgouttageFr >= tempoFinEgouttageFr) {
	    departTempoVoletsFr = time(NULL);
	    gifEgouttageFroid = false;
	    degivrageFroid = false;
            arretFroid();
        } else {
            m_froidRelais.desactiveTousRelais();
        }
        
        break;
	
    }
}
