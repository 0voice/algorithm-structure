//图的深度优先遍历源代码
//有如下要求：
//1.分别采用邻接矩阵存储结构实现图的深度优先遍历
//2.对任意给定的图（顶点数边树自定）建立它的邻接矩阵并输出
//3.实现图的深度优先遍历

#include <iostream>
using namespace std;
template<typename T,typename E>

class _edge
{
public:
    int _dest;
    E _cost;
    _edge<T,E>* _link;
    _edge(){}
    _edge(int _num,T _weight):_dest(_num),_cost(_weight),_link(NULL){}
    bool operator!=(_edge<T,E>& rhs)const
    {
        return (_dest != rhs._dest) ? true : false;
    }
};

template<typename T,typename E>
struct _vertex
{
    T _data;
    _edge<T,E>* _adj;
};

template<typename T,typename E>
class _graphLink
{
    friend istream& operator>>(istream& is,_graphLink<T,E>& rhs);
    friend ostream& operator<<(ostream& os,_graphLink<T,E>& rhs);
public:
    _graphLink(int sz = 100);
    ~_graphLink();
    int _getCurVert()const{return _curVert;}
    T _getValue(int i)
    {
        return (i >= 0 && i <= _curVert) ? _nodeTable[ i ]._data : 0;
    }
    bool _insV(const T& _vert);
    bool _insE(int v1,int v2);
    int _getFirstNeighBor(int v);
    int _getNextNeighBor(int v,int w);
    int _getVertexPos(const T vert)
    {
        for (int i = 0;i < _curVert;i ++)
            if (_nodeTable[ i ]._data == vert)
                return i;

        return -1;
    }
private:
    int _curVert;
    int _curEdge;
    int _maxVert;
    _vertex<T,E>* _nodeTable;
};

template<typename T,typename E>
_graphLink<T,E>::_graphLink(int sz)
{
_maxVert = sz;_curVert = 0;_curEdge = 0;
_nodeTable = new _vertex<T,E>[_maxVert + 1];
for (int i = 0;i < _maxVert;i ++)_nodeTable[ i ]._adj = NULL;
}

template<typename T,typename E>
_graphLink<T,E>::~_graphLink()
{
    for (int i = 0;i < _curVert;i ++)
    {
        _edge<T,E>* p = _nodeTable[ i ]._adj;
        while (p != NULL)
        {
            _nodeTable[ i ]._adj = p ->_link;
            delete p;p = _nodeTable[ i ]._adj;
        }
    }
    delete [] _nodeTable;
}

template<typename T,typename E>
int _graphLink<T,E>::_getFirstNeighBor(int v)
{
    if (v != -1)
    {
        _edge<T,E> *p = _nodeTable[ v ]._adj;
        if (p != NULL)return p ->_dest;
    }

    return -1;
}

template<typename T,typename E>
int _graphLink<T,E>::_getNextNeighBor(int v, int w)
{
    if (v != -1)
    {
        _edge<T,E>* p = _nodeTable[ v ]._adj;
        while (p != NULL && p ->_dest != w)p = p ->_link;
        if (p != NULL && p ->_link != NULL)
            return p ->_link ->_dest;
    }
    return -1;
}

template<typename T,typename E>
bool _graphLink<T,E>::_insV(const T &_vert)
{
    if (_curVert == _maxVert)return false;
        _nodeTable[ _curVert ]._data = _vert;
        _curVert ++;
        return true;
}

template<typename T,typename E>
bool _graphLink<T,E>::_insE(int v1, int v2)
{
    if (v1 >= 0 && v1 <= _curVert && v2 >= 0 && v2 <= _curVert)
    {
        _edge<T,E> *q,*p = _nodeTable[ v1 ]._adj;
        while (p != NULL && p ->_dest != v2)p = p ->_link;
        if (p != NULL)return false;
        p = new _edge<T,E>;q = new _edge<T,E>;
        p ->_dest = v2;p ->_link = _nodeTable[ v1 ]._adj;
        _nodeTable[ v1 ]._adj = p;
        q ->_dest = v1;q ->_link = _nodeTable[ v2 ]._adj;
        _nodeTable[ v2 ]._adj = q;
        _curEdge ++;
        return true;
    }

    return 0;
}

template<typename T,typename E>
void _dfs(_graphLink<T,E>& _g,const T& v)
{
    int _loc,n = _g._getCurVert();
    bool* _visited = new bool[n + 1];
    for (int i = 0;i <= n;i ++)_visited[ i ] = false;
    _loc = _g._getVertexPos(v);
    _dfs(_g,_loc,_visited);
    delete [] _visited;
}

template<typename T,typename E>
void _dfs(_graphLink<T,E>& _g,int v,bool _visited[])
{
    cout<<"dfs:"<<_g._getValue(v)<<" ";
    _visited[ v ] = true;
    int w = _g._getFirstNeighBor(v);
    while (w != -1)
    {
        if (_visited[ w ] == false)_dfs(_g,w,_visited);
        w = _g._getNextNeighBor(v,w);
    }
}

int main()
{
    int n,k,m;
    int e1,e2;
    cin>>n;
    while (n --)
    {
        cin>>k>>m;
        _graphLink<int,int> _g(k);
        for (int i = 1;i <= k;i ++)
        _g._insV(i);
        for (int i = 0;i < m;i ++)
        {
            scanf("%d%d",&e1,&e2);
            _g._insE(e1,e2);
        }
        _dfs(_g,1);
    }
    system("PAUSE");
    return 0;
}
