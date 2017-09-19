#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

#define vertex_t int
#define weigth_t int

struct Graph{
	int numberOfVertex;
	vector<vector<pair<vertex_t, weigth_t> > > listOfAdj;
};

void fillGraph(Graph& g){
	int n, m;
	int x, y, w;
	cin >> n >> m;
	g.numberOfVertex = n;
	g.listOfAdj.resize(n);
	for (int i = 0; i < m; i++){
		cin >> x >> y >> w;
		--x, --y;
		g.listOfAdj[x].push_back(make_pair(y, w));
		g.listOfAdj[y].push_back(make_pair(x, w));
	}
}

int findMSTbyPrima(const Graph& g, const int root = 0){
	vector<vertex_t> parent(g.numberOfVertex, -1);
	vector<weigth_t> key(g.numberOfVertex, INT_MAX);
	set<pair<weigth_t, vertex_t> > priorQ;
	int curVert, weigthMST = 0;
	for (int i = 0; i < g.numberOfVertex; i++){
		priorQ.insert(make_pair(key[i], i));
	}
	key[root] = 0;
	priorQ.erase(make_pair(INT_MAX, root));
	priorQ.insert(make_pair(key[root], root));
	while (!priorQ.empty()){
		curVert = priorQ.begin()->second;
		priorQ.erase(priorQ.begin());
		if (parent[curVert] != -1)
			weigthMST += key[curVert];
		for (int i = 0; i < g.listOfAdj[curVert].size(); i++){
			int AdjVert = g.listOfAdj[curVert][i].first;
			int AdjEdgeWeigth = g.listOfAdj[curVert][i].second;
			if (priorQ.find(make_pair(key[AdjVert], AdjVert)) != priorQ.end()){
				if (AdjEdgeWeigth < key[AdjVert]){
					int prevKey = key[AdjVert];
					parent[AdjVert] = curVert;
					key[AdjVert] = AdjEdgeWeigth;
					priorQ.erase(priorQ.find(make_pair(prevKey, AdjVert)));
					priorQ.insert(make_pair(key[AdjVert], AdjVert));
				}
			}
		}
	}
	return weigthMST;
}
int main(){	
	Graph g;
	fillGraph(g);
	int weigthOfMST = findMSTbyPrima(g);
	cout << weigthOfMST << endl;
	return 0;
}