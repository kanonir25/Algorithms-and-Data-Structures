#include <iostream>
#include <vector>

struct Graph{
	short amount;
	std::vector<std::vector<bool> > matrix;
};

void fillGraph(Graph& g){
	short n;
	char c;
	std::cin >> n;
	g.amount = n;
	g.matrix.resize(g.amount);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			g.matrix[i].push_back(0);
	for (int i = 0; i < g.amount; i++)
		for (int j = 1; j < g.amount - i; j++){
		std::cin >> c;
		if (c == 'R')
			g.matrix[i][i + j] = 1;
		else
			g.matrix[i + j][i] = 1;
		}
}

void dfs_visit(const Graph& g, const short vert, std::vector<short>& col, bool& oneColor){
	col[vert] = 1;
	for (int i = 0; i < g.amount; i++){
		if (g.matrix[vert][i] && col[i] == 1){
			oneColor = false;
		}
		else if (g.matrix[vert][i] && col[i] == 0){
			dfs_visit(g, i, col, oneColor);
		}
	}
	col[vert] = 2;
}

bool DFS(const Graph& g){
	bool oneColor = true;
	std::vector<short> col(g.amount, 0);
	for (int i = 0; i < g.amount; i++)
		if (col[i] == 0){
			dfs_visit(g, i, col, oneColor);
		}
	return oneColor;
}
int main(){
	Graph g;
	fillGraph(g);
	bool oneColor = DFS(g);
	if (oneColor)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;
	return 0;
}