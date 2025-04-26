#include "gainable.h"

#include <QDebug>

#include "gpioPin.hpp"

#define OFF HIGH
#define ON LOW

const int capteurFiltre = 27;
const int thermostats = 17;

Gainable::Gainable()
{
    qDebug() << "Gainable";
    
    pinMode (capteurFiltre, INPUT_PULLUP);
    pinMode (thermostats, INPUT_PULLUP);
    
    m_gainableConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    //m_gainableParametres ->setAtomicSyncRequired(false);
    
    m_gainableTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_gainableFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
    m_gainableFiltre ->lireChronos();
    m_gainableFroid.chronoNettoyageFiltreFr = m_gainableFiltre ->chronoNettoyageFiltre;
    
    m_timerMajGainable = new QTimer(this);
    m_timerMajGainable ->start(m_timerGainable);
    connect(m_timerMajGainable, &QTimer::timeout, this, &Gainable::fonctionsGainable); // lire les fonctions du programme gainable toute les secondes
}

void Gainable::onChangeGainableState(bool m_state)
{
    departGainable = m_state;
}

void Gainable::fonctionsGainable()
{
    time_t rawtime;
    time ( & rawtime);

    qDebug() << "ChronoNettoyageFiltre" << m_gainableFiltre ->chronoNettoyageFiltre;
    qDebug() << "ChronoNettoyageFoltreFr" << m_gainableFroid.chronoNettoyageFiltreFr;
    qDebug() << ctime ( & rawtime);
    
    afficheLabelModes();
    afficheGifsNettoyageFiltre();
    afficheGifsVentInterieur();
    afficheGifsVentExterieur();
    afficheGifCompresseur();
    afficheGifDegivrage();
    afficheGifEgouttage();
    
    switch (etatsGainable) {
        
        case MARCHE:
        
        qDebug() << "MARCHE";
        
        if (departGainable == true) {
            if (digitalRead (thermostats) == ON) { // si un des thermostats est a 1
                etatsGainable = ETATS_FILTRE;
            } else {
                m_gainableFroid.arretFroid();
                arretGainable();
            }
        } else {
            m_gainableFroid.arretFroid();
            arretGainable();
        }
        
        break;
        
        case ETATS_FILTRE:
        
        qDebug() << "ETATS_FILTRE";
        
        if (digitalRead (capteurFiltre) == ON) {
            gifNettoyageFiltreEnCours = true;
            etatsGainable = ENTRETIEN_FILTRE_EN_COURS;
        } else if (m_gainableFiltre ->chronoNettoyageFiltre >= tempsArretProgramme) {
			
        } else if (m_gainableFiltre ->chronoNettoyageFiltre >= tempsNettoyageFiltre) {
			
        } else {
            m_gainableFiltre ->lireChronos();
            etatsGainable = MODES;
        }
        
        break;
        
        case ENTRETIEN_FILTRE_EN_COURS:
        
        qDebug() << "ENTRETIEN_FILTRE_EN_COURS";
        
        if (digitalRead (capteurFiltre) == OFF) {
            etatsGainable = REMISE_A_ZERO_COMPTEUR_FILTRE;
        } else {
            arretGainable();
            m_gainableFroid.arretFroid();
        }
        
        break;
        
        case ENTRETIEN_OK:
        
        qDebug() << "ENTRETIEN_OK";
        
        etatsGainable = MODES;
        
        break;
        
        case REMISE_A_ZERO_COMPTEUR_FILTRE:
        
        qDebug() << "REMISE_A_ZERO_COMPTEUR_FILTRE";
        
        if (gifNettoyageFiltreEnCours = true) {
            m_gainableFiltre ->chronoNettoyageFiltre = 0;
            m_gainableFiltre ->ecritChronoNettoyageFiltre();
            gifNettoyageFiltreEnCours = false;
            etatsGainable = ENTRETIEN_OK;
        }
        
        break;
        
        case MODES:
        
        qDebug() << "MODES";
        
        m_gainableTemperatures ->lireTemperatureExt();
        m_gainableConsignes ->lireConsignesGainable();
        
        if (m_gainableTemperatures ->temperatureExt < m_gainableConsignes ->consigneEteHiver) { // si la temperature ext(nord moyenne regionnale) est inferieur as 13.5°
            m_gainableChauffage.labelModeChauffage = true; // mode chauffage
            //m_gainableChauffage.modeChauffage();
        } else if (m_gainableTemperatures ->temperatureExt < m_gainableConsignes ->consigneCanicule) { // si la temperature ext(nord) est inferieur as 30°C
            labelModeFroid = true;
            etatsGainable = FROID;
        } else { // si non
            //etatsGainable = COMMANDE_CANICULE; // mode canicule
        }
        
        break;
        
        case FROID:
        
        qDebug() << "FROID";
        
        if (departGainable == false) {
            etatsGainable = MARCHE;
        } else if (digitalRead (thermostats) == OFF) { // si un des thermostats est a 1
            etatsGainable = MARCHE;
        } else {
            m_gainableFroid.modeFroid();
        }
        
        break;
        
        case CHAUFFAGE:
        
        m_gainableChauffage.modeChauffage();
        
        break;
        
        case CANICULE:
        
        break;
        
        case ARRET:
        
        qDebug() << "ARRET";

        //etatsGainable = DEPART;
        
        break;
    }
}

void Gainable::afficheLabelModes()
{
    if (labelModeFroid == true) {
        emit majLabel(0);
    } else if (m_gainableChauffage.labelModeChauffage == true) {
        emit majLabel(1);
    } else if (labelModeCanicule == true) {
        emit majLabel(2);
    } else {   
        emit majLabel(3);
    }
}

void Gainable::afficheGifsNettoyageFiltre()
{
    if (gifArretProgrammeFiltre == true) {
        emit afficheGifsFiltre(0);
    } else if (gifNettoyageFiltreEnCours == true) {
        emit afficheGifsFiltre(1);
    } else if (gifNettoyageFiltre == true) {
        emit afficheGifsFiltre(2);
    } else {
        emit afficheGifsFiltre(3);
    }
}

void Gainable::afficheGifsVentInterieur()
{
    if (m_gainableFroid.gifVentilationFroid == true) {
        emit afficheGifsVentInt(0);// affiche grande vitesse
    } else {
        if (m_gainableFroid.gifVentilationIntFroid == true) {
            m_gainableHysteresis.hysteresisTempVitesseIntFroid();
            if (m_gainableHysteresis.tempVitIntFr == false) {
                emit afficheGifsVentInt(1); // petite vitesse si faux
            }else {
                emit afficheGifsVentInt(0);
            }
        } else if (m_gainableChauffage.gifVentilationIntChauffage == true) {
            m_gainableHysteresis.hysteresisTempVitesseIntChauf();
            if (m_gainableHysteresis.tempVitIntCh == true) {
                emit afficheGifsVentInt(1);
            } else {
                emit afficheGifsVentInt(0);
            }
        } else {
            emit afficheGifsVentInt(2);// efface gif ventillation interieur
        }
    }
}

void Gainable::afficheGifsVentExterieur()
{
    if (m_gainableFroid.gifVentilationExtFroid == true) {
        m_gainableHysteresis.hysteresisTempVitesseExtFroid();
        if (m_gainableHysteresis.tempVitExtFr == false) {
            emit afficheGifsVentExt(0);
        } else {
            emit afficheGifsVentExt(1);
        }
    } else if (m_gainableChauffage.gifVentilationExtChauffage == true) {
        m_gainableHysteresis.hysteresisTempVitesseExtChauf();
        if (m_gainableHysteresis.tempVitExtCh == true) {
            emit afficheGifsVentExt(0);
        } else {
            emit afficheGifsVentExt(1);
        }
    } else {
        emit afficheGifsVentExt(2);
    }
}

void Gainable::afficheGifsVentDegivrageFroid()
{
    if(m_gainableFroid.gifVentilationDegFroid == true) {
        emit afficheGifsVentInt(0);
    } else {
        emit afficheGifsVentInt(1);
    }
}

void Gainable::afficheGifCompresseur()
{
    if (m_gainableFroid.gifFroid == true) {
	emit afficheGifComp(0);
    } else if (m_gainableChauffage.gifChauffage == true) {
	emit afficheGifComp(1);
    } else {
	emit afficheGifComp(2);
    }
}

void Gainable::afficheGifDegivrage()
{
    if (m_gainableFroid.gifDegivrageFroid == true) {
        if (gifElectrique == true) {
            emit afficheGifDeg(1);
        } else {
            emit afficheGifDeg(0);
        }
    } else {
        emit afficheGifDeg(2);
    }
}

void Gainable::afficheGifEgouttage()
{
    if (m_gainableFroid.gifEgouttageFroid == true) {
	emit afficheGifEgout(0);
    } else {
	emit afficheGifEgout(1);
    }
}

void Gainable::arretGainable()
{
    qDebug() << "arretGainable()";
    
    labelModeFroid = false;
    m_gainableFroid.gifFroid = false;
    m_gainableChauffage.labelModeChauffage = false;
    m_gainableFroid.gifVentilationFroid = false;
    m_gainableFroid.gifVentilationIntFroid = false;
    m_gainableFroid.gifVentilationExtFroid = false;
    m_gainableFroid.gifVentilationDegFroid = false;
    m_gainableFroid.gifDegivrageFroid = false;
    m_gainableFroid.gifEgouttageFroid = false;
    m_gainableRelais.desactiveRelaiEteHiver();
    m_gainableRelais.desactiveTousRelais();
}
