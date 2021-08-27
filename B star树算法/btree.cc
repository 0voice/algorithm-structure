// Project: B*-trees floorplanning
// Advisor: Yao-Wen Chang  <ywchang@cis.nctu.edu.tw>
// Authors: Jer-Ming Hsu   <barz@cis.nctu.edu.tw>
// 	    Hsun-Cheng Lee <gis88526@cis.nctu.edu.tw>
// Sponsor: Arcadia Inc.
// Date:    7/19/2000 ~

//---------------------------------------------------------------------------
#include <stack>
#include <algorithm>
#include "btree.h"
//---------------------------------------------------------------------------
float rotate_rate = 0.3;
float swap_rate = 0.5;

//---------------------------------------------------------------------------
//   Initialization
//---------------------------------------------------------------------------

void B_Tree::clear(){
  // initial contour value
  contour_root = NIL;
  FPlan::clear();
}

void B_Tree::init(){
  // initialize contour structure
  contour.resize(modules_N);
    
  // initialize b*tree by complete binary tree
  nodes.resize(modules_N);
  nodes_root=0;
  for(int i=0; i < modules_N; i++){
    nodes[i].id = i;
    nodes[i].parent = (i+1)/2-1;
    nodes[i].left   = (2*i+1 < modules_N ? 2*i+1 : NIL);
    nodes[i].right  = (2*i+2 < modules_N ? 2*i+2 : NIL);
  }
  nodes[0].parent = NIL;
  best_sol.clear();
  last_sol.clear();
  clear();
  normalize_cost(10);
} 

//---------------------------------------------------------------------------
//   Testing, Debuging tools
//---------------------------------------------------------------------------

bool B_Tree::legal(){
  int num=0;
  return legal_tree(NIL,nodes_root,num);
}

bool B_Tree::legal_tree(int p,int n,int &num){
  num++;
  if(nodes[n].parent!=p) return false;
  if(nodes[n].left != NIL)
    if(legal_tree(n,nodes[n].left,num) != true) return false;

  if(nodes[n].right != NIL)
    if(legal_tree(n,nodes[n].right,num) != true) return false;

  if(p==NIL) // root
    return (num==modules_N);
  return true;
}

void B_Tree::testing(){
  int p,n;
  Solution E;

  do{
    n = rand()%modules_N;
    p = rand()%modules_N;

    while(n==nodes_root)		// n is not root
      n = rand()%modules_N;

    while(n==p||nodes[n].parent==p||nodes[p].parent==n)	// n != p & n.parent != p
      p = rand()%modules_N;
   
    Node &node = nodes[n];
    Node &parent = nodes[p];
    get_solution(E);
    swap_node(parent,node);
  }while(legal());

  cout << "p=" << p << ", n=" << n << endl;
  recover(E);
  show_tree();
  cout << "\n  p=" << p << ", n=" << n << endl;
  swap_node(nodes[p],nodes[n]);
  show_tree();
}

void B_Tree::show_tree(){
  cout << "root: " << nodes_root << endl;
  for(int i=0; i < modules_N; i++){
    cout << nodes[i].id << ": ";
    cout << nodes[i].left << " ";
    cout << nodes[i].parent << " ";
    cout << nodes[i].right << endl;
  }
}

//---------------------------------------------------------------------------
//   Placement modules
//---------------------------------------------------------------------------

void B_Tree::packing(){
  stack<int> S;

  clear();
  int p = nodes_root;

  place_module(p,NIL);
  Node &n = nodes[p];
  if(n.right != NIL)      S.push(n.right);
  if(n.left  != NIL)      S.push(n.left);

  // inorder traverse
  while(!S.empty()){
    p = S.top();
    S.pop();
    Node &n = nodes[p];

    assert(n.parent != NIL);
    bool is_left = (nodes[n.parent].left == n.id);
    place_module(p,n.parent,is_left);

    if(n.right != NIL)      S.push(n.right);
    if(n.left  != NIL)      S.push(n.left);
  }

  // compute Width, Height
  double max_x=-1,max_y=-1;
  for(int p= contour_root; p != NIL; p=contour[p].front){
    max_x = max(max_x,double(modules_info[p].rx));  
    max_y = max(max_y,double(modules_info[p].ry));
  }

  Width  = max_x;
  Height = max_y;
  Area   = Height*Width;

  FPlan::packing(); 	// for wirelength  
}

// is_left: default is true
void B_Tree::place_module(int mod,int abut,bool is_left){
  Module_Info &mod_mf = modules_info[mod];
  mod_mf.rotate       = nodes[mod].rotate;
  mod_mf.flip         = nodes[mod].flip;

  int w =  modules[mod].width;
  int h =  modules[mod].height;
  if(nodes[mod].rotate)
    swap(w,h);
  
  if(abut==NIL){	// root node
    contour_root = mod;
    contour[mod].back = NIL;
    contour[mod].front = NIL;
    mod_mf.x  = mod_mf.y = 0;
    mod_mf.rx = w, mod_mf.ry = h;
    return;
  }
  
  int p;   // trace contour from p

  if(is_left){	// left
    int abut_width = (nodes[abut].rotate ? modules[abut].height : 
                                           modules[abut].width);
    mod_mf.x  = modules_info[abut].x + abut_width;
    mod_mf.rx = mod_mf.x + w;
    p = contour[abut].front;

    contour[abut].front = mod;
    contour[mod].back = abut;

    if(p==NIL){  // no obstacle in X axis
      mod_mf.y = 0;
      mod_mf.ry = h;
      contour[mod].front = NIL;
      return;
    }
  }else{	// upper
    mod_mf.x = modules_info[abut].x;
    mod_mf.rx = mod_mf.x + w;
    p = abut;
     
    int n=contour[abut].back;

    if(n==NIL){ // i.e, mod_mf.x==0
      contour_root = mod;
      contour[mod].back = NIL;
    }
    else{
      contour[n].front = mod;
      contour[mod].back = n;
    }
  }
  
  int min_y = INT_MIN;
  int bx,by;
  assert(p!=NIL);
    
  for(; p!=NIL ; p=contour[p].front)
  {
    bx = modules_info[p].rx;
    by = modules_info[p].ry;
    min_y = max(min_y, by);
      
    if(bx >= mod_mf.rx){ 	// update contour
      mod_mf.y = min_y;
      mod_mf.ry = mod_mf.y + h;
      if(bx > mod_mf.rx){
        contour[mod].front = p;
        contour[p].back = mod;
      }else{ 			// bx==mod_mf.rx
        int n= contour[p].front;
        contour[mod].front = n;
        if(n!=NIL)
          contour[n].back = mod;
      }
      break;     
    }
  }

  if(p==NIL){
    mod_mf.y  = (min_y==INT_MIN? 0 : min_y);
    mod_mf.ry = mod_mf.y + h;
    contour[mod].front = NIL;
  }
}

//---------------------------------------------------------------------------
//   Manipulate B*Tree auxilary procedure
//---------------------------------------------------------------------------

void B_Tree::wire_nodes(int parent,int child,DIR edge){
  assert(parent!=NIL);
  (edge==LEFT? nodes[parent].left: nodes[parent].right) = child;
  if(child!=NIL) nodes[child].parent = nodes[parent].id;
}

int B_Tree::child(int node,DIR d){
  assert(node!=NIL);
  return (d==LEFT? nodes[node].left:nodes[node].right);  
}


//---------------------------------------------------------------------------
//   Simulated Annealing Temporal Solution
//---------------------------------------------------------------------------

void B_Tree::get_solution(Solution &sol){
  sol.nodes_root = nodes_root;
  sol.nodes = nodes;
  sol.cost = getCost();
}

void B_Tree::keep_sol(){
  get_solution(last_sol);
}

void B_Tree::keep_best(){
  get_solution(best_sol);
}

void B_Tree::recover(){
  recover(last_sol);
  // recover_partial();
}

void B_Tree::recover_best(){
  recover(best_sol);
}

void B_Tree::recover(Solution &sol){
  nodes_root = sol.nodes_root;
  nodes = sol.nodes;
}

void B_Tree::recover_partial(){
  if(changed_root != NIL)
    nodes_root = changed_root;
  
  for(int i=0; i < changed_nodes.size(); i++){
    Node &n = changed_nodes[i];
    nodes[n.id] = n;
  }
}

void B_Tree::add_changed_nodes(int n){
  if(n==NIL) return;

  for(int i=0; i < changed_nodes.size(); i++)
    if(changed_nodes[i].id == n)
	return;
  changed_nodes.push_back(nodes[n]);
}

//---------------------------------------------------------------------------
//   Simulated Annealing Permutation Operations
//---------------------------------------------------------------------------

void B_Tree::perturb(){
  int p,n;
  n = rand()%modules_N;

//  changed_nodes.clear();
//  changed_root = NIL;


  if(rotate_rate > rand_01()){
//    changed_nodes.push_back(nodes[n]);
    nodes[n].rotate = !nodes[n].rotate;
    if(rand_bool()) nodes[n].flip = !nodes[n].flip;
  }
  else{ 	

    if(swap_rate >rand_01()){
      do{
        p = rand()%modules_N;
      }while(n==p||nodes[n].parent==p||nodes[p].parent==n);

//      changed_nodes.push_back(nodes[p]);
//      changed_nodes.push_back(nodes[n]);

      swap_node(nodes[p],nodes[n]);

    }else{
      do{
        p = rand()%modules_N;
      }while(n==p);

//      changed_nodes.push_back(nodes[p]);
//      changed_nodes.push_back(nodes[n]);

      delete_node(nodes[n]);
      insert_node(nodes[p],nodes[n]);
    }
  }
}

void B_Tree::swap_node(Node &n1, Node &n2){

  if(n1.left!=NIL){  
    //add_changed_nodes(n1.left);
    nodes[n1.left].parent  = n2.id;
  }
  if(n1.right!=NIL){
    //add_changed_nodes(n1.right);
    nodes[n1.right].parent = n2.id;  
  }
  if(n2.left!=NIL){
    //add_changed_nodes(n2.left);
    nodes[n2.left].parent  = n1.id;
  }
  if(n2.right!=NIL){
    //add_changed_nodes(n2.right);
    nodes[n2.right].parent = n1.id;  
  }

  if(n1.parent != NIL){
    //add_changed_nodes(n1.parent);
    if(nodes[n1.parent].left==n1.id)
       nodes[n1.parent].left  = n2.id;
    else
       nodes[n1.parent].right = n2.id; 
  }else{
    changed_root = n1.id;
    nodes_root = n2.id;
  }

  if(n2.parent != NIL){
    //add_changed_nodes(n2.parent);
    if(nodes[n2.parent].left==n2.id)
       nodes[n2.parent].left  = n1.id;
    else
       nodes[n2.parent].right = n1.id; 
  }else{
//    changed_root = n2.id;
    nodes_root = n1.id;
  }

  swap(n1.left,n2.left);
  swap(n1.right,n2.right);
  swap(n1.parent,n2.parent);
}

void B_Tree::insert_node(Node &parent, Node &node){
  node.parent = parent.id;
  bool edge = rand_bool();

  if(edge){
    //add_changed_nodes(parent.left);
    node.left  = parent.left;
    node.right = NIL;
    if(parent.left!=NIL)
      nodes[parent.left].parent = node.id;

    parent.left = node.id;

  }else{
    //add_changed_nodes(parent.right);
    node.left  = NIL;
    node.right = parent.right;
    if(parent.right!=NIL)
      nodes[parent.right].parent = node.id;
    
    parent.right = node.id;
  }
}

void B_Tree::delete_node(Node &node){
  int child    = NIL;	// pull which child
  int subchild = NIL;   // child's subtree
  int subparent= NIL; 

  if(!node.isleaf()){
    bool left= rand_bool();			// choose a child to pull up
    if(node.left ==NIL) left=false;
    if(node.right==NIL) left=true;

    //add_changed_nodes(node.left);
    //add_changed_nodes(node.right);

    if(left){
      child = node.left;			// child will never be NIL
      if(node.right!=NIL){
        subchild  = nodes[child].right;
        subparent = node.right;
        nodes[node.right].parent = child; 
        nodes[child].right = node.right;	// abut with node's another child
      }
    }
    else{
      child = node.right;
      if(node.left!=NIL){
        subchild  = nodes[child].left;
        subparent = node.left;
	nodes[node.left].parent = child;
        nodes[child].left = node.left;
      }
    }
    //add_changed_nodes(subchild);
    nodes[child].parent = node.parent;
  }

  if(node.parent == NIL){			// root
//    changed_root = nodes_root;
    nodes_root = child;
  }else{					// let parent connect to child
    //add_changed_nodes(node.parent);
    if(node.id == nodes[node.parent].left)
      nodes[node.parent].left  = child;
    else
      nodes[node.parent].right = child;
  }

  // place subtree
  if(subchild != NIL){
    Node &sc = nodes[subchild];
    assert(subparent != NIL);

    while(1){
      Node &p = nodes[subparent];

      if(p.left==NIL || p.right==NIL){
        //add_changed_nodes(p.id);

	sc.parent = p.id;
        if(p.left==NIL) p.left = sc.id;
        else p.right = sc.id;
        break;
      }else{
	subparent = (rand_bool() ? p.left : p.right);
      }
    }
  }
}


bool B_Tree::delete_node2(Node &node,DIR pull){
  DIR npull = !pull;
 
  int p = node.parent;
  int n= node.id;
  int c= child(n,pull);
  int cn=child(n,npull);

  assert(n!= nodes_root); // not root;

  DIR p2c = (nodes[p].left==n ? LEFT:RIGHT);

  if(c==NIL){
    wire_nodes(p,cn,p2c);
    return (cn!=NIL);   // folding
  }else{
    wire_nodes(p,c,p2c);
  }

  while(c!=NIL){
    int k=child(c,npull);
    wire_nodes(c,cn ,npull);
    cn= k;
    n= c;
    c= child(c,pull);
  }

  if(cn != NIL){
    wire_nodes(n,cn,pull);
    return true;
  }else 
    return false;
}

/*
   Insert node into parent's left or right subtree according by "edge".
   Push node into parent's subtree in  "push" direction.

   if "fold" is true, then fold the leaf.
   (for the boundary condition of "delete" operation)

   delete <==> insert are permutating operations that can be recoved.
*/

void B_Tree::insert_node2(Node &parent,Node &node,
                        DIR edge=LEFT,DIR push=LEFT,bool fold=false){
  DIR npush = !push;
  int p= parent.id;
  int n= node.id;
  int c= child(p,edge);

  wire_nodes(p,n,edge);
  wire_nodes(n,c,push);
    
  while(c!=NIL){
    wire_nodes(n,child(c,npush) ,npush);
    n= c;
    c= child(c,push);
  }
  wire_nodes(n,NIL,npush);

  if(fold){
    wire_nodes(nodes[n].parent,NIL,push);
    wire_nodes(nodes[n].parent,n,npush); 
  }
}
