#ifndef GAINABLE_H
#define GAINABLE_H

#include <ctime>

#include "froid.h"
#include "chauffage.h"
#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "relais.h"
#include "hysteresisvitesses.h"

class Gainable: public QObject
{
    Q_OBJECT
    
public:
    Gainable();
    
    QTimer *m_timerMajGainable;
    
    int m_timerGainable = 1000;
    
    bool gifNettoyageFiltreEnCours = false;
    bool gifNettoyageFiltre = false;
    bool gifArretProgrammeFiltre = false;
    
    bool labelModeFroid = false;
    
    bool departGainable = true;
    
    bool labelModeCanicule = false;
    
    bool gifElectrique = false;
    
    void fonctionsGainable();
    
    void afficheLabelModes();
    
    void afficheGifsNettoyageFiltre();
    
    void afficheGifsVentInterieur();
    void afficheGifsVentExterieur();
    void afficheGifsVentDegivrageFroid();
    
    void afficheGifCompresseur();
    
    void afficheGifDegivrage();
    
    void afficheGifEgouttage();
    
    void arretGainable();
    
public slots:// recevoir
    void onChangeGainableState(bool m_state);
    
signals:
    void majLabel(int m_mode);
    
    void afficheGifsFiltre(int m_gifsFiltre);
    
    void afficheGifsVentInt(int m_gifsVentilationInt);
    void afficheGifsVentExt(int m_gifsVentilationExt);
    void afficheGifsVentDegFr(int m_gifsVentilationDegFr);
    
    void afficheGifComp(int m_gifCompresseur);
    
    void afficheGifDeg(int m_gifDegivrage);
    
    void afficheGifEgout(int m_gifEgouttage);

private:
    Froid m_gainableFroid;
    
    Chauffage m_gainableChauffage;
    
    Consignes *m_gainableConsignes;
    
    Temperatures *m_gainableTemperatures;
    
    Filtre *m_gainableFiltre;
    
    Relais m_gainableRelais;
    
    HysteresisVitesses m_gainableHysteresis;

    unsigned long long tempsNettoyageFiltre = 1820;//1820000; // 21 jours  alerte nettoyage filtre
    unsigned long long tempsArretProgramme = 2679;//2679000; // 1 mois arret programme par manque d'entretien filtre
    
    enum
    {
        MARCHE,
        ETATS_FILTRE,
        ENTRETIEN_FILTRE_EN_COURS,
        ENTRETIEN_OK,
        REMISE_A_ZERO_COMPTEUR_FILTRE,
        MODES,
        FROID,
        CHAUFFAGE,
        CANICULE,
        ARRET,
    } etatsGainable = MARCHE;
};

#endif // GAINABLE_H
