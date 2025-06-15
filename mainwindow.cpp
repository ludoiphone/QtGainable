#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QWidget (parent)
{
    qDebug() << "Mainwindow";
    
    m_mainwindowTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_threadDs18b20 = new QThread();
    m_mainwindowDs18b20.moveToThread(m_threadDs18b20);
    connect(m_threadDs18b20, &QThread::started, &m_mainwindowDs18b20, &DS18B20::ecritureDs18b20);
    m_threadDs18b20 ->start();

    m_window = new QWidget;
    m_window ->setFixedSize(1920,1080);
    m_window ->setWindowTitle("Gainable");
    adjustSize();
    
    m_label = new QLabel(m_window);
    
    m_labelFroid = new QLabel(m_window);
    m_labelFroid ->setFixedSize(1920,1080);
    m_movieFroid = new QMovie("/home/ludo/Qt/test2/build/gif/refroidissement.gif");
    m_labelFroid ->setMovie(m_movieFroid);
    m_movieFroid ->setSpeed(125);
    
    m_labelChauffage = new QLabel(m_window);
    m_labelChauffage ->setFixedSize(1920,1080);
    m_movieChauffage = new QMovie("/home/ludo/Qt/test2/build/gif/chauffage.gif");
    m_labelChauffage ->setMovie(m_movieChauffage);
    m_movieChauffage ->setSpeed(125);
    
    m_labelCanicule = new QLabel(m_window);
    m_labelCanicule ->setFixedSize(1920,1080);
    m_movieCanicule = new QMovie("/home/ludo/Qt/test2/build/gif/canicule.gif");
    m_labelCanicule ->setMovie(m_movieCanicule);
    m_movieCanicule ->setSpeed(125);
    
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
    m_labelGifNettoyageFiltre = new QLabel(m_window);
    m_labelGifNettoyageFiltre ->setGeometry(20,840,200,200);
    m_movieGifNettoyageFiltre = new QMovie("/home/ludo/Qt/test2/build/gif/nettoyageFiltre.gif");
    m_labelGifNettoyageFiltre ->setMovie(m_movieGifNettoyageFiltre);
    m_labelGifArretProgramme = new QLabel(m_window);
    m_labelGifArretProgramme ->setGeometry(720,300,480,480);
    m_movieGifArretProgramme = new QMovie("/home/ludo/Qt/test2/build/gif/arretProgrammeFiltre.gif");
    m_labelGifArretProgramme ->setMovie(m_movieGifArretProgramme);
    
    m_labelGifVentInt = new QLabel(m_window);
    m_labelGifVentInt ->setGeometry(1105,845,200,200);
    m_movieGifVentInt = new QMovie("/home/ludo/Qt/test2/build/gif/ventilateurInt.gif");
    m_labelGifVentInt ->setMovie(m_movieGifVentInt);
    m_labelGifVitesse1Int = new QLabel(m_window);
    m_labelGifVitesse1Int ->setGeometry(1040,900,60,60);
    m_movieGifVitesse1Int = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse1.gif");
    m_labelGifVitesse1Int ->setMovie(m_movieGifVitesse1Int);
    m_labelGifVitesse4Int = new QLabel(m_window);
    m_labelGifVitesse4Int ->setGeometry(1040,900,60,60);
    m_movieGifVitesse4Int = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse4.gif");
    m_labelGifVitesse4Int ->setMovie(m_movieGifVitesse4Int);
    
    m_labelGifVentExt = new QLabel(m_window);
    m_labelGifVentExt ->setGeometry(910,830,200,200);
    m_movieGifVentExt = new QMovie("/home/ludo/Qt/test2/build/gif/ventilateurExt.gif");
    m_labelGifVentExt ->setMovie(m_movieGifVentExt);
    m_labelGifVitesse1Ext = new QLabel(m_window);
    m_labelGifVitesse1Ext ->setGeometry(860,900,60,60);
    m_movieGifVitesse1Ext = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse1.gif");
    m_labelGifVitesse1Ext ->setMovie(m_movieGifVitesse1Ext);
    m_labelGifVitesse2Ext = new QLabel(m_window);
    m_labelGifVitesse2Ext ->setGeometry(860,900,60,60);
    m_movieGifVitesse2Ext = new QMovie("/home/ludo/Qt/test2/build/gif/vitesse2.gif");
    m_labelGifVitesse2Ext ->setMovie(m_movieGifVitesse2Ext);
    
    m_labelGifFroid = new QLabel(m_window);
    m_labelGifFroid ->setGeometry(1210,845,200,200);
    m_movieGifFroid = new QMovie("/home/ludo/Qt/test2/build/gif/froid.gif");
    m_labelGifFroid ->setMovie(m_movieGifFroid);
    
    m_labelGifChauffage = new QLabel(m_window);
    m_labelGifChauffage ->setGeometry(1220,840,200,200);
    m_movieGifChauffage = new QMovie("/home/ludo/Qt/test2/build/gif/chauffe.gif");
    m_labelGifChauffage ->setMovie(m_movieGifChauffage);
    
    m_labelGifDegivrage = new QLabel(m_window);
    m_labelGifDegivrage ->setGeometry(1220,850,200,200);
    m_movieGifDegivrage = new QMovie("/home/ludo/Qt/test2/build/gif/degivrage.gif");
    m_labelGifDegivrage ->setMovie(m_movieGifDegivrage);
    
    m_labelGifEclaire = new QLabel(m_window);
    m_labelGifEclaire ->setGeometry(1160,830,200,200);
    m_movieGifEclaire = new QMovie("/home/ludo/Qt/test2/build/gif/eclaire.gif");
    m_labelGifEclaire ->setMovie(m_movieGifEclaire);
    
    m_labelGifEgouttage = new QLabel(m_window);
    m_labelGifEgouttage ->setGeometry(1120,820,200,200);
    m_movieGifEgouttage = new QMovie("/home/ludo/Qt/test2/build/gif/egouttage.gif");
    m_labelGifEgouttage ->setMovie(m_movieGifEgouttage);
    
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
    
    m_timer1 = new QTimer(this);
    m_timer1 ->start(m_timerTemps);
    connect(m_timer1, &QTimer::timeout, this, &MainWindow::affichageTemperatures); // mise a jour de la temperature toute les 10 secondes

    connect(this, &MainWindow::changeGainableState, &m_mainwindowGainable, &Gainable::onChangeGainableState);
    
    connect(&m_mainwindowGainable, &Gainable::majLabel, this, &MainWindow::changeLabel);
    changeLabel(0);

    connect(&m_mainwindowGainable, &Gainable::afficheGifsFiltre, this, &MainWindow::affichageGifsNettoyageFiltre);
    affichageGifsNettoyageFiltre(0);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifVentInt, this, &MainWindow::affichageGifVentInt);
    affichageGifVentInt(0);
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVitessesInt, this, &MainWindow::affichageGifsVitessesInt);
    //affichageGifsVitessesInt(0);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifVentExt, this, &MainWindow::affichageGifVentExt);
    affichageGifVentExt(0);
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVitessesExt, this, &MainWindow::affichageGifsVitessesExt);
    affichageGifsVitessesExt(0);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifsVentDegFr, this, &MainWindow::affichageGifsVentDegFr);
    affichageGifsVentDegFr(0);

    connect(&m_mainwindowGainable, &Gainable::afficheGifComp, this, &MainWindow::affichageGifComp);
    affichageGifComp(0);
    
    connect(&m_mainwindowGainable, &Gainable::afficheGifDeg, this, &MainWindow::affichageGifDegivrage);
    affichageGifDegivrage(0);
    connect(&m_mainwindowGainable, &Gainable::afficheGifElectric, this, &MainWindow::affichageGifElectric);
    affichageGifElectric(0);

    connect(&m_mainwindowGainable, &Gainable::afficheGifEgout, this, &MainWindow::affichageGifEgouttage);
    affichageGifEgouttage(0);
    
    connect(m_marche, &QPushButton::clicked, this, &MainWindow::reStartGainable);
    connect(m_consigne, &QPushButton::clicked, this, &MainWindow::afficheConsignes);
    connect(m_stop, &QPushButton::clicked, this, &MainWindow::stopGainable);
    
    m_window->show();
    
    m_threadGainable = new QThread();
    m_mainwindowGainable.moveToThread(m_threadGainable);
    connect(m_threadGainable, &QThread::started, &m_mainwindowGainable, &Gainable::gainable);
    m_threadGainable ->start();
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
        
        m_movieFroid ->stop();
        m_labelFroid ->hide();
        m_movieChauffage ->stop();
        m_labelChauffage ->hide();
        m_movieCanicule ->stop();
        m_labelCanicule ->hide();
        m_label ->setPixmap(QPixmap("/home/ludo/Qt/test2/build/images/abigael.jpg"));
        
        
        break;
 
        case 1:
        
        m_movieChauffage ->stop();
        m_labelChauffage ->hide();
        m_movieCanicule ->stop();
        m_labelCanicule ->hide();
        m_movieFroid ->start();
        m_labelFroid ->show();
        
        break;
        
        case 2:
        
        m_movieFroid ->stop();
        m_labelFroid ->hide();
        m_movieChauffage ->start();
        m_labelChauffage ->show();
        
        break;

        case 3:

        m_movieFroid ->stop();
        m_labelFroid ->hide();
        m_movieCanicule ->start();
        m_labelCanicule ->show();
        
        break;

     }
}

void MainWindow::affichageGifsNettoyageFiltre(int m_gifsFiltre)
{
    switch (m_gifsFiltre) {
        
        case 0: 
        
        m_movieGifNettoyageEnCours ->stop();
        m_labelGifNettoyageEnCours ->hide();
        m_movieGifArretProgramme ->stop();
        m_labelGifArretProgramme ->hide();
        m_movieGifNettoyageFiltre ->stop();
        m_labelGifNettoyageFiltre ->hide();
        
        break;
        
        case 1:
        
        m_movieGifNettoyageFiltre ->start();
        m_labelGifNettoyageFiltre ->show();
        
        break;
        
        case 2:
        
        m_movieGifNettoyageFiltre ->start();
        m_labelGifNettoyageFiltre ->show();
        m_movieGifArretProgramme ->start();
        m_labelGifArretProgramme ->show();
        
        break;
        
        case 3:
        
        m_movieGifNettoyageFiltre ->stop();
        m_labelGifNettoyageFiltre ->hide();
        m_movieGifArretProgramme ->stop();
        m_labelGifArretProgramme ->hide();
        m_movieGifNettoyageEnCours ->start();
        m_labelGifNettoyageEnCours ->show();
        
        break;
    }
}

void MainWindow::affichageGifVentInt(int m_gifVentilationInt)
{
    switch (m_gifVentilationInt) {
        
        case 0:
        
        m_movieGifVentInt ->stop();
        m_labelGifVentInt ->hide();
        
        break;
        
        case 1:
        
        m_movieGifVentInt ->start();
        m_labelGifVentInt ->show();
        
        break;
    }
}

void MainWindow::affichageGifsVitessesInt(int m_gifsVitessesInt)
{
    switch (m_gifsVitessesInt) {
        
        case 0:
        
        m_movieGifVitesse1Int ->stop();
        m_labelGifVitesse1Int ->hide();
        m_movieGifVitesse4Int ->stop();
        m_labelGifVitesse4Int ->hide();
        
        break;
        
        case 1:
        
        m_movieGifVitesse1Int ->start();
        m_labelGifVitesse1Int ->show();
        m_movieGifVitesse4Int ->stop();
        m_labelGifVitesse4Int ->hide();
        
        break;
        
        case 4:
        
        m_movieGifVitesse1Int ->stop();
        m_labelGifVitesse1Int ->hide();
        m_movieGifVitesse4Int ->start();
        m_labelGifVitesse4Int ->show();
        
        break;
    }
}

void MainWindow::affichageGifVentExt(int m_gifVentilationExt)
{
    switch (m_gifVentilationExt) {
        
        case 0:
        
        m_movieGifVentExt ->stop();
        m_labelGifVentExt ->hide();
        
        break;
        
        case 1:
        
        m_movieGifVentExt ->start();
        m_labelGifVentExt ->show();
        
        break;
    }
}

void MainWindow::affichageGifsVitessesExt(int m_gifsVitessesExt)
{
    switch (m_gifsVitessesExt) {
        
        case 0:
        
        m_movieGifVitesse1Ext ->stop();
        m_labelGifVitesse1Ext ->hide();
        m_movieGifVitesse2Ext ->stop();
        m_labelGifVitesse2Ext ->hide();
        
        break;
        
        case 1:
        
        m_movieGifVitesse2Ext ->stop();
        m_labelGifVitesse2Ext ->hide();
        m_movieGifVitesse1Ext ->start();
        m_labelGifVitesse1Ext ->show();
        
        break;
        
        case 2:
        
        m_movieGifVitesse1Ext ->stop();
        m_labelGifVitesse1Ext ->hide();
        m_movieGifVitesse2Ext ->start();
        m_labelGifVitesse2Ext ->show();
        
        break;
    }
}

void MainWindow::affichageGifsVentDegFr(int m_gifsVentilationDegFr)/////////////////////////////////////////////////////////////////////////
{
    switch (m_gifsVentilationDegFr) {
        
        case 0:
        
        m_movieGifVentInt ->stop();
        m_labelGifVentInt ->hide();
        m_movieGifVitesse1Int ->stop();
        m_labelGifVitesse1Int ->hide();
        m_movieGifVitesse4Int ->stop();
        m_labelGifVitesse4Int ->hide();
        
        break;
        
        case 1:
        
        m_labelGifVentExt ->show();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->show();
        
        break;
        
        case 4:
        
        m_labelGifVentExt ->show();
        m_labelGifVitesse1Int ->hide();
        m_labelGifVitesse4Int ->show();
        
        break;
    }
}

void MainWindow::affichageGifComp(int m_gifCompresseur)
{
    switch (m_gifCompresseur) {
        
        case 0:
        
        m_movieGifFroid ->stop();
        m_labelGifFroid ->hide();
        m_movieGifChauffage ->stop();
        m_labelGifChauffage ->hide();
        
        break;
        
        case 1:
        
        m_movieGifFroid ->start();
        m_labelGifFroid ->show();
        
        break;
        
        case 2:
        
        m_movieGifChauffage ->start();
        m_labelGifChauffage ->show();
        
        break;
    }
    
}

void MainWindow::affichageGifDegivrage(int m_gifDegivrage)
{
    switch (m_gifDegivrage) {
        
        case 0:
        
        m_movieGifDegivrage ->stop();
        m_labelGifDegivrage ->hide();
        
        break;
        
        case 1:
        
        m_movieGifDegivrage ->start();
        m_labelGifDegivrage ->show();
        
        break;
    }
        
}

void MainWindow::affichageGifElectric(int m_gifElectric)
{
    switch (m_gifElectric) {
        
        case 0:
        
        m_movieGifEclaire ->stop();
        m_labelGifEclaire ->hide();

        break;
        
        case 1:
        
        m_movieGifEclaire ->start();
        m_labelGifEclaire ->show();
        
        break;
    }
}

void MainWindow::affichageGifEgouttage(int m_gifEgouttage)
{
    switch (m_gifEgouttage) {
        
        case 0:
        
        m_movieGifEgouttage ->stop();
        m_labelGifEgouttage ->hide();
        
        break;
        
        case 1:
        
        m_movieGifEgouttage ->start();
        m_labelGifEgouttage ->show();
        
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
