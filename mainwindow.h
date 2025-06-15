#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include "temperatures.h"
#include "ds18b20.h"
#include "gainable.h"
#include "affichecons.h"

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    
public slots:
    void changeLabel(int m_mode);
    
    void affichageGifsNettoyageFiltre(int m_gifsFiltre);
    
    void affichageGifVentInt(int m_gifVentilationInt);
    void affichageGifsVitessesInt(int m_gifsVitessesInt);
    
    void affichageGifVentExt(int m_gifVentilationExt);
    void affichageGifsVitessesExt(int m_gifsVitessesExt);
    
    void affichageGifsVentDegFr(int m_gifsVentilationDegFr);
    
    void affichageGifComp(int m_gifCompresseur);
    
    void affichageGifDegivrage(int m_gifDegivrage);
    void affichageGifElectric(int m_gifElectric);
    
    void affichageGifEgouttage(int m_gifEgouttage);

signals:    
    void changeGainableState(bool m_state);

private:
    Temperatures *m_mainwindowTemperatures;
    
    DS18B20 m_mainwindowDs18b20;
    
    Gainable m_mainwindowGainable;
    
    AfficheCons *m_afficheCons;
    
    QTimer *m_timer1;
    int m_timerTemps = 10000;
    
    QThread *m_threadDs18b20;
    
    QThread *m_threadGainable;
    
    QWidget *m_window;
    
    QLabel *m_label;
    
    QLabel *m_labelFroid;
    QMovie *m_movieFroid;
    QLabel *m_labelChauffage;
    QMovie *m_movieChauffage;
    QLabel *m_labelCanicule;
    QMovie *m_movieCanicule;
    
    QLCDNumber *m_tempExtLue;
    QLCDNumber *m_tempUnitExtLue;
    QLCDNumber *m_tempEcExtLue;
    QLCDNumber *m_tempUnitIntLue;
    QLCDNumber *m_tempEcIntLue;
    
    QLabel *m_labelGifNettoyageFiltre;
    QMovie *m_movieGifNettoyageFiltre;
    
    QLabel *m_labelGifArretProgramme;
    QMovie *m_movieGifArretProgramme;
    
    QLabel *m_labelGifNettoyageEnCours;
    QMovie *m_movieGifNettoyageEnCours;
    
    QLabel *m_labelGifVentInt;
    QMovie *m_movieGifVentInt;
    QLabel *m_labelGifVitesse1Int;
    QMovie *m_movieGifVitesse1Int;
    QLabel *m_labelGifVitesse4Int;
    QMovie *m_movieGifVitesse4Int;
    
    QLabel *m_labelGifVentExt;
    QMovie *m_movieGifVentExt;
    QLabel *m_labelGifVitesse1Ext;
    QMovie *m_movieGifVitesse1Ext;
    QLabel *m_labelGifVitesse2Ext;
    QMovie *m_movieGifVitesse2Ext;
    
    QLabel *m_labelGifFroid;
    QMovie *m_movieGifFroid;
    
    QLabel *m_labelGifChauffage;
    QMovie *m_movieGifChauffage;
    
    QLabel *m_labelGifDegivrage;
    QMovie *m_movieGifDegivrage;
    
    QLabel *m_labelGifEgouttage;
    QMovie *m_movieGifEgouttage;
    
    QLabel *m_labelGifEclaire;
    QMovie *m_movieGifEclaire;

    QGroupBox *m_disp1; //tempExt
    QGroupBox *m_disp2; //tempUnitExt
    QGroupBox *m_disp3; //tempEcExt
    QGroupBox *m_disp4; //tempUnitInt
    QGroupBox *m_disp5; //tempEcInt
    
    QPushButton *m_marche;
    QPushButton *m_consigne;
    QPushButton *m_stop;
    
    void affichageTemperatures();
    
    void afficheConsignes();
    void stopGainable();
    void reStartGainable();
};
#endif // MAINWINDOW_H
