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
    
    m_gainableTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_gainableFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
}

void Gainable::gainable()
{
    m_timerMajGainable = new QTimer(this);
    m_timerMajGainable ->start(m_timerGainable);
    connect(m_timerMajGainable, &QTimer::timeout, this, &Gainable::fonctionsGainable); // lire les fonctions du programme gainable toute les secondes
}

void Gainable::onChangeGainableState(bool m_state)
{
    departGainable = m_state;
}

void Gainable::etatModes()
{
    m_gainableTemperatures ->lireTemperatureExt();
    m_gainableConsignes ->lireConsignesGainable();
    transitionGainable = MODES;
}

void Gainable::etatModeFroid()
{
    labelModeChauffage = false;
    labelModeCanicule = false;
    labelModeFroid = true;
    m_gainableFroid.modeFroid();
    transitionGainable = FROID;
}

void Gainable::etatModeChauffage()
{
    labelModeFroid = false;
    labelModeChauffage = true;
    m_gainableChauffage.modeChauffage();
    transitionGainable = CHAUFFAGE;
}

void Gainable::etatModeCanicule()
{
    labelModeFroid = false;
    labelModeCanicule = true;
    m_gainableCanicule.modeCanicule();
    transitionGainable = CANICULE;
}

void Gainable::etatFiltre()
{
    m_gainableFiltre ->lireChronoFiltre();
    m_gainableFiltre ->chronoNettoyageFiltre;
    qDebug() << "chronoNettoyageFiltre" << m_gainableFiltre ->chronoNettoyageFiltre;
    transitionGainable = FILTRE;
}

void Gainable::etatFiltreANettoyer()
{
     gifNettoyageFiltre = true;
     transitionGainable = MODES;
}

void Gainable::etatArretProgrammeNettoyageFiltre()
{
    gifArretProgrammeFiltre = true;
    etatArretGainable();
    transitionGainable = FILTRE;
}

void Gainable::etatEntretienFiltreEnCours()
{
    gifArretProgrammeFiltre = false;
    gifNettoyageFiltre = false;
    gifNettoyageFiltreEnCours = true;
    etatArretGainable();
    transitionGainable = ENTRETIEN_FILTRE_EN_COURS;
}

void Gainable::etatRemiseAZeroCompteurFiltre()
{
    m_gainableFiltre ->chronoNettoyageFiltre = 0;
    m_gainableFiltre ->ecritChronoNettoyageFiltre();
    gifNettoyageFiltreEnCours = false;
    transitionGainable = FILTRE;
}

void Gainable::etatArretGainable()
{
    transitionGainable = ARRET_GAINABLE;
}

void Gainable::fonctionsGainable()
{   
    time_t rawtime;
    time ( & rawtime);

    qDebug() << ctime ( & rawtime);
    
    qDebug() << "passeEnModeChauffage" << m_gainableFroid.passeEnModeChauffage;
    //qDebug() << "consigneIntCa" << m_gainableCanicule.consigneIntCa;
    
    afficheLabelModes();
    afficheGifsNettoyageFiltre();
    afficheGifsVentInterieur();
    afficheGifsVentExterieur();
    afficheGifCompresseur();
    afficheGifDegivrage();
    afficheGifEgouttage();

    switch (transitionGainable) {
        
        case FILTRE:
        
        qDebug() << "FILTRE";
        
        if (m_gainableFiltre ->chronoNettoyageFiltre >= tempsArretProgramme) {
            etatArretProgrammeNettoyageFiltre();
            if (digitalRead (capteurFiltre) == ON) {
                etatEntretienFiltreEnCours();
            }
        } else {
            if (m_gainableFiltre ->chronoNettoyageFiltre >= tempsNettoyageFiltre) {
                etatFiltreANettoyer();
            }
            etatModes();
        }
        
        break;
        
        case ENTRETIEN_FILTRE_EN_COURS:
        
        qDebug() << "ENTRETIEN_FILTRE_EN_COURS";
        
        if (digitalRead (capteurFiltre) == OFF) {
            etatRemiseAZeroCompteurFiltre();
        }

        break;
        
        case MODES:
        
        qDebug() << "MODES";
        
        if (m_gainableTemperatures ->temperatureExt < m_gainableConsignes ->consigneEteHiver) { // si la temperature ext(nord moyenne regionnale) est inferieur as 13.5°
            etatModeChauffage();
        } else if (m_gainableTemperatures ->temperatureExt < m_gainableConsignes ->consigneCanicule) { // si la temperature ext(nord) est inferieur as 30°C
            etatModeFroid();
        } else {
            etatModeCanicule();
        }
        
        break;
        
        case FROID:
        
        qDebug() << "FROID";
        
        if (digitalRead (capteurFiltre) == ON) {
            etatEntretienFiltreEnCours();
        } else if (departGainable == true && digitalRead (thermostats) == ON) {
            if (m_gainableFroid.passeEnModeChauffage == true) {
                etatModeChauffage();
            } else if (m_gainableFroid.passeEnModeCanicule == true) {
                etatModeCanicule();
            } else {
                etatModeFroid();
            }
        } else {
            etatArretGainable();
        }

        break;
        
        case CHAUFFAGE:
        
        qDebug() << "CHAUFFAGE";
        
        if (digitalRead (capteurFiltre) == ON) {
            etatEntretienFiltreEnCours();
        } else if (departGainable == true && digitalRead (thermostats) == ON) {
            if (m_gainableChauffage.passeEnModeFroidEnChauffage == true) {
                etatModeFroid();
            } else {
                etatModeChauffage();
            }
        } else {
            etatArretGainable();
        }
        
        break;
        
        case CANICULE:
        
        if (digitalRead (capteurFiltre) == ON) {
            etatEntretienFiltreEnCours();
        } else if (departGainable == true && digitalRead (thermostats) == ON) {
            if (m_gainableCanicule.passeEnModeFroidEnCanicule == true) {
                etatModeFroid();
            } else {
                etatModeCanicule();
            }
        } else {
            etatArretGainable();
        }
        
        break;
        
        case ARRET_GAINABLE:

        qDebug() << "ARRET_GAINABLE";
        
        if (digitalRead (capteurFiltre) == ON) {
            etatEntretienFiltreEnCours();
        } else if (departGainable == false || digitalRead (thermostats) == OFF) {
            if (labelModeFroid == true) {
                m_gainableFroid.etatArretFroid();
                labelModeFroid = false;
            } else if (labelModeChauffage == true) {
                m_gainableChauffage.etatArretChauffage();
                labelModeChauffage = false;
            } else {
                if (labelModeCanicule == true) {
                    m_gainableCanicule.etatArretCanicule();
                    labelModeCanicule = false;
                }
            }
        } else {
            etatFiltre();
        }
        
        break;
    }
}

void Gainable::afficheLabelModes()
{
    if (labelModeFroid == true) {
        emit majLabel(1);
    } else if (labelModeChauffage == true) {
        emit majLabel(2);
    } else if (labelModeCanicule == true) {
        emit majLabel(3);
    } else {   
        emit majLabel(0);
    }
}

void Gainable::afficheGifsNettoyageFiltre()
{
    if (gifArretProgrammeFiltre == true) {
        emit afficheGifsFiltre(2);
    } else if (gifNettoyageFiltre == true) {
        emit afficheGifsFiltre(1);
    } else if (gifNettoyageFiltreEnCours == true) {
        emit afficheGifsFiltre(3);
    } else {
        emit afficheGifsFiltre(0);
    }
}

void Gainable::afficheGifsVentInterieur()
{
    if (m_gainableFroid.gifVentilationFroid == true) {
        emit afficheGifVentInt(1);
        emit afficheGifsVitessesInt(4);
    } else if (m_gainableFroid.gifVentilationIntFroid == true) {
        emit afficheGifVentInt(1);
        m_gainableVitesses.vitesseIntFroid();
        if (m_gainableVitesses.tempVitIntFr == true) {
            emit afficheGifsVitessesInt(4);
        } else {
            emit afficheGifsVitessesInt(1);
        }
    } else if (m_gainableChauffage.gifVentilationChauffage == true) {
        emit afficheGifVentInt(1);
        emit afficheGifsVitessesInt(4);
    } else if (m_gainableChauffage.gifVentilationIntChauffage == true) {
        emit afficheGifVentInt(1);
        m_gainableVitesses.vitesseIntChauf();
        if (m_gainableVitesses.tempVitIntCh == true) {
            emit afficheGifsVitessesInt(4);
        } else {
            emit afficheGifsVitessesInt(1);
        }
    } else if (m_gainableCanicule.gifVentilationCanicule == true) {
        emit afficheGifVentInt(1);
        emit afficheGifsVitessesInt(4);
    } else if (m_gainableCanicule.gifVentilationIntCanicule == true) {
        emit afficheGifVentInt(1);
        m_gainableVitesses.vitesseIntCa();
        if (m_gainableVitesses.tempVitIntCa == true) {
            emit afficheGifsVitessesInt(4);
        } else {
            emit afficheGifsVitessesInt(1);
        }
    } else {
        if (m_gainableFroid.passeEnModeChauffage == true || m_gainableFroid.passeEnModeCanicule == true || m_gainableChauffage.passeEnModeFroidEnChauffage == true 
        || m_gainableCanicule.passeEnModeFroidEnCanicule == true) {
            emit afficheGifVentInt(1);
        } else {
            emit afficheGifVentInt(0);// efface gif ventillation interieur
            emit afficheGifsVitessesInt(0); // efface gif vitesses interieur
        }
    }
}

void Gainable::afficheGifsVentExterieur()
{
    if (m_gainableFroid.gifVentilationExtFroid == true || m_gainableCanicule.gifVentilationExtCanicule == true) {
        emit afficheGifVentExt(1);
        m_gainableVitesses.vitesseExtFroid();
        if (m_gainableVitesses.tempVitExtFr == true) {
            emit afficheGifsVitessesExt(2);// grand vitesse
        } else {
            emit afficheGifsVitessesExt(1);// petit vitesse
        }
    } else if (m_gainableChauffage.gifVentilationExtChauffage == true) {
        emit afficheGifVentExt(1);
        m_gainableVitesses.vitesseExtChauf();
        if (m_gainableVitesses.tempVitExtCh == true) {
            emit afficheGifsVitessesExt(2);
        } else {
            emit afficheGifsVitessesExt(1);
        }
    } else {
        emit afficheGifVentExt(0);
        emit afficheGifsVitessesExt(0);
    }
}

void Gainable::afficheGifsVentDegivrageFroid()
{
    if(m_gainableFroid.gifVentilationDegFroid == true) {
        emit afficheGifVentInt(1);
    } else {
        emit afficheGifVentInt(0);
    }
}

void Gainable::afficheGifCompresseur()
{
    if (m_gainableFroid.gifFroid == true) {
	emit afficheGifComp(1);
    } else if (m_gainableChauffage.gifChauffage == true) {
	emit afficheGifComp(2);
    } else {
	emit afficheGifComp(0);
    }
}

void Gainable::afficheGifDegivrage()
{
    if (m_gainableFroid.gifDegivrageFroid == true) {
        emit afficheGifDeg(1);
    } else if ( m_gainableChauffage.gifDegivrageChauffage == true) {
        if (m_gainableChauffage.gifElectriqueChauffage == true) {
            emit afficheGifElectric(1);
        } else {
            emit afficheGifElectric(0);
        }
    } else {
        emit afficheGifDeg(0);
        emit afficheGifElectric(0);
    }
}

void Gainable::afficheGifEgouttage()
{
    if (m_gainableFroid.gifEgouttageFroid == true) {
        emit afficheGifEgout(0);
    } else if (m_gainableChauffage.gifEgouttageChauffage == true) {
        emit afficheGifEgout(1);
    } else {
        emit afficheGifEgout(0);
    }
}
