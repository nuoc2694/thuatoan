#include <bits/stdc++.h>

using namespace std;

bool solutionA(int n, int k, int a[]){
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;++j){
            int sum=0;
            for(int u=i;u<=j;++u){
                sum=sum+u;
                if(sum==k) return true;
            }
        }
    }
    return false;
}

bool solutionB(int n, int k, int a[]){
    int b[1000];
    b[0]=0;
    for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
    for(int i=0;i<=n;++i){
        for(int j=i;j<=n;++j){
            if(b[j]-b[i]==k) return true;
        }
    }
    return false;
}

bool solutionC(int n, int k, int a[]){
    int b[1000];
    b[0]=0;
    for(int i=1;i<=n;++i) b[i]=b[i-1]+a[i];
    int jp=1;
    for(int i=0;i<=n;++i){
        for(int j=jp;j<=n;++j){
            if(b[j]-b[i]==k) return true;
            else if(b[j]-b[i]>k){
                jp=j;
                break;
            }
        }
    }
    return false;
}


int main(){
    int n,k,a[1000];
    cin >> n;
    for(int i=1;i<=n;++i) cin >> a[i];
    cin >> k;
    cout << solutionC(n,k,a);
    return 0;
}