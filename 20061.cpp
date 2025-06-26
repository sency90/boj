#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
constexpr int LM = 20040;
bool M[2][LM+20][4];
int F[2] = {LM, LM}, R[2] = {LM, LM};
struct Coord {
	int x,y;
	Coord(){}
	Coord(int x, int y):x(x),y(y) {}
};
vector<int> tx_list;
int score;
struct Block {
	vector<Coord> co_list[2];
	Block(int t, int x, int y) {
		co_list[0].push_back(Coord(0,y));
		co_list[1].push_back(Coord(0,x));
		if(t==2) {
			co_list[0].emplace_back(0,y+1);
			co_list[1].emplace_back(1,x);
		}
		else if(t==3) {
			co_list[0].emplace_back(1,y);
			co_list[1].emplace_back(0,x+1);
		}

		for(int i=0; i<2; i++) {
			printf("[%d]: ", i);
			for(int j=0; j<co_list[i].size(); j++) {
				printf("(%d,%d) ", co_list[i][j].x,co_list[i][j].y);
			}
			puts("");
		}
	}

	bool is_line_full(bool (*m)[4], int x) {
		int cnt=0;
		for(int i=0; i<4; i++) {
			if(m[x][i]) cnt++;
		}
		return cnt==4;
	}

	void pull_lines(bool (*m)[4], int from, int to) {
		for(int i=from; i>=to; i--) {
			for(int j=0; j<4; j++) {
				m[i+1][j] = m[i][j];
			}
		}
		score++;
	}

	void go_down() {
		for(int z=0; z<2; z++) {
			bool (*m)[4] = M[z];
			int & f = F[z];
			int & r = R[z];
			vector<Coord> & cos = co_list[z];

			int li=r-2;
			for(int i=r-1; i<=f; i++) {
				bool filled = false;
				for(int j=0; j<cos.size(); j++) {
					Coord & co = cos[j];
					if(i+co.x>f || m[i+co.x][co.y]) {
						filled = true;
						break;
					}
				}
				if(!filled) li = i;
			}

			tx_list.clear();
			for(int j=0; j<cos.size(); j++) {
				Coord & co = cos[j];
				m[li+co.x][co.y] = true;
				r = min(r, li+co.x-1);
				tx_list.push_back(li+co.x);
			}
			sort(tx_list.begin(), tx_list.end());

			for(int i=tx_list.size()-1; i>=0; i--) {
				int tx = tx_list[i];
				if(is_line_full(m, tx)) {
					if(tx == f) f--;
					else pull_lines(m, tx-1,r);
				}
			}

			printf("[%d] f:%d, r:%d\n", z,f,r);
			assert(f>=r);
			while(f-r+1 > 4) f--;
		}
	}

};

void tetris(int t, int x, int y) {
	Block block(t,x,y);
}
int main() {
	int N; scanf("%d", &N);
	for(int i=0; i<N; i++) {
		int t,x,y;
		scanf("%d%d%d",&t,&x,&y);
		Block block(t,x,y);
		block.go_down();
	}
	printf("%d\n", score);
	int cnt=0;
	for(int z=0; z<2; z++) {
		bool (*m)[4] = M[z];
		for(int i=R[z]+1; i<=F[z]; i++) {
			for(int j=0; j<4; j++) {
				if(m[i][j]) {
					cnt++;
					printf("%d %d %d\n", z,i,j);
				}
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
