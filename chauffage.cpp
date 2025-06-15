#include "chauffage.h"

#include <QDebug>

Chauffage::Chauffage()
{
    qDebug() << "Chauffage";
    
    m_chauffageConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    
    m_chauffageTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_chauffageFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
}

void Chauffage::etatMarcheChauffage()
{
    m_chauffageRelais.activeRelaiEteHiver();
    departTempoVoletsCh = time(NULL);
    transitionGainableChauffage = TEMPO_VOLETS_CHAUFFAGE;
}

void Chauffage::etatVoletsChauffage()
{
    gifVentilationChauffage = true;
    m_chauffageRelais.activeRelaisVentilationInt();
    m_chauffageFiltre ->departChronoFiltre = time(NULL);
    departTempoControleTemperatureCh = time(NULL);
    transitionGainableChauffage = CONTROLE_TEMPERATURE_CHAUFFAGE;
}

void Chauffage::etatControleTemperatureChauffage()
{
    m_chauffageRelais.activeRelaisVentilationInt();
}

void Chauffage::etatDepartChauffage()
{
    gifVentilationChauffage = false;
    m_chauffageRelais.desactiveRelaisVentilationInt();
    departTempoCompCh = time(NULL);
    transitionGainableChauffage = TEMPO_COMPRESSEUR_CHAUFFAGE;
}

void Chauffage::etatModeChauffageFroid()
{
    passeEnModeFroidEnChauffage = true;
    etatArretChauffage();
    transitionGainableChauffage = ARRET_CHAUFFAGE;
}

void Chauffage::etatVentilationsExterieurChauffage()
{
    gifVentilationExtChauffage = true;
    m_chauffageRelais.activeRelaisVentExtChauffage();
}

void Chauffage::etatCompresseurChauffage()
{
    gifChauffage = true;
    m_chauffageRelais.activeRelaiComp();
    departTempoControleTemperatureVentilationCh = time(NULL);
    transitionGainableChauffage = CONTROLE_TEMPERATURE_VENTILATION_INTERIEUR;
}

void Chauffage::etatControleTemperatureVentilationChauffage()
{
    gifVentilationIntChauffage = true;
    m_chauffageRelais.activeRelaisVentIntChauffage();
    departTempoDegCh = time(NULL);
    transitionGainableChauffage = TEMPO_DEGIVRAGE_CHAUFFAGE;
}

void Chauffage::etatVentilationsChauffage()
{
    m_chauffageRelais.activeRelaisVentExtChauffage();
    m_chauffageRelais.activeRelaisVentIntChauffage();
}

void Chauffage::etatDegivrageChauffage()
{
    gifVentilationExtChauffage = false;
    gifVentilationIntChauffage = false;
    gifChauffage = false;
    m_chauffageFiltre ->finChronoFiltre = time(NULL);
    //m_chauffageParametres ->chronoFiltre = (finChronoFiltre - departChronoFiltre) + m_chauffageParametres ->chronoFiltre;
    //m_chauffageParametres ->ecritChronoFiltre();
    m_chauffageRelais.desactiveTousRelais();
    transitionGainableChauffage = MODE_DEGIVRAGE_CHAUFFAGE;
}

void Chauffage::etatModeDegivrageElectric()
{
    departTempoV4VDegElec = time(NULL);
    //compteurDegElec++;
    transitionGainableChauffage = TEMPO_DEGIVRAGE_V4V;
}

void Chauffage::etatModeDegivrageNaturel()
{
    departTempoDegNat = time(NULL);
    //compteurDegNat++;
    transitionGainableChauffage = DEGIVRAGE_NATUREL;
}

void Chauffage::etatDegivrageV4V()
{
    gifDegivrageChauffage = true;
    m_chauffageRelais.activeRelaiV4V();
    //compteurV4VDegElec++;
    departTempoCompDegElec = time(NULL);
    transitionGainableChauffage = TEMPO_DEGIVRAGE_COMPRESSEUR;
}

void Chauffage::etatDegivrageCompresseur()
{
    gifElectriqueChauffage = true;
    m_chauffageRelais.activeRelaiComp();
    //compteurCompDegElec++;
    departTempoTempDegElec = time(NULL);
    transitionGainableChauffage = CONTROLE_TEMPERATURE_DEGIVRAGE_ELECTRIC;
}

void Chauffage::etatControleDegivrageElectric()
{
    gifDegivrageChauffage = false;
    gifElectriqueChauffage = false;
    //compteurEgouttageCh++;
    //compteurFinDegTemps++;
    departTempoEgouttageCh = time(NULL);
    transitionGainableChauffage = EGOUTTAGE_CHAUFFAGE;
}

void Chauffage::etatEgouttageChauffage()
{
    gifEgouttageChauffage = true;
    m_chauffageRelais.activeRelaisVentEgouttageCh();
    //compteurFinEgouttageNat++;
    departTempoFinEgouttageCh = time(NULL);
    transitionGainableChauffage = FIN_EGOUTTAGE_CHAUFFAGE;
}

void Chauffage::etatFinEgouttageChauffage()
{
    gifEgouttageChauffage = false;
    m_chauffageRelais.desactiveTousRelais();
}

void Chauffage::etatArretChauffage()
{
    gifChauffage = false;
    gifVentilationChauffage = false;
    gifVentilationIntChauffage = false;
    gifVentilationExtChauffage = false;
    gifVentilationDegChauffage = false;
    gifDegivrageChauffage = false;
    gifEgouttageChauffage = false;
    if (passeEnModeFroidEnChauffage == true) {
	m_chauffageRelais.activeRelaisVentilationInt();
    } else {
	m_chauffageRelais.desactiveTousRelais();
    }
    m_chauffageFiltre ->lireChronoFiltre();
    qDebug() << "chronoNettoyageFiltre arretFroid()" << m_chauffageFiltre ->chronoNettoyageFiltre;
    m_chauffageFiltre ->finChronoFiltre = time(NULL);
    qDebug() << "finChronoFiltre" << m_chauffageFiltre ->finChronoFiltre << "departChronoFiltre" << m_chauffageFiltre ->departChronoFiltre;
    m_chauffageFiltre ->chronoNettoyageFiltre = (m_chauffageFiltre ->finChronoFiltre - m_chauffageFiltre ->departChronoFiltre) + m_chauffageFiltre ->chronoNettoyageFiltre;
    qDebug() << "chronoNettoyageFiltre arretFroid()" << m_chauffageFiltre ->chronoNettoyageFiltre;
    m_chauffageFiltre ->ecritChronoNettoyageFiltre();
    transitionGainableChauffage = ARRET_CHAUFFAGE;
}

void Chauffage::modeChauffage()
{
    switch (transitionGainableChauffage) {
	
	case MARCHE_CHAUFFAGE:
	
	qDebug() << "MARCHE_CHAUFFAGE";
	
	etatMarcheChauffage();
	
	break;
	
	case TEMPO_VOLETS_CHAUFFAGE:
	
	qDebug() << "TEMPO_VOLETS_CHAUFFAGE";
	
	if (time(NULL) - departTempoVoletsCh >= tempoVoletsCh) {
	    etatVoletsChauffage();
	}
	
	break;
	
	case CONTROLE_TEMPERATURE_CHAUFFAGE:
        
	qDebug() << "CONTROLE_TEMPERATURE_CHAUFFAGE";
	
	if (time(NULL) - departTempoControleTemperatureCh >= tempoControleTemperatureCh) { // tempo de 3 minutes
	    m_chauffageTemperatures ->lireTemperatureUniteInt();
	    m_chauffageTemperatures ->lireTemperatureUniteExt();
	    m_chauffageConsignes ->lireConsignesGainable();
	    if (m_chauffageTemperatures ->temperatureUnitInt < m_chauffageConsignes ->consigneDepartChauffageEnChauffage) { // si la temperature unite interieur est supperieur (reglable entre 17 et 21) 
		if (m_chauffageTemperatures ->temperatureUnitExt < m_chauffageConsignes ->consigneBlocChauf) { // si la tremperature est inferieur as 10°C
		    etatDepartChauffage();
		} else {
		    departTempoControleTemperatureCh = time(NULL);
		}
	    } else if (m_chauffageTemperatures ->temperatureUnitInt > m_chauffageConsignes ->consigneDepartFroidEnChauffage) { // si non si la temperature unite interieur est inferieur as 22°C
		etatModeChauffageFroid();
	    } else {
		departTempoControleTemperatureCh = time(NULL);
	    }
	} else {
	    etatControleTemperatureChauffage();
	}

        break;

        case TEMPO_COMPRESSEUR_CHAUFFAGE:
    
        qDebug() << "TEMPO_COMPRESSEUR_CHAUFFAGE";
        
	if (time(NULL) - departTempoCompCh >= tempoCompCh) {
	    etatCompresseurChauffage();
	} else {
	    etatVentilationsExterieurChauffage();
	}

        break;
	
	case CONTROLE_TEMPERATURE_VENTILATION_INTERIEUR:
	
	qDebug() << "CONTROLE_TEMPERATURE_VENTILATION_CHAUFFAGE";
	
	if (time(NULL) - departTempoControleTemperatureVentilationCh >= tempoControleTemperatureVentilationCh) {
	    m_chauffageTemperatures ->lireTemperatureEcInt();
	    m_chauffageConsignes ->lireConsignesGainable();
	    if (m_chauffageTemperatures ->temperatureEcInt >= m_chauffageConsignes ->consigneDepartVentIntCh) {
		etatControleTemperatureVentilationChauffage();
	    } else {
		departTempoControleTemperatureVentilationCh = time(NULL);
	    }
	} else {
	    etatVentilationsExterieurChauffage();
	}
	
	break;

        case TEMPO_DEGIVRAGE_CHAUFFAGE:
        
        qDebug() << "TEMPO_DEGIVRAGE_CHAUFFAGE";
	
	if (time(NULL) - departTempoDegCh >= tempoDegCh) {
	    etatDegivrageChauffage();
	} else {
	    etatVentilationsChauffage();
	}
        
        break;

        case MODE_DEGIVRAGE_CHAUFFAGE:
        
        qDebug() << "MODE_DEGIVRAGE_CHAUFFAGE";
	
	m_chauffageTemperatures ->lireTemperatureUniteExt();
	m_chauffageConsignes ->lireConsignesGainable();
	if (m_chauffageTemperatures ->temperatureUnitExt <= m_chauffageConsignes ->consigneModeDegCh) {
	    etatModeDegivrageElectric();
         } else {
	     etatModeDegivrageNaturel();
        }
    
        break;
	
	case TEMPO_DEGIVRAGE_V4V:
        
        qDebug() << "TEMPO_DEGIVRAGE_V4V";
    
        if (time(NULL) - departTempoV4VDegElec >= tempoV4VDegElec) {
	    etatDegivrageV4V();
        }

        break;
	
	case TEMPO_DEGIVRAGE_COMPRESSEUR:
        
        qDebug() << "TEMPO_DEGIVRAGE_COMPRESSEUR";
    
        if (time(NULL) - departTempoCompDegElec >= tempoCompDegElec) {
            etatDegivrageCompresseur();
        }

        break;
	
	case CONTROLE_TEMPERATURE_DEGIVRAGE_ELECTRIC:
    
        qDebug() << "CONTROLE_TEMPERATURE_DEGIVRAGE_ELECTRIC";
	
	if (time(NULL) - departTempoControleTemperatureDegivrageElectric >= tempoControleTemperatureDegivrageElectric) {
	    m_chauffageTemperatures ->lireTemperatureEcExt();
	    m_chauffageConsignes ->lireConsignesGainable();
	    if (m_chauffageTemperatures ->temperatureEcExt >= m_chauffageConsignes ->consigneFinDegCh || time(NULL) - departTempoTempDegElec >= tempoTempDegElec) {
		etatControleDegivrageElectric();
	    } else {
		departTempoControleTemperatureDegivrageElectric = time(NULL);
	    }
	}

        break;

        case DEGIVRAGE_NATUREL:
    
        qDebug() << "DEGIVRAGE_NATUREL";
    
        if (time(NULL) - departTempoDegNat >= tempoDegNat) {
            departTempoEgouttageCh = time(NULL);
	    gifDegivrageChauffage = false;
            //compteurEgouttageNat++;
            transitionGainableChauffage = EGOUTTAGE_CHAUFFAGE;
        } else {
            m_chauffageRelais.desactiveTousRelais();
            gifDegivrageChauffage = true;
        }

        break;
	
        case EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "EGOUTTAGE_CHAUFFAGE";
	
	if (time(NULL) - departTempoEgouttageCh >= tempoEgouttageCh) {
	    etatEgouttageChauffage();
        }

        break;

        case FIN_EGOUTTAGE_CHAUFFAGE:
    
        qDebug() << "FIN_EGOUTTAGE_CHAUFFAGE";
    
        if (time(NULL) - departTempoFinEgouttageCh >= tempoFinEgouttageCh) {
            etatMarcheChauffage();
        }

        break;
	
	case ARRET_CHAUFFAGE:
	
	qDebug() << "ARRET_CHAUFFAGE";
	
	etatMarcheChauffage();
	
	break;
    }
}

        /*case EGOUTTAGE_CHAUFFAGE:
    
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

        break;*/

