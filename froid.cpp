#include "froid.h"

#include <QDebug>

Froid::Froid()
{
    qDebug() << "Froid";
    
    m_froidConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);

    m_froidTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_froidFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
}

void Froid::etatMarcheFroid()
{
    m_froidRelais.desactiveRelaiEteHiver();
    departTempoVoletsFr = time(NULL);
    transitionGainableFroid = TEMPO_VOLETS_FROID;
}

void Froid::etatVoletsFroid()
{
    gifVentilationFroid = true;
    m_froidRelais.activeRelaisVentilationInt();
    m_froidFiltre ->departChronoFiltre = time(NULL);
    departTempoControleTemperatureFr = time(NULL);
    transitionGainableFroid = TEMPO_CONTROLE_TEMPERATURE_FROID;
}

void Froid::etatControleTemperatureFroid()
{
    m_froidRelais.activeRelaisVentilationInt();
}

void Froid::etatDepartFroid()
{
    gifVentilationFroid = false;
    gifVentilationIntFroid = true;
    gifVentilationExtFroid = true;
    m_froidRelais.activeRelaisVentFroid();
    departTempoV4VFr = time(NULL);
    transitionGainableFroid = TEMPO_V4V_FROID;
}

void Froid::etatModeFroidChauffage()
{
    passeEnModeChauffage = true;
    etatArretFroid();
    transitionGainableFroid = ARRET_FROID;
}

void Froid::etatModeFroidCanicule()
{
    passeEnModeCanicule = true;
    etatArretFroid();
    transitionGainableFroid = ARRET_FROID;
}

void Froid::etatVentilationsFroid()
{
    m_froidRelais.activeRelaisVentFroid();
}

void Froid::etatV4VFroid()
{
    m_froidRelais.activeRelaiV4V();
    //compteurV4V++;
    departTempoCompresseurFr = time(NULL);
    transitionGainableFroid = TEMPO_COMPRESSEUR_FROID;
}

void Froid::etatCompresseurFroid()
{
    gifFroid = true;
    m_froidRelais.activeRelaiComp();
    //compteurComp++;
    departTempoControleDegivrageFr = time(NULL);
    transitionGainableFroid = TEMPO_CONTROLE_TEMPERATURE_DEGIVRAGE_FROID;
}

void Froid::etatControleDegivrageFroid()
{
    departTempoDegivrageFr = time(NULL);
    m_froidRelais.forceVentIntDegFr = true;
    transitionGainableFroid = CONTROLE_DEGIVRAGE_FROID;
}

void Froid::etatControleTemperatureDegivrageFroid()
{
    departTempoDegivrageFr = time(NULL);
    m_froidRelais.forceVentIntDegFr = false;
    transitionGainableFroid = CONTROLE_DEGIVRAGE_FROID;
}

void Froid::etatFinDegivrageFroid()
{
    gifFroid = false;
    m_froidRelais.forceVentIntDegFr = false;
    gifVentilationExtFroid = false;
    gifVentilationIntFroid = false;
    gifDegivrageFroid = true;
    degivrageFroid = true;
    m_froidFiltre ->finChronoFiltre = time(NULL);
    /*m_froidParametres ->chronoFiltre = (m_froidFiltre.finChronoFiltre - m_froidFiltre.departChronoFiltre) + m_froidParametres ->chronoFiltre;
    * m_froidParametres ->ecritChronoFiltre();*/
    //m_froidGainable.finChronoFiltre = time(NULL);
    //m_froidParametres ->chronoNettoyageFiltre = (m_froidGainable.finChronoFiltre - m_froidGainable.departChronoFiltre) + m_froidParametres ->chronoNettoyageFiltre;
    //m_froidParametres ->ecritChronoNettoyageFiltre();
    m_froidRelais.desactiveTousRelais();
    //compteurDegFr++;
    transitionGainableFroid = FIN_DEGIVRAGE_FROID; // passe en degivrage
}

void Froid::etatEgouttageFroid()
{
    departTempoEgouttageFr = time(NULL);
    gifDegivrageFroid = false;
    gifVentilationDegFroid = true;
    gifEgouttageFroid = true;
    //compteurEgouttageFr++;
    transitionGainableFroid = TEMPO_EGOUTTAGE_FROID;
}

void Froid::etatFinEgouttageFroid()
{
    departTempoFinEgouttageFr = time(NULL);
    gifVentilationDegFroid = false;
    //compteurFinEgouttageFr++;
    m_froidRelais.activeRelaisVentEgouttageFr();
    transitionGainableFroid = TEMPO_FIN_EGOUTTAGE_FROID;
}

void Froid::etatArretFroid()
{
    gifFroid = false;
    gifVentilationFroid = false;
    gifVentilationIntFroid = false;
    gifsVitessesIntFroid = false;
    gifVentilationExtFroid = false;
    gifVentilationDegFroid = false;
    gifDegivrageFroid = false;
    gifEgouttageFroid = false;
    if (passeEnModeChauffage == true || passeEnModeCanicule == true) {
	m_froidRelais.activeRelaisVentilationInt();
    } else {
	m_froidRelais.desactiveTousRelais();
    }
    m_froidFiltre ->lireChronoFiltre();
    qDebug() << "chronoNettoyageFiltre arretFroid()" << m_froidFiltre ->chronoNettoyageFiltre;
    m_froidFiltre ->finChronoFiltre = time(NULL);
    qDebug() << "finChronoFiltre" << m_froidFiltre ->finChronoFiltre << "departChronoFiltre" << m_froidFiltre ->departChronoFiltre;
    m_froidFiltre ->chronoNettoyageFiltre = (m_froidFiltre ->finChronoFiltre - m_froidFiltre ->departChronoFiltre) + m_froidFiltre ->chronoNettoyageFiltre;
    qDebug() << "chronoNettoyageFiltre arretFroid()" << m_froidFiltre ->chronoNettoyageFiltre;
    m_froidFiltre ->ecritChronoNettoyageFiltre();
    transitionGainableFroid = ARRET_FROID;
}

void Froid::modeFroid()
{
    switch (transitionGainableFroid) {
        
        case MARCHE_FROID:
            
        qDebug() << "MARCHE_FROID";
	
	etatMarcheFroid();
	
        break;
        
        case TEMPO_VOLETS_FROID:
		
        qDebug() << "TEMPO_VOLETS_FROID";
            
        if (time(NULL) - departTempoVoletsFr >= tempoVoletsFr) { // tempo de 10 secondes pour l'initialisation des volets
            etatVoletsFroid();
        }
        
        break;
        
        case TEMPO_CONTROLE_TEMPERATURE_FROID:
            
        qDebug() << "TEMPO_CONTROLE_TEMPERATURE_FROID";
            
        if (time(NULL) - departTempoControleTemperatureFr >= tempoControleTemperatureFr) { // tempo de 3 minutes
            m_froidTemperatures ->lireTemperatureUniteInt();
            m_froidConsignes ->lireConsignesGainable();
            if (m_froidTemperatures ->temperatureUnitInt > m_froidConsignes ->consigneDepartFroidEnFroid) { // si la temperature unite interieur est supperieur à consigne froid
		etatDepartFroid();
            } else if (m_froidTemperatures ->temperatureUnitInt < m_froidConsignes ->consigneDepartChauffageEnFroid) { // si non si la temperature unite interieur est inferieur à consigne chauffage
		etatModeFroidChauffage();
	    } else if (m_froidTemperatures ->temperatureExt >= m_froidConsignes ->consigneCanicule) { // si la temperature ext est supperieur à consigne canicule 
		etatModeFroidCanicule();
            } else {
                departTempoControleTemperatureFr = time(NULL);
            }
        } else {
            etatControleTemperatureFroid();
        }
	
	break;
		
	case TEMPO_V4V_FROID:
        
	qDebug() << "TEMPO_V4V_FROID";
	
	if (time(NULL) - departTempoV4VFr >= tempoV4VFr) {
	    etatV4VFroid();
	} else {
	    etatVentilationsFroid();
	}
        
	break;
	
	case TEMPO_COMPRESSEUR_FROID:
        
	qDebug() << "TEMPO_COMPRESSEUR_FROID";
        
	if (time(NULL) - departTempoCompresseurFr >= tempoCompresseurFr) {
	    etatCompresseurFroid();
	} else {
	    etatVentilationsFroid();
	}
	
	break;
	
	case TEMPO_CONTROLE_TEMPERATURE_DEGIVRAGE_FROID:
        
	qDebug() << "TEMPO_CONTROLE_TEMPERATURE_DEGIVRAGE_FROID";
	
	if (time(NULL) - departTempoControleDegivrageFr >= tempoControleDegivrageFr) { // tempo 20 minutes
	    m_froidTemperatures ->lireTemperatureEcInt();
	    m_froidConsignes ->lireConsignesGainable();
	    if (m_froidTemperatures ->temperatureEcInt < m_froidConsignes ->consigneDegFr) { // si temperature echangeur interieur est inferieur as -3°C (reglable)
		etatControleDegivrageFroid();
	    } else {
		departTempoControleDegivrageFr = time(NULL);
	    }
	} else {
	    etatVentilationsFroid();
	}
			
	break;
                
	case CONTROLE_DEGIVRAGE_FROID:
	
	qDebug() << "CONTROLE_DEGIVRAGE_FROID";
	
	if (time(NULL) - departTempoDegivrageFr >= tempoDegivrageFr) { // tempo 2 minutes
	    m_froidTemperatures ->lireTemperatureEcInt();
	    m_froidConsignes ->lireConsignesGainable();
	    if (degivrageFroid == true) {
		transitionGainableFroid = FIN_DEGIVRAGE_FROID; 
	    } else if (m_froidTemperatures ->temperatureEcInt < m_froidConsignes ->consigneDegFr) { // si la temperature echangeur est a -3°C 
		etatFinDegivrageFroid();
	    } else {
		etatControleTemperatureDegivrageFroid();
	    }
	} else {
	    etatVentilationsFroid();
	}
    
        break;

        case FIN_DEGIVRAGE_FROID:
        
        qDebug() << "FIN_DEGIVRAGE_FROID";
	
	if (m_froidTemperatures ->temperatureEcInt >= m_froidConsignes ->consigneFinDegFr) { // si la temperature est supperieur as 12°C
	    etatEgouttageFroid();
	} else {
	    etatControleTemperatureDegivrageFroid();
	}

        break;

        case TEMPO_EGOUTTAGE_FROID:
    
        qDebug() << "TEMPO_EGOUTTAGE_FROID";
        
	if (time(NULL) - departTempoEgouttageFr >= tempoEgouttageFr) {
	    etatFinEgouttageFroid();
	}

        break;

        case TEMPO_FIN_EGOUTTAGE_FROID:
        
        qDebug() << "TEMPO_FIN_EGOUTTAGE_FROID";
	
	if (time(NULL) - departTempoFinEgouttageFr >= tempoFinEgouttageFr) {
	   etatMarcheFroid();
	}

        break;
	
	case ARRET_FROID:
	
	qDebug() << "ARRET_FROID";
	
	etatMarcheFroid();
	
	break;
    }
}
