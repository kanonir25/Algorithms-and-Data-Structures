#include <iostream>
#include <vector>

using namespace std;

enum colour{ white, gray, black };

struct Graph{
	int amount;
	vector<vector<int> > list;
};
void fillGraph(Graph& g){
	int n, m;
	int x, y;
	cin >> n >> m;
	g.amount = n;
	g.list.resize(n);
	for (int i = 0; i < m; i++){
		cin >> x >> y;
		--x, --y;
		g.list[x].push_back(y);
		g.list[y].push_back(x);
		}
}

void dfs_visit(const Graph& g, const int vert, vector<int>& col, vector<int>& par, bool& ifCircle){
	for (int i = 0; i < g.list[vert].size(); i++){
		if (col[g.list[vert][i]] != -1 && par[vert] != g.list[vert][i] && col[g.list[vert][i]] == col[vert]){
			ifCircle = true;
		}
		else if (col[g.list[vert][i]] == -1){
			par[g.list[vert][i]] = vert;
			if (col[vert] == 0)
				col[g.list[vert][i]] = 1;
			else
				col[g.list[vert][i]] = 0;
			dfs_visit(g, g.list[vert][i], col, par, ifCircle);
		}
	}
	col[vert] = 2;
}

bool DFS(const Graph& g){
	bool circle = false;
	vector<int> parent(g.amount, -1);
	vector<colour> col(g.amount, white);
	vector<int> paint(g.amount, -1);
	for (int i = 0; i < g.amount; i++)
		if (paint[i] == -1){
			paint[i] = 0;
			dfs_visit(g, i, paint, parent, circle);
		}
	return circle;
}
int main(){
	Graph g;
	fillGraph(g);
	bool ifCircle = DFS(g);
	if (!ifCircle)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}
