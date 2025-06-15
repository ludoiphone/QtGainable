#ifndef DS18B20_H
#define DS18B20_H

#include "temperatures.h"
#include "consignes.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 128

typedef unsigned char uchar;
typedef unsigned int  uint;

class DS18B20: public QObject
{
	Q_OBJECT
    
public:
    double consigneIntCa;
    double consigneVentIntCa;
    
    float tempExt();
    float tempUnitExt();
    float tempEchangeurExt();
    float tempUnitInt();
    float tempEchangeurInt();
    
public slots:
    void ecritureDs18b20();

private:
    Temperatures *m_ds18b20Temperatures;
    
    Consignes *m_ds18b20Consignes;
    
    QTimer *m_timerSondes;
    int timerSondes = 10000;
    
    double tempExtLue;
    double tempUnitExtLue;
    double tempEchangeurExtLue;
    double tempUnitIntLue;
    double tempEchangeurIntLue;
    
    float temp0;
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    
    int i, j;
    int fd0, fd1, fd2, fd3, fd4;
    int ret;

    char buf[BUFSIZE];
    char tempBuf[5];
    
    void ecritDs18b20();
};

#endif // DS18B20_H
