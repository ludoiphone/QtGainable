#include "threadsondes.h"

#include <QDebug>

ThreadSondes::ThreadSondes()
{
    qDebug() << "ThreadSondes";
    
    m_threadSondesTemperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    
    m_timerEcritTemperatures = new QTimer(this);
    m_timerEcritTemperatures ->start(timerEcrit);
    connect(m_timerEcritTemperatures, &QTimer::timeout, this, &ThreadSondes::ecritToutesTemperaturesLue);
}

void ThreadSondes::ecritToutesTemperaturesLue()
{
	qDebug() << "ecritTemperatures()";
    
    m_threadSondesTemperatures ->ecritToutesTemperatures();
}

void ThreadSondes::run()
{
	qDebug() << "run()";
	/*while(1) { 
		m_threadSondesTemperatures ->ecritToutesTemperatures();
		sleep(15);
	}*/
}
