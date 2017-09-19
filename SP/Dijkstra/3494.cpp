#include <iostream>
#include <vector>
#include <set>
#include <climits>
using namespace std;

#define vertex_t int

struct Edge{
	vertex_t end;
	int weigth;
	Edge(int _end = 0, int _weigth = 0) : end(_end), weigth(_weigth){}
};

struct Graph{
	int numberOfVertex;
	vector<vector<Edge> > listOfAdj;
};

vertex_t fillGraph(Graph& g){
	int n, m, root;
	int v1, v2, w;
	cin >> n >> m;
	g.numberOfVertex = n;
	g.listOfAdj.resize(n);
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2 >> w;
		g.listOfAdj[v1].push_back(Edge(v2, w));
		g.listOfAdj[v2].push_back(Edge(v1, w));
	}
	cin >> root;
	return root;
}

bool relax(const int u, const int v, const int weigth, vector<int>& distance, multiset<pair<vertex_t, vertex_t> >& cmp){
	if (distance[u] < INT_MAX && distance[v] > distance[u] + weigth){
		distance[v] = distance[u] + weigth;
		if (!cmp.empty())
			cmp.insert(make_pair(distance[v], v));
		return true;
	}
	return false;
}

vector<vertex_t> Dejkstra(const Graph& g, const int root){
	vector<int> distance(g.numberOfVertex, INT_MAX);
	vector<bool> used(g.numberOfVertex, false);
	multiset<pair<vertex_t, vertex_t> > cmpDistance;
	for (int i = 0; i < g.listOfAdj[root].size(); i++)
		distance[g.listOfAdj[root][i].end] = g.listOfAdj[root][i].weigth;
	distance[root] = 0;
	for (int i = 0; i < g.numberOfVertex; i++)
		cmpDistance.insert(make_pair(distance[i], i));

	for (int i = 0; i < g.numberOfVertex - 1; i++){
		while (used[cmpDistance.begin()->second]){
			cmpDistance.erase(cmpDistance.begin());
		}
		int curVert = cmpDistance.begin()->second;
		int curWeigth = cmpDistance.begin()->first;
		used[curVert] = true;
		cmpDistance.erase(cmpDistance.begin());
		for (int i = 0; i < g.listOfAdj[curVert].size(); i++)
			if (!used[g.listOfAdj[curVert][i].end])
				relax(curVert, g.listOfAdj[curVert][i].end, g.listOfAdj[curVert][i].weigth, distance, cmpDistance);
	}
	return distance;
}

void printDistance(const vector<int>& arr){
	for (int i = 0; i < arr.size(); i++)
		if (arr[i] < INT_MAX)
			cout << arr[i] << ' ';
		else
			cout << 2009000999 << ' ';
	cout << endl;
}


int main(){
	Graph g;
	int numOfBlocks;
	cin >> numOfBlocks;
	for (int i = 0; i < numOfBlocks; i++){
		int root = fillGraph(g);
		vector<vertex_t> arrayOfDistance = Dejkstra(g, root);
		printDistance(arrayOfDistance);
		g.listOfAdj.clear();
	}
	return 0;
}