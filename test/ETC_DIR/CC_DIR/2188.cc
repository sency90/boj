#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
vector<int> v[201];
int am[201],bm[201];
bool chk[201];
bool bipartite(int x) {
    if(chk[x]) return false;
    chk[x]=true;
    for(auto &y: v[x]) {
        //if(chk[bm[y]]) continue; //안써도 된다. chk[y]로 쓰지 않도록 주의할 것.
        if(!bm[y]||bipartite(bm[y])) {
            am[x]=y;
            bm[y]=x;
            return true;
        }
    }
    return false;
}
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1; i<=n; i++) {
        int si; scanf("%d",&si);
        for(int j=1; j<=si; j++) {
            int s; scanf("%d",&s);
            v[i].push_back(s);
        }
    }
    int ans=0;
    for(int i=1; i<=n; i++) {
        memset(chk, false, sizeof(chk));
        if(bipartite(i)) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
