#include <iostream>
#include <vector>

using namespace std;

pair<int,int> fillMatrix(vector<vector<int> >& matrix){
	int n, v1, v2;
	cin >> n >> v1 >> v2;
	matrix.resize(n);
	for (int i = 0; i < n; i++)
		matrix[i].resize(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrix[i][j];
	return make_pair(v1 - 1, v2 - 1);
}

void Floid(vector<vector<int> >& matrix){
	for (int k = 0; k < matrix.size(); k++)
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix.size(); j++)
				if (matrix[i][k] != -1 && matrix[k][j] != -1 && (matrix[i][j] != -1 && matrix[i][j] > matrix[i][k] + matrix[k][j] || matrix[i][j] == -1))
					matrix[i][j] = matrix[i][k] + matrix[k][j];
}

int main(){
	vector<vector<int> > matrix;
	pair<int, int> p;
	p = fillMatrix(matrix);
	Floid(matrix);
	cout << matrix[p.first][p.second] << endl;
	return 0;
}