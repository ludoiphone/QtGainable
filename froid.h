#ifndef FROID_H
#define FROID_H

#include <ctime>

#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "relais.h"

class Froid
{

public:
    Froid();

    bool gifFroid = false;

    bool gifVentilationFroid = false;
    bool gifVentilationIntFroid = false;
    bool gifsVitessesIntFroid = false;
    bool gifVentilationExtFroid = false;
    bool gifVentilationDegFroid = false;
    
    bool gifDegivrageFroid = false;
    bool gifEgouttageFroid = false;
    
    bool degivrageFroid = false;
    
    bool passeEnModeChauffage = false;
    bool passeEnModeCanicule = false;
    
    void modeFroid();
    void etatArretFroid();

private:
    Temperatures *m_froidTemperatures;
    
    Consignes *m_froidConsignes;
    
    Filtre *m_froidFiltre;
    
    Relais m_froidRelais;
    
    int tempoVoletsFr = 10; // 10 secondes
    unsigned long long departTempoVoletsFr;
    
    int tempoControleTemperatureFr = 30; // 300 secondes (5 minutes)
    unsigned long long departTempoControleTemperatureFr;
    
    int tempoV4VFr = 4.5; // 45 secondes
    unsigned long long departTempoV4VFr;

    int tempoCompresseurFr = 9; // 1 minute 30 secondes
    unsigned long long departTempoCompresseurFr;
    
    int tempoDegivrageFr = 12; // 2 minutes
    unsigned long long departTempoDegivrageFr;
    
    int tempoControleDegivrageFr = 120; // 20 minutes
    unsigned long long departTempoControleDegivrageFr;
    
    int tempoEgouttageFr = 30; // 5 minutes
    unsigned long long departTempoEgouttageFr;
    
    int tempoFinEgouttageFr = 10; // 1 minutes
    unsigned long long departTempoFinEgouttageFr;
    
    enum
    {
        MARCHE_FROID,
        TEMPO_VOLETS_FROID,
        TEMPO_CONTROLE_TEMPERATURE_FROID,
        TEMPO_V4V_FROID,
        TEMPO_COMPRESSEUR_FROID,
        TEMPO_CONTROLE_TEMPERATURE_DEGIVRAGE_FROID,
        CONTROLE_DEGIVRAGE_FROID,
        FIN_DEGIVRAGE_FROID,
        TEMPO_EGOUTTAGE_FROID,
        TEMPO_FIN_EGOUTTAGE_FROID,
        ARRET_FROID,
    } transitionGainableFroid = ARRET_FROID;
    
    void tempoVolets();
	
    void etatMarcheFroid();
    void etatVoletsFroid();
    void etatControleTemperatureFroid();
    void etatDepartFroid();
    void etatModeFroidChauffage();
    void etatModeFroidCanicule();
    void etatVentilationsFroid();
    void etatV4VFroid();
    void etatCompresseurFroid();
    void etatControleDegivrageFroid();
    void etatControleTemperatureDegivrageFroid();
    void etatFinDegivrageFroid();
    void etatEgouttageFroid();
    void etatFinEgouttageFroid();
};

#endif //FROID_H
