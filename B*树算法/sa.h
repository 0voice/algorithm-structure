//---------------------------------------------------------------------------
#ifndef sa_btreeH
#define sa_btreeH
//---------------------------------------------------------------------------
#include "fplan.h"
//---------------------------------------------------------------------------
extern float init_avg;
extern float avg_ratio;
extern float lamda;

double SA_Floorplan(FPlan &fp, int k, int local=0, float term_T=0.1);
double Random_Floorplan(FPlan &fp,int times);
//---------------------------------------------------------------------------
#endif
