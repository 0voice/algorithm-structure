// Project: B*-trees floorplanning
// Advisor: Yao-Wen Chang  <ywchang@cis.nctu.edu.tw>
// Authors: Jer-Ming Hsu   <barz@cis.nctu.edu.tw>
// 	    Hsun-Cheng Lee <gis88526@cis.nctu.edu.tw>
// Sponsor: Arcadia Inc.
// Date:    7/19/2000 ~

//---------------------------------------------------------------------------
#include "fplan.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <sys/time.h>
#include <sys/resource.h>

//---------------------------------------------------------------------------
char line[100],t1[40],t2[40];
ifstream fs;

FPlan::FPlan(float calpha=1){
  norm_area= 1;
  norm_wire= 1;
  cost_alpha=calpha;
}

void FPlan::packing(){
  if(cost_alpha!=1)
     calcWireLength();
}

void FPlan::clear(){
  Area = 0; 
  WireLength = 0;
}

double FPlan::getCost(){
  if(cost_alpha==1)
     return cost_alpha*(Area/norm_area);
  else if(cost_alpha < 1e-4)
     return (WireLength/norm_wire);
  else
     return cost_alpha*(Area/norm_area)+(1-cost_alpha)*(WireLength/norm_wire);
}

float FPlan::getDeadSpace(){
  return 100*(Area-TotalArea)/float(Area);
}

void FPlan::normalize_cost(int t){
  norm_area=norm_wire=0;

  for(int i=0; i < t; i++){
    perturb();
    packing();
    norm_area += Area;
    norm_wire += WireLength;
  }
  
  norm_area /= t;
  norm_wire /= t;
  printf("normalize area=%.0f, wire=%.0f\n", norm_area, norm_wire);
}

//---------------------------------------------------------------------------
//   Read
//---------------------------------------------------------------------------

char* tail(char *str){
    str[strlen(str)-1]=0;
    return str;
}

void FPlan::read(char *file){
  filename = file; 
  fs.open(file);
  if(fs==NULL)
    error("unable to open file: %s",file);

  bool final=false;
  Module dummy_mod;
  for(int i=0; !fs.eof(); i++){
    // modules
    modules.push_back(dummy_mod);	// new module
    Module &mod = modules.back();
    mod.id = i;
    mod.pins.clear();

    fs >> t1 >> t2;
    tail(t2);			// remove ";"
    strcpy(mod.name,t2);

    fs >> t1 >> t2;
    if(!strcmp(t2,"PARENT;"))
	final= true;
    
    // dimension
    read_dimension(mod);    
    read_IO_list(mod,final);

    // network
    if(final){
      read_network();
      break;
    }
  }

  root_module = modules.back();
  modules.pop_back();		// exclude the parent module
  modules_N = modules.size();  
  modules_info.resize(modules_N);
  modules.resize(modules_N);

  create_network();

  TotalArea = 0;
  for(int i=0; i < modules_N; i++)
    TotalArea += modules[i].area;

}

void FPlan::read_dimension(Module &mod){
    fs >> t1;
    int min_x=INT_MAX,min_y=INT_MAX,max_x=INT_MIN,max_y=INT_MIN;
    int tx,ty;
    for(int i=0; i < 4;i++){
      fs >> tx >> ty; 
      min_x=min(min_x,tx); max_x=max(max_x,tx);
      min_y=min(min_y,ty); max_y=max(max_y,ty);
    }

    mod.x      = min_x;
    mod.y      = min_y;
    mod.width  = max_x - min_x;
    mod.height = max_y - min_y;
    mod.area   = mod.width * mod.height;
    fs >> t1 >> t2;
}

void FPlan::read_IO_list(Module &mod,bool parent=false){
    // IO list
    while(!fs.eof()){
      Pin p;
      fs.getline(line,100);
      if(strlen(line)==0) continue;
      sscanf(line,"%s %*s %d %d",t1,&p.x,&p.y);

      if(!strcmp(t1,"ENDIOLIST;"))
	break;

      if(parent){ // IO pad is network
       // make unique net id
        net_table.insert(make_pair(string(t1),net_table.size()));
        p.net = net_table[t1];
      }

      p.mod = mod.id;
      p.x -= mod.x;  p.y -= mod.y;	// shift to origin

      mod.pins.push_back(p);
    }
    fs.getline(line,100);
}

void FPlan::read_network(){
    while(!fs.eof()){
      bool end=false;
      int n=0;
      fs >> t1 >> t2;
      if(!strcmp(t1,"ENDNETWORK;"))
        break;
      // determine which module interconnection by name
      int m_id;
      for(m_id=0; m_id < modules.size(); m_id++)
        if(!strcmp(modules[m_id].name,t2))
   	  break;
      if(m_id== modules.size())
 	error("can't find suitable module name!");
        
      while(!fs.eof()){
        fs >> t1;
        if(t1[strlen(t1)-1]==';'){
 	  tail(t1);
          end=true;
        }

        // make unique net id
        net_table.insert(make_pair(string(t1),net_table.size()));
        modules[m_id].pins[n++].net = net_table[t1];
        if(end) break;
      }
    }
}

//---------------------------------------------------------------------------
//   Wire Length Estimate
//---------------------------------------------------------------------------

void FPlan::create_network(){
  network.resize(net_table.size());

  for(int i=0; i < modules_N; i++){
    for(int j=0; j < modules[i].pins.size(); j++){
      Pin &p = modules[i].pins[j];
      network[p.net].push_back(&p);
    }
  }

  for(int j=0; j < root_module.pins.size(); j++){
    Pin &p = root_module.pins[j];
    network[p.net].push_back(&p);
  }

  connection.resize(modules_N+1);
  for(int i=0; i < modules_N+1; i++){
    connection[i].resize(modules_N+1);
    fill(connection[i].begin(), connection[i].end(), 0);
  }

  for(int i=0; i < network.size(); i++){
    for(int j=0; j < network[i].size()-1; j++){
      int p= network[i][j]->mod;
      for(int k=j+1 ; k < network[i].size(); k++){
        int q= network[i][k]->mod;
        connection[p][q]++;
        connection[q][p]++;   
      }
    }
  }
}


void FPlan::scaleIOPad(){
  float px = Width/float(root_module.width);
  float py = Height/float(root_module.height);
    
  for(int i=0; i < root_module.pins.size(); i++){
    Pin &p = root_module.pins[i];
    p.ax = int(px * p.x);
    p.ay = int(py * p.y);
    
  }      
}

double FPlan::calcWireLength(){

  scaleIOPad();
 
  WireLength=0;
  // compute absolute position
  for(int i=0; i < modules_N; i++){   
    int mx= modules_info[i].x, my= modules_info[i].y;
    bool rotate= modules_info[i].rotate;
    int w= modules[i].width;

    for(int j=0; j < modules[i].pins.size(); j++){
      Pin &p = modules[i].pins[j];

      if(!rotate){      
        p.ax= p.x+mx, p.ay= p.y+my;
      }
      else{ // Y' = W - X, X' = Y
	p.ax= p.y+mx, p.ay= (w-p.x)+my;
      } 
    }
  }

  for(int i=0; i < network.size(); i++){     
    int max_x= INT_MIN, max_y= INT_MIN;      
    int min_x= INT_MAX, min_y= INT_MAX;      

    assert(network[i].size() > 0);
    for(int j=0; j < network[i].size(); j++){
      Pin &p = *network[i][j];
      max_x= max(max_x, p.ax), max_y= max(max_y, p.ay);
      min_x= min(min_x, p.ax), min_y= min(min_y, p.ay);
    }
//    printf("%d %d %d %d\n",max_x,min_x,max_y,min_y);
    WireLength += (max_x-min_x)+(max_y-min_y);
  }
  return WireLength;
}

//---------------------------------------------------------------------------
//   Modules Information
//---------------------------------------------------------------------------

string query_map(map<string,int> M,int value){
  for(map<string,int>::iterator p=M.begin(); p != M.end(); p++){
    if(p->second == value)
      return p->first;
  }
  return "";
}

void FPlan::show_modules()
{
  for(int i=0; i < modules.size();i++){
    cout << "Module: " << modules[i].name << endl;
    cout << "  Width = " << modules[i].width;
    cout << "  Height= " << modules[i].height << endl;
    cout << "  Area  = " << modules[i].area << endl;
//    cout << modules[i].pins.size() << " Pins:\n";
//    for(int j=0; j < modules[i].pins.size(); j++){
//      cout << query_map(net_table,modules[i].pins[j].net) << " ";
//      cout << modules[i].pins[j].x << " " << modules[i].pins[j].y << endl;
//    }
  }
}

void FPlan::list_information(){

  string info = filename + ".info";   
  ofstream of(info.c_str());
  
  of << modules_N << " " << Width << " " << Height << endl;
  for(int i=0; i < modules_N; i++){
    of << modules_info[i].x  << " " << modules_info[i].rx  << " ";
    of << modules_info[i].y << " " << modules_info[i].ry << endl;
  }
  of << endl;

  calcWireLength(); 
  int x,y,rx,ry;
  for(int i=0; i < network.size(); i++){
    assert(network[i].size()>0);
    x = network[i][0]->ax;
    y = network[i][0]->ay;
    
    for(int j=1; j < network[i].size(); j++){
      rx = network[i][j]->ax;
      ry = network[i][j]->ay;
      of << x << " " << y << " " << rx << " " << ry << endl;
      x = rx, y = ry;
    }
  }

  cout << "Num of Module  = " << modules_N << endl;
  cout << "Height         = " << Height*1e-3 << endl;
  cout << "Width          = " << Width*1e-3 << endl;
  cout << "Area           = " << Area*1e-6 << endl;
  cout << "Wire Length    = " << calcWireLength()*1e-3 << endl;
  cout << "Total Area     = " << TotalArea*1e-6 << endl;
  printf( "Dead Space     = %.2f\n", getDeadSpace());
}

//---------------------------------------------------------------------------
//   Auxilliary Functions
//---------------------------------------------------------------------------

void error(char *msg,char *msg2=""){
  printf(msg,msg2);
  cout << endl;
  throw 1;
}

bool rand_bool(){
  return bool(rand()%2);
}

float rand_01(){
  return float(rand()%10000)/10000;
}

double seconds(){
   rusage time;
   getrusage(RUSAGE_SELF,&time);
   return (double)(1.0*time.ru_utime.tv_sec+0.000001*time.ru_utime.tv_usec);
}
