#include <iostream>
#include <vector>
#include <map>
#define MIT map<weigth_t, pair<vertex_t, vertex_t> >::iterator 
#define vertex_t int
#define weigth_t int
using namespace std;

class DSU{
	vector<int> parent;
	vector<int> weigth;
public:
	DSU(const int n){
		parent.resize(n);
		for (int i = 0; i < n; i++){
			make_set(i);
			weigth.push_back(0);
		}
	}
	void make_set(const int x){
		parent[x] = x;
	}
	int find_set(const int x){
		if (parent[x] == x)
			return x;
		return parent[x] = find_set(parent[x]);
	}
	bool union_sets(const int x, const int y){
		int a = find_set(x);
		int b = find_set(y);
		if (a != b)
			if (weigth[a] > weigth[b]){
			parent[b] = a;
			weigth[a] += weigth[b];
			}
			else{
				parent[a] = b;
				weigth[b] += weigth[a];
			}
		else
			return false;
		return true;
	}
};

struct Graph{
	int numberOfVertex;
	multimap<weigth_t, pair<vertex_t, vertex_t> > weigEdges;
};

void fillGraph(Graph& g){
	int n, m;
	int v1, v2, w;
	cin >> n >> m;
	g.numberOfVertex = n;
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2 >> w;
		--v1, --v2;
		g.weigEdges.insert(make_pair(w, make_pair(v1, v2)));
	}
}

int MSTbyKruscal(const Graph& g){
	DSU dsu(g.numberOfVertex);
	int weigthMST = 0;
	for (MIT it = g.weigEdges.begin(); it != g.weigEdges.end(); it++){
		if (dsu.union_sets(it->second.first, it->second.second)){
			weigthMST += it->first;
		}
	}
	return weigthMST;
}

void showMST(int weigth){
	cout << weigth << endl;
}

int main(){
	Graph g;
	fillGraph(g);
	int weigthMST = MSTbyKruscal(g);
	showMST(weigthMST);
	return 0;
}