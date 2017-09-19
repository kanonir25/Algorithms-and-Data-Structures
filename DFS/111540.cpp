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
	int *Comp;
	int freqComp; //колво компонент связности
	int vertex; 
public:
	graph(){}
	graph(int ** a, int n){
		vertex = n;
		col = new colour[n];
		freqComp = 0;
		d = new time_t[n];
		f = new time_t[n];
		Comp = new int[n];
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
			matrix[i] = new int[n];
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++)
				matrix[i][j] = a[i][j];
			col[i] = white;
			d[i] = 0;
			f[i] = 0;
			Comp[i] = -1;
		}
	}
	void dfs_visit(int vert){
		col[vert] = gray;
		Comp[vert] = freqComp;
		d[vert] = ++time;
		for (int i = 0; i < vertex; i++){
			if (matrix[vert][i] == 1 && col[i] == white){
				dfs_visit(i);
			}
		}
		col[vert] = black;
		f[vert] = ++time;
	}
	void dfs(){
		time = 0;
		for (int i = 0; i < vertex; i++){
			if (col[i] == white){
				dfs_visit(i);
				++freqComp;
			}
		}
	}
	int adj(){
		int freqq = 0;
		for (int i = 0; i < vertex; i++)
			if (col[i] == black)
				++freqq;
		return freqq;
	}
	friend ostream& operator << (ostream& os, const graph& gph){
		deque<int> d;
		for (int i = 0; i < gph.freqComp; i++){
			for (int j = 0; j < gph.vertex; j++){
				if (gph.Comp[j] == i)
					d.push_back(j);
			}
			os << d.size() << endl;
			int cap = d.size();
			for (int k = 0; k < cap; k++){
				os << ++d.front() << ' ';
				d.pop_front();
			}
			cout << endl;
			d.clear();
		}
		return os;
	}
	int get_freqComp(){
		return freqComp;
	}
};

int main(){
	int n, pair;
	int x, y;
	cin >> n >> pair;
	int **a = new int*[n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = 0;
	for (int i = 0; i < pair; i++){
		cin >> x >> y;
		--x, --y;
		a[x][y] = 1;
		a[y][x] = 1;
	}
	graph gph(a, n);
	gph.dfs();
	cout << gph.get_freqComp() << endl;
	cout << gph;
	for (int i = 0; i < n; i++)
		delete[]a[i];
	delete[]a;
	system("pause");
	return 0;
}