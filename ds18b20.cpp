#include "ds18b20.h"

float DS18B20::tempExt()
{
    fd0 = open("/sys/bus/w1/devices/28-3ce1e3804835/w1_slave", O_RDONLY);

    if(-1 == fd0){
        perror("open device file error");
        return 1;
    }
     while(1){
        ret = read(fd0, buf, BUFSIZE);
        if(0 == ret){
			break;
        }
        if(-1 == ret){
            if(errno == EINTR){
                continue;
            }
            perror("read()");
            close(fd0);
            return 1;
        }
    }

    for(i=0;i<sizeof(buf);i++){
        if(buf[i] == 't'){
            for(j=0;j<sizeof(tempBuf);j++){
                tempBuf[j] = buf[i+2+j];
            }
        }
    }

    tempExtLue = (float)atoi(tempBuf) / 1000;

    close(fd0);

    return temp0;
}

float DS18B20::tempUnitExt()
{
    fd1 = open("/sys/bus/w1/devices/28-3ce1e3809744/w1_slave", O_RDONLY);

    if(-1 == fd1){
        perror("open device file error");
        return 1;
    }
     while(1){
        ret = read(fd1, buf, BUFSIZE);
        if(0 == ret){
			break;
        }
        if(-1 == ret){
            if(errno == EINTR){
                continue;
            }
            perror("read()");
            close(fd1);
            return 1;
        }
    }

    for(i=0;i<sizeof(buf);i++){
        if(buf[i] == 't'){
            for(j=0;j<sizeof(tempBuf);j++){
                tempBuf[j] = buf[i+2+j];
            }
        }
    }

    tempUnitExtLue = (float)atoi(tempBuf) / 1000;

    close(fd1);

    return temp1;
}

float DS18B20::tempEchangeurExt()
{
    fd2 = open("/sys/bus/w1/devices/28-3ce1e38060ec/w1_slave", O_RDONLY);

    if(-1 == fd2){
        perror("open device file error");
        return 1;
    }
     while(1){
        ret = read(fd2, buf, BUFSIZE);
        if(0 == ret){
			break;
        }
        if(-1 == ret){
            if(errno == EINTR){
                continue;
            }
            perror("read()");
            close(fd2);
            return 1;
        }
    }

    for(i=0;i<sizeof(buf);i++){
        if(buf[i] == 't'){
            for(j=0;j<sizeof(tempBuf);j++){
                tempBuf[j] = buf[i+2+j];
            }
        }
    }

    tempEchangeurExtLue = (float)atoi(tempBuf) / 1000;

    close(fd2);

    return temp2;
}

float DS18B20::tempUnitInt()
{
    fd3 = open("/sys/bus/w1/devices/28-3ce1e3801251/w1_slave", O_RDONLY);

    if(-1 == fd3){
        perror("open device file error");
        return 1;
    }
     while(1){
        ret = read(fd3, buf, BUFSIZE);
        if(0 == ret){
			break;
        }
        if(-1 == ret){
            if(errno == EINTR){
                continue;
            }
            perror("read()");
            close(fd3);
            return 1;
        }
    }

    for(i=0;i<sizeof(buf);i++){
        if(buf[i] == 't'){
            for(j=0;j<sizeof(tempBuf);j++){
                tempBuf[j] = buf[i+2+j];
            }
        }
    }

    tempUnitIntLue = (float)atoi(tempBuf) / 1000;

    close(fd3);

    return temp3;
}

float DS18B20::tempEchangeurInt()
{
    fd4 = open("/sys/bus/w1/devices/28-3ce1e3805e9f/w1_slave", O_RDONLY);

    if(-1 == fd4){
        perror("open device file error");
        return 1;
    }
     while(1){
        ret = read(fd4, buf, BUFSIZE);
        if(0 == ret){
			break;
        }
        if(-1 == ret){
            if(errno == EINTR){
                continue;
            }
            perror("read()");
            close(fd4);
            return 1;
        }
    }

    for(i=0;i<sizeof(buf);i++){
        if(buf[i] == 't'){
            for(j=0;j<sizeof(tempBuf);j++){
                tempBuf[j] = buf[i+2+j];
            }
        }
    }

    tempEchangeurIntLue = (float)atoi(tempBuf) / 1000;

    close(fd4);

    return temp4;
}

void DS18B20::ecritureDs18b20()
{
    m_timerSondes = new QTimer(this);
    m_timerSondes ->start(timerSondes);
    connect(m_timerSondes, &QTimer::timeout, this, &DS18B20::ecritDs18b20);
}

void DS18B20::ecritDs18b20()
{
    m_ds18b20Temperatures = new Temperatures(QString("settings/temperatures.ini"), QSettings::IniFormat);
    m_ds18b20Consignes = new Consignes(QString("settings/consignes.ini"), QSettings::IniFormat);
    
    tempExt();
    tempUnitExt();
    tempEchangeurExt();
    tempUnitInt();
    tempEchangeurInt();
    
    m_ds18b20Temperatures ->temperatureExt = tempExtLue;
    m_ds18b20Temperatures ->temperatureUnitExt = tempUnitExtLue;
    m_ds18b20Temperatures ->temperatureEcExt = tempEchangeurExtLue;
    m_ds18b20Temperatures ->temperatureUnitInt = tempUnitIntLue;
    m_ds18b20Temperatures ->temperatureEcInt = tempEchangeurIntLue;
    
    m_ds18b20Temperatures ->ecritToutesTemperatures();
    
    consigneIntCa = tempExtLue - 6;
    m_ds18b20Consignes ->consigneIntCanicule = consigneIntCa;
    
    consigneVentIntCa = consigneIntCa + 2;
    m_ds18b20Consignes ->consigneVentIntCanicule = consigneVentIntCa;
    
    m_ds18b20Consignes ->ecritConsigneIntCanicule();
    m_ds18b20Consignes ->ecritConsigneVentIntCanicule();
}
