#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int M[2][10][4];
struct Block{
	int sz,x[2],y[2];
	Block(){}
	Block(int t, int x, int y) {
		this->x[0] = x;
		this->y[0] = y;

		if(t==2) { //1x2
			this->x[1] = x;
			this->y[1] = y+1;
			sz=2;
		}
		else if(t==3) {
			this->x[1] = x+1;
			this->y[1] = y;
			sz=2;
		}
		else sz=1;
	}

	void rotate() {
		for(int i=0; i<sz; i++) {
			swap(x[i],y[i]);
		}
	}

	bool is_next_empty(int z) const {
		int (*m)[4] = M[z];
		int cnt=0;
		for(int i=0; i<sz; i++) {
			if(x[i]+1>=10) return false;
			if(m[x[i]+1][y[i]]==0) cnt++;
		}
		if(sz == cnt) return true;
		else return false;
	}

	void go_down1() {
		for(int i=0; i<sz; i++) x[i]++;
	}
	
};
void go_down(Block & blk, int z) {
	if(blk.is_next_empty(z)) {
		blk.go_down1();
		go_down(blk, z);
	}
}
void set_block(Block & blk, int z) {
	int (*m)[4] = M[z];
	for(int i=0; i<blk.sz; i++) {
		m[blk.x[i]][blk.y[i]] = 1;
	}
}
vector<int> alive_lines;
int score;
void clear_lines(int z) {
	int (*m)[4] = M[z];
	alive_lines.clear();
	for(int i=9; i>=4; i--) {
		int cnt=0;
		for(int j=0; j<4; j++) {
			if(m[i][j]==1) {
				cnt++;
			}
		}
		if(cnt!=4) {
			alive_lines.push_back(i);
		}
		else score++;
	}

	for(int i=0,j=9; i<alive_lines.size(); i++,j--) {
		if(j==alive_lines[i]) continue;
		for(int k=0; k<4; k++) {
			m[j][k] = m[alive_lines[i]][k];
			m[alive_lines[i]][k]=0;
		}
	}
}
void handle_special_lines(int z) {
	int (*m)[4] = M[z];
	int cnt=0;
	for(int i=5; i>=4; i--) {
		for(int j=0; j<4; j++) {
			if(m[i][j]) {
				cnt++;
				break;
			}
		}
	}

	if(cnt>0) {
		for(int i=9-cnt; i>=4; i--) {
			for(int j=0; j<4; j++) {
				m[i+cnt][j] = m[i][j];
				m[i][j]=0;
			}
		}
	}

}
int main() {
	int N; scanf("%d", &N);
	for(int i=0; i<N; i++) {
		int t,x,y;
		scanf("%d%d%d", &t,&x,&y);
		Block blk1(t,x,y);
		go_down(blk1, 0);
		set_block(blk1, 0);
		clear_lines(0);
		handle_special_lines(0);

		Block blk2(t,x,y);
		blk2.rotate();
		go_down(blk2, 1);
		set_block(blk2, 1);
		clear_lines(1);
		handle_special_lines(1);
	}
	int ans=0;
	for(int z=0; z<2; z++) {
		for(int i=4; i<=9; i++) {
			for(int j=0; j<4; j++) {
				if(M[z][i][j]==1) {
					ans++;
				}
			}
		}
	}
	printf("%d\n%d\n", score, ans);
	return 0;
}
