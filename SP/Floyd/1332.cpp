#include<iostream>
#include <vector>

using namespace std;

struct Graph{
	int amount;
	vector<vector<int> > matrix;
};

void fillGraph(Graph& g){
	int n;
	cin >> n;
	g.amount = n;
	g.matrix.resize(n);
	for (int i = 0; i < n; i++)
		g.matrix[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> g.matrix[i][j];
}

void printAnswer(const vector<vector<int> >& matrix){
	for (int i = 0; i < matrix.size(); i++){
		for (int j = 0; j < matrix.size(); j++)
			if (i == j || matrix[i][j])
				cout << 1 << ' ';
			else
				cout << 0 << ' ';
		cout << endl;
	}
}

vector<vector<int> > Floyd(const Graph& g){
	vector<vector<int> > matrix(g.amount, vector<int>(g.amount, 0));
	for (int i = 0; i < g.amount; i++)
		for (int j = 0; j < g.amount; j++)
			if (i != j)
				matrix[i][j] = g.matrix[i][j];
	for (int k = 0; k < g.amount; k++)
		for (int i = 0; i < g.amount; i++)
			for (int j = 0; j < g.amount; j++)
				if (!matrix[i][j] && matrix[i][k] && matrix[k][j])
					matrix[i][j] = matrix[i][k] + matrix[k][j];
	return matrix;
}

int main(){
	Graph g;
	fillGraph(g);
	vector<vector<int> > answer = Floyd(g);
	printAnswer(answer);
	return 0;
}