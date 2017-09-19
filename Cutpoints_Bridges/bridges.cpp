#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
enum colour{ white, gray, black };
#define vertex_t int
#define time_t int

struct Graph{
	int numberOfVertex;
	vector<vector<int> > edges;
	multimap<pair<vertex_t, vertex_t>, int > all_edges;
};

void fillGraph(Graph& g){
	int n, m;
	int v1, v2;
	cin >> n >> m;
	g.numberOfVertex = n;
	g.edges.resize(n);
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2;
		g.edges[v1 - 1].push_back(v2 - 1);
		g.edges[v2 - 1].push_back(v1 - 1);
		g.all_edges.insert(make_pair(make_pair(v1 - 1, v2 - 1), i));
	}
}

void dfs_visit(const Graph& g, const int curVert, vector<colour>& color, vector<time_t>& tin, vector<vertex_t>& parent, vector<time_t>& up, set<int>& bridges, int& time){
	color[curVert] = gray;
	tin[curVert] = ++time;
	up[curVert] = tin[curVert];
	for (int i = 0; i < g.edges[curVert].size(); i++){
		if (color[g.edges[curVert][i]] == gray && parent[curVert] != g.edges[curVert][i]){
			up[curVert] = min(up[curVert], tin[g.edges[curVert][i]]);
		}
		else if (color[g.edges[curVert][i]] == white){
			parent[g.edges[curVert][i]] = curVert;
			dfs_visit(g, g.edges[curVert][i], color, tin, parent, up, bridges, time);
			up[curVert] = min(up[curVert], up[g.edges[curVert][i]]);
			if (up[g.edges[curVert][i]] > tin[curVert]){
				multimap<pair<vertex_t, vertex_t>, int> ::const_iterator it = g.all_edges.find(make_pair(curVert, g.edges[curVert][i]));
				if (it == g.all_edges.end())
					it = g.all_edges.find(make_pair(g.edges[curVert][i], curVert));
				int forw = g.all_edges.count(make_pair(curVert, g.edges[curVert][i]));
				int backw = g.all_edges.count(make_pair(g.edges[curVert][i], curVert)); 
				if (forw + backw == 1) //проверяем наличие кратных ребер
					bridges.insert(it->second + 1);
			}
		}
	}
	color[curVert] = black;
}

set<int> DFS(const Graph& g){
	vector<colour> color(g.numberOfVertex, white);
	vector<time_t> tin(g.numberOfVertex, -1);
	vector<vertex_t> parent(g.numberOfVertex, -1);
	vector<time_t> up(g.numberOfVertex, INT_MAX);
	set<int> numberOfBridges;
	int time = 0;
	for (int i = 0; i < g.numberOfVertex; i++){
		if (color[i] == white)
			dfs_visit(g, i, color, tin, parent, up, numberOfBridges, time);
	}
	return numberOfBridges;
}

void printNumberOfBridges(const set<int>& bridge){
	cout << bridge.size() << endl;
	for (set<int>::iterator it = bridge.begin(); it != bridge.end(); it++)
		cout << *it << endl;
}


int main(){
	Graph g;
	fillGraph(g);
	set<int> bridges = DFS(g);
	printNumberOfBridges(bridges);
	system("pause");
	return 0;
}