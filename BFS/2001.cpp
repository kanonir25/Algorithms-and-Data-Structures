#include <iostream>
#include <vector>
#include <queue>
using namespace std;

pair<int, int> fillData(){
	int begin, end;
	cin >> begin >> end;
	return make_pair(begin, end);
}

inline int shiftRight(const int& vert){
	return vert % 10 * 1000 + vert / 1000 * 100 + vert / 100 % 10 * 10 + vert % 100 / 10;
}

inline int shiftLeft(const int& vert){
	return vert / 1000 + vert / 100 % 10 * 1000 + vert % 100 / 10 * 100 + vert % 10 * 10;
}


vector<int> BFS(int beg, int fin){
	vector<bool> used(10000, false);
	vector<int> parent(10000, -1);
	queue<int> numbers;
	used[beg] = true;
	bool isFound = false;
	numbers.push(beg);
	while (!isFound){
		int curNumber = numbers.front();
		numbers.pop();
		for (int i = 0; i < 4; i++){
			if (i == 0 && curNumber / 1000 != 9 && !used[curNumber + 1000]){
				if (curNumber + 1000 == fin){
					isFound = true;
				}
				else{
					numbers.push(curNumber + 1000);
					used[curNumber + 1000] = true;
				}
				parent[curNumber + 1000] = curNumber;
			}
			if (i == 1 && curNumber % 10 != 1 && !used[curNumber - 1]){
				if (curNumber - 1 == fin){
					isFound = true;
				}
				else{
					numbers.push(curNumber - 1);
					used[curNumber - 1] = true;
				}
				parent[curNumber - 1] = curNumber;
			}
			if (i == 2){
				int sL = shiftLeft(curNumber);
				//int sR = shiftRight(curNumber);
				if (!used[sL]){
					if (sL == fin){
						isFound = true;
					}
					else{
						numbers.push(sL);
						used[sL] = true;
					}
					parent[sL] = curNumber;
				}
			}
			if (i == 3){
				int sR = shiftRight(curNumber);
				if (!used[sR]){
					if (sR == fin){
						isFound = true;
					}
					else{
						numbers.push(sR);
						used[sR] = true;
					}
					parent[sR] = curNumber;
				}
			}
		}
	}
	return parent;
}

void printSequence(const vector<int>& seq, const int& beg, const int& fin){
	vector<int> answer;
	answer.push_back(fin);
	int prev = seq[fin];
	while (prev != -1){
		//cout << prev << endl;
		answer.push_back(prev);
		prev = seq[prev];
	}
	for (int i = answer.size() - 1; i >= 0; i--)
		cout << answer[i] << endl;
}

int main(){
	pair<int, int> data = fillData();
	vector<int> sequenceNumbers = BFS(data.first, data.second);
	printSequence(sequenceNumbers, data.first, data.second);
//	system("pause");
	return 0;
}