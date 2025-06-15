#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H

#include <ctime>

#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "relais.h"

class Chauffage
{

public:
    Chauffage();
    
    bool gifChauffage = false;
    
    bool gifVentilationChauffage = false;
    bool gifVentilationIntChauffage = false;
    bool gifVentilationExtChauffage = false;
    bool gifVentilationDegChauffage = false;
    
    bool gifDegivrageChauffage = false;
    bool gifElectriqueChauffage = false;
    bool gifEgouttageChauffage = false;
    
    bool degivrageChauffage = false;
    
    bool passeEnModeFroidEnChauffage = false;
    
    void modeChauffage();
    
    void etatArretChauffage();

private:
    Temperatures *m_chauffageTemperatures;
    
    Consignes *m_chauffageConsignes;
    
    Filtre *m_chauffageFiltre;
    
    Relais m_chauffageRelais;
    
    
    
    int tempoVoletsCh = 10; // 10 secondes
    unsigned long long departTempoVoletsCh;
    
    int tempoControleTemperatureCh = 30; // 300 secondes (5 minutes)
    unsigned long long departTempoControleTemperatureCh;
    
    int tempoCompCh = 9; // 1 minute 30 secondes
    unsigned long long departTempoCompCh;
    
    int tempoControleTemperatureVentilationCh = 5; // 5 secondes
    unsigned long long departTempoControleTemperatureVentilationCh;
    
    int tempoTempDegCh = 12; // 2 minutes
    unsigned long long departTempoTempDegCh;
    
    int tempoCompDegElec = 60; // 1 minutes
    unsigned long long departTempoCompDegElec;
    
    int tempoV4VDegElec = 60; // 1 minutes
    unsigned long long departTempoV4VDegElec;
    
    int tempoTempDegElec = 30; // 5 minutes
    unsigned long long departTempoTempDegElec;
    
    int tempoDegCh = 240; // 40 minutes
    unsigned long long departTempoDegCh;
    
    int tempoControleTemperatureDegivrageElectric = 5; // 5 secondes
    unsigned long long departTempoControleTemperatureDegivrageElectric;
    
    int tempoDegNat = 60; // 10 minutes
    unsigned long long departTempoDegNat;
    
    int tempoEgouttageCh = 30; // 5 minutes
    unsigned long long departTempoEgouttageCh;
    
    int tempoFinEgouttageCh = 18; // 3 minutes
    unsigned long long departTempoFinEgouttageCh;
    
    enum
    {
        MARCHE_CHAUFFAGE,
        TEMPO_VOLETS_CHAUFFAGE,
        CONTROLE_TEMPERATURE_CHAUFFAGE,
        TEMPO_COMPRESSEUR_CHAUFFAGE,
        CONTROLE_TEMPERATURE_VENTILATION_INTERIEUR,
        TEMPO_DEGIVRAGE_CHAUFFAGE,
        MODE_DEGIVRAGE_CHAUFFAGE,
        TEMPO_DEGIVRAGE_V4V,
        TEMPO_DEGIVRAGE_COMPRESSEUR,
        CONTROLE_TEMPERATURE_DEGIVRAGE_ELECTRIC,
        DEGIVRAGE_NATUREL,
        EGOUTTAGE_CHAUFFAGE,
        FIN_EGOUTTAGE_CHAUFFAGE,
        ARRET_CHAUFFAGE,
	} transitionGainableChauffage = ARRET_CHAUFFAGE;
	
    void etatMarcheChauffage();
    void etatVoletsChauffage();
    void etatControleTemperatureChauffage();
    void etatModeChauffageFroid();
    void etatDepartChauffage();
    void etatVentilationsExterieurChauffage();
    void etatCompresseurChauffage();
    void etatControleTemperatureVentilationChauffage();
    void etatVentilationsChauffage();
    void etatDegivrageChauffage();
    void etatModeDegivrageElectric();
    void etatModeDegivrageNaturel();
    void etatDegivrageV4V();
    void etatDegivrageCompresseur();
    void etatControleDegivrageElectric();
    void etatEgouttageChauffage();
    void etatFinEgouttageChauffage();
};

#endif //CHAUFFAGE_H
