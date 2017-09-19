#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;

struct numbers{
	string given;
	int divident;
	set<int> digits;
};

void fillNumbers(numbers& num){
	string com;
	int k, number, x;
	cin >> com >> k >> number;
	num.given = com;
	num.divident = k;
	for (int i = 0; i < number; i++){
		cin >> x;
		num.digits.insert(x);
	}

}


void printPath(const numbers& Numb, const vector<int>& parent, vector<int>& add, int residue){
	int temp = 0;
	vector<int> path;
	while (temp != residue)
	{
		path.push_back(add[temp]);
		temp = parent[temp];
	}
	cout << Numb.given;
	for (int i = path.size() - 1; i >= 0; --i) 
		cout << path[i];
}

vector<int> BFS(numbers& Numb, vector<int>& add, int& residue) {
	queue<int> list;
	vector<int> parent(Numb.divident + 1, INT_MAX);
	vector<int> path;
	//
	for (int i = 0; i < Numb.given.size(); i++)
		residue = (residue * 10 + (Numb.given[i] - '0')) % Numb.divident; // pascal's principle
	list.push(residue);
	parent[residue] = -1;
	//
	while (list.size())
	{
		int u = list.front();
		list.pop();
		for (set<int>::iterator it = Numb.digits.begin(); it != Numb.digits.end(); it++)
		{
			int possible_residue = (u * 10  + *it) % Numb.divident;
			if (parent[possible_residue] == INT_MAX)
			{
				add[possible_residue] = *it;
				parent[possible_residue] = u;
				list.push(possible_residue);
				if (parent[0] != INT_MAX) break;
			}
		}
	}
	return parent;
};

int main() {
	numbers Numb;
	fillNumbers(Numb);
	int residue = 0;
	vector<int> add(Numb.divident + 1);
	vector<int> parent = BFS(Numb, add, residue);
	if (parent[0] == INT_MAX)
		cout << "-1" << endl;
	else
		printPath(Numb, parent, add, residue);
	return 0;
}