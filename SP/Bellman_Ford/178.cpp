#include <iostream>
#include <vector>
#include <climits>
#define vertex_t int
#define weigth_t int
using namespace std;

struct Graph{
	int numberOfVertex;
	vector<pair<vertex_t, vertex_t> > edges;
	vector<weigth_t> weigth;
};

void fillGraph(Graph& g){
	int n, m;
	int v1, v2, w;
	cin >> n >> m;
	g.numberOfVertex = n;
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2 >> w;
		--v1, --v2;
		g.edges.push_back(make_pair(v1, v2));
		g.weigth.push_back(w);
	}
}
bool relax(const int u, const int v, vector<int>& d, const int weig){
	if (d[u] < INT_MAX && d[u] + weig < d[v]){
		d[v] = d[u] + weig;
		return true;
	}
	return false;
}


void printMinWeigths(const vector<int>& dist) {
	for (int i = 0; i < dist.size(); i++){
		if (dist[i] != INT_MAX)
			cout << dist[i] << ' ';
		else
			cout << 30000 << ' ';
	}
}
void doBellman_Ford(const Graph& g, vector<weigth_t>& weigths){
	vector<int> parent(g.numberOfVertex, -1);
	weigths[0] = 0;
	parent[0] = 0;
	for (int i = 0; i < g.numberOfVertex - 1; i++){
		for (int j = 0; j < g.edges.size(); j++){
			relax(g.edges[j].first, g.edges[j].second, weigths, g.weigth[j]);
		}
	}
}


int main(){
	Graph g;
	fillGraph(g);
	vector<weigth_t> weigths(g.numberOfVertex, INT_MAX);
	doBellman_Ford(g, weigths);
	printMinWeigths(weigths);
	return 0;
}