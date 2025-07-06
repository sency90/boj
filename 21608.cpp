#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int sno_list[401];
int sno_N;
int order[401][4];
struct Coord {
	int x,y;
	Coord(){}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};
int v[21][21];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
struct Priority{
	int lovecnt;
	int vacant;
	Coord co;
	Priority(){}
	Priority(int lovecnt, int vacant, int x, int y):lovecnt(lovecnt),vacant(vacant),co(x,y) {}
	bool operator<(const Priority & rhs) const {
		if(lovecnt == rhs.lovecnt) {
			if(vacant == rhs.vacant) return co<rhs.co;
			else return vacant > rhs.vacant;
		}
		else return lovecnt > rhs.lovecnt;
	}

	void print() const {
		printf("l:%d, v:%d, co(%d,%d)\n", lovecnt, vacant, co.x, co.y);
	}
};
Priority prt_list[401];
int find_idx(int *order, int adj_sno) {
	for(int i=0; i<4; i++) {
		if(order[i] == adj_sno) return i;
	}
	return -1;
}

inline int score(int lovecnt) {
	switch(lovecnt) {
		case 0: return 0;
		case 1: return 1;
		case 2: return 10;
		case 3: return 100;
		case 4: return 1000;
		default: return 0;
	}
}
int main() {
	int N; scanf("%d", &N);
	int M = N*N;
	for(int i=0; i<M; i++) {
		int sno; scanf("%d", &sno);
		for(int j=0; j<4; j++) {
			scanf("%d", &order[sno][j]);
		}
		sort(order[sno], order[sno]+4);
		sno_list[i] = sno;
	}

	int mxlovecnt=0;
	int mxvacant=0;
	for(int z=0; z<M; z++) {
		int sno = sno_list[z];
		int prt_N=0;
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=N; j++) {
				if(v[i][j]) continue;
				int lovecnt=0, vacant=0;
				for(int k=0; k<4; k++) {
					int nx = i+dx[k];
					int ny = j+dy[k];
					if(nx<=0||ny<=0||nx>N||ny>N) continue;
					if(v[nx][ny]>0) {
						int idx = find_idx(order[sno], v[nx][ny]);
						if(idx>=0) lovecnt++;
					}
					else vacant++;
				}
				prt_list[prt_N++] = Priority(lovecnt, vacant, i,j);
			}
		}

		sort(prt_list, prt_list+prt_N);
		v[prt_list[0].co.x][prt_list[0].co.y] = sno;
	}


	int ans=0;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			int lovecnt=0;
			for(int k=0; k<4; k++) {
				int nx=i+dx[k];
				int ny=j+dy[k];
				if(nx<=0||ny<=0||nx>N||ny>N) continue;
				int idx = find_idx(order[v[i][j]], v[nx][ny]);
				if(idx>=0) lovecnt++;
			}
			ans += score(lovecnt);
		}
	}
	printf("%d\n", ans);
	return 0;
}
