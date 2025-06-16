#include <cstdio>
using namespace std;
int v[21][21];
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};
constexpr int QN = 512;
constexpr int QMASK = QN-1;
struct Queue{
	Coord arr[QN];
	int f,r;
	Queue():f(0),r(0) {}
	Queue(Queue & rhs) {
		int sz = rhs.size();
		f=rhs.f;
		r=rhs.r;
		for(int i=0,j=f; i<sz; i++,j=((j+1)&QMASK)) {
			arr[j] = rhs.arr[j];
		}
	}
	void clear() {f=r=0;}

	void push(const Coord & co) {
		arr[r++] = co;
		r&=QMASK;
	}
	
	Coord & front() {
		return arr[f];
	}

	void pop() {
		f++;
		f&=QMASK;
	}

	int size() const {
		int sz = r-f;
		if(sz<0) sz+=QN;

		return sz;
	}

	bool empty() const {
		return r==f;
	}
};

struct Fish{
	int sz;
	int eat_cnt;
	Coord co;
	Fish():sz(2),eat_cnt(0){}
	void refresh() {
		eat_cnt++;
		if(sz == eat_cnt) {
			sz++;
			eat_cnt=0;
		}
	}
	void print() {
		printf("sz:%d, eat_cnt:%d, co:(%d,%d)\n", sz, eat_cnt, co.x, co.y);
	}
};

int n;
Queue q;
int dx[] = {-1,0,0,1};
int dy[] = {0,-1,1,0};
int chk[21][21];
int CHKVAL;
int bfs(Fish & fish) {
	CHKVAL++;
	q.clear();
	q.push(fish.co);
	int dist=0;
	Coord ans_list[81];
	int ans_N=0;
	while(!q.empty()) {
		int sz = q.size();
		for(int z=0; z<sz; z++) {
			Coord co = q.front(); q.pop();
			if(v[co.x][co.y]>0 && v[co.x][co.y]<fish.sz) {
				ans_list[ans_N++] = co;
			}
			if(ans_N == 0) {
				for(int i=0; i<4; i++) {
					int nx=co.x+dx[i];
					int ny=co.y+dy[i];
					if(nx<0||ny<0||nx>=n||ny>=n) continue;
					if(chk[nx][ny] == CHKVAL) continue;
					if(v[nx][ny] > fish.sz) continue;
					chk[nx][ny] = CHKVAL;
					q.push(Coord(nx,ny));
				}
			}
		}
		if(ans_N>0) break;
		dist++;
	}
	if(ans_N==0) return 0;
	//printf("ans_N: %d\n", ans_N);

	int mni = 0;
	for(int i=1; i<ans_N; i++) {
		if(ans_list[i] < ans_list[mni]) {
			mni = i;
		}
	}

	fish.co = ans_list[mni];
	v[fish.co.x][fish.co.y] = 0;
	fish.refresh();
	//fish.print();
	return dist;
}
int main() {
	Fish fish;
	scanf("%d", &n);
	int fish_cnt=0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			scanf("%d", &v[i][j]);
			if(v[i][j] == 9) {
				fish.co = Coord(i,j);
				v[i][j] = 0;
			}
			else if(v[i][j] > 0) fish_cnt++;
		}
	}

	int prv_ans=-1;
	int ans=0;
	while(fish_cnt>0) {
		ans+=bfs(fish);
		if(prv_ans == ans) break;
		prv_ans = ans;
	}
	printf("%d\n", ans);
	return 0;
}
