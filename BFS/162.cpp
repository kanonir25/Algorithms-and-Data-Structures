#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

struct Table{
	int width;
	int heigth;
	vector<vector<bool> > matrix;
};

void fillTable(Table& t){
	int n, m;
	bool x;
	cin >> n >> m;
	t.heigth = n;
	t.width = m;
	t.matrix.resize(t.heigth);
	for (int i = 0; i < t.heigth; i++)
		t.matrix[i].resize(t.width);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			cin >> x;
			t.matrix[i][j] = x;
		}
}

void doBfs(int X, int Y, Table& t, vector<vector<int> >& dist){
	queue<pair<int, int> > q;
	q.push(make_pair(X, Y));
	while (!q.empty()){
		int curX = q.front().first;
		int curY = q.front().second;
		for (int i = -1; i <= 1; i++){
			for (int j = -1; j <= 1; j++){
				if (abs(i) + abs(j) == 1 && curX + i >= 0 && curX + i < t.heigth && curY + j >= 0 && curY + j < t.width && t.matrix[curX + i][curY + j] != 1 && dist[curX + i][curY + j] > dist[curX][curY] + 1){
					dist[curX + i][curY + j] = dist[curX][curY] + 1;
					q.push(make_pair(curX + i, curY + j));
				}
			}
		}
		q.pop();
	}
}

void printAns(const vector<vector<int> > dist){
	for (int i = 0; i < dist.size(); i++){
		for (int j = 0; j < dist[i].size(); j++)
			cout << dist[i][j] << ' ';
		cout << endl;
	}
}

void BFS(Table& t){
	vector<vector<int> > distance(t.heigth);
	for (int i = 0; i < t.heigth; i++)
		for (int j = 0; j < t.width; j++)
			distance[i].push_back(INT_MAX);
	for (int i = 0; i < t.heigth; i++)
		for (int j = 0; j < t.width; j++)
			if (t.matrix[i][j] == 1){
				distance[i][j] = 0;
				doBfs(i, j, t, distance);
		}
	printAns(distance);
}

int main(){
	Table t;
	fillTable(t);
	BFS(t);
//	system("pause");
	return 0;
}