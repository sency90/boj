#include <cstdio>
using namespace std;
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    if(n*m%3==0) puts("YES");
    else puts("NO");
    return 0;
}
