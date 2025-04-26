#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QWidget (parent)
{
    qDebug() << "Mainwindow";
    
    m_mainwindowTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);

    m_window = new QWidget;
    m_window ->setFixedSize(1920,1080);
    m_window ->setWindowTitle("Gainable");
    adjustSize();
    
    m_label = new QLabel(m_window);
    
    m_disp1 = new QGroupBox("Temp°C Ext",m_window);
    m_disp1 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp1 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp1 ->setGeometry(200,40,240,120);
    m_tempExtLue = new QLCDNumber(m_disp1);
    m_tempExtLue ->setGeometry(0,35,240,80);

    m_disp2 = new QGroupBox("Temp°C UnitExt",m_window);
    m_disp2 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp2 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp2 ->setGeometry(520,40,240,120);
    m_tempUnitExtLue = new QLCDNumber(m_disp2);
    m_tempUnitExtLue ->setGeometry(0,35,240,80);
    
    m_disp3 = new QGroupBox("Temp°C EcUnitExt",m_window);
    m_disp3 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp3 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp3 ->setGeometry(840,40,240,120);
    m_tempEcExtLue = new QLCDNumber(m_disp3);
    m_tempEcExtLue ->setGeometry(0,35,240,80);

    m_disp4 = new QGroupBox("Temp°C UnitInt",m_window);
    m_disp4 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp4 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp4 ->setGeometry(1160,40,240,120);
    m_tempUnitIntLue = new QLCDNumber(m_disp4);
    m_tempUnitIntLue ->setGeometry(0,35,240,80);
    
    m_disp5 = new QGroupBox("Temp°C EcUnitInt",m_window);
    m_disp5 ->setStyleSheet("QGroupBox:title {color: orangered;}");
    m_disp5 ->setFont(QFont("Times", 18, QFont::Bold));
    m_disp5 ->setGeometry(1480,40,240,120);
    m_tempEcIntLue = new QLCDNumber(m_disp5);
    m_tempEcIntLue ->setGeometry(0,35,240,80);
    
    affichageTemperatures();
    
    m_labelGifNettoyageEnCours = new QLabel(m_window);
    m_labelGifNettoyageEnCours ->setGeometry(720,300,480,480);
    m_movieGifNettoyageEnCours = new QMovie("/home/ludo/Qt/test2/build/gif/nettoyageEnCours.gif");
    m_labelGifNettoyageEnCours ->setMovie(m_movieGifNettoyageEnCours);
    m_movieGifNettoyageEnCours ->start();
    m_labelGifNettoyageFiltre = new QLabel(m_window);
    m_labelGifNettoyageFiltre ->setGeometry(20,840,200,200);
    m_movieGifNettoyageFiltre = new QMovie("/home/ludo/Qt/test2/build/gif/nettoyageFiltre.gif");
    m_labelGifNettoyageFiltre ->setMovie(m_movieGifNettoyageFiltre);
    m_movieGifNettoyageFiltre ->start();
    m_labelGifArretProgramme = new QLabel(m_window);
    m_labelGifArretProgramme ->setGeometry(720,300,480,480);
    m_movieGifArretProgramme = new QMovie("/home/ludo/Qt/test2/build/gif/arretProgrammeFiltre.gif");
    m_labelGifArretProgramme ->setMovie(m_movieGifArretProgramme);
    m_movieGifArretProgramme ->start();
    
    m_labelGifVentInt = new QLabel(m_window);
    m_labelGifVentInt ->setGeometry(1105,845,200,200);
    m_movieGifVentInt = new QMovie("/home/ludo/Qt/test2/build/gif/ventilateurInt.gif");
    m_labelGifVentInt ->setMovie(m_movieGifVentInt);
    m_movieGifVentInt ->start();
    m_labelGifVitesse1Int = new QLabel(m_window);
    m_labelGifVitesse1Int ->setGeometry(1040,900,60,60);
    m_movieGifVitesse1Int = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse1.gif");
    m_labelGifVitesse1Int ->setMovie(m_movieGifVitesse1Int);
    m_movieGifVitesse1Int ->start();
    m_labelGifVitesse4Int = new QLabel(m_window);
    m_labelGifVitesse4Int ->setGeometry(1040,900,60,60);
    m_movieGifVitesse4Int = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse4.gif");
    m_labelGifVitesse4Int ->setMovie(m_movieGifVitesse4Int);
    m_movieGifVitesse4Int ->start();
    
    m_labelGifVentExt = new QLabel(m_window);
    m_labelGifVentExt ->setGeometry(910,830,200,200);
    m_movieGifVentExt = new QMovie("/home/ludo/Qt/test2/build/gif/ventilateurExt.gif");
    m_labelGifVentExt ->setMovie(m_movieGifVentExt);
    m_movieGifVentExt ->start();
    m_labelGifVitesse1Ext = new QLabel(m_window);
    m_labelGifVitesse1Ext ->setGeometry(860,900,60,60);
    m_movieGifVitesse1Ext = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse1.gif");
    m_labelGifVitesse1Ext ->setMovie(m_movieGifVitesse1Ext);
    m_movieGifVitesse1Ext ->start();
    m_labelGifVitesse2Ext = new QLabel(m_window);
    m_labelGifVitesse2Ext ->setGeometry(860,900,60,60);
    m_movieGifVitesse2Ext = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse2.gif");
    m_labelGifVitesse2Ext ->setMovie(m_movieGifVitesse2Ext);
    m_movieGifVitesse2Ext ->start();
    
    m_labelGifFroid = new QLabel(m_window);
    m_labelGifFroid ->setGeometry(1210,845,200,200);
    m_movieGifFroid = new QMovie("/home/ludo/Qt/test2/build/gif/froid.gif");
    m_labelGifFroid ->setMovie(m_movieGifFroid);
    m_movieGifFroid ->start();
    
    m_labelGifChauffage = new QLabel(m_window);
    m_labelGifChauffage ->setGeometry(1220,840,200,200);
    m_movieGifChauffage = new QMovie("/home/ludo/Qt/test2/build/gif/chauffage.gif");
    m_labelGifChauffage ->setMovie(m_movieGifChauffage);
    m_movieGifChauffage ->start();
    
    m_labelGifDegivrage = new QLabel(m_window);
    m_labelGifDegivrage ->setGeometry(1220,850,200,200);
    m_movieGifDegivrage = new QMovie("/home/ludo/Qt/test2/build/gif/degivrage.gif");
    m_labelGifDegivrage ->setMovie(m_movieGifDegivrage);
    m_movieGifDegivrage ->start();
    
    m_labelGifEclaire = new QLabel(m_window);
    m_labelGifEclaire ->setGeometry(1160,830,200,200);
    m_movieGifEclaire = new QMovie("/home/ludo/Qt/test2/build/gif/eclaire.gif");
    m_labelGifEclaire ->setMovie(m_movieGifEclaire);
    m_movieGifEclaire ->start();
    
    m_labelGifEgouttage = new QLabel(m_window);
    m_labelGifEgouttage ->setGeometry(1120,820,200,200);
    m_movieGifEgouttage = new QMovie("/home/ludo/Qt/test2/build/gif/egouttage.gif");
    m_labelGifEgouttage ->setMovie(m_movieGifEgouttage);
    m_movieGifEgouttage ->start();
    
    m_marche = new QPushButton("Démarrage ??",m_window);
    m_marche ->setGeometry(1080,900,240,95);
    m_marche ->setStyleSheet("font-size: 30px;background-color: lime");
    m_marche ->hide();
    
    m_consigne = new QPushButton("Consignes",m_window);
    m_consigne ->setGeometry(1340,900,240,95);
    m_consigne ->setStyleSheet("font-size: 30px;");
    m_consigne ->show();
    
    m_stop = new QPushButton("Stop ??",m_window);
    m_stop ->setGeometry(1600,900,240,95);
    m_stop ->setStyleSheet("font-size: 30px;background-color: red");
    m_stop ->show();
    
    m_mainwindowThreadSondes.start();
    
    m_timer1 = new QTimer(this);
    m_timer1 ->start(m_timerTemps);
    connect(m_timer1, &QTimer::timeout, this, &MainWindow::affichageTemperatures); // affiche temperature toute les 10 secondes

    connect(this, &MainWindow::changeGainableState, &m_mainwindowGainable, &Gainable::onChangeGainableState);
    
    connect(&m_mainwindowGainable, &Gainable::majLabel, this, &MainWindow::changeLabel);
    changeLabel(3);

    connect(&m_mainwindowGainable, &Gainable::afficheGifsFiltre, this, &MainWindow::affichageGifsNettoyageFiltre);
    affichageGifsNettoyageFiltre(3);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVentInt, this, &MainWindow::affichageGifsVentInt);
    affichageGifsVentInt(2);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVentExt, this, &MainWindow::affichageGifsVentExt);
    affichageGifsVentExt(2);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVentDegFr, this, &MainWindow::affichageGifsVentDegFr);
    affichageGifsVentDegFr(1);

    connect(&m_mainwindowGainable, &Gainable::afficheGifComp, this, &MainWindow::affichageGifComp);
    affichageGifComp(2);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifDeg, this, &MainWindow::affichageGifDegivrage);
    affichageGifDegivrage(2);

    connect(&m_mainwindowGainable, &Gainable::afficheGifEgout, this, &MainWindow::affichageGifEgouttage);
    affichageGifEgouttage(1);
    
    m_window->show();

    connect(m_marche, &QPushButton::clicked, this, &MainWindow::reStartGainable);
    connect(m_consigne, &QPushButton::clicked, this, &MainWindow::afficheConsignes);
    connect(m_stop, &QPushButton::clicked, this, &MainWindow::stopGainable);
    
    m_mainwindowGainable.fonctionsGainable();
}

void MainWindow::affichageTemperatures()
{
    m_mainwindowTemperatures ->lireToutesTemperatures();
    
    m_tempExtLue ->display(m_mainwindowTemperatures ->temperatureExt);
    m_tempUnitExtLue ->display(m_mainwindowTemperatures ->temperatureUnitExt);
    m_tempEcExtLue ->display(m_mainwindowTemperatures ->temperatureEcExt);
    m_tempUnitIntLue ->display(m_mainwindowTemperatures ->temperatureUnitInt);
    m_tempEcIntLue ->display(m_mainwindowTemperatures ->temperatureEcInt);
}

void MainWindow::changeLabel(int m_mode)
{
    switch (m_mode) {
        
        case 0:
        
        m_label ->setPixmap(QPixmap("/home/ludo/Qt/test2/build/images/froid.jpg"));
        
        break;
 
        case 1:
        
        m_label ->setPixmap(QPixmap("/home/ludo/Qt/test2/build/images/chauffage.jpg"));
        
        break;
        
        case 2:
        
        m_label ->setPixmap(QPixmap("/home/ludo/Qt/test2/build/images/canicule.jpg"));
        
        break;
 
        default:
        
        m_label ->setPixmap(QPixmap("/home/ludo/Qt/test2/build/images/abigael.jpg"));
        
        break;

     }
}

void MainWindow::affichageGifsNettoyageFiltre(int m_gifsFiltre)
{
    switch (m_gifsFiltre) {
        
        case 0:
        
        m_labelGifArretProgramme ->show();
        m_labelGifNettoyageFiltre ->show();
        
        break;
        
        case 1:
        
        m_labelGifArretProgramme ->hide();
        m_labelGifNettoyageFiltre ->hide();
        m_labelGifNettoyageEnCours ->show();
        
        break;
        
        case 2:
        
        m_labelGifNettoyageFiltre ->show();
        
        break;
        
        default:
        
        m_labelGifNettoyageEnCours ->hide();
        m_labelGifArretProgramme ->hide();
        m_labelGifNettoyageFiltre ->hide();
        
        break;
    }
}

void MainWindow::affichageGifsVentInt(int m_gifsVentilationInt)
{
    switch (m_gifsVentilationInt) {
        
        case 0:
        
        m_labelGifVentInt ->show();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->show();
        
        break;
        
        case 1:
        
        m_labelGifVentInt ->show();
        m_labelGifVitesse1Int ->show();
        m_labelGifVitesse4Int ->hide();
        
        break;
        
        default:
        
        m_labelGifVentInt ->hide();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->hide();
        
        break;
    }
}

void MainWindow::affichageGifsVentExt(int m_gifsVentilationExt)
{
    switch (m_gifsVentilationExt) {
        
        case 0:
        
        m_labelGifVentExt ->show();
        m_labelGifVitesse1Ext ->show();
        m_labelGifVitesse2Ext ->hide();
        
        break;
        
        case 1:
        
        m_labelGifVentExt ->show();
        m_labelGifVitesse1Ext ->hide();
        m_labelGifVitesse2Ext ->show();
        
        break;
        
        default:
        
        m_labelGifVentExt ->hide();
        m_labelGifVitesse1Ext ->hide();
        m_labelGifVitesse2Ext ->hide();
        
        break;
    }
}

void MainWindow::affichageGifsVentDegFr(int m_gifsVentilationDegFr)
{
    switch (m_gifsVentilationDegFr) {
        
        case 0:
        
        m_labelGifVentExt ->show();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->show();
        
        break;
        
        default:
        
        m_labelGifVentInt ->hide();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->hide();
        
        break;
    }
}

void MainWindow::affichageGifComp(int m_gifCompresseur)
{
    switch (m_gifCompresseur) {
        
        case 0:
        
        m_labelGifFroid ->show();
        
        break;
        
        case 1:
        
        m_labelGifChauffage ->show();
        
        break;
        
        default:
        
        m_labelGifFroid ->hide();
        m_labelGifChauffage ->hide();
        
        break;
    }
    
}

void MainWindow::affichageGifDegivrage(int m_gifDegivrage)
{
    switch (m_gifDegivrage) {
        
        case 0:
        
        m_labelGifDegivrage ->show();
        
        break;
        
        case 1:
        
        m_labelGifDegivrage ->show();
        m_labelGifEclaire ->show();
        
        default:
        
        m_labelGifDegivrage ->hide();
        m_labelGifEclaire ->hide();
        
        break;
    }
        
}

void MainWindow::affichageGifEgouttage(int m_gifEgouttage)
{
    switch (m_gifEgouttage) {
        
        case 0:
        
        m_labelGifEgouttage ->show();
        
        break;
        
        default:
        
        m_labelGifEgouttage ->hide();
        
        break;
    }
}

void MainWindow::afficheConsignes()
{
    qDebug() << "afficheConsignes()";
    m_afficheCons = new AfficheCons();
    m_afficheCons ->readCons();
}

void MainWindow::stopGainable()
{
    qDebug() << "stopGainable()";
    m_stop ->hide();
    m_marche ->show();
    emit changeGainableState(false);
}

void MainWindow::reStartGainable()
{
    qDebug() << "restartGainable()";
    m_marche ->hide();
    m_stop ->show();
    emit changeGainableState(true);
}
