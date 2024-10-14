#include <iostream>
using namespace std;

char a[11][11],b[101][101];

int main() {
    int n,m,k,i, j, it, it2;
    cin>>n>>m>>k;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin>>a[i][j];
    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            for(it=0;it<k;it++) {
                for(it2=0;it2<k;it2++) {
                    b[(i-1)*k+1+it][(j-1)*k+1+it2]=a[i][j];
                }
            }
        }
    }
    for(i=1;i<=n*k;i++) {
        for(j=1;j<=m*k;j++) {
            cout<<b[i][j];
        }
        cout<<endl;
    }
    return 0;
}