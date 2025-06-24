#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int S=0, E=32;
int horse[4];
int dice[10];
int pt[33];
vector<vector<int>> v;

int w[33][6];

int mx;
void dfs(int th, int sum) {
	mx = max(sum, mx);
	if(th==10) {
		return;
	}

	for(int i=0; i<4; i++) {
		if(horse[i] == E) continue;

		int y = w[horse[i]][dice[th]];
		if(y!=E) {
			bool good = true;
			for(int j=0; j<4; j++) {
				if(i==j) continue;
				if(horse[j] == y) {
					good = false;
					break;
				}
			}
			if(!good) continue;
		}

		int prv_y = horse[i];
		horse[i] = y;
		dfs(th+1, sum + pt[y]);
		horse[i] = prv_y;
	}
}

int main() {
	v.resize(33, vector<int>());
	for(int i=0; i<20; i++) {
		v[i].emplace_back(i+1);
		pt[i]=i*2;
	}
	pt[20]=40;

	v[5].emplace_back(21);
	for(int i=21; i<26; i++) {
		v[i].emplace_back(i+1);
	}
	v[26].emplace_back(20);

	v[10].emplace_back(31);
	v[31].emplace_back(30);
	v[30].emplace_back(24);

	v[15].emplace_back(29);
	v[29].emplace_back(28);
	v[28].emplace_back(27);
	v[27].emplace_back(24);

	v[20].emplace_back(32);
	v[32].emplace_back(32);

	pt[21] = 13;
	pt[22] = 16;
	pt[23] = 19;
	pt[24] = 25;
	pt[25] = 30;
	pt[26] = 35;
	pt[27] = 26;
	pt[28] = 27;
	pt[29] = 28;
	pt[30] = 24;
	pt[31] = 22;
	pt[32] = 0;

	for(int i=0; i<33; i++) {
		int y = v[i][0];
		if(v[i].size()>1) y = v[i][1];
		for(int j=1; j<=5; j++) {
			w[i][j] = y;
			y = v[y][0];
		}
	}

	for(int i=0; i<10; i++) {
		scanf("%d", &dice[i]);
	}

	dfs(0,0);
	printf("%d\n", mx);
	
	return 0;
}
