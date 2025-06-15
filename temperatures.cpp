#include "temperatures.h"

Temperatures::Temperatures(const QString &nomDuFichier, QSettings::Format format): QSettings(nomDuFichier, format)
{
    qDebug() << "temperatures";
}

void Temperatures::ecritTempExtLue()
{   
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureExterieurLue", temperatureExt);
    this ->endGroup();
}

void Temperatures::ecritTempUnitExtLue()
{
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureUniteExterieurLue", temperatureUnitExt);
    this ->endGroup();
}

void Temperatures::ecritTempEcExtLue()
{
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureEchangeurExterieurLue", temperatureEcExt);
    this ->endGroup();
}

void Temperatures::ecritTempUnitIntLue()
{
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureUniteInterieurLue", temperatureUnitInt);
    this ->endGroup();
}

void Temperatures::ecritTempEcIntLue()
{    
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureEchangeurInterieurLue", temperatureEcInt);
    this ->endGroup();
}

void Temperatures::lireTemperatureExt()
{
    m_mutexTemperatures.lock();
    
    qDebug() << "lireTemperaturesExt()";
    
    this ->beginGroup("Temperatures");
    temperatureExt = this ->value("TemperatureExterieurLue").toDouble();
    this ->endGroup();
    
    m_mutexTemperatures.unlock();
}

void Temperatures::lireTemperatureUniteExt()
{   
    m_mutexTemperatures.lock();
     
    qDebug() << "lireTemperatureUniteExt()";
	
    this ->beginGroup("Temperatures");
    temperatureUnitExt = this ->value("TemperatureUniteExterieurLue").toDouble();
    this ->endGroup();
    
    m_mutexTemperatures.unlock();
}

void Temperatures::lireTemperatureEcExt()
{    
    m_mutexTemperatures.lock();
    
    qDebug() << "lireTemperatureEcExt()";
	
    this ->beginGroup("Temperatures");
    temperatureEcExt = this ->value("TemperatureEchangeurExterieurLue").toDouble();
    this ->endGroup();
    
    m_mutexTemperatures.unlock();
}

void Temperatures::lireTemperatureUniteInt()
{
    m_mutexTemperatures.lock();
    
    qDebug() << "lireTemperatureUniteInt()";
	
    this ->beginGroup("Temperatures");
    temperatureUnitInt = this ->value("TemperatureUniteInterieurLue").toDouble();
    this ->endGroup();
    
    m_mutexTemperatures.unlock();
}

void Temperatures::lireTemperatureEcInt()
{
    m_mutexTemperatures.lock();
    
    qDebug() << "lireTemperatureEcInt()";
	
    this ->beginGroup("Temperatures");
    temperatureEcInt = this ->value("TemperatureEchangeurInterieurLue").toDouble();
    this ->endGroup();
    
    m_mutexTemperatures.unlock();
}
