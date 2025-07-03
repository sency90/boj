#include <cstdio>
#include <queue>
using namespace std;
int N,K;
constexpr int NA = -1; //not available

struct Can{
	int dur, ri;
	Can():ri(NA) {}
	Can(int dur, int ri):dur(dur),ri(ri) {}
};

int next(int pos) {
	pos++;
	return pos % (N*2);
}

deque<Can> dq;

void go_around() {
	dq[N-1].ri = NA;
	Can last = dq.back();
	last.ri = NA;

	dq.pop_back();
	dq.push_front(last);
	dq[N-1].ri = NA;
}

int main() {
	scanf("%d%d",&N,&K);
	int lim = N*2;
	for(int i=0; i<lim; i++) {
		Can can;
		scanf("%d", &can.dur);
		dq.push_back(can);
	}

	int stage = 0, rn=0;
	while(true) {
		stage++;
		go_around();

		int cnt=0;
		for(int i=dq.size()-1; i>=0; i--) {
			if(dq[i].dur==0) cnt++;
			if(dq[i].ri<0) continue;
			int ni = next(i);
			if(dq[ni].dur>=1 && dq[ni].ri<0) {
				if(--dq[ni].dur == 0) cnt++;
				dq[ni].ri = dq[i].ri;
				dq[i].ri = NA;
			}
		}
		dq[N-1].ri = NA;

		if(dq[0].dur>=1) {
			if(--dq[0].dur == 0) cnt++;
			dq[0].ri = rn++;
		}
		dq[N-1].ri = NA;

		if(cnt >= K) {
			printf("%d\n", stage);
			return 0;
		}
	}

	return 0;
}
