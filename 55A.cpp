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
vector<vector<int> > rearragements{ { 1, 2, 3 }, { 1, 3, 2 }, { 2, 1, 3 }, { 2, 3, 1 }, { 3, 1, 2 }, { 3, 2, 1 } };
int height = 0;
int Start = 55;
int FirstToColor = 1;

void print(vector<int>& v) {
	for (int i = 0; i < v.size(); ++i)
		cerr << v[i] ;
	cerr << "\n";
}

//ld tCheck = 0;
//ld tGlobalCheck = 0;
//ld tChoice = 0;
//ld tReduce = 0;

void init() {
	height = 0;
	criticals.clear();
	quadraples.clear();

	criticals.resize(n);
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
			for (int k = j + 1; k < n; ++k) {
				if ((i + j + k) % 3 != 0)
					continue;
				int x = (i + j + k) / 3;
				if (i == x) continue;
				if (j == x) continue;
				if (k == x) continue;
	//					if(j < k)
				criticals[i].push_back({ j, k, x });
	//					if (i < k)
				criticals[j].push_back({ i, k, x });
	//					if (i < j)
				criticals[k].push_back({ i, j, x });;
	//					if (i < j && j < k)
				criticals[x].push_back({ i, j, k });
		
				quadraples.push_back({ i, j, k, x });
			}
		}
	}

}

int choice(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, set<int>& availableQuadraples) {

	time_t t1 = clock();

	/*vector<int> possibleNumbers;
	for (int i = 0; i < n; ++i)
		if (A[i] != TRUE && B[i] != TRUE && C[i] != TRUE && )
			possibleNumbers.push_back(i);*/

	pair<int, int> bestPlace = make_pair(-1, -1);
	vector<int> cost(n, 0);
	for (auto it : availableQuadraples) {
		auto ap = quadraples[it];
		int counter = 1;
		for (auto element : ap) {
			if (A[element] == TRUE || B[element] == TRUE || C[element] == TRUE || D[element] == TRUE)
				++counter;
		}
		for (auto element : ap) {
			if (A[element] == TRUE || B[element] == TRUE || C[element] == TRUE || D[element] == TRUE)
				continue;
			cost[element] += counter;
		}

	}

	//print(cost);

	for (int i = 0; i < n; ++i)
		if (cost[i] > 0)
			bestPlace = max(bestPlace, make_pair(cost[i], i));

//	tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
	return bestPlace.second;

	/*if (possibleNumbers.empty())
		return -1;
	else
		return possibleNumbers[rand() % possibleNumbers.size()];*/

}

bool littleAllFalsesCheck(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, int x) {
	return (!(A[x] == FALSE && B[x] == FALSE && C[x] == FALSE && D[x] == FALSE));
}

bool check(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, int x) {

	time_t t1 = clock();
	int trues = 0;
	if (A[x] == TRUE) ++trues;
	if (B[x] == TRUE) ++trues;
	if (C[x] == TRUE) ++trues;
	if (D[x] == TRUE) ++trues;

	if (trues > 1){
		//tCheck += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
		return false;
	}

	if (A[x] == FALSE && B[x] == FALSE && C[x] == FALSE && D[x] == FALSE){
//		tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
		return false;
	}

	for (int i = 0; i < criticals[x].size(); ++i) {
		int a = criticals[x][i][0];
		int b = criticals[x][i][1];
		int c = criticals[x][i][2];
		if (A[a] == TRUE && A[b] == TRUE && A[c] == TRUE && A[x] == TRUE) {
			//tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC; 
			return false; 
		}
		if (B[a] == TRUE && B[b] == TRUE && B[c] == TRUE && B[x] == TRUE) { 
			//tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC; 
			return false; 
		}
		if (C[a] == TRUE && C[b] == TRUE && C[c] == TRUE && C[x] == TRUE) { 
			//tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC; 
			return false; 
		}
		if (D[a] == TRUE && D[b] == TRUE && D[c] == TRUE && D[x] == TRUE) {
			//tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC; 
			return false; }
	}
	//tChoice += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
	return true;
}

/*bool globalCheck(vector<int>& A, vector<int>& B, vector<int>& C) {

	time_t t1 = clock();

	for (int x = 0; x < n; ++x) {
		if (A[x] == FALSE && B[x] == FALSE && C[x] == FALSE && D[x] == FALSE){
//			tGlobalCheck += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
			return false;
		}
		int trues = 0;
		if (A[x] == TRUE) ++trues;
		if (B[x] == TRUE) ++trues;
		if (C[x] == TRUE) ++trues;
		if (D[x] == TRUE) ++trues;
		if (trues > 1){
//			tGlobalCheck += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
			return false;
		}
	}

	for (auto ap : quadraples) {
		bool flA = true, flB = true, flC = true;
		for (auto element : ap) {
			flA &= (A[element] == TRUE);
			flB &= (B[element] == TRUE);
			flC &= (C[element] == TRUE);
			flD &= (D[element] == TRUE);
		}
		if (flA || flB || flC || flD){
//			tGlobalCheck += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
			return false;
		}
	}
//	tGlobalCheck += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
	return true;
}*/

void update(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, set<int>& availableQuadraples){

	vector<int> toDelete;

	for (auto it : availableQuadraples) {
		auto ap = quadraples[it];
		bool counterA = false;
		bool counterB = false;
		bool counterC = false;
		bool counterD = false;
		bool falseA = false;
		bool falseB = false;
		bool falseC = false;
		bool falseD = false;
		for (auto element : ap) {
			if (A[element] == TRUE) counterA = true;
			if (B[element] == TRUE) counterB = true;
			if (C[element] == TRUE) counterC = true;
			if (D[element] == TRUE) counterD = true;
			if (A[element] == FALSE) falseA = true;
			if (B[element] == FALSE) falseB = true;
			if (C[element] == FALSE) falseC = true;
			if (D[element] == FALSE) falseD = true;
		}
		int q = 0;
		if (counterA) ++q;
		if (counterB) ++q;
		if (counterC) ++q;
		if (counterD) ++q;
		
		/*if (q > 1) {
			toDelete.push_back(it);

		}*/

		if ((q > 1) || (counterA & falseA) || (counterB & falseB) || (counterC & falseC) || (counterD & falseD)) {
			toDelete.push_back(it);

		}
	
	}
	for (auto it : toDelete)
		availableQuadraples.erase(it);
}

bool reduce(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, set<int>& availableQuadraples) {

	time_t t1 = clock();
	while (true) {

		bool flag = false;

		update(A, B, C, D, availableQuadraples);

		for (auto it : availableQuadraples) {
			auto ap = quadraples[it];

			int countA = 0;
			int countB = 0;
			int countC = 0;
			int countD = 0;

			for (auto element : ap) {
				if (A[element] == TRUE) ++countA;
				if (B[element] == TRUE) ++countB;
				if (C[element] == TRUE) ++countC;
				if (D[element] == TRUE) ++countD;
			}
			if (countA == 4 || countB == 4 || countC == 4 || countD == 4)
				return false;
			if (countA + countB + countC + countD < 4) {
				for (auto element : ap) {
					if (countA == 3 && A[element] == MAYBE){
						A[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, D, element)){
//							tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
							return false;
						}
					}
					if (countB == 3 && B[element] == MAYBE) {
						B[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, D, element)){
//							tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
							return false;
						}
					}
					if (countC == 3 && C[element] == MAYBE){
						C[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, D, element)){
//							tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
							return false;
						}
					}
					if (countD == 3 && D[element] == MAYBE){
						D[element] = FALSE;
						flag = true;
						if (!littleAllFalsesCheck(A, B, C, D, element)){
//							tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
							return false;
						}
					}
				}
			}
		}

		update(A, B, C, D, availableQuadraples);

		for (int x = 0; x < n; ++x) {
			if (A[x] == TRUE || B[x] == TRUE || C[x] == TRUE || D[x] == TRUE)
				continue;
			int counterFalse = 0;
			if (A[x] == FALSE) ++counterFalse;
			if (B[x] == FALSE) ++counterFalse;
			if (C[x] == FALSE) ++counterFalse;
			if (D[x] == FALSE) ++counterFalse;
			if (counterFalse == 3) {
				if (A[x] == MAYBE) {
					A[x] = TRUE;
					//if (!check(A, B, C, D, x)){
//						tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
					//	return false;
					//}
				}
				if (B[x] == MAYBE) {
					B[x] = TRUE;
//					if (!check(A, B, C, D, x)) {
//						tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
//						return false;
//					}
				}
				if (C[x] == MAYBE) {
					C[x] = TRUE;
//					if (!check(A, B, C, D, x)) {
//						tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
//						return false;
//					}
				}
				if (D[x] == MAYBE) {
					D[x] = TRUE;
//					if (!check(A, B, C, D, x)) {
//						tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
//						return false;
//					}
				}
				flag = true;
			}
		}
		if (!flag)
			break;
	}
//	tReduce += (clock() - t1) / 1.0 / CLOCKS_PER_SEC;
	return true;

}

bool checkAnswer(vector<int>&A, vector<int>& B, vector<int>& C, vector<int>& D) {
	print(A);
	print(B);
	print(C);
	print(D);

	for (int it = 0; it < ans.size(); ++it) {
		if (ans[it] == '?') {
			if (A[it] != FALSE)
				ans[it] = 'A';
			if (B[it] != FALSE)
				ans[it] = 'B';
			if (C[it] != FALSE)
				ans[it] = 'C';
			if (D[it] != FALSE)
				ans[it] = 'D';
		}
	}

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
			cerr << i << " " << j << " " << k << " " << x << " - very bad!\n";
			return false;
		}
				}
}

bool dfs(vector<int>&A, vector<int>& B, vector<int>& C, vector<int>& D, set<int>& availableQuadraples){

	int chosenNumber = choice(A, B, C, D, availableQuadraples);
	++height;
	/*print(A);
	print(B);
	print(C);
	print(D);
	cout << "height = " << height << "\n";
	cout << "chosen number = " << chosenNumber << "\n";
	cout << "available Quadraples size: " << availableQuadraples.size() << "\n";
	for (int j = 0; j < 1000000000; ++j) {
		int a = 228 * 265;
		int b = a;
		if (j % 434244034 == 228)
			cerr << "228!\n";
	}
/*	for (auto it : availableQuadraples) {
		auto ap = quadraples[it];
		for (auto x : ap)
			cout << x << " ";
		cout << "\n";
	}*/

	if (chosenNumber < 0) {
		for (int x = 0; x < n; ++x) {
			bool flag = false;
			if (A[x] == TRUE)
				cout << 'A', ans += 'A', flag = true;
			if (B[x] == TRUE)
				cout << 'B', ans += 'B', flag = true;
			if (C[x] == TRUE)
				cout << 'C', ans += 'C', flag = true;
			if (D[x] == TRUE)
				cout << 'D', ans += 'D', flag = true;
			if (!flag)
				cout << '?', ans += '?';
		}
		cout << endl;
		if (checkAnswer(A, B, C, D)) {
			cout << ans << " - correct!" << endl;
		}
		else {
			cout << ans << " - incorrect!" << endl;
		}
		return true;
	}

	int create = height % 6;
	vector<int> randoms = rearragements[create];
	//vector<int> randoms{ create ^ 0, create ^ 1, create ^ 2, create ^ 3 };
	//print(randoms);
	//vector<int> randoms{ 1, 2, 3, 4 };
	//random_shuffle(randoms.begin(), randoms.end());

	for (auto cur : randoms) {

		if (cur == 1 && A[chosenNumber] != FALSE)
		{
			vector<int> A1 = A;
			vector<int> B1 = B;
			vector<int> C1 = C;
			vector<int> D1 = D;
			set<int> availableQuadraples1 = availableQuadraples;
			A1[chosenNumber] = TRUE;
			B1[chosenNumber] = FALSE;
			C1[chosenNumber] = FALSE;
			D1[chosenNumber] = FALSE;
			//if (check(A1, B1, C1, D1, chosenNumber))
			if (reduce(A1, B1, C1, D1, availableQuadraples1))
				if (dfs(A1, B1, C1, D1, availableQuadraples1))
					return true;
				else
					--height;
		}

		if (cur == 2 && B[chosenNumber] != FALSE)
		{
			vector<int> A1 = A;
			vector<int> B1 = B;
			vector<int> C1 = C;
			vector<int> D1 = D;
			set<int> availableQuadraples1 = availableQuadraples;
			A1[chosenNumber] = FALSE;
			B1[chosenNumber] = TRUE;
			C1[chosenNumber] = FALSE;
			D1[chosenNumber] = FALSE;
			//if (check(A1, B1, C1, D1, chosenNumber))
			if (reduce(A1, B1, C1, D1, availableQuadraples1))
				if (dfs(A1, B1, C1, D1, availableQuadraples1))
					return true;
				else
					--height;
		}

		if (cur == 3 && C[chosenNumber] != FALSE)
		{
			vector<int> A1 = A;
			vector<int> B1 = B;
			vector<int> C1 = C;
			vector<int> D1 = D;
			set<int> availableQuadraples1 = availableQuadraples;
			A1[chosenNumber] = FALSE;
			B1[chosenNumber] = FALSE;
			C1[chosenNumber] = TRUE;
			D1[chosenNumber] = FALSE;
			//if (check(A1, B1, C1, D1, chosenNumber))
			if (reduce(A1, B1, C1, D1, availableQuadraples1))
				if (dfs(A1, B1, C1, D1, availableQuadraples1))
					return true;
				else
					--height;
		}

		/*if (cur == 4 && D[chosenNumber] != FALSE)
		{
			vector<int> A1 = A;
			vector<int> B1 = B;
			vector<int> C1 = C;
			vector<int> D1 = D;
			set<int> availableQuadraples1 = availableQuadraples;
			A1[chosenNumber] = FALSE;
			B1[chosenNumber] = FALSE;
			C1[chosenNumber] = FALSE;
			D1[chosenNumber] = TRUE;
			//if (check(A1, B1, C1, D1, chosenNumber))
			if (reduce(A1, B1, C1, D1, availableQuadraples1))
				if (dfs(A1, B1, C1, D1, availableQuadraples1))
					return true;
				else
					--height;
		}*/
	}

	return false;
}

int d = 5;
int magic228 = 25;

int main() {

	freopen("output55A.txt", "w", stdout);

	for (int k = Start; k < 100; ++k) {
		//cin >> FirstToColor;
		n = k;
		init();
		cout << "n = " << n << "\n";
		cout << quadraples.size() << "\n";
		set<int> availableQuadraples;
		for (int i = 0; i < quadraples.size(); ++i)
			availableQuadraples.insert(i);
		vector<int> A(n, MAYBE);
		vector<int> B(n, MAYBE);
		vector<int> C(n, MAYBE);
		vector<int> D(n, MAYBE);

		int firstNumbereToChoice = choice(A, B, C, D, availableQuadraples);
		firstNumbereToChoice = 0;
		cout << firstNumbereToChoice << "\n";
		A[firstNumbereToChoice] = FALSE;
		B[firstNumbereToChoice] = FALSE;
		C[firstNumbereToChoice] = FALSE;
		D[firstNumbereToChoice] = FALSE;

		if (FirstToColor == 1)
			A[firstNumbereToChoice] = TRUE;
		if (FirstToColor == 2)
			B[firstNumbereToChoice] = TRUE;
		if (FirstToColor == 3)
			C[firstNumbereToChoice] = TRUE;
		if (FirstToColor == 4)
			D[firstNumbereToChoice] = TRUE;

		//int bigDegree = 1;
		//for (int i = 0; i < d; ++i)
		//	bigDegree *= 4;

		//vector<int> funnyFunction{ 0, 1, 2, 4, 6, 9, 12, 14 };

		//for (int i = 233; i < bigDegree; ++i){
		time_t t = clock();
		vector<int> AA = A;
		vector<int> BB = B;
		vector<int> CC = C;
		vector<int> DD = D;
		set<int> availableQuadraples2 = availableQuadraples;
		//int ii = i;

		/*for(int up = 1; up <= d; ++up) {
			int res = ii % 4;
			ii /= 4;
			int index = magic228 + funnyFunction[d - up] + 1;
			AA[index] = FALSE;
			BB[index] = FALSE;
			CC[index] = FALSE;
			DD[index] = FALSE;
			if (res == 0)
			AA[index] = TRUE, cout << "A";
			if (res == 1)
			BB[index] = TRUE, cout << "B";
			if (res == 2)
			CC[index] = TRUE, cout << "C";
			if (res == 3)
			DD[index] = TRUE, cout << "D";

			}
			cout << "$\n";*/

		if (!reduce(AA, BB, CC, DD, availableQuadraples2) || !dfs(AA, BB, CC, DD, availableQuadraples2))
			cout << "\n no counter examples - FAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAiL\n\n";
		cout << endl;
		cout << (clock() - t) / 1.0 / CLOCKS_PER_SEC << "\n";
		cout << ans << endl;
		//cout << ans << "\n";

		//if (checkAnswer(AA, BB, CC, DD))
		//	cout << ans << " - correct!\n";
		//else
		//cout << ans << " - incorrect!\n";

		//cout << tCheck << "\n";
		//cout << tChoice << "\n";
		//cout << tReduce << "\n";
		//cout << tGlobalCheck << "\n";
		ans.clear();
		//	}
	}
	

	return 0;
}