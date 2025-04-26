#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "consignes.h"
#include "filtre.h"

Consignes *m_initConsignes;
Filtre *m_initFiltre;

int main(int argc, char *argv[])
{
    qDebug() << "main";
    
    QApplication app(argc, argv);
    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor)); // cache pointeur Sourie
    
    m_initConsignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    m_initConsignes ->controleConsignes();
    
    m_initFiltre = new Filtre(QString("settings/filtre.ini"), QSettings::IniFormat);
    m_initFiltre ->controleFiltre();

    MainWindow window;
    
    return app.exec();
}
