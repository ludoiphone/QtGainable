#include "canicule.h"

Canicule::Canicule()
{
	m_caniculeConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);

    m_caniculeTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_caniculeFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
}

void Canicule::etatMarcheCanicule()
{
	departTempoVoletsCa = time(NULL);
	transitionGainableCanicule = CONTROLE_TEMPERATURE_CANICULE;
}

void Canicule::etatVoletsCanicule()
{
    gifVentilationCanicule = true;
    m_caniculeRelais.activeRelaisVentilationInt();
    m_caniculeFiltre ->departChronoFiltre = time(NULL);
    departTempoControleTemperatureCa = time(NULL);
    transitionGainableCanicule = CONTROLE_TEMPERATURE_CANICULE;
}

void Canicule::etatControleTemperatureCanicule()
{
	gifVentilationCanicule = true;
	m_caniculeRelais.activeRelaisVentilationInt();
}

void Canicule::etatDepartCanicule()
{
	gifVentilationCanicule = false;
    gifVentilationIntCanicule = true;
    gifVentilationExtCanicule = true;
    m_caniculeRelais.activeRelaisVentCanicule();
    departTempoV4VCa = time(NULL);
    transitionGainableCanicule = TEMPO_V4V_CANICULE;
}

void Canicule::etatModeCaniculeFroid()
{
	passeEnModeFroidEnCanicule = true;
    etatArretCanicule();
    transitionGainableCanicule = ARRET_CANICULE;
}

void Canicule::etatVentilationsCanicule()
{
	m_caniculeRelais.activeRelaisVentCanicule();
}

void Canicule::etatV4VCanicule()
{
	m_caniculeRelais.activeRelaiV4V();
    //compteurV4V++;
    departTempoCompresseurCa = time(NULL);
    transitionGainableCanicule = TEMPO_COMPRESSEUR_CANICULE;
}

void Canicule::etatCompresseurCanicule()
{
	gifCanicule = true;
	m_caniculeRelais.activeRelaiComp();
	transitionGainableCanicule = CONTROLE_VENTILATION_CANICULE;
}

void Canicule::etatArretCanicule()
{
	 qDebug() << "arretCanicule()";

    if (gifCanicule == true) {
		
    }
    gifCanicule = false;
    gifVentilationCanicule = false;
    gifVentilationIntCanicule= false;
    gifVentilationExtCanicule= false;
    if (passeEnModeFroidEnCanicule == true) {
		m_caniculeRelais.activeRelaisVentilationInt();
	} else {
		m_caniculeRelais.desactiveTousRelais();
	}
    m_caniculeFiltre ->lireChronoFiltre();
	qDebug() << "chronoNettoyageFiltre arretFroid()" << m_caniculeFiltre ->chronoNettoyageFiltre;
	m_caniculeFiltre ->finChronoFiltre = time(NULL);		
	qDebug() << "finChronoFiltre" << m_caniculeFiltre ->finChronoFiltre << "departChronoFiltre" << m_caniculeFiltre ->departChronoFiltre;
	m_caniculeFiltre ->chronoNettoyageFiltre = (m_caniculeFiltre ->finChronoFiltre - m_caniculeFiltre ->departChronoFiltre) + m_caniculeFiltre ->chronoNettoyageFiltre;
	qDebug() << "chronoNettoyageFiltre arretFroid()" << m_caniculeFiltre ->chronoNettoyageFiltre;
	m_caniculeFiltre ->ecritChronoNettoyageFiltre();
    transitionGainableCanicule = ARRET_CANICULE;
}

void Canicule::modeCanicule()
{
	switch (transitionGainableCanicule) {
		
		case MARCHE_CANICULE:
		
		qDebug() << "MARCHE_CANICULE";
		
		etatMarcheCanicule();
		
		break;
		
		case TEMPO_VOLETS_CANICULE:
		
        qDebug() << "TEMPO_VOLETS_CANICULE";
            
        if (time(NULL) - departTempoVoletsCa >= tempoVoletsCa) { // tempo de 10 secondes pour l'initialisation des volets
            etatVoletsCanicule();
        }
        
        break;
		
		case CONTROLE_TEMPERATURE_CANICULE:
		
		qDebug() << "CONTROLE_TEMPERATURE_CANICULE";
		
		if (time(NULL) - departTempoControleTemperatureCa >= tempoControleTemperatureCa) { // tempo de 3 minutes
			m_caniculeTemperatures ->lireTemperatureUniteInt();
			m_caniculeTemperatures ->lireTemperatureExt();
			m_caniculeConsignes ->lireConsigneIntCanicule();
			if (m_caniculeTemperatures ->temperatureUnitInt >= m_caniculeConsignes ->consigneIntCanicule) { 
				etatDepartCanicule();
			} else if (m_caniculeTemperatures ->temperatureExt <= m_caniculeConsignes ->consigneCanicule) { // si non si la temperature unite interieur est inferieur as 22°C
				etatModeCaniculeFroid();
			} else {
				departTempoControleTemperatureCa = time(NULL);
			}
		} else {
			etatControleTemperatureCanicule();
		}

        break;
        
        case TEMPO_V4V_CANICULE:
        
        qDebug() << "TEMPO_V4V_CANICULE";
        
        if (time(NULL) - departTempoV4VCa >= tempoV4VCa) {
			etatV4VCanicule();
		} else {
			etatVentilationsCanicule();
		}
        
        break;
        
        case TEMPO_COMPRESSEUR_CANICULE:
        
        qDebug() << "TEMPO_COMPRESSEUR_CANICULE";
        
        if (time(NULL) - departTempoCompresseurCa >= tempoCompresseurCa) {
			etatCompresseurCanicule();
		} else {
			etatVentilationsCanicule();
		}
		
		break;
		
		case CONTROLE_VENTILATION_CANICULE:
		
		qDebug() << "CONTROLE_VENTILATION_CANICULE";
		
		etatVentilationsCanicule();
		
		break;
		
		case ARRET_CANICULE:
		
		qDebug() << "ARRET_CANICULE";
		
		etatMarcheCanicule();
		
		break;
	}
}
