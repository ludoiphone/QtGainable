#ifndef GAINABLE_H
#define GAINABLE_H

#include <ctime>

#include "froid.h"
#include "chauffage.h"
#include "canicule.h"
#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "vitesses.h"

class Gainable: public QObject
{
    Q_OBJECT
    
public:
    Gainable();
    
    QTimer *m_timerMajGainable;
    int m_timerGainable = 250;
    
    bool gifNettoyageFiltreEnCours = false;
    bool gifNettoyageFiltre = false;
    bool gifArretProgrammeFiltre = false;
    
    bool labelModeFroid = false;
    bool labelModeChauffage = false;
    bool labelModeCanicule = false;
    
    bool departGainable = true;
    
    void fonctionsGainable();
    
    void afficheLabelModes();
    
    void afficheGifsNettoyageFiltre();
    
    void afficheGifsVentInterieur();
    
    void afficheGifsVentExterieur();
    
    void afficheGifsVentDegivrageFroid();
    
    void afficheGifCompresseur();
    
    void afficheGifDegivrage();
    
    void afficheGifEgouttage();
    
public slots:// recevoir
    void gainable();
    
    void onChangeGainableState(bool m_state);
    
signals:
    void majLabel(int m_mode);
    
    void afficheGifsFiltre(int m_gifsFiltre);
    
    void afficheGifVentInt(int m_gifVentilationInt);
    void afficheGifsVitessesInt(int m_gifsVitessesInt);
    
    void afficheGifVentExt(int m_gifVentilationExt);
    void afficheGifsVitessesExt(int m_gifsVitessesExt);
    
    void afficheGifsVentDegFr(int m_gifsVentilationDegFr);
    void afficheGifElectric(int m_gifElectric);
    
    void afficheGifComp(int m_gifCompresseur);
    
    void afficheGifDeg(int m_gifDegivrage);
    
    void afficheGifEgout(int m_gifEgouttage);

private:
    Froid m_gainableFroid;
    
    Chauffage m_gainableChauffage;
    
    Canicule m_gainableCanicule;
    
    Consignes *m_gainableConsignes;
    
    Temperatures *m_gainableTemperatures;
    
    Filtre *m_gainableFiltre;
    
    Vitesses m_gainableVitesses;

    unsigned long tempsNettoyageFiltre = 1820;//1820000; // 21 jours  alerte nettoyage filtre
    unsigned long tempsArretProgramme = 2679;//2679000; // 1 mois arret programme par manque d'entretien filtre
    
    enum
    {
        FILTRE,
        ENTRETIEN_FILTRE_EN_COURS,
        MODES,
        FROID,
        CHAUFFAGE,
        CANICULE,
        ARRET_GAINABLE,
    } transitionGainable = ARRET_GAINABLE;
    
    void etatModes();
    void etatModeFroid();
    void etatModeChauffage();
    void etatModeCanicule();
    void etatFiltre();
    void etatFiltreANettoyer();
    void etatArretProgrammeNettoyageFiltre();
    void etatEntretienFiltreEnCours();
    void etatRemiseAZeroCompteurFiltre();
    void etatArretGainable();
};

#endif // GAINABLE_H
