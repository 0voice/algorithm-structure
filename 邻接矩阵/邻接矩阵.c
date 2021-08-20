#include <iostream>
#include <cassert>
#include <vector>
#include <ctime>

using namespace std;

//稠密图-邻接矩阵
class DenseGraph {
	private:
		int n,m;
		bool directed;//是否为有向图
		vector< vector<bool> > g;

	public:
		//构造方法
		DenseGraph(int n, bool directed) {
			this->n = n;
			this->directed = directed;
			this->m = 0;
			for(int i = 0; i < n; i++) {
				g.push_back(vector<bool> (n , false));
			}
		}
		~DenseGraph() {

		}
		//返回顶点个数
		int V() {
			return n;
		}
		//返回边条数
		int E() {
			return m;
		}
		//两节点添加边
		void addEdge(int v, int w) {
			if (hasEdge(v, w)) {
				return ;
			}
			g[v][w] = true;
			if (!directed) {
				g[w][v] = true;
			}
			m++;

		}
		//两节点是否有边
		bool hasEdge(int v,int w) {
			assert(v >= 0 && v < n);
			assert(w >= 0 && w < n);
			return g[v][w];
		}
		//打印图矩阵的值
		void printG() {
			for(int i = 0; i < n ; i++) {

				for(int j = 0; j < n; j++) {
					cout << g[i][j]	 << " ";
				}
				cout << endl;
			}
		}

		//自定义迭代器 进行访问
		class adjIterator {
			private:
				DenseGraph &G;
				int index;
				int v;
			public:
				adjIterator(DenseGraph &graph, int v) :G(graph) {
					this->v = v;
					this->index = -1;
				}

				int begin() {
					index = - 1;
					return next();
				}

				int next() {
					for(index += 1; index < G.V(); index++) {
						if (G.g[v][index]) {
							return index;
						}
					}
					return -1;
				}

				bool end() {
					return index >= G.V();
				}
		};

};


int main() {
	srand(time(NULL));
	int n = 10;//节点数
	int m = 66;//边条数

	DenseGraph denseGraph = DenseGraph(n, false);
	for (int i =0; i < m; i++) {
		int v = rand() % n;
		int w = rand() % n;
		denseGraph.addEdge(v, w);
	}

	cout << "以下是添加了边的关系后图中矩阵的值:" << endl;
	denseGraph.printG();

	cout << endl;
	cout << "以下是通过自定义迭代器进行访问节点0关联的边:" << endl;

	for (int i = 0; i < n; i++) {
		DenseGraph::adjIterator adj(denseGraph, i);
		cout << "节点" <<  i << ":";
		for(int w = adj.begin(); !adj.end(); w = adj.next()) {
			cout << w <<" ";

		}
		cout <<endl;
	}

	return 0;
}
