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
    bool gifVentilationExtFroid = false;
    bool gifVentilationDegFroid = false;
    
    bool gifDegivrageFroid = false;
    bool gifEgouttageFroid = false;
    
    bool degivrageFroid = false;
    
    unsigned long long departChronoFiltreFr;
    unsigned long long finChronoFiltreFr;
    unsigned long chronoNettoyageFiltreFr;
    
    void modeFroid();
    
    void arretFroid();
    
    void chauffageFroid();

private:
    Temperatures *m_froidTemperatures;
    
    Consignes *m_froidConsignes;
    
    Filtre *m_froidFiltre;
    
    Relais m_froidRelais;
    
    unsigned short tempoVoletsFr = 10; // 10 secondes
    unsigned long long departTempoVoletsFr;
    
    unsigned short tempoVentilationFr = 15; // 150 secondes (2 min 30 secondes)
    unsigned long long departTempoVentilationFr;
    
    unsigned short tempoV4VFr = 4.5; // 45 secondes
    unsigned long long departTempoV4VFr;

    unsigned short tempoCompresseurFr = 9; // 1 minute 30 secondes
    unsigned long long departTempoCompresseurFr;
    
    unsigned short tempoTempsDegivrageFr = 120; // 20 minutes
    unsigned long long departTempoTempsDegivrageFr;

    unsigned short tempoDegivrageFr = 12; // 2 minutes
    unsigned long long departTempoDegivrageFr;
    
    unsigned short tempoEgouttageFr = 30; // 5 minutes
    unsigned long long departTempoEgouttageFr;
    
    unsigned short tempoFinEgouttageFr = 18; // 3 minutes
    unsigned long long departTempoFinEgouttageFr;
    
    unsigned short tempoFinDegivrageFr = 10; // 10 secondes
    unsigned long long departTempoFinDegivrageFr;
    
    enum
    {
        TEMPO_VOLETS_FROID,
        TEMPO_VENTILATION_FROID,
        TEMPO_V4V_FROID,
        TEMPO_COMPRESSEUR_FROID,
        TEMPO_VENTILATION_DEGIVRAGE_FROID,
        TEMPO_DEGIVRAGE_FROID,
        DEGIVRAGE_FROID,
        EGOUTTAGE_FROID,
        FIN_EGOUTTAGE_FROID,
        //COMMANDE_CANICULE,
        //TEMPO_V4V_CANICULE,
        //TEMPO_COMPRESSEUR_CANICULE,
        //TEMPO_DEGIVRAGE_CANICULE,
    } etatsGainableFroid = TEMPO_VOLETS_FROID;
	
};

#endif //FROID_H
