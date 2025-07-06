#include <cstdio>
using namespace std;
int tmp[64][64], arr[64][64];
inline int Max(int x, int y) { return x>y?x:y; }
void rotate(int N) {
	for(int i=0,v=N-1; i<N; i++,v--) {
		for(int j=0,u=0; j<N; j++,u++) {
			//(i,j)->(u,v)
			tmp[u][v] = arr[i][j];
		}
	}
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			arr[i][j] = tmp[i][j];
		}
	}
}

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

int a[64][64];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
Coord co_list[64*64];

bool chk[64][64];
int M;
int dfs(int x, int y) {
	chk[x][y] = true;
	int sum = 1;
	for(int i=0; i<4; i++) {
		int nx = x+dx[i];
		int ny = y+dy[i];
		if(nx<0||ny<0||nx>=M||ny>=M) continue;
		if(chk[nx][ny]) continue;
		if(a[nx][ny]==0) continue;
		sum += dfs(nx,ny);
	}
	return sum;
}
int main() {
	int N,Q;
	scanf("%d%d",&N,&Q);
	M = 1<<N;
	for(int i=0; i<M; i++) {
		for(int j=0; j<M; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i=0; i<Q; i++) {
		int L;
		scanf("%d", &L);
		int d = 1<<L;
		for(int u=0; u<M; u+=d) {
			for(int v=0; v<M; v+=d) {
				for(int i=u,ii=0; i<u+d; i++,ii++) {
					for(int j=v,jj=0; j<v+d; j++,jj++) {
						arr[ii][jj] = a[i][j];
					}
				}
				rotate(d);
				for(int i=u,ii=0; i<u+d; i++,ii++) {
					for(int j=v,jj=0; j<v+d; j++,jj++) {
						a[i][j] = arr[ii][jj];
					}
				}
			}
		}

		int co_N=0;
		for(int u=0; u<M; u++) {
			for(int v=0; v<M; v++) {
				if(a[u][v]==0) continue;
				int no_ice_cnt=0;
				for(int z=0; z<4; z++) {
					int nx = u+dx[z];
					int ny = v+dy[z];
					if(nx<0||ny<0||nx>=M||ny>=M) {
						no_ice_cnt++;
					}
					else if(a[nx][ny] == 0) {
						no_ice_cnt++;
						//co_list[co_N++] = Coord(nx,ny);
					}
				}
				if(no_ice_cnt>=2) co_list[co_N++] = Coord(u,v);
			}
		}
		for(int k=0; k<co_N; k++) {
			a[co_list[k].x][co_list[k].y]--;
		}
	}

	int sum = 0;
	for(int i=0; i<M; i++) {
		for(int j=0; j<M; j++) {
			sum += a[i][j];
		}
	}

	printf("%d\n", sum);

	int mx = 0;
	for(int i=0; i<M; i++) {
		for(int j=0; j<M; j++) {
			if(chk[i][j] || a[i][j]==0) continue;
			mx = Max(mx, dfs(i,j));
		}
	}
	printf("%d\n", mx);
	return 0;
}
