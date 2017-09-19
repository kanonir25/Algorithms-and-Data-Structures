#include <iostream>
#include <vector>
#define weigth_t int
using namespace std;

class DSU{
	vector<int> parent;
	vector<int> weigth;
	vector<int> weigthEdges;
public:
	DSU(const int n){
		parent.resize(n);
		weigth.resize(n);
		for (int i = 0; i < n; i++){
			make_set(i);
		}
	}
	void make_set(const int x){
		parent[x] = x;
		weigth[x] = 1;
	}
	int find_set(const int x){
		if (parent[x] == x)
			return x;
		return parent[x] = find_set(parent[x]);
	}
	void union_sets(const int x, const int y){
		int a = find_set(x);
		int b = find_set(y);
		if (weigth[a] > weigth[b]){
			parent[b] = a;
			weigth[a] += weigth[b];
		}
		else{
			parent[a] = b;
			weigth[b] += weigth[a];
		}
	}
};

void addEdge(DSU& dsu, vector<weigth_t>& weigComp){
	int v1, v2, w;
	cin >> v1 >> v2 >> w;
	--v1, --v2;
	if (dsu.find_set(v1) != dsu.find_set(v2)){
		int fv1 = dsu.find_set(v1);
		int fv2 = dsu.find_set(v2);
		dsu.union_sets(v1, v2);
		if (dsu.find_set(v1) == fv1){
			weigComp[fv1] += weigComp[fv2];
			weigComp[fv2] = 0;
		}
		else {
			weigComp[fv2] += weigComp[fv1];;
			weigComp[fv1] = 0;
		}
	}
	else
		dsu.union_sets(v1, v2);
	weigComp[dsu.find_set(v1)] += w;
}

void printRepres(DSU& dsu, const vector<weigth_t>& weigComp){
	int x;
	cin >> x;
	int repres = dsu.find_set(x - 1);
	cout << weigComp[repres] << endl;
}

/*void doCommands(){
	int n, m;
	int com, x, repres;
	cin >> n >> m;
	DSU dsu(n);
	vector<weigth_t> weigComp(n, 0);
	for (int i = 0; i < m; i++){
		cin >> com;
		if (com == 1)
			addEdge(dsu, weigComp);
		else if (com == 2)
			printRepres(dsu, weigComp);
	}
}*/

int main(){
	int n, m;
	int command;
	cin >> n >> m;
	DSU dsu(n);
	vector<weigth_t> weigComp(n, 0);
	for (int i = 0; i < m; i++){
		cin >> command;
		if (command == 1)
			addEdge(dsu, weigComp);
		else if (command == 2)
			printRepres(dsu, weigComp);
	}
	//doCommands();
	return 0;
}