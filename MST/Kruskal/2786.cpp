#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class DSU{
	vector<int> parent;
	vector<int> weigth;
public:
	DSU(int n){
		parent.resize(n);
		weigth.resize(n);
		for (int i = 0; i < n; i++){
			make_set(i);
		}
	}
	void make_set(int x){
		parent[x] = x;
		weigth[x] = 1;
	}
	int find_set(int x){
		if (parent[x] == x)
			return x;
		return parent[x] = find_set(parent[x]);
	}
	void union_sets(int x, int y){
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

void printAnswer(stack<string>& s){
	while (!s.empty()){
		cout << s.top() << endl;
		s.pop();
	}
	system("pause");
}
void doCommands(){
	int n, m, numCom;
	int v1, v2;
	cin >> n >> m >> numCom;
	DSU dsu(n);
	stack<pair<string, pair<int, int> > > edges;
	stack<string> results;
	string command;
	for (int i = 0; i < m; i++){
		cin >> v1 >> v2;
	}
	for (int i = 0; i < numCom; i++){
		cin >> command >> v1 >> v2;
		--v1, --v2;
		edges.push(make_pair(command, make_pair(v1, v2)));
	}
	for (int i = 0; i < numCom; i++){
		if (edges.top().first == "cut"){
			dsu.union_sets(edges.top().second.first, edges.top().second.second);
		}
		else if (edges.top().first == "ask"){
			if (dsu.find_set(edges.top().second.first) != dsu.find_set(edges.top().second.second))
				results.push("NO");
			else
				results.push("YES");
		}
		edges.pop();
	}
	printAnswer(results);
}

int main(){
	doCommands();
	return 0;
}