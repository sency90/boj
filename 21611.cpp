#include <cstdio>
#include <vector>
using namespace std;
int N,M,LM;
int v[52][52][2], t;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int sx,sy; //shark x,y
int chk[52][52], CV;
vector<int> list;
struct Coord{
	int x,y;
	Coord(){}
	Coord(int x, int y):x(x),y(y) {}
};
int px[] = {0,1,0,-1}; //just for numbering
int py[] = {-1,0,1,0};
Coord co_by_num[3000];
int num_by_co[52][52];
void numbering() {
	int x=sx, y=sy;
	int num=0;
	num_by_co[x][y] = num;
	co_by_num[num++] = Coord(x,y);

	int cnt=0, dir=0;
	while(num<LM) {
		cnt++;
		for(int i=0; i<cnt; i++) {
			x+=px[dir];
			y+=py[dir];
			num_by_co[x][y] = num;
			co_by_num[num++] = Coord(x,y);
		}
		dir = (dir+1)%4;
		for(int i=0; i<cnt; i++) {
			x+=px[dir];
			y+=py[dir];
			num_by_co[x][y] = num;
			co_by_num[num++] = Coord(x,y);
		}
		dir = (dir+1)%4;
	}
}
void blizzard(int d, int s) {
	++CV;
	int nx=sx, ny=sy;
	for(int i=0; i<s; i++) {
		nx += dx[d];
		ny += dy[d];
		chk[nx][ny] = CV;
	}

	list.clear();
	for(int i=0; i<LM; i++) {
		if(chk[co_by_num[i].x][co_by_num[i].y] == CV) continue;
		list.push_back(v[co_by_num[i].x][co_by_num[i].y][t]);
	}
	for(int i=0; i<list.size(); i++) {
		v[co_by_num[i].x][co_by_num[i].y][t^1] = list[i];
	}
	for(int i=list.size(); i<LM; i++) {
		v[co_by_num[i].x][co_by_num[i].y][t^1] = 0;
	}
}

struct Intv{
	int b,e;
	Intv(){}
	Intv(int b, int e):b(b),e(e) {}
};

vector<Intv> intv_list;

int ans[4];

bool explode() {
	bool has_explode = false;
	int cnt=0, lim=LM;
	intv_list.clear();
	intv_list.push_back(Intv(0,0));
	for(int i=1; i<LM; i++) {
		if(v[co_by_num[i].x][co_by_num[i].y][t]==0) {
			lim = i;
			break;
		}
		if(v[co_by_num[i-1].x][co_by_num[i-1].y][t] == v[co_by_num[i].x][co_by_num[i].y][t]) {
			cnt++;
		}
		else {
			if(cnt>=4) {
				intv_list.push_back(Intv(i-cnt, i));
				ans[v[co_by_num[i-1].x][co_by_num[i-1].y][t]] += cnt;
				has_explode = true;
			}
			cnt=1;
		}
	}
	if(cnt>=4) {
		intv_list.push_back(Intv(lim-cnt, lim));
		ans[v[co_by_num[lim-1].x][co_by_num[lim-1].y][t]] += cnt;
		has_explode = true;
	}
	if(!has_explode) return false;

	intv_list.push_back(Intv(lim,lim));
	int n_num=0;
	for(int i=1; i<intv_list.size(); i++) {
		for(int num=intv_list[i-1].e; num<intv_list[i].b; num++) {
			v[co_by_num[n_num].x][co_by_num[n_num].y][t^1] = v[co_by_num[num].x][co_by_num[num].y][t];
			n_num++;
		}
	}
	for(int i=n_num; i<LM; i++) {
		if(v[co_by_num[i].x][co_by_num[i].y][t^1] == 0) break;
		v[co_by_num[i].x][co_by_num[i].y][t^1] = 0;
	}
	t^=1;
	return has_explode;
}

void make_new_v() {
	int lim = LM, n_num=1, cnt=0;
	for(int i=1; i<LM; i++) {
		if(v[co_by_num[i].x][co_by_num[i].y][t]==0) {
			lim = i;
			break;
		}
		if(v[co_by_num[i-1].x][co_by_num[i-1].y][t] == v[co_by_num[i].x][co_by_num[i].y][t]) cnt++;
		else {
			if(cnt>0) {
				v[co_by_num[n_num].x][co_by_num[n_num].y][t^1] = cnt;
				n_num++;
				if(n_num>=LM) goto BRK;
				v[co_by_num[n_num].x][co_by_num[n_num].y][t^1] = v[co_by_num[i-1].x][co_by_num[i-1].y][t];
				n_num++;
				if(n_num>=LM) goto BRK;
			}
			cnt=1;
		}
	}

	if(cnt>0) {
		v[co_by_num[n_num].x][co_by_num[n_num].y][t^1] = cnt;
		n_num++;
		if(n_num>=LM) goto BRK;
		v[co_by_num[n_num].x][co_by_num[n_num].y][t^1] = v[co_by_num[lim-1].x][co_by_num[lim-1].y][t];
		n_num++;
		if(n_num>=LM) goto BRK;
	}

	for(int i=n_num; i<LM; i++) {
		if(v[co_by_num[i].x][co_by_num[i].y][t^1] == 0) break;
		v[co_by_num[i].x][co_by_num[i].y][t^1] = 0;
	}

BRK:
	t^=1;
}

int main() {
	scanf("%d%d",&N,&M);
	LM = N*N;
	sx = sy = (N+1)/2;
	numbering();
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			scanf("%d", &v[i][j][t]);
		}
	}
	for(int i=0; i<M; i++) {
		int d,s;
		scanf("%d%d",&d,&s);
		d--;
		blizzard(d,s);
		t^=1;
		while(explode());
		make_new_v();
	}
	printf("%d\n", ans[1]+2*ans[2]+3*ans[3]);
	return 0;
}
