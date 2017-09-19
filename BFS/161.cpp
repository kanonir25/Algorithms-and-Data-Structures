#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
enum colour{white, gray};

using namespace std;

struct chessTable{
	int size;
	pair<int, int> begin;
	pair<int, int> end;
};



void fillData(chessTable& ct){
	int n;
	cin >> n;
	ct.size = n;
	int x1, x2, y1, y2;
	cin >> x1 >> y1;
	cin >> x2 >> y2;
	--x1, --x2, --y1, --y2;
	ct.begin = make_pair(x1, y1);
	ct.end = make_pair(x2, y2);
}

void printPath (const pair<int, int>& cury, const vector<vector<pair<int, int> > >& par, const chessTable& t){
	vector<pair<int, int> > ans;
	pair<int, int> cur = cury;
	while (cur != t.begin){
		ans.push_back(make_pair(cur.first, cur.second));
		cur = par[cur.first][cur.second];
	}
	cout << t.begin.first + 1 << ' ' << t.begin.second + 1 << endl;
	for (int i = ans.size() - 1; i >= 0; i--){
		cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << endl;
	}
}

void BFS(const chessTable& t){
	int distance = 0;
	vector<vector<colour> > col(t.size);
	vector<vector<int> > dist(t.size);
	vector<vector<pair<int, int> > > parent(t.size);
	for (int i = 0; i < t.size; i++){
		col[i].resize(t.size);
		dist[i].resize(t.size);
		parent[i].resize(t.size);
	}
	queue<pair<int, int> > q;
	q.push(t.begin);
	dist[t.begin.first][t.begin.second] = 0;
	while (!q.empty()){
		pair<int, int> cur = q.front();
		if (cur == t.end){
			cout << dist[cur.first][cur.second] << endl;
			printPath(cur, parent, t);
			break;
		}
		for (int i = -2; i <= 2; i++)
			for (int j = -2; j <= 2; j++)
				if (abs(i) + abs(j) == 3 && cur.first + i < t.size && cur.first + i >= 0 && cur.second + j < t.size && cur.second + j >= 0 && col[cur.first + i][cur.second + j] != gray){
						q.push(make_pair(cur.first + i, cur.second + j));
						dist[cur.first + i][cur.second + j] = dist[cur.first][cur.second] + 1;
						col[cur.first + i][cur.second + j] = gray;
						parent[cur.first + i][cur.second + j] = cur;
				}
		q.pop();
	}
}
int main(){
	chessTable ct;
	fillData(ct);
	BFS(ct);
	return 0;
}  