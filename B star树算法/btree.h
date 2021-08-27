// Project: B*-trees floorplanning
// Advisor: Yao-Wen Chang  <ywchang@cis.nctu.edu.tw>
// Authors: Jer-Ming Hsu   <barz@cis.nctu.edu.tw>
// 	    Hsun-Cheng Lee <gis88526@cis.nctu.edu.tw>
// Sponsor: Arcadia Inc.
// Date:    7/19/2000 ~

//---------------------------------------------------------------------------
#ifndef btreeH
#define btreeH
//---------------------------------------------------------------------------
#include <vector>
#include <cassert>
#include "fplan.h"
//---------------------------------------------------------------------------
const int NIL = -1;
typedef bool DIR;
const bool LEFT=0, RIGHT=1;

struct Node{
  int id,parent,left,right;
  bool rotate,flip;
  bool isleaf(){ return (left==NIL && right==NIL); }
};
 
struct Contour{
  int front,back;
};

class B_Tree : public FPlan{
  public:
    B_Tree(float calpha=1) :FPlan(calpha) {}
    virtual void init();
    virtual void packing();
    virtual void perturb();
    virtual void keep_sol();
    virtual void keep_best();    
    virtual void recover();
    virtual void recover_best();

    // debuging
    void testing();
    
  protected:
    
    void show_tree();  
    void place_module(int mod,int abut,bool is_left=true);
    bool legal();
    void clear();
    
    // Auxilary function
    void wire_nodes(int parent,int child,DIR edge);
    int child(int node,DIR d);
    bool legal_tree(int p,int n,int &num);
    void add_changed_nodes(int n);
  
    // SA permutating operation
    void swap_node(Node &n1, Node &n2);
    void insert_node(Node &parent,Node &node);
    void delete_node(Node &node);
    
    bool delete_node2(Node &node,DIR pull);
    void insert_node2(Node &parent,Node &node,
                     DIR edge,DIR push,bool fold=false);

    int contour_root;
    vector<Contour> contour;
    int nodes_root;
    vector<Node> nodes;   

 
  private:        
    struct Solution{
      int nodes_root;
      vector<Node> nodes;
      double cost;
      Solution() { cost = 1; }
      void clear() { cost = 1, nodes.clear(); }
    };
  
    void get_solution(Solution &sol);
    void recover(Solution &sol);
    void recover_partial();

    Solution best_sol, last_sol;
    // for partial recover
    vector<Node> changed_nodes;
    int changed_root;    
};

//---------------------------------------------------------------------------
#endif
