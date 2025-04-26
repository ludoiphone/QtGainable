#ifndef TEMPERATURES_H
#define TEMPERATURES_H

#include <QtWidgets>

#include "sondes.h"

class Temperatures: public QSettings
{
    Q_OBJECT

public:
    Temperatures(const QString &nomDuFichier, QSettings::Format format);
    
    double temperatureExt;
    double temperatureUnitExt;
    double temperatureEcExt;
    double temperatureUnitInt;
    double temperatureEcInt;

    void ecritToutesTemperatures();
    
    void ecritTempExtLue();
    void ecritTempUnitExtLue();
    void ecritTempEcExtLue();
    void ecritTempUnitIntLue();
    void ecritTempEcIntLue();
    
    void lireToutesTemperatures();
    
    void lireTemperatureExt();
    void lireTemperatureUniteExt();
    void lireTemperatureEcExt();
    void lireTemperatureUniteInt();
    void lireTemperatureEcInt();

private:
    QMutex m_mutexTemperatures;
};

#endif // PARAMETRES_H
