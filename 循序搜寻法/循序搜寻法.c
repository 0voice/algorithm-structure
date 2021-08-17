#include<queue>
#include<stack>

using namespace std;

struct SE{
  int vIndex;
  int tag;
  SE* next;
};

struct SMap{
  SE* pE;
  int nnode;
};

void visit(SE *se){
  printf("%d\n", se->vIndex);
}

SMap* create_map(int matrix[][6], int n){
  SMap* pMap = new SMap();
  pMap->nnode = n;
  pMap->pE = new SE[n];
  memset(pMap->pE, 0, n*sizeof(SE));
  for (int i = 0; i<n; i++){
    pMap->pE[i].vIndex = i;
    pMap->pE[i].tag = 0;
    SE* p = &pMap->pE[i];
    for (int j = 0; j<n; j++){
      if (matrix[i][j] != 0){
        p->next = new SE();
        p->next->vIndex = j;
        p->next->tag = 0;
        p->next->next = NULL;
        p = p->next;
      }
    }
  }
  return pMap;
}

int BFS(SMap* pMap, int n){
  queue<SE*> q;
  for (int i = 0; i < n; i++){
    if (pMap->pE[i].tag == 0){
      q.push(&pMap->pE[i]);
      while (!q.empty()){
        SE *se = q.front();
        q.pop();
        if (pMap->pE[se->vIndex].tag == 1){
          continue;
        }
        visit(se);
        pMap->pE[se->vIndex].tag = 1;
        SE * p = se;
        while (p->next){
          p = p->next;
          if (pMap->pE[p->vIndex].tag == 0){
            q.push(p);
          }
        }
      }
    }
  }
  return 0;
}

int DFS(SMap* pMap, int n){
  stack<SE*> s;
  for (int i = 0; i < n; i++){
    if (pMap->pE[i].tag == 0){
      s.push(&pMap->pE[i]);
      while (!s.empty()){
        SE *se = s.top();
        s.pop();
        if (pMap->pE[se->vIndex].tag == 1){
          continue;
        }
        visit(se);
        pMap->pE[se->vIndex].tag = 1;
        SE * p = &pMap->pE[se->vIndex];
        stack<SE*> tmp;
        while (p->next){
          p = p->next;
          if (pMap->pE[p->vIndex].tag == 0){
            tmp.push(p);
          }
        }
        while (!tmp.empty()){
          s.push(tmp.top());
          tmp.pop();
        }
      }
    }
  }
  return 0;
}

int main(){
  int map[6][6] = {
    { 0, 1, 0, 1, 0, 0 },
    { 1, 0, 1, 1, 1, 0 },
    { 0, 1, 0, 1, 0, 0 },
    { 1, 1, 1, 0, 1, 0 },
    { 0, 1, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 1, 0 }
  };
  SMap* smap = create_map(map, 6);
// BFS(smap, 6);
  DFS(smap, 6);
  return 0;
}
