#ifndef FILTRE_H
#define FILTRE_H

#include <QtWidgets>

class Filtre: public QSettings
{
    Q_OBJECT
    
public:
    Filtre(const QString &nomDuFichier, QSettings::Format format);
    
    unsigned long long chronoNettoyageFiltre;
    
    void controleFiltre();
    
    void ecritChronoNettoyageFiltre();
    
    void lireChronos();

private:
    unsigned long long chronoFiltreDefaut = 0;
    
    void ecritChronoNettoyageFiltreDefaut();

};

#endif // FILTRE_H
