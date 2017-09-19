#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

enum colour { white, gray, black };
class Graph{
	int ** matrix;
	colour* color;
	int* parent;
	int* distance;
	int time;
	int size;
	queue<int> qq;
public:
	Graph(){
	}
	Graph(int **a, int n){
		time = 0;
		size = n;
		distance = new int[n];
		color = new colour[n];
		parent = new int[n];
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
			matrix[i] = new int[n];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++)
				matrix[i][j] = a[i][j];
			color[i] = white;
			parent[i] = -1;
			distance[i] = -1;
		}
	}
	void BFS(int v){
		color[v] = gray;
		distance[v] = time;
		qq.push(v);
		while (!qq.empty()){
			int u = qq.front();
			for (int i = 0; i < size; i++){
				if (matrix[u][i] == 1 && color[i] == white){
					parent[i] = u;
					distance[i] = distance[u] + 1;
					color[i] = gray;
					qq.push(i);
				}
			}
			//++time;
			color[u] = black;
			qq.pop();
		}
	}
	void bfs_result(int p){
		stack<int> stk;
		if (distance[p] == -1){
			cout << -1 << endl;
			return;
		}
		else if (!distance[p]){
			cout << 0 << endl;
			return;
		}
		cout << distance[p] << endl;
		int i = p;
		stk.push(++p);
		while (parent[i] != -1){
			stk.push(parent[i] + 1);
			i = parent[i];
		}
		while (!stk.empty()){
			cout << stk.top() << ' ';
			stk.pop();
		}
	}
};

int main(){
	int n, beg, end;
	cin >> n;
	int **a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	Graph gph(a, n);
	cin >> beg >> end;
	--beg, --end;
	gph.BFS(beg);
	gph.bfs_result(end);
	system("pause");
	return 0;
}