#include <iostream>
#include <vector>

using namespace std;

enum colour{white, gray, black};

struct Graph{
	int amount;
	vector<vector<bool> > matrix;
};
void fillGraph(Graph& g){
	int n;
	bool x;
	cin >> n;
	g.amount = n;
	g.matrix.resize(n);
	for (int i = 0; i < n; i++)
		g.matrix[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++){
			cin >> x;
			g.matrix[i][j] = x;
	}
}

void dfs_visit(const Graph& g, const int vert, vector<colour>& col, vector<int>& par, bool& ifCircle){
	col[vert] = gray;
	for (int i = 0; i < g.amount; i++){
		if (g.matrix[vert][i] && col[i] == gray){
			ifCircle = true;
			break;
		}
		else if (g.matrix[vert][i] && col[i] == white){
			par[i] = vert;
			dfs_visit(g, i, col, par, ifCircle);
		}
	}
	col[vert] = black;
}

bool DFS(const Graph& g){
	bool circle = false;
	vector<int> parent(g.amount, -1);
	vector<colour> col(g.amount, white);
	for (int i = 0; i < g.amount; i++){
		if (col[i] == white)
			dfs_visit(g, i, col, parent, circle);
	}
	return circle;
}

int main(){
	Graph g;
	fillGraph(g);
	bool ifCircle = DFS(g);
	if (ifCircle)
		cout << 1 << endl;
	else
		cout << 0 << endl;
	return 0;
}