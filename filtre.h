#ifndef FILTRE_H
#define FILTRE_H

#include <QtWidgets>

class Filtre: public QSettings
{
    Q_OBJECT
    
public:
    Filtre(const QString &nomDuFichier, QSettings::Format format);
    
    unsigned long long chronoNettoyageFiltre;
    unsigned long long departChronoFiltre;
    unsigned long long finChronoFiltre;
        
    void controleFiltre();
    
    void ecritChronoNettoyageFiltre();
    
    void lireChronoFiltre();

private:
    int chronoFiltreDefaut = 0;
    
    void ecritChronoNettoyageFiltreDefaut();
    
    QMutex m_mutexFiltre;

};

#endif // FILTRE_H
