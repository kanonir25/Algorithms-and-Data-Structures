#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge{
	int begin;
	int time_b;
	int end;
	int time_e;
	Edge(int _beg = 0, int _tb = 0, int _end = 0, int _te = 0) : begin(_beg), time_b(_tb), end(_end), time_e(_te){}
};

struct Graph{
	int numberOfVertex;
	vector<Edge> edges;
};

bool relax(const int u, const int v, vector<int>& minTime, vector<int>& curTime, const int time_left, const int time_arr){
	if (minTime[u] < INT_MAX && time_left >= curTime[u] && minTime[v] > time_arr){
		minTime[v] = time_arr;
		curTime[v] = time_arr;
		return true;
	}
	return false;
}

vector<int> Ford_Bellman(const Graph& g, const int start, const int finish){
	int old_time = 0;
	vector<int> curTime(g.numberOfVertex, old_time);
	vector<int> minTime(g.numberOfVertex, INT_MAX);
	minTime[start] = old_time;
	for (int i = 0; i <= 1001; i++)
		for (int j = 0; j < g.edges.size(); j++)
			relax(g.edges[j].begin, g.edges[j].end, minTime, curTime, g.edges[j].time_b, g.edges[j].time_e);
	return minTime;
	}

pair<int, int> fillGraph(Graph& g){
	int n, start, finish, numOfEdges;
	int v1, v2, time1, time2;
	cin >> n >> start >> finish >> numOfEdges;
	g.numberOfVertex = n;
	for (int i = 0; i < numOfEdges; i++){
		cin >> v1 >> time1 >> v2 >> time2;
		g.edges.push_back(Edge(v1 - 1, time1, v2 - 1, time2));
	}
	return make_pair(start - 1, finish - 1);
}

int main(){
	Graph g;
	pair<int, int> destination = fillGraph(g);
	vector<int> result = Ford_Bellman(g, destination.first, destination.second);
	cout << result[destination.second] << endl;
	return 0;
}