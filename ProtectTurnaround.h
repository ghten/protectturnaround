/* 
 * File:   ProtectTurnaround.h
 * Author: Javier
 *
 * Created on 9 de mayo de 2014, 13:16
 */

#ifndef PROTECTTURNAROUND_H
#define	PROTECTTURNAROUND_H

class ProtectTurnaround {
public:
    ProtectTurnaround();
    ProtectTurnaround(const ProtectTurnaround& orig);
    virtual ~ProtectTurnaround();
    int VerifFormat(time_t t1, time_t t2,wchar_t *begin,wchar_t *end, wchar_t *usetime);
    int TimeBet(time_t currenttime, time_t t1, time_t t2);
    int CalcBars(int bars,int cbars);
    char Calcul(int bars,int risk,int cbars,double *high,double *low,double *close,time_t currenttime,time_t prevalerttime,int delay);
private:
    int hours,minutes;
    void CalHour(wchar_t *hour);
};

#endif	/* PROTECTTURNAROUND_H */

