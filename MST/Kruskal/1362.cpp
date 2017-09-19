#include <iostream>
#include <vector>
#include <set>

using namespace std;

class DSU{
	vector<int> representer;
	vector<int> weigth;
public:
	DSU(const int n){
		representer.resize(n);
		weigth.resize(n);
		for (int i = 0; i < n; i++)
			make_set(i);
	}
	void make_set(const int x){
		representer[x] = x;
		weigth[x] = 1;
	}
	int find_set(const int x){
		if (representer[x] == x)
			return x;
		return representer[x] = find_set(representer[x]);
	}
	bool union_sets(const int x, const int y){
		int a = find_set(x);
		int b = find_set(y);
		if (a != b){
			if (weigth[a] >= weigth[b]){
				representer[b] = a;
				weigth[a] += weigth[b];
			}
			else{
				representer[a] = b;
				weigth[b] += weigth[a];
			}
			return true;
		}
		return false;
	}

};

int  findTheLeastOfNumberBridges(DSU& dsu){
	int m;
	int v1, v2, numberOflastBridge = 0;
	cin >> m;
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2;
		if (dsu.union_sets(v1, v2))
			numberOflastBridge = i;
	}
	return numberOflastBridge + 1;
}

int main(){
	int n; 
	cin >> n;
	DSU dsu(n + 1);
	int number = findTheLeastOfNumberBridges(dsu);
	cout << number << endl;
	return 0;
}
