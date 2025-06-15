#ifndef CANICULE_H
#define CANICULE_H

#include "consignes.h"
#include "temperatures.h"
#include "filtre.h"
#include "relais.h"

class Canicule
{
	
public:
    Canicule();
    
    bool gifCanicule = false;
    
    bool gifVentilationCanicule = false;
    bool gifVentilationIntCanicule = false;
    bool gifVentilationExtCanicule = false;
    
    bool passeEnModeFroidEnCanicule = false;
    
    void modeCanicule();
    void etatArretCanicule();
    
private:
    
    Consignes *m_caniculeConsignes;
    
    Temperatures *m_caniculeTemperatures;
    
    Filtre *m_caniculeFiltre;
    
    Relais m_caniculeRelais;
    
    int tempoVoletsCa = 10; // 10 secondes
    unsigned long long departTempoVoletsCa;
    
    int tempoControleTemperatureCa = 30; // 300 secondes (3 minutes)
    unsigned long long departTempoControleTemperatureCa;
    
    int tempoV4VCa = 4.5; // 45 secondes
    unsigned long long departTempoV4VCa;

    int tempoCompresseurCa = 9; // 1 minute 30 secondes
    unsigned long long departTempoCompresseurCa;
    
    enum
    {
		MARCHE_CANICULE,
		TEMPO_VOLETS_CANICULE,
		CONTROLE_TEMPERATURE_CANICULE,
        TEMPO_V4V_CANICULE,
        TEMPO_COMPRESSEUR_CANICULE,
        CONTROLE_VENTILATION_CANICULE,
        ARRET_CANICULE,
	} transitionGainableCanicule = ARRET_CANICULE;

	void etatMarcheCanicule();
	void etatVoletsCanicule();
	void etatControleTemperatureCanicule();
	void etatDepartCanicule();
	void etatModeCaniculeFroid();
	void etatVentilationsCanicule();
	void etatV4VCanicule();
	void etatCompresseurCanicule();
};

#endif // CANICULE_H
