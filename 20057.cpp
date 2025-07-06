#include <cstdio>
using namespace std;
int dx[] = {0,1,0,-1};
int dy[] = {-1,0,1,0};
int N;
int a[510][510];
//<- v -> ^
int rotate(int dir, int d) {
	return (dir + d)%4;
}
bool tornado(int x, int y, int dir) {
	int sum = 0;
	int d = a[x][y]*0.07;
	int L = dir;
	int D = rotate(dir, 1);
	int R = rotate(dir, 2);
	int U = rotate(dir, 3);
	a[x+dx[U]][y+dy[U]] += d;
	a[x+dx[D]][y+dy[D]] += d;
	sum += (d<<1);
	d = a[x][y]*0.02;
	a[x+2*dx[U]][y+2*dy[U]] += d;
	a[x+2*dx[D]][y+2*dy[D]] += d;
	sum += (d<<1);
	d = a[x][y]*0.1;
	a[x+dx[U]+dx[L]][y+dy[U]+dy[L]] += d;
	a[x+dx[L]+dx[D]][y+dy[L]+dy[D]] += d;
	sum += (d<<1);
	d = a[x][y]*0.01;
	a[x+dx[U]+dx[R]][y+dy[U]+dy[R]] += d;
	a[x+dx[R]+dx[D]][y+dy[R]+dy[D]] += d;
	sum += (d<<1);
	d = a[x][y]*0.05;
	a[x+2*dx[L]][y+2*dy[L]] += d;
	sum += d;
	a[x+dx[L]][y+dy[L]] += a[x][y]-sum;
	if(x==2 && y==2) return true;
	else return false;
}
int main() {
	scanf("%d",&N);
	for(int i=2; i<N+2; i++) {
		for(int j=2; j<N+2; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	//(0,0) -> (2,2)
	int x=N/2+2, y=N/2+2, dir=0, cnt=0;
	while(true) {
		cnt++;
		for(int i=0; i<cnt; i++) {
			x+=dx[dir];
			y+=dy[dir];
			if(tornado(x,y,dir)) goto BRK;
		}
		dir=(dir+1)%4;
		for(int i=0; i<cnt; i++) {
			x+=dx[dir];
			y+=dy[dir];
			if(tornado(x,y,dir)) goto BRK;
		}
		dir=(dir+1)%4;
	}
BRK:
	long long ans = 0;
	for(int i=0; i<N+4; i++) {
		for(int j=0; j<N+4; j++) {
			if(j<=1 || j>=N+2) ans += a[i][j];
			else if(i<=1 || i>=N+2) ans += a[i][j];
		}
	}
	printf("%lld\n", ans);
	return 0;
};
