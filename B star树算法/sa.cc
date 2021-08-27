// Project: B*-trees floorplanning
// Advisor: Yao-Wen Chang  <ywchang@cis.nctu.edu.tw>
// Authors: Jer-Ming Hsu   <barz@i.cis.nctu.edu.tw>
// 	    Hsun-Cheng Lee <gis88526@cis.nctu.edu.tw>
// Sponsor: Arcadia Inc.
// Date:    7/19/2000 ~

//---------------------------------------------------------------------------
#include <cmath>
#include "sa.h"
//---------------------------------------------------------------------------
float init_avg = 0.00001;
int hill_climb_stage = 7;
float avg_ratio=150;
float lamda=1.3;

double mean(vector<double> &chain){
  double sum=0;
  for(int i=0; i < chain.size();i++)
     sum+= chain[i];
  return sum/chain.size();
}

double std_var(vector<double> &chain){
  double m = mean(chain);
  double sum=0;
  double var;
  int N= chain.size();

  for(int i=0; i < N;i++)
     sum += (chain[i]-m)*(chain[i]-m);

  var = sqrt(sum/(N-1));
  printf("  m=%.4f ,v=%.4f\n",m,var);

  return var;
}

/* Simulated Annealing B*Tree Floorplan
   k: factor of the number of permutation in one temperature
   local: local search iterations
   termT: terminating temperature
*/
double SA_Floorplan(FPlan &fp, int k, int local=0, float term_T=0.1)
{
  int MT,uphill,reject;
  double pre_cost,best,cost;
  float d_cost,reject_rate;
  
  int N = k * fp.size();
  float P=0.9;
  float T,actual_T=1;
  double avg=init_avg;
  float conv_rate = 1;
  double time=seconds(); 

  double estimate_avg = 0.08 / avg_ratio;
  cout << "Estimate Average Delta Cost = " << estimate_avg << endl;

  if(local==0)
    avg = estimate_avg;

  T = avg / log(P);  
  
  // get inital solution
  fp.packing();
  fp.keep_sol();  
  fp.keep_best();
  pre_cost =  best = fp.getCost();
  
  int good_num=0,bad_num=0;
  double total_cost=0;
  int count=0;
  ofstream of("/tmp/btree_debug");

  do{
   count++;
   total_cost = 0;
   MT=uphill=reject=0;
   printf("Iteration %d, T= %.2f\n", count,  actual_T);
   
   vector<double> chain; 
 
   for(; uphill < N && MT < 2*N; MT++){
       fp.perturb();
       fp.packing();
       cost = fp.getCost(); 
       d_cost = cost - pre_cost;
       float p = exp(d_cost/T);
       

       chain.push_back(cost);

       if(d_cost <=0 || rand_01() < p ){
         fp.keep_sol();
         pre_cost = cost;

         if(d_cost > 0){       
           uphill++, bad_num++;
           of << d_cost << ": " << p << endl;
         }else  if(d_cost < 0)  good_num++;

         // keep best solution
         if(cost < best){
           fp.keep_best();
           best = cost;
           printf("   ==>  Cost= %f, Area= %.6f, ", best, fp.getArea()*1e-6);
           printf("Wire= %.3f\n", fp.getWireLength()*1e-3);  
           assert(fp.getArea() >= fp.getTotalArea());
           time = seconds();  
         }
       }
       else{
         reject++;
         fp.recover();
       }
   }
//   cout << T << endl;
   double sv = std_var(chain);
   float r_t = exp(lamda*T/sv);
   T = r_t*T;


   // After apply local-search, start to use normal SA
   if(count == local){
     T = estimate_avg/ log(P);
     T *= pow(0.9,local);		// smothing the annealing schedule
     actual_T = exp(estimate_avg/T);
   }
   if(count > local){
     actual_T = exp(estimate_avg/T);
     conv_rate = 0.95;
   }

   reject_rate = float(reject)/MT;
   printf("  T= %.2f, r= %.2f, reject= %.2f\n\n", actual_T, r_t, reject_rate);

  }while(reject_rate < conv_rate && actual_T > term_T);

  if(reject_rate >= conv_rate)
    cout << "\n  Convergent!\n";
  else if(actual_T <= term_T)
    cout << "\n Cooling Enough!\n";

  printf("\n good = %d, bad=%d\n\n", good_num, bad_num);

  fp.recover_best();
  fp.packing();
  return time; 
}

double Random_Floorplan(FPlan &fp,int times){
  int N =times,t=0;
  double total_cost=0,pre_cost,cost,best;

  fp.packing();
  pre_cost = best = fp.getCost();

 do{
  for(int i=0; i < N;i++){
    fp.perturb();
    fp.packing();
  
    cost = fp.getCost();
    if(cost-pre_cost > 0){
      t++;
      total_cost += cost-pre_cost;
      pre_cost = cost;
    }

    if(cost < best){
      fp.keep_best();
      best = cost;
      cout << "==> Cost=" << best << endl;
    }
  }	
 }while(total_cost==0);

  fp.recover_best();
  fp.packing();

  total_cost /= t;
  return total_cost;
}

