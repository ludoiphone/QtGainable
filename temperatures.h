#ifndef TEMPERATURES_H
#define TEMPERATURES_H

#include <QtWidgets>

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

    void ecritTempExtLue();
    void ecritTempUnitExtLue();
    void ecritTempEcExtLue();
    void ecritTempUnitIntLue();
    void ecritTempEcIntLue();
    
    void ecritToutesTemperatures()
    {
        m_mutexTemperatures.lock();
        
        ecritTempExtLue();
        ecritTempUnitExtLue();
        ecritTempEcExtLue();
        ecritTempUnitIntLue();
        ecritTempEcIntLue();
        
        m_mutexTemperatures.unlock();
    };
    
    void lireTemperatureExt();
    void lireTemperatureUniteExt();
    void lireTemperatureEcExt();
    void lireTemperatureUniteInt();
    void lireTemperatureEcInt();
    
    void lireToutesTemperatures()
    {
        lireTemperatureExt();
        lireTemperatureUniteExt();
        lireTemperatureEcExt();
        lireTemperatureUniteInt();
        lireTemperatureEcInt();
    };

private:
    QMutex m_mutexTemperatures;
};

#endif // PARAMETRES_H
