/*
 * Fuzzy.c
 *
 *  Created on: 2021ƒÍ6‘¬15»’
 *      Author: wanghuitong~computer
 */
#include "Init.h"
#include "Fuzzy.h"
float fuzzy_kp = 0.0;   //ƒ£∫˝À„µ√µƒkp÷µ
float fuzzy_kd = 0.0;   //ƒ£∫˝À„µ√µƒkd÷µ
/*
 *
 *@brief      ƒ£∫˝PDøÿ÷∆
 *
 *
*/
float E_SBUF=0,EC_SBUF=0;
float ABS(float a)
{
    return a<0?-a:a;
    }

void PD_Fuzzy(float position , float position_error)
{
    int fe = 0,fec = 0;// ‰»ÎµΩƒ£∫˝¿Ôµƒ∆´≤Ó
    int pe = 0,pec = 0;// ‰»ÎµΩƒ£∫˝¿Ôµƒ∆´≤Ó±‰ªØ¡ø
    int num=0;
    float eRule[7]  = {0,30,49,80,100,149,180};//∆´≤Óµƒ∑÷∂Œµ„
    float ecRule[7] = {0,15,20,22,24,26,30};//∆´≤Ó±‰ªØ¡øµƒ∑÷∂Œµ„

    float Rule_kp[7]= {9.2,9.6,10,10.1,10.2,10.3,10.4};//kp¡• Ù∫Ø ˝÷––ƒ÷µ
    float Rule_kd[7]= {10,10.1,10.2,10.3,10.4,10.5,10.6};//kd¡• Ù∫Ø ˝÷––ƒ÷µ
//    float Rule_kp[7]= {10.2,10.6,10.8,11,11.2,11.4,11.6};//kp¡• Ù∫Ø ˝÷––ƒ÷µ//3300
//    float Rule_kd[7]= {5,5.1,5.2,5.3,5.4,5.5,5.6};//kd¡• Ù∫Ø ˝÷––ƒ÷µ
    float eFuzzy[2] = {0.0,0.0};//∆´≤Ó¡• Ù∂»
    float ecFuzzy[2]= {0.0, 0.0};//∆´≤Ó±‰ªØ¡• Ù∂»
    float U1Fuzzy_kp[7]={0,0,0,0,0,0,0};
    float U1Fuzzy_kd[7]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    int rule_kp[7][7]=
    {
//±»¿˝œÓ£¨∏˙ÀÊ∆´≤Óµƒ±‰ªØ∂¯±‰ªØ£¨ø…“‘∏ƒ±‰œµÕ≥µƒœÏ”¶ÀŸ∂»£¨¥”ø™ª∑∂‘ ˝∑˘∆µÃÿ–‘∑÷Œˆ£¨‘ˆ¥ÛKPº¥‘ˆ¥Û¡ÀΩÿ÷π∆µ¬
//  ec 0 1 2 3 4 5 6  //e
      {0,0,1,1,1,2,2},//0    3,2,2,1,1,1,0
      {0,1,1,1,2,3,3},//1    2,2,1,1,1,0,0
      {1,1,2,2,3,3,4},//2    2,2,1,1,1,0,0
      {1,1,2,3,3,4,4},//3    4,3,2,1,1,1,0
      {1,2,2,3,4,4,4},//4
      {2,3,4,4,5,5,5},//5
      {3,3,4,5,5,6,6} //6
    };


//      {2,2,1,1,1,0,0},//0    3,2,2,1,1,1,0
//      {3,3,2,1,1,1,0},//1    2,2,1,1,1,0,0
//      {4,3,3,2,2,1,1},//2    2,2,1,1,1,0,0
//      {4,4,3,3,2,1,1},//3    4,3,2,1,1,1,0
//      {4,4,4,3,2,2,1},//4
//      {5,5,5,4,4,3,2},//5
//      {6,6,5,5,4,3,3} //6




    int rule_kd[7][7]=
    {
//Œ¢∑÷œÓœ‡µ±”⁄◊Ëƒ·£¨ø…“‘ π’µ¥øÏÀŸÀ•ºı£¨±‰µ√Œ»∂®£¨¥”∆µ”Ú∑÷ŒˆΩ«∂»Ω≤£¨‘ˆ¥ÛKDº¥‘ˆº”¡Àœ‡Œª‘£¡ø
//  ec 0 1 2 3 4 5 6  //e
      {3,3,4,5,5,6,6},//0
      {3,3,4,4,5,5,5},//1
      {2,3,3,4,5,5,5},//2
      {1,2,2,3,3,4,5},//3
      {1,1,2,2,3,3,3},//4
      {0,1,1,1,2,2,3},//5
      {0,0,1,1,1,2,2} //6
    };
//»∑∂® ‰»Î¡ø

    fe  = (int)(ABS(position)*10);
    fec = (int)(ABS(position_error)*100);
//≥ı º«Â¡„
    fuzzy_kp = 0.0;
    fuzzy_kd = 0.0;
     //…œŒªª˙¥Ú”°±‰¡ø
//  E_SBUF = fe;
//  EC_SBUF= fec;

//»∑∂®kpµƒ¡• Ù∂»
    if(fe < eRule[0])
    {
        eFuzzy[0] =1.0;
        pe= 0;
    }
    else if(fe < eRule[1])
    {
        eFuzzy[0] = (eRule[1]-fe)/(eRule[1]-eRule[0]);
        pe = 0;
    }
    else if(fe < eRule[2])
    {
        eFuzzy[0] = (eRule[2] -fe)/(eRule[2]-eRule[1]);
        pe =1;
    }
    else if(fe < eRule[3])
    {
        eFuzzy[0] = (eRule[3] -fe)/(eRule[3]-eRule[2]);
        pe =2;
    }
    else if(fe < eRule[4])
    {
        eFuzzy[0] = (eRule[4]-fe)/(eRule[4]-eRule[3]);
        pe=3;
    }
    else if(fe < eRule[5])
    {
        eFuzzy[0] = (eRule[5]-fe)/(eRule[5]-eRule[4]);
        pe=4;
    }
    else if(fe < eRule[6])
    {
        eFuzzy[0] = (eRule[6]-fe)/(eRule[6]-eRule[5]);
        pe=5;
    }
    else
    {
        eFuzzy[0] =1.0;
        pe=6;
    }
    eFuzzy[1] = 1.0 - eFuzzy[0];
//»∑∂®kd¡• Ù∂»
    if(fec <= ecRule[0])
    {
        ecFuzzy[0] =1.0;
        pec = 0;
    }
    else if(fec < ecRule[1])
    {
        ecFuzzy[0] = (ecRule[1] - fec)/(ecRule[1]-ecRule[0]);
        pec = 0 ;
    }
    else if(fec < ecRule[2])
    {
        ecFuzzy[0] = (ecRule[2] - fec)/(ecRule[2]-ecRule[1]);
        pec = 1;
    }
    else if(fec < ecRule[3])
    {
        ecFuzzy[0] = (ecRule[3] - fec)/(ecRule[3]-ecRule[2]);
        pec = 2 ;
    }
    else if(fec < ecRule[4])
    {
        ecFuzzy[0] = (ecRule[4] - fec)/(ecRule[4]-ecRule[3]);
        pec=3;
    }
    else if(fec < ecRule[5])
    {
        ecFuzzy[0] = (ecRule[5]-fec)/(ecRule[5]-ecRule[4]);
        pec=4;
    }
    else if(fec<ecRule[6])
    {
        ecFuzzy[0] = (ecRule[6]-fec)/(ecRule[6]-ecRule[5]);
        pec=5;
    }
    else
    {
        ecFuzzy[0] =1.0;
        pec=6;
    }
    ecFuzzy[1] = 1.0 - ecFuzzy[0];
//≤È—ØkpπÊ‘Ú±Ì
//±ﬂ‘µ¥¶¿Ì¢ŸŒ™∑¿÷π ˝◊È‘ΩΩÁ¢⁄µ˜ªª∂‘Ω«√Êª˝
    if(pe<(RANK-1) && pec<(RANK-1))//e∫Õe'∂º√ª”–¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];

        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];

        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];

        num = rule_kp[pec+1][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[1];
    }
    else if(pe==(RANK-1) && pec<(RANK-1))//e¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kp[pec+1][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))//e'¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kp[pec][pe+1];
        U1Fuzzy_kp[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else//e∫Õe'Õ¨ ±¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kp[pec][pe];
        U1Fuzzy_kp[num] += eFuzzy[0]*ecFuzzy[0];
    }
//≤È—ØkdπÊ‘Ú±Ì
    if(pe<(RANK-1) && pec<(RANK-1))//e∫Õe'∂º√ª”–¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];

        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];

        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];

        num = rule_kd[pec+1][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[1];
    }
    else if(pe==(RANK-1) && pec<(RANK-1))//e¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kd[pec+1][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[1];
    }
    else if(pe<(RANK-1) && pec==(RANK-1))//e'¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
        num = rule_kd[pec][pe+1];
        U1Fuzzy_kd[num] += eFuzzy[1]*ecFuzzy[0];
    }
    else//e∫Õe'Õ¨ ±¥ÔµΩ±ﬂ‘µ
    {
        num = rule_kd[pec][pe];
        U1Fuzzy_kd[num] += eFuzzy[0]*ecFuzzy[0];
    }
//÷ÿ–ƒ∑®Ω‚ƒ£∫˝
   for(int t=0;t<RANK;t++)
   {
       fuzzy_kp += U1Fuzzy_kp[t] * Rule_kp[t];
       fuzzy_kd += U1Fuzzy_kd[t] * Rule_kd[t];
   }
//   //…œŒªª˙¥Ú”°±‰¡ø
//  E_SBUF = position;
//  EC_SBUF= position_error;
}



