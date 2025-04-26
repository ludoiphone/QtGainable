#ifndef CHAUFFAGE_H
#define CHAUFFAGE_H

#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "relais.h"

class Chauffage
{

public:
    Chauffage();
    
    bool labelModeChauffage = false;
    
    bool gifChauffage = false;
    
    bool gifVentilationChauffage = false;
    bool gifVentilationIntChauffage = false;
    bool gifVentilationExtChauffage = false;
    bool gifVentilationDegChauffage = false;
    
    bool gifDegivrageChauffage = false;
    bool gifElectriqueChauffage = false;
    bool gifEgouttageChauffage = false;
    
    bool degivrageChauffage = false;
    
    unsigned long long departChronoFiltreCh;
    unsigned long long finChronoFiltreCh;
    
    void modeChauffage();
    
    void arretChauffage();
    
    void froidChauffage();


private:
    Temperatures *m_chauffageTemperatures;
    
    Consignes *m_chauffageConsignes;
    
    Filtre *m_chauffageFiltre;
    
    Relais m_chauffageRelais;
    
    unsigned short tempoVoletsCh = 10; // 10 secondes
    unsigned long long departTempoVoletsCh;
    
    unsigned short tempoVentilationCh = 15; // 150 secondes (2 min 30 secondes)
    unsigned long long departTempoVentilationCh;
    
    unsigned short tempoCompCh = 9; // 1 minute 30 secondes
    unsigned long long departTempoCompCh;
    
    unsigned short tempoTempDegCh = 12; // 2 minutes
    unsigned long long departTempoTempDegCh;
    
    unsigned short tempoCompDegElec = 6.0; // 1 minutes
    unsigned long long departTempoCompDegElec;
    
    unsigned short tempoV4VDegElec = 6.0; // 1 minutes
    unsigned long long departTempoV4VDegElec;
    
    unsigned short tempoTempDegElec = 30; // 5 minutes
    unsigned long long departTempoTempDegElec;
    
    unsigned short tempoDegCh = 270; // 45 minutes
    unsigned long long departTempoDegCh;
    
    unsigned short tempoDegNat = 60; // 10 minutes
    unsigned long long departTempoDegNat;
    
    unsigned short tempoEgouttageCh = 30; // 5 minutes
    unsigned long long departTempoEgouttageCh;
    
    unsigned short tempoFinEgouttageCh = 18; // 3 minutes
    unsigned long long departTempoFinEgouttageCh;
    
    enum
    {
        DEPART_CHAUFFAGE,
		COMMANDE_CHAUFFAGE,
        TEMPO_COMPRESSEUR_CHAUFFAGE,
        TEMPO_DEGIVRAGE,
        MODE_DEGIVRAGE,
        DEGIVRAGE_NATUREL,
        EGOUTTAGE_NATUREL,
        FIN_EGOUTTAGE_NATUREL,
        TEMPO_DEG_V4V,
        TEMPO_DEG_COMPRESSEUR,
        DEGIVRAGE_ELECTRIC,
        EGOUTTAGE_CHAUFFAGE,
        FIN_EGOUTTAGE_CHAUFFAGE,
	} etatsGainableChauffage = DEPART_CHAUFFAGE;
	
};

#endif //CHAUFFAGE_H
