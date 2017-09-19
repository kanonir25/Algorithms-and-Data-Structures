#include <iostream>
#include <vector>
#include <cstdio>
#include <climits>
#define vertex_t int

using namespace std;

struct infoAboutTravel{
	int home;
	int destination;
	int nights;
	infoAboutTravel(vertex_t v1, vertex_t v2, int night){
		home = v1;
		destination = v2;
		nights = night;
	}
};

struct Graph{
	int numberOfVertex;
	vector<pair<vertex_t, vertex_t> > edges;
	vector<int> weigth;
};

infoAboutTravel fillGraph(Graph& g){
	int numOfCities, numOfRaces, amountOfNights, liveCity, destCity;
	int from, to, cost;
	cin >> numOfCities >> numOfRaces >> amountOfNights >> liveCity >> destCity;
	g.numberOfVertex = numOfCities;
	for (int i = 0; i < numOfRaces; i++){
		cin >> from >> to >> cost;
		g.edges.push_back(make_pair(from - 1, to - 1));
		g.weigth.push_back(cost);
	}
	return infoAboutTravel(liveCity - 1, destCity - 1, amountOfNights);
}

bool relax(const int u, const int v, vector<int>& old_costs, vector<int>& new_costs, const int weig){
	if (old_costs[u] < INT_MAX && old_costs[u] + weig < new_costs[v]){
		new_costs[v] = old_costs[u] + weig;
		return true;
	}
	return false;
}

vector<int> Bellman_Ford(const Graph& g, const int beg, const int fin, const int nigths){
	vector<int> old_costs(g.numberOfVertex, INT_MAX);
	vector<int> new_costs(g.numberOfVertex, INT_MAX);
	vector<int> longer(g.numberOfVertex, 0);
	old_costs[beg] = 0;
	for (int i = 0; i < nigths; i++){
		for (int j = 0; j < g.edges.size(); j++){
			relax(g.edges[j].first, g.edges[j].second, old_costs, new_costs, g.weigth[j]);
		}
		copy(new_costs.begin(), new_costs.end(), old_costs.begin());
	}
	return new_costs;
}


int main(){
	Graph g;
	infoAboutTravel info = fillGraph(g);
	vector<int> costs = Bellman_Ford(g, info.home, info.destination, info.nights);
	if (costs[info.destination] < INT_MAX)
		cout << costs[info.destination] << endl;
	else
		cout << -1 << endl;
	return 0;
}
