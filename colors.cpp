#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
#include <set>
using namespace std;
#define ld long double
enum womenLogic { FALSE, MAYBE, TRUE };
int n;
string ans;
vector<vector<vector<int> > > criticals;
vector<vector<int> > quadraples;

void init() {

	criticals.resize(n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				for (int x = 0; x < n; ++x) {
		if (i == j) continue;
		if (i == k) continue;
		if (i == x) continue;
		if (j == k) continue;
		if (j == x) continue;
		if (k == x) continue;
		if (i + j + k == 3 * x) {
			criticals[i].push_back({ j, k, x });
			criticals[j].push_back({ i, k, x });
			criticals[k].push_back({ i, j, x });
			criticals[x].push_back({ i, j, k });
			if (i < j && j < k)
				quadraples.push_back({ i, j, k, x });
		}
				}
}

int choice(vector<int>& A, vector<int>& B, vector<int>& C, set<int>& availableQuadraples) {

	vector<int> possibleNumbers;
	for (int i = 0; i < n; ++i)
		if (A[i] != TRUE && B[i] != TRUE && C[i] != TRUE)
			possibleNumbers.push_back(i);

	pair<int, int> bestPlace = make_pair(-1, -1);
	vector<int> cost(n, 0);
	for (auto it : availableQuadraples) {
		auto ap = quadraples[it];
		int counter = 1;

		for (auto element : ap) {
			if (A[element] == TRUE || B[element] == TRUE || C[element] == TRUE)
				++counter;
		}

		for (auto element : ap) {
			if (A[element] == TRUE || B[element] == TRUE || C[element] == TRUE)
				continue;
			cost[element] += counter;
		}
	}

	for (int i = 0; i < n; ++i)
		if (cost[i] > 0)
			bestPlace = max(bestPlace, make_pair(cost[i], i));

	return bestPlace.second;

}

bool littleAllFalsesCheck(vector<int>& A, vector<int>& B, vector<int>& C, int x) {
	return (!(A[x] == FALSE && B[x] == FALSE && C[x] == FALSE));
}

bool check(vector<int>& A, vector<int>& B, vector<int>& C, int x) {
	
	int trues = 0;
	if (A[x] == TRUE) ++trues;
	if (B[x] == TRUE) ++trues;
	if (C[x] == TRUE) ++trues;
	if (trues > 1)
		return false;

	if (A[x] == FALSE && B[x] == FALSE && C[x] == FALSE)
		return false;

	for (int i = 0; i < criticals[x].size(); ++i) {
		int a = criticals[x][i][0];
		int b = criticals[x][i][1];
		int c = criticals[x][i][2];
		if (A[a] == TRUE && A[b] == TRUE && A[c] == TRUE && A[x] == TRUE) return false; 
		if (B[a] == TRUE && B[b] == TRUE && B[c] == TRUE && B[x] == TRUE) return false;
		if (C[a] == TRUE && C[b] == TRUE && C[c] == TRUE && C[x] == TRUE) return false;
	}

	return true;
}

void update(vector<int>& A, vector<int>& B, vector<int>& C, set<int>& availableQuadraples){
	
	vector<int> toDelete;
	for (auto it : availableQuadraples) {
		auto ap = quadraples[it];
		int counterA = 0;
		int counterB = 0;
		int counterC = 0;
		for (auto element : ap) {
			if (A[element] == TRUE) ++counterA;
			if (B[element] == TRUE) ++counterB;
			if (C[element] == TRUE) ++counterC;
		}
			int q = counterA * counterB + counterB * counterC + counterC * counterA;
			if (q > 0)
				toDelete.push_back(it);
	}
	for (auto it : toDelete)
		availableQuadraples.erase(it);
}

bool reduce(vector<int>& A, vector<int>& B, vector<int>& C, set<int>& availableQuadraples) {
	
	while (true) {
		bool flag = false;
		update(A, B, C, availableQuadraples);

		for (auto it : availableQuadraples) {
			auto ap = quadraples[it];
			int countA = 0;
			int countB = 0;
			int countC = 0;
			for (auto element : ap) {
				if (A[element] == TRUE) ++countA;
				if (B[element] == TRUE) ++countB;
				if (C[element] == TRUE) ++countC;
			}
			if (countA + countB + countC < 4) {
				for (auto element : ap) {
					if (countA == 3 && A[element] == MAYBE){
						A[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, element))
							return false;
					}
					if (countB == 3 && B[element] == MAYBE) {
						B[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, element))
							return false;
					}
					if (countC == 3 && C[element] == MAYBE){
						C[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, element))
							return false;
					}
				}
			}
		}

		for (int x = 0; x < n; ++x) {
			if (A[x] == TRUE || B[x] == TRUE || C[x] == TRUE)
				continue;
			int counterFalse = 0;
			if (A[x] == FALSE) ++counterFalse;
			if (B[x] == FALSE) ++counterFalse;
			if (C[x] == FALSE) ++counterFalse;
			if (counterFalse == 2) {
				if (A[x] == MAYBE) {
					A[x] = TRUE;
					if (!check(A, B, C, x))
						return false;
				}
				if (B[x] == MAYBE) {
					B[x] = TRUE;
					if (!check(A, B, C, x))
						return false;
				}
				if (C[x] == MAYBE) {
					C[x] = TRUE;
					if (!check(A, B, C, x))
						return false;
				}
				flag = true;
			}
		}
		if (!flag)
			break;

	}

	return true;

}

bool dfs(vector<int>&A, vector<int>& B, vector<int>& C, set<int>& availableQuadraples){

	int chosenNumber = choice(A, B, C, availableQuadraples);

	if (chosenNumber < 0) {
		for (int x = 0; x < n; ++x) {
			if (A[x] == TRUE)
				cout << 'A', ans += 'A';
			if (B[x] == TRUE)
				cout << 'B', ans += 'B';
			if (C[x] == TRUE)
				cout << 'C', ans += 'C';
		}
		return true;
	}

	{
		vector<int> A1 = A;
		vector<int> B1 = B;
		vector<int> C1 = C;
		set<int> availableQuadraples1 = availableQuadraples;
		A1[chosenNumber] = TRUE;
		B1[chosenNumber] = FALSE;
		C1[chosenNumber] = FALSE;
		if (check(A1, B1, C1, chosenNumber))
			if (reduce(A1, B1, C1, availableQuadraples1))
				if (dfs(A1, B1, C1, availableQuadraples1))
					return true;
	}

	{
		vector<int> A1 = A;
		vector<int> B1 = B;
		vector<int> C1 = C;
		set<int> availableQuadraples1 = availableQuadraples;
		A1[chosenNumber] = FALSE;
		B1[chosenNumber] = TRUE;
		C1[chosenNumber] = FALSE;
		if (check(A1, B1, C1, chosenNumber))
			if (reduce(A1, B1, C1, availableQuadraples1))
				if (dfs(A1, B1, C1, availableQuadraples1))
					return true;
	}

	{
		vector<int> A1 = A;
		vector<int> B1 = B;
		vector<int> C1 = C;
		set<int> availableQuadraples1 = availableQuadraples;
		A1[chosenNumber] = FALSE;
		B1[chosenNumber] = FALSE;
		C1[chosenNumber] = TRUE;;
		if (check(A1, B1, C1, chosenNumber))
			if (reduce(A1, B1, C1, availableQuadraples1))
				if (dfs(A1, B1, C1, availableQuadraples1))
					return true;
	}

	return false;

}

bool checkAnswer() {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				for (int x = 0; x < n; ++x) {
		if (i == j) continue;
		if (i == k) continue;
		if (i == x) continue;
		if (j == k) continue;
		if (j == x) continue;
		if (k == x) continue;
		if (i + j + k != 3 * x) continue;
		if (ans[i] == ans[j] && ans[j] == ans[k] && ans[k] == ans[x]) {
			cerr << i << " " << j << " " << k << " " << x << "\n";
			return false;
		}
				}
}

int main() {

	cin >> n;
	init();
	
	set<int> availableQuadraples;
	for (int i = 0; i < quadraples.size(); ++i)
		availableQuadraples.insert(i);
	vector<int> A(n, MAYBE);
	vector<int> B(n, MAYBE);
	vector<int> C(n, MAYBE);
	A[3] = TRUE;
	B[3] = FALSE;
	C[3] = FALSE;
	time_t t = clock();
	if (!dfs(A, B, C, availableQuadraples))
		cout << "\n no counter examples\n\n";
	cout << "\n";
	cout << (clock() - t) / 1.0 / CLOCKS_PER_SEC << "\n";
	checkAnswer();

	system("pause");

	return 0;
}