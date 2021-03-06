// 2 "PathGame.cpp"
// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Cat Snuke and wolf Sothe are playing the Path Game.

The Path Game is played on a rectangular grid of square cells.
The grid has 2 rows and some positive number of columns.
Each cell is either black or white.

A left-to-right path in the grid is a sequence of white cells such that the first cell in the sequence is in the leftmost column, the last cell in the sequence is in the rightmost column, and each pair of consecutive cells shares a common side.

The initial coloring of the grid is such that there is at least one left-to-right path.
You are given this initial coloring as a vector <string> board with two elements.
For each i and j, board[i][j] is either '#' (representing a black cell) or '.' (representing a white cell).

The players take alternating turns.
In each turn, the current player has to choose and color one white cell black.
Snuke goes first.
The game ends when there is no longer a left-to-right path on the board.
The last player who colored a cell loses the game.
In other words, the loser is the player who was forced to block the last left-to-right path.

Assume that both players play the game optimally.
Return "Snuke" (quotes for clarity) if Snuke wins the game, and "Sothe" otherwise.

DEFINITION
Class:PathGame
Method:judge
Parameters:vector <string>
Returns:string
Method signature:string judge(vector <string> board)


CONSTRAINTS
-board will contain 2 elements.
-Each element in board will contain between 1 and 1000 characters, inclusive.
-All elements in board will have the same length.
-Each character in board will be '#' or '.'.
-The grid described by board will contain a left-to-right path.


EXAMPLES

0)
{"#.."
,"..."}

Returns: "Snuke"

Snuke has exactly one winning move: he must color the lower right cell.
After this move the resulting grid will still contain a left-to-right path.
Sothe will then have four possible moves, but each of those loses the game immediately.

1)
{"#"
,"."}

Returns: "Sothe"

Snuke has to color the only white cell black, and he immediately loses the game.

2)
{"....."
,"..#.."}

Returns: "Sothe"



3)
{".#..."
,"....."}

Returns: "Snuke"



4)
{".....#..#........##......."
,"..........#..........#...."}

Returns: "Snuke"



*/
// END CUT HERE

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <set>

using namespace std;

typedef long long LL;

class PathGame {
	public:
	string judge(vector <string> board) {
		int len = board[0].length();
		bool forbidden[2][1001] = {0};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < len; j++) {
				if (board[i][j] == '#') forbidden[i][j] = true;
				for (int j2 = j-1; j2 <= j+1; j2++) {
					if (j2 >= 0 && j2 < len) {
						forbidden[1-i][j] = true;
					}
				}
			}
		}

		int grundy[1001][1<<4] = {0};
		for (int n = 1; n <= len; n++) {
			for (int mask = 0; mask < 1<<4; mask++) {
//				set<int> visited;
				int visited[100000] = {0};
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < n; j++) {
						if (j == 0 && (mask & 1<<i) != 0) continue;
						if (j == n-1 && (mask & 1<<(2+i) != 0)) continue;
//						visited.insert(grundy[j][mask & 3 | 1<<(3-i)] ^ 0 ^ grundy[n - j - 1][mask & 12 | 1<<(1-i)]);
						visited[grundy[j][mask & 3 | 1<<(3-i)] ^ 0 ^ grundy[n - j - 1][mask & 12 | 1<<(1-i)]] = 1;
					}
				}
//				while (visited.find(grundy[n][mask]) != visited.end()) {
				while (visited[grundy[n][mask]]) {
					grundy[n][mask]++;
				}
			}
		}

/*
		for (int n = 0; n < len; n++) {
			for (int mask = 0; mask < 1<<4; mask++) {
				printf("%d %d %d\n", n, mask, grundy[n][mask]);
			}
		}*/

		int ans = 0;
		for (int i = 0; i < len;) {
			if (!forbidden[0][i] || !forbidden[1][i]) {
				int j = i;
				while (j+1 < len && (!forbidden[0][j+1] || !forbidden[1][j+1])) {
					j++;
				}
				int mask = 0;
				if (forbidden[0][i]) mask |= 1;
				if (forbidden[1][i]) mask |= 2;
				if (forbidden[0][j]) mask |= 4;
				if (forbidden[1][j]) mask |= 8;
				ans ^= grundy[j-i+1][mask];
				i = j+1;
			} else {
				i++;
			}
		}

		return ans == 0 ? "Sothe" : "Snuke";
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"#.."
,"..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Snuke"; verify_case(0, Arg1, judge(Arg0)); }
	void test_case_1() { string Arr0[] = {"#"
,"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Sothe"; verify_case(1, Arg1, judge(Arg0)); }
	void test_case_2() { string Arr0[] = {"....."
,"..#.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Sothe"; verify_case(2, Arg1, judge(Arg0)); }
	void test_case_3() { string Arr0[] = {".#..."
,"....."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Snuke"; verify_case(3, Arg1, judge(Arg0)); }
	void test_case_4() { string Arr0[] = {".....#..#........##......."
,"..........#..........#...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Snuke"; verify_case(4, Arg1, judge(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	PathGame ___test;
	___test.run_test(-1);
}

// END CUT HERE
