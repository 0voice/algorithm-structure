// Project: B*-trees floorplanning
// Advisor: Yao-Wen Chang  <ywchang@cis.nctu.edu.tw>
// Authors: Jer-Ming Hsu   <barz@cis.nctu.edu.tw>
// 	    Hsun-Cheng Lee <gis88526@cis.nctu.edu.tw>
// Sponsor: Arcadia Inc.
// Date:    7/19/2000 ~

//---------------------------------------------------------------------------
#ifndef fplanH
#define fplanH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cstdio>
//---------------------------------------------------------------------------
using namespace std;

struct Pin{
  int mod;
  int net;
  int x,y;    // relative position
  int ax,ay;  // absolute position
  Pin(int x_=-1,int y_=-1){ x=x_,y=y_; }
};
typedef vector<Pin> Pins;
typedef Pin* Pin_p;
typedef vector<Pin_p> Net;
typedef vector<Net > Nets;

enum Module_Type { MT_Hard, MT_Soft, MT_Reclinear, MT_Buffer };

struct Module{
  int id;
  char name[20];
  int width,height;
  int x,y;
  int area;
  Pins pins;
  Module_Type type;
};
typedef vector<Module> Modules;

struct Module_Info{
  bool rotate, flip;
  int x,y;
  int rx,ry;
};

typedef vector<Module_Info> Modules_Info;

class FPlan{
  public:
    FPlan(float calpha);
    void read(char*);
    virtual void init()		=0;
    virtual void packing();
    virtual void perturb()	=0;    
    virtual void keep_sol()	=0;
    virtual void keep_best()	=0;
    virtual void recover()	=0;
    virtual void recover_best() =0;
    virtual double getCost();    

    int    size()         { return modules_N; }
    double getTotalArea() { return TotalArea; }
    double getArea()      { return Area;      }
    int    getWireLength(){ return WireLength;}
    double getWidth()     { return Width;     }
    double getHeight()    { return Height;    }
    float  getDeadSpace();

    // information
    void list_information();
    void show_modules();    
    void normalize_cost(int);
    
  protected:
    void clear();
    double calcWireLength();
    void scaleIOPad(); 

    double Area;
    double Width,Height;
    int WireLength;
    double TotalArea;
    
    int modules_N;    
    Modules modules;
    Module  root_module;
    Modules_Info modules_info;    
    Nets network;
    double norm_area, norm_wire;
    float cost_alpha;
    vector<vector<int> > connection;
    
  private:
    void read_dimension(Module&);
    void read_IO_list(Module&,bool parent);
    void read_network();
    void create_network();   

    map<string,int> net_table;
    string filename; 
};


void error(char *msg,char *msg2="");
bool rand_bool();
float rand_01();
double seconds();
      
//---------------------------------------------------------------------------
#endif
