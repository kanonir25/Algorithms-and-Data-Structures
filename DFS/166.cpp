#include <iostream>
#include <deque>
using namespace std;
enum colour{ white, gray, black };

class graph{
	int **matrix;
	colour *col;
	time_t time;
	time_t *d;
	time_t *f;
	deque<int> topsort;
	int *parent;
	int vertex;
	bool tree;
public:
	graph(){}
	graph(int ** a, int n){
		vertex = n;
		tree = true;
		parent = new int[n];
		col = new colour[n];
		d = new time_t[n];
		f = new time_t[n];
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
			matrix[i] = new int[n];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++)
				matrix[i][j] = a[i][j];
			col[i] = white;
			d[i] = 0;
			f[i] = 0;
			parent[i] = 0;
		}
	}
	void dfs_visit(int vert){
		col[vert] = gray;
		d[vert] = ++time;
		for (int i = 0; i < vertex; i++){
			if (matrix[vert][i] == 1 && col[i] == gray){
				tree = false;
			}
			else if (matrix[vert][i] == 1 && col[i] == white){
				parent[i] = vert;
				dfs_visit(i);
			}
		}
		col[vert] = black;
		if (tree)
			topsort.push_front(vert);
		f[vert] = ++time;
	}
	void dfs(){
		time = 0;
		for (int i = 0; i < vertex; i++){
			if (col[i] == white)
				dfs_visit(i);
		}
	}
	int adj(){
		int freqq = 0;
		for (int i = 0; i < vertex; i++)
			if (col[i] == black)
				++freqq;
		return freqq;
	}
	bool get_tree(){
		return tree;
	}
	deque <int> get_tops(){
		return topsort;
	}
	bool isTop(){
		return tree;
	}
	void printTop(){
		int siz = topsort.size();
		cout << "Yes" << endl;
		for (int i = 0; i < siz; i++){
			cout << ++topsort.front() << ' ';
			topsort.pop_front();
		}
	}
};

int main(){
	int n, kol, x, y;
	cin >> n >> kol;
	deque<int> tops;
	int **a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = 0;
	for (int i = 0; i < kol; i++){
		cin >> x >> y;
		--x, --y;
		a[x][y] = 1;
	}
	graph gph(a, n);
	gph.dfs();
	if (gph.isTop())
		gph.printTop();
	else
		cout << "No" << endl;
	system("pause");
	return 0;
}