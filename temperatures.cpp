#include "temperatures.h"

Temperatures::Temperatures(const QString &nomDuFichier, QSettings::Format format): QSettings(nomDuFichier, format)
{
    qDebug() << "temperatures";
}

void Temperatures::ecritToutesTemperatures()
{
    ecritTempExtLue();
    ecritTempUnitExtLue();
    ecritTempEcExtLue();
    ecritTempUnitIntLue();
    ecritTempEcIntLue();
}

void Temperatures::ecritTempExtLue()
{   
    DS18B20 ds18b20_0 {"28-3ce1e3804835"};
    temperatureExt = ds18b20_0.readTemp();
    qDebug() << "temperatureExtLue = " << temperatureExt;
    
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureExterieurLue", temperatureExt);
    this ->endGroup();
}

void Temperatures::ecritTempUnitExtLue()
{
    DS18B20 ds18b20_1 {"28-3ce1e3809744"};
    temperatureUnitExt = ds18b20_1.readTemp();
    qDebug() << "temperatureUnitExtLue = " << temperatureUnitExt;
    
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureUniteExterieurLue", temperatureUnitExt);
    this ->endGroup();
}

void Temperatures::ecritTempEcExtLue()
{
    DS18B20 ds18b20_2 {"28-3ce1e38060ec"};
    temperatureEcExt = ds18b20_2.readTemp();
    qDebug() << "temperatureEcExtLue = " << temperatureEcExt;
    
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureEchangeurExterieurLue", temperatureEcExt);
    this ->endGroup();
}

void Temperatures::ecritTempUnitIntLue()
{
    DS18B20 ds18b20_3 {"28-3ce1e3801251"};
    temperatureUnitInt = ds18b20_3.readTemp();
    qDebug() << "temperatureUnitIntLue = " << temperatureUnitInt;
    
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureUniteInterieurLue", temperatureUnitInt);
    this ->endGroup();
}

void Temperatures::ecritTempEcIntLue()
{  
    DS18B20 ds18b20_4{"28-3ce1e3805e9f"};
    temperatureEcInt = ds18b20_4.readTemp();
    qDebug() << "temperatureEcIntLue = " << temperatureEcInt;
      
    this ->beginGroup("Temperatures");
    this ->setValue("TemperatureEchangeurInterieurLue", temperatureEcInt);
    this ->endGroup();
}

void Temperatures::lireToutesTemperatures()
{
    lireTemperatureExt();
    lireTemperatureUniteExt();
    lireTemperatureEcExt();
    lireTemperatureUniteInt();
    lireTemperatureEcInt();
}

void Temperatures::lireTemperatureExt()
{
    qDebug() << "lireTemperaturesExt()";
    
    this ->beginGroup("Temperatures");
    temperatureExt = this ->value("TemperatureExterieurLue").toDouble();
    this ->endGroup();
}

void Temperatures::lireTemperatureUniteExt()
{
    qDebug() << "lireTemperatureUniteExt()";
	
    this ->beginGroup("Temperatures");
    temperatureUnitExt = this ->value("TemperatureUniteExterieurLue").toDouble();
    this ->endGroup();
}

void Temperatures::lireTemperatureEcExt()
{
    qDebug() << "lireTemperatureEcExt()";
	
    this ->beginGroup("Temperatures");
    temperatureEcExt = this ->value("TemperatureEchangeurExterieurLue").toDouble();
    this ->endGroup();
}

void Temperatures::lireTemperatureUniteInt()
{
    qDebug() << "lireTemperatureUniteInt()";
	
    this ->beginGroup("Temperatures");
    temperatureUnitInt = this ->value("TemperatureUniteInterieurLue").toDouble();
    this ->endGroup();
}

void Temperatures::lireTemperatureEcInt()
{
    qDebug() << "lireTemperatureEcInt()";
	
    this ->beginGroup("Temperatures");
    temperatureEcInt = this ->value("TemperatureEchangeurInterieurLue").toDouble();
    this ->endGroup();
}
