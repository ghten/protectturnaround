/* 
 * File:   ProtectTurnaround.cpp
 * Author: Javier
 * 
 * Created on 9 de mayo de 2014, 13:16
 */

#include <cstdio>
#include <ctime>
#include <wchar.h>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include "ProtectTurnaround.h"

ProtectTurnaround::ProtectTurnaround() {
}

ProtectTurnaround::ProtectTurnaround(const ProtectTurnaround& orig) {
}

ProtectTurnaround::~ProtectTurnaround() {
}

using namespace std;

//+------------------------------------------------------------------+
//| Verifie the format HH:MM of Begin and End                        |
//|                                                                  |
//+------------------------------------------------------------------+
int ProtectTurnaround::VerifFormat(time_t t1, time_t t2,wchar_t *begin,wchar_t *end, wchar_t *usetime){
   
   if(wcslen(begin) != 5){
      return(1);
   }
   
   if(wcslen(end) != 5){
      return(2);
   }
   
   if(wcschr(begin,L':')==NULL){
      return(1);
   }
   
    if(wcschr(end,L':')==NULL){
      return(2);
   }
   
   //****************************************Begin******************************************************
   this->CalHour(begin);
   if(!(this->hours>=0 && this->hours<=23)){
      return(3);
   }
   
   if(!(this->minutes>=0 && this->minutes<=59)){
      return(4);
   }
   //**********************************************end Begin**********************************************
   
    //****************************************End******************************************************
   this->CalHour(end);
   if(!(this->hours>=0 && this->hours<=23)){
      return(5);
   }
   
   if(!(this->minutes>=0 && this->minutes<=59)){
      return(6);
   }
   //**********************************************end End**********************************************
   
   if(t1>=t2){
       return(7);
   }
   
   if(wcslen(usetime) != 1){
      return(8);
   }
   
   if(wcscmp(usetime,L"Y")!=0 && wcscmp(usetime,L"N")!=0 && wcscmp(usetime,L"n")!=0 && wcscmp(usetime,L"y")!=0){
      return(8);
   }
   return(0);   
}

/****************************************************************************************************
* calculed hour and minutes
*****************************************************************************************************/
void ProtectTurnaround::CalHour(wchar_t *hour){
    char chour[3],cmm[3];
    
    for(int i=0;i <= 5;i++){
        switch(i){
            case 0:
                chour[0]=hour[i];
                break;
            case 1:
                chour[1]=hour[i];
                break;
            case 2:
                chour[2]='\0';
                break;
            case 3:
                cmm[0]=hour[i];
                break;
            case 4:
                cmm[1]=hour[i];
                break;
            case 5:
                cmm[2]='\0';
                break;
        }
    }
    this->hours=atoi(chour);
    this->minutes=atoi(cmm);
} 

//+------------------------------------------------------------------+
//|Check whether the time was the fork                               |
//|                                                                  |
//+------------------------------------------------------------------+
int ProtectTurnaround::TimeBet(time_t currenttime, time_t t1, time_t t2){
       
   //test if hour between begin and end
    if(currenttime >= t1 && currenttime <= t2){
        return(0);
    }else{
        return(1);
    }    
}    

//+------------------------------------------------------------------+
//|Calculeted bars                              |
//|                                                                  |
//+------------------------------------------------------------------+
int ProtectTurnaround::CalcBars(int bars,int cbars){
    int result;
    
    result=cbars;  
    if (cbars>=bars) result=bars;
    return(result);
}

//+------------------------------------------------------------------+
//|Calculeted if buy or sell                                         |
//|                                                                  |
//+------------------------------------------------------------------+
char ProtectTurnaround::Calcul(int bars,int risk,int cbars,double *high,double *low,
        double *close,time_t currenttime,time_t prevalerttime,int delay){
    int K,shift,i,period=60,SSP=9;
    double smin,smax,SsMax,SsMin,price;
    bool uptrend=false,old=false;
    char result='N';
     
    if(bars<=SSP+1){
       return(result);
    } 
    
    K=33-risk;
    
    for (shift = cbars-SSP; shift>=0; shift--){ 
        SsMax=high[shift]; 
        SsMin=low[shift]; 
        
        for (i=shift;i<=shift+SSP-1;i++){
            price=high[i];
            if(SsMax<price) SsMax=price;
                price=low[i];
            if(SsMin>=price)  SsMin=price;
        }
        
        smin = SsMin+(SsMax-SsMin)*K/100; 
        smax = SsMax-(SsMax-SsMin)*K/100; 
        
        if (close[shift]<smin){
            uptrend = false;
	}
	      
	if (close[shift]>smax){
            uptrend = true;
	}
        
        if (uptrend!=old && uptrend==true){
            if (shift==0 && (currenttime - prevalerttime > period*delay)){
                result='B';
            }
        }
        if (uptrend!=old && uptrend==false){
            if (shift==0 && (currenttime - prevalerttime > period*delay)){
                result='S';
            }
        }
        old=uptrend;
    }
    return(result);
}