#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include <set>
enum colour{ white, gray, black };
#define vertex_t int
#define time_t int
using namespace std;

struct Graph{
	int numberOfTowers;
	int numberOfVertex;
	vector<vector<vertex_t> > edges;
};

void fillGraph(Graph& g){
	int n, m;
	int v1, v2, v3;
	cin >> n >> m;
	g.numberOfTowers = n;
	g.edges.resize(n + m);
	g.numberOfVertex = g.numberOfTowers + m;
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2 >> v3;
		g.edges[v1 - 1].push_back(n + i);
		g.edges[v2 - 1].push_back(n + i);
		g.edges[v3 - 1].push_back(n + i);
		g.edges[n + i].push_back(v1 - 1);
		g.edges[n + i].push_back(v2 - 1);
		g.edges[n + i].push_back(v3 - 1);

	}
}
void dfs_visit(const Graph& g, const int curVert, vector<colour>& color, vector<time_t>& tin, vector<vertex_t>& parent, vector<time_t>& up, int& time, set<vertex_t>& points, int isRoot = false){
	int children = 0;
	tin[curVert] = ++time;
	up[curVert] = tin[curVert];
	color[curVert] = gray;
	for (int i = 0; i < g.edges[curVert].size(); i++){
		if (color[g.edges[curVert][i]] == gray && parent[curVert] != g.edges[curVert][i]){
			up[curVert] = min(up[curVert], tin[g.edges[curVert][i]]);
		}
		if (color[g.edges[curVert][i]] == white){
			++children;
			parent[g.edges[curVert][i]] = curVert;
			dfs_visit(g, g.edges[curVert][i], color, tin, parent, up, time, points);
			up[curVert] = min(up[curVert], up[g.edges[curVert][i]]);
			if (!isRoot && up[g.edges[curVert][i]] >= tin[curVert])
				points.insert(curVert + 1);
		}
	}
	if (isRoot && children >= 2)
		points.insert(curVert + 1);
	color[curVert] = black;
}

set<int> DFS(const Graph& g){
	vector<colour> color(g.numberOfVertex, white);
	vector<time_t> tin(g.numberOfVertex, -1);
	vector<vertex_t> parent(g.numberOfVertex, -1);
	vector<time_t> up(g.numberOfVertex, INT_MAX);
	set<vertex_t> points;
	int time = 0;
	for (int i = 0; i < g.numberOfVertex; i++){
		if (color[i] == white)
			dfs_visit(g, i, color, tin, parent, up, time, points, true);
	}
	return points;
}

void printPoints(const set<int>& points, const int diff){
	int count = 0;
	for (set<int>::iterator it = points.begin(); it != points.end(); it++)
		if (*it - diff > 0)
			++count;
	cout << count << endl;
	for (set<int>::iterator it = points.begin(); it != points.end(); it++)
		if (*it - diff > 0)
			cout << *it - diff << endl;
}

int main(){
	Graph g;
	fillGraph(g);
	set<int> points = DFS(g);
	printPoints(points, g.numberOfTowers);
	return 0;
}