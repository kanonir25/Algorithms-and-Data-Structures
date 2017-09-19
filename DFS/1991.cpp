#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <functional>
#include <climits>
#define MIT map<int, int> :: iterator
using namespace std;

enum colour{white, gray, black};

struct Graph{
	int amount;
	vector<vector<int> > list;
};

void fillGraph(Graph& g, vector<vector<int> >& transpList){
	int n, m;
	int v1, v2;
	cin >> n >> m;
	g.amount = n;
	g.list.resize(n);
	transpList.resize(n);
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2;
		g.list[v1 - 1].push_back(v2 - 1);
		transpList[v2 - 1].push_back(v1 - 1);
	}
}

bool transpose(Graph& g, const vector<vector<int> >& transp){
	for (int i = 0; i < g.amount; i++)
		g.list[i].clear();
	g.list.resize(g.amount);
	for (int i = 0; i < transp.size(); i++)
		for (int j = 0; j < transp[i].size(); j++)
			g.list[i].push_back(transp[i][j]);
	return true;
}

void dfs_visit(const Graph& g, const int vert, vector<colour>& col, vector<int>& par, map<int, int, greater<int> >& tout, int& time, vector<int>& includesComp, bool ifTransp = false, int amountComp = 0){
	col[vert] = gray;
	if (ifTransp == 1)
		includesComp[vert] = amountComp;
	for (int j = 0; j < g.list[vert].size(); j++){
		if (col[g.list[vert][j]] == white){
			par[g.list[vert][j]] = vert;
			dfs_visit(g, g.list[vert][j], col, par, tout, time, includesComp, ifTransp, amountComp);
		}
	}
	col[vert] = black;
	tout.insert(make_pair(++time, vert));
}

void printAns(const int numberOfComp, const vector<int>& components){
	cout << numberOfComp << endl;
	for (int i = 0; i < components.size();  i++){
			cout << components[i] + 1 << ' ';
	}
}

void DFS(const Graph& g, map<int, int, greater<int> >& tOut,bool ifTransposed = false){
	vector<colour> color(g.amount, white);
	vector<int> parent(g.amount, -1);
	vector<int> includesOfComp(g.amount);
	int amountComponentsOfStrongS = 0;
	int time = 0;
	if (!ifTransposed){
		for (int i = 0; i < g.amount; i++){
			if (color[i] == white)
				dfs_visit(g, i, color, parent, tOut, time, includesOfComp);
		}
	}
	else
		for (MIT it = tOut.begin(); it != tOut.end(); it++)
			if (color[it->second] == white){
				dfs_visit(g, it->second, color, parent, tOut, time, includesOfComp, ifTransposed, amountComponentsOfStrongS);
				++amountComponentsOfStrongS;
			}
	if (ifTransposed)
		printAns(amountComponentsOfStrongS, includesOfComp);
}

int main(){
	Graph g;
	vector<vector<int> > transposeList;
	map<int, int, greater<int> > tOut;
	fillGraph(g, transposeList);
	DFS(g, tOut);
	bool ifTransposed = transpose(g, transposeList);
	DFS(g, tOut, ifTransposed);
	//system("pause");
	return 0;
}