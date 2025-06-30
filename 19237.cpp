#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
int N,M,K;
struct Cell{
	int sno; //shark no
	int tm; //time
	Cell(){}
	Cell(int sno, int tm):sno(sno),tm(tm) {}
	void print() const {
		printf("(%2d,%2d) ", sno,tm);
	}
};
Cell v[20][20];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int dead_cnt;
struct Shark{
	int sno;
	int x,y;
	int cur_d;
	int dir[4][4];

	int move(int cur_time) {
		for(int i=0; i<4; i++) {
			int d = dir[cur_d][i];
			int nx = x+dx[d];
			int ny = y+dy[d];
			if(nx<0||ny<0||nx>=N||ny>=N) continue; //out of bound

			if(v[nx][ny].tm <= cur_time) { //there isn't a shark or scent of a shark.
				v[nx][ny] = Cell(sno, cur_time+K);
				go(nx,ny,d);
				return 0;
			} 
			if(v[nx][ny].tm == cur_time+K) { //other shark was there just before
				int dead_sno = max(v[nx][ny].sno, sno);
				v[nx][ny].sno = min(v[nx][ny].sno, sno);
				dead_cnt++;
				go(nx,ny,d);
				return dead_sno;
			}
		}
		for(int i=0; i<4; i++) {
			int d = dir[cur_d][i];
			int nx = x+dx[d];
			int ny = y+dy[d];
			if(nx<0||ny<0||nx>=N||ny>=N) continue; //out of bound
			if(v[nx][ny].sno==sno) {
				v[nx][ny] = Cell(sno, cur_time+K);
				go(nx,ny,d);
				return 0;
			}
		}
		assert(false);
		return 0;
	}
	void go(int x, int y, int d) {
		this->x=x;
		this->y=y;
		this->cur_d = d;
	}
	
};
Shark s[401];
int main() {
	scanf("%d%d%d",&N,&M,&K);

	int cur_tm = 0;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			int sno;
			scanf("%d", &sno);
			if(sno!=0) {
				s[sno].sno=sno;
				s[sno].x=i;
				s[sno].y=j;
				v[i][j] = Cell(sno,cur_tm+K);
			}
		}
	}
	for(int i=1; i<=M; i++) {
		scanf("%d", &s[i].cur_d);
		s[i].cur_d--;
	}
	for(int i=1; i<=M; i++) {
		for(int d=0; d<4; d++) {
			for(int j=0; j<4; j++) {
				scanf("%d", &s[i].dir[d][j]);
				s[i].dir[d][j]--;
			}
		}
	}

	while(cur_tm<1000) {
		if(M-dead_cnt==1) break;
		cur_tm++;
		printf("[cur_tm: %d] %d\n", cur_tm, dead_cnt);
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				v[i][j].print();
			}
			puts("");
		}
		puts("");

		for(int i=1; i<=M; i++) {
			if(s[i].sno == 0) continue;
			int dead_sno = s[i].move(cur_tm);
			if(dead_sno) s[dead_sno].sno=0;
		}


		//printf("[cur_tm: %d] %d\n", cur_tm, dead_cnt);
		//for(int i=0; i<N; i++) {
		//	for(int j=0; j<N; j++) {
		//		v[i][j].print();
		//	}
		//	puts("");
		//}
		//puts("");
	}

BRK:
	if(M-dead_cnt!=1) puts("-1");
	else printf("%d\n", cur_tm);

	return 0;
}
