/* 
 * File:   Turnaround.h
 * Author: Javier
 *
 * Created on 9 de mayo de 2014, 13:06
 */

#ifndef TURNAROUND_H
#define	TURNAROUND_H

#ifdef _WINDLL
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT __declspec(dllimport)
#endif // _WINDLL

#ifdef __cplusplus
extern "C"{  
#endif    
    
DLLEXPORT int ProtectDll_1(time_t *t, wchar_t *begin, wchar_t *end, wchar_t *usetime, char type);      
DLLEXPORT int ProtectDll_2(int bars,int cbars); 
DLLEXPORT void ProtectDll_3();
DLLEXPORT char ProtectDll_4(
                            int bars,
                            int risk,
                            int cbars,
                            double *high,
                            double *low,
                            double *close,
                            time_t currenttime,
                            time_t prevalerttime,
                            int delay);

#ifdef __cplusplus
}  
#endif  

#endif	/* TURNAROUND_H */

