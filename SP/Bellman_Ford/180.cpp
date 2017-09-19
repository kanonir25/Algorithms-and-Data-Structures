#include <iostream>
#include <vector>
#include <queue>
#define weigth_t int
#define vertex_t int
using namespace std;

struct Graph{
	int numberOfVertex;
	vector<vector<weigth_t> > matrixOfAdj;
};

void fillGraph(Graph& g){
	int n;
	cin >> n;
	g.numberOfVertex = n;
	g.matrixOfAdj.resize(n);
	for (int i = 0; i < n; i++)
		g.matrixOfAdj[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> g.matrixOfAdj[i][j];
}
bool relax(const int u, const int v, vector<int>& par, vector<int>& dist, const Graph& g){
	if (dist[v] > dist[u] + g.matrixOfAdj[u][v]){
		dist[v] = dist[u] + g.matrixOfAdj[u][v];
		par[v] = u;
		return true;
	}
	return false;
}

void findCircle(const Graph& g, const int vert, const vector<int>& par){
	int startCircle = vert;
	for (int i = 0; i < g.numberOfVertex; i++){
		startCircle = par[startCircle];
	}
	vector<int> circle;
	circle.push_back(startCircle);
	int curVert = par[startCircle];
	while (curVert != startCircle){
		circle.push_back(curVert);
		curVert = par[curVert];
	}
	circle.push_back(curVert);
	cout << circle.size() << endl;
	for (int i = circle.size() - 1; i >= 0; i--)
		cout << circle[i] + 1 << ' ';
}

pair<bool, vertex_t> doFordBellman(const Graph& g, vector<vertex_t>& parent){
	vector<int> dist(g.numberOfVertex, 100000);
	int source = 0;
	dist[source] = 0;
	for (int i = 0; i < g.numberOfVertex - 1; i++)
		for (int k = 0; k < g.numberOfVertex; k++)
			for (int j = 0; j < g.numberOfVertex; j++){
				if (g.matrixOfAdj[k][j] != 100000)
					relax(k, j, parent, dist, g);
			}
	int vertOfRelaxedEdge = -1;
	for (int k = 0; k < g.numberOfVertex; k++)
		for (int j = 0; j < g.numberOfVertex; j++){
			if (g.matrixOfAdj[k][j] != 100000 && relax(k, j, parent, dist, g)){
				vertOfRelaxedEdge = j;
				k = g.numberOfVertex;
				break;
			}
		}
	if (vertOfRelaxedEdge == -1)
		return make_pair(false, -1);
	else
		return make_pair(true, vertOfRelaxedEdge);
}

int main(){
	Graph g;
	fillGraph(g);
	vector<vertex_t> parent(g.numberOfVertex, 0);
	pair<bool, vertex_t> ifCircle = doFordBellman(g, parent);
	if (!ifCircle.first)
		cout << "NO" << endl;
	else{
		cout << "YES" << endl;
		findCircle(g, ifCircle.second, parent);
	}
	return 0;
}