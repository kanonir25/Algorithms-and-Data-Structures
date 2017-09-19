#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

struct Graph{
	int numberOfVertex;
	vector<vector<int> > matrixOfAdj;
};

pair<int, int> fillGraph(Graph& g){
	int n;
	int start, finish;
	cin >> n >> start >> finish;
	g.numberOfVertex = n;
	g.matrixOfAdj.resize(n);
	for (int i = 0; i < n; i++)
		g.matrixOfAdj[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> g.matrixOfAdj[i][j];
	return make_pair(start - 1, finish - 1);
}

bool relax(const int u, const int v, const Graph& g, vector<int>& dist, vector<int>& prev){
	if (dist[u] < INT_MAX && u != v && g.matrixOfAdj[u][v] != -1 && dist[u] + g.matrixOfAdj[u][v] < dist[v]){
		dist[v] = dist[u] + g.matrixOfAdj[u][v];
		prev[v] = u;
		return true;
	}
	return false;
}

vector<int> Dejkstra(const Graph& g, const int beg){
	vector<int> dist(g.numberOfVertex, INT_MAX);
	vector<int> prev(g.numberOfVertex, -1);
	for (int i = 0; i < g.numberOfVertex; i++){
		if (g.matrixOfAdj[beg][i] != -1 && i != beg){
			dist[i] = g.matrixOfAdj[beg][i];
			prev[i] = beg;
		}
	}
	dist[beg] = 0;
	vector<bool> isUsed(g.numberOfVertex, false);
	multiset<pair<int, int> > dista;
	for (int i = 0; i < g.numberOfVertex; i++)
		dista.insert(make_pair(dist[i], i));

	for (int i = 0; i < g.numberOfVertex - 1; i++){
		int curVert = dista.begin()->second;
		int curWeigth = dista.begin()->first;
		isUsed[curVert] = true;
		dista.erase(dista.begin());
		for (int i = 0; i < g.numberOfVertex; i++){ 
			if (!isUsed[i])
				relax(curVert, i, g, dist, prev);
		}
		dista.clear();
		for (int i = 0; i < g.numberOfVertex; i++)
			if (!isUsed[i])
				dista.insert(make_pair(dist[i], i));

	}
	return prev;
}

void printPath(const vector<int>& prev, const int finish, const int start){
	vector<int> path;
	int fin = finish;
	if (fin == start){
		cout << fin + 1;
		return;
	}
	if (prev[fin] == -1){
		cout << -1;
		return;
	}
	path.push_back(fin + 1);
	while (prev[fin] != -1){
		path.push_back(prev[fin] + 1);
		fin = prev[fin];
	}
	for (int i = path.size() - 1; i >= 0; i--)
		cout << path[i] << ' ';
}

int main(){
	Graph g;
	pair<int, int> destination = fillGraph(g);
	vector<int> matrixOfPrev = Dejkstra(g, destination.first);
	printPath(matrixOfPrev, destination.second, destination.first);
	return 0;
}