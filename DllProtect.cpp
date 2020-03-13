/* 
 * File:   ProtectTurnaround.cpp
 * Author: Javier
 * 
 * Created on 9/05/2014, 13:13
 */
#include <cstdio>
#include <ctime>
#include "ProtectTurnaround.h"

/*
 * Function exported
 */
#define	_WINDLL
#include "Turnaround.h"

ProtectTurnaround *pag=0;

int ProtectDll_1(time_t *t, wchar_t *begin, wchar_t *end, wchar_t *usetime, char type){
      
    switch(type){
        case 'I':
            pag=new ProtectTurnaround();
            return(pag->VerifFormat(t[1],t[2],begin,end,usetime));
            break;
            
        case 'T':
            return(pag->TimeBet(t[0],t[1],t[2]));
            break;    
    }
}

int ProtectDll_2(int bars,int cbars){
    return(pag->CalcBars(bars,cbars));
}

void ProtectDll_3(){
    delete pag;
}

char ProtectDll_4(int bars,int risk,int cbars,double *high,double *low,double *close,time_t currenttime,time_t prevalerttime,int delay){
    return(pag->Calcul(bars,risk,cbars,high,low,close,currenttime,prevalerttime,delay));
}