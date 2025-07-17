#include <cstdio>
#include <map>
#include <unordered_set>
using namespace std;
constexpr int N = 4;
constexpr int NA = -1;
int M,S;
int id;
struct Fish{
	int x,y,d,id;
	Fish(){}
	Fish(int x, int y, int d):x(x),y(y),d(d) {}
	Fish(int x, int y, int d, int id):x(x),y(y),d(d),id(id) {}
	bool operator<(const Fish & rhs) const {
		return id<rhs.id;
	}
	void print() const {
		printf("[%2d] (%d,%d), dir:%d\n", id,x,y,d);
	}
};

int idno;
map<int, Fish> fid_fish_dic, fid_fish_copydic;
int dx[] = {0,-1,-1,-1,0,1,1,1};
int dy[] = {-1,-1,0,1,1,1,0,-1};
Fish shark;
int smell[N][N];

inline void DecreaseSmell() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if(smell[i][j]) smell[i][j]--;
		}
	}
}

inline void NextDir(int & dir) {
	dir=(dir+7)&7;
}

inline bool IsOutOfBound(int x, int y) {
	return x<0||y<0||x>=N||y>=N;
}

constexpr int U = 0;
constexpr int L = 1;
constexpr int D = 2;
constexpr int R = 3;
int px[] = {-1,0,1,0};
int py[] = {0,-1,0,1};

unordered_set<int> fid_uset[N][N];

//2 2 2
//11 0000  C 3
//0x30 0xC 0x3
long long CV;
long long chk[4][4];
bool CanGo(const Fish & s, int dirbit) {
	int p[3] = {(dirbit & 0x30)>>4, (dirbit&0xC)>>2, dirbit&0x3};
	int sx=s.x, sy=s.y;
	for(int i=0; i<3; i++) {
		sx += px[p[i]];
		sy += py[p[i]];
		if(IsOutOfBound(sx,sy)) return false;
	}
	return true;
}

int GoFake(const Fish & s, int dirbit) {
	CV++;
	int p[3] = {(dirbit & 0x30)>>4, (dirbit&0xC)>>2, dirbit&0x3};
	int sx=s.x, sy=s.y;
	int ret=0;
	for(int i=0; i<3; i++) {
		sx += px[p[i]];
		sy += py[p[i]];
		if(chk[sx][sy]!=CV) {
			ret += fid_uset[sx][sy].size();
			chk[sx][sy] = CV;
		}
	}
	return ret;
}

void Go(Fish & s, int dirbit) {
	int p[3] = {(dirbit & 0x30)>>4, (dirbit&0xC)>>2, dirbit&0x3};
	int sx=s.x, sy=s.y;
	for(int i=0; i<3; i++) {
		sx += px[p[i]];
		sy += py[p[i]];
		for(int fid : fid_uset[sx][sy]) {
			if(fid_fish_dic.count(fid)>0) {
				fid_fish_dic.erase(fid);
			}
		}
		if(fid_uset[sx][sy].size()>0) {
			smell[sx][sy]=3;
		}
		fid_uset[sx][sy].clear();
	}
	s.x = sx;
	s.y = sy;
}

void debug(int no) {
	for(const auto & it : fid_fish_dic) {
		it.second.print();
	}
}


int main() {
	scanf("%d%d",&M,&S);

	int x,y,d;
	for(int i=0; i<M; i++) {
		scanf("%d%d%d",&x,&y,&d);
		x--; y--; d--;
		fid_fish_dic[i] = Fish(x,y,d,i);
		fid_uset[x][y].insert(i);
	}
	idno = M;

	scanf("%d%d",&x,&y);
	x--; y--;
	shark = Fish(x,y,0,0);
	//debug(1);

	while(S--) {
		//2.
		for(auto & it: fid_fish_dic) {
			int fid = it.first;
			Fish & f = it.second;

			//copy
			fid_fish_copydic[idno] = f;
			fid_fish_copydic[idno].id = idno;
			idno++;

			int dir = f.d;
			for(int i=0; i<8; i++, NextDir(dir)) {
				int nx = f.x + dx[dir];
				int ny = f.y + dy[dir];

				if(IsOutOfBound(nx,ny)) continue;
				if(smell[nx][ny]) continue;
				if(shark.x==nx && shark.y==ny) continue;
				fid_uset[f.x][f.y].erase(f.id);
				f.x = nx;
				f.y = ny;
				f.d = dir;
				fid_uset[f.x][f.y].insert(f.id);
				break;
			}

		}
		//debug(2);

		//3.
		int mx_cnt=-1, mxi=NA;
		for(int i=0; i<64; i++) {
			if(!CanGo(shark,i)) continue;
			int cnt = GoFake(shark,i);
			if(cnt > mx_cnt) {
				mx_cnt = cnt;
				mxi = i;
			}
		}
		//debug(3);

		if(mxi!=NA) {
			//printf("mx_cnt:%d, mxi:%d\n", mx_cnt,mxi);
			Go(shark,mxi);
		}
		//else { puts("ERR"); }

		//4.
		DecreaseSmell();
		//debug(4);

		//5.
		fid_fish_dic.insert(fid_fish_copydic.begin(), fid_fish_copydic.end());
		for(auto & it : fid_fish_copydic) {
			const Fish & f = it.second;
			fid_uset[f.x][f.y].insert(f.id);
		}
		fid_fish_copydic.clear();
		//debug(5);
	}

	printf("%d\n", (int)fid_fish_dic.size());
	return 0;
}
