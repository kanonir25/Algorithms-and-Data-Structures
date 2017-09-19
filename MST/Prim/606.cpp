#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <climits>

#define vertex_t int
#define weigth_t int
using namespace std;

struct Graph{
	int number;
	vector<vector<int> > matrixOfWeigth;
};

void fillGraph(Graph& g){
	int n;
	cin >> n;
	g.number = n;
	g.matrixOfWeigth.resize(n);
	for (int i = 0; i < n; i++)
		g.matrixOfWeigth[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> g.matrixOfWeigth[i][j];
}

int findMST(Graph& g){
	int head = 0;
	int weigthMST = 0;
	vector<bool> isUsed(g.number, false);
	multimap<weigth_t, vertex_t> priorQ;
	vector<int> key(g.number, INT_MAX);
	for (int i = 0; i < g.number; i++)
		priorQ.insert(make_pair(key[i], i));
	priorQ.insert(make_pair(0, head));
	while (!priorQ.empty()){
		if (isUsed[priorQ.begin()->second]){
			priorQ.erase(priorQ.begin());
			continue;
		}
		int curVert = priorQ.begin()->second;
		int curWeigth = priorQ.end()->first;
		weigthMST += curWeigth;
		priorQ.erase(priorQ.begin());
		for (int i = 0; i < g.number; i++)
			if (!isUsed[i] && key[i] > g.matrixOfWeigth[curVert][i]){
				key[i] = g.matrixOfWeigth[curVert][i];
				priorQ.insert(key[i], i);
			}
	}
	return weigthMST;
}

int main(){
	Graph g;
	fillGraph(g);
	cout << findMST(g) << endl;
	return 0;
}