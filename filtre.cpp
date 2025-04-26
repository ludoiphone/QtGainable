#include "filtre.h"

Filtre::Filtre(const QString &nomDuFichier, QSettings::Format format): QSettings(nomDuFichier, format)
{
	qDebug() << "Filtre";
}

void Filtre::controleFiltre()
{
    if (this ->childGroups().contains("filtre")) {
        qDebug() << "Fichier Filtre OK";
    } else {
        qDebug() << "Creation Fichier Filtre DEFAUT ";
        ecritChronoNettoyageFiltreDefaut();
    }
}

void Filtre::ecritChronoNettoyageFiltreDefaut()
{
    this ->beginGroup("filtre");
    this ->setValue("ChronoNettoyageFiltre",chronoFiltreDefaut);
    this ->endGroup();
}

void Filtre::ecritChronoNettoyageFiltre()
{
    qDebug() << "ecritChronoNettoyageFiltre()";

    this ->beginGroup("filtre");
    this ->setValue("ChronoNettoyageFiltre", chronoNettoyageFiltre);
    this ->endGroup();
}

void Filtre::lireChronos()
{
    qDebug() << "lireChronosFiltre()";
    
    this ->beginGroup("filtre");
    chronoNettoyageFiltre = this ->value("ChronoNettoyageFiltre",chronoNettoyageFiltre).toLongLong();
    this ->endGroup();
}
