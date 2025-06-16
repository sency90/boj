#include <cstdio>
#include <cstdlib>
using namespace std;
int R,C,T;
constexpr int NA = -1;
struct Coord{
	int x,y;
	Coord():x(NA),y(NA) {}
	Coord(int x, int y):x(x),y(y) {}
};

int a[51][51][2];
Coord air[2];

void init_a(int t) {
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			a[i][j][t] = 0;
		}
	}
	a[air[0].x][air[0].y][t]=-1;
	a[air[1].x][air[1].y][t]=-1;
}

int t;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
Coord nxt_co[51][51];
int main() {
	scanf("%d%d%d",&R,&C,&T);
	int ai=0;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			scanf("%d", &a[i][j][t]);
			if(a[i][j][t]<0) {
				air[ai++] = Coord(i,j);
			}
		}
	}
	
	//air[0]: -> ^ <- v (2 1 3 0) - counter clockwise
	//air[1]: -> v <- ^ (2 0 3 1) - clockwise
	int dir[2][4] = {{2,1,3,0}, {2,0,3,1}};

	for(int z=0; z<2; z++) {
		Coord cur_co = air[z];
		for(int i=0; i<4; i++) {
			while(true) {
				int nx = cur_co.x + dx[dir[z][i]];
				int ny = cur_co.y + dy[dir[z][i]];
				if(nx<0||ny<0||nx>=R||ny>=C) break;
				if(nxt_co[cur_co.x][cur_co.y].x>=0) break;
				nxt_co[cur_co.x][cur_co.y] = Coord(nx,ny);
				cur_co = Coord(nx,ny);
			}
		}
	}

	int ti=0;
	while(true) {
		init_a(t^1);
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				if(a[i][j][t]<=0) continue;

				a[i][j][t^1] += a[i][j][t];
				int d = a[i][j][t]/5;
				int cnt_dir=0;
				for(int k=0; k<4; k++) {
					int nx=i+dx[k];
					int ny=j+dy[k];
					if(nx<0||ny<0||nx>=R||ny>=C) continue;
					if(a[nx][ny][t^1]<0) continue;
					a[nx][ny][t^1] += d;
					cnt_dir++;
				}
				a[i][j][t^1] -= d*cnt_dir;
			}
		}
		t^=1;

		init_a(t^1);
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				if(a[i][j][t]<0) continue;

				Coord nco = nxt_co[i][j]; //next_co
				if(nco.x<0) {
					a[i][j][t^1] += a[i][j][t];
					continue;
				}

				if(a[nco.x][nco.y][t^1]<0) continue; //there's a air cleaner.

				a[nco.x][nco.y][t^1] += a[i][j][t];
			}
		}
		ti++;
		t^=1;

		if(ti == T) break;
	}

	int ans=0;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			if(a[i][j][t]>0) {
				ans += a[i][j][t];
			}
		}
	}
	printf("%d\n", ans);

	return 0;
}
