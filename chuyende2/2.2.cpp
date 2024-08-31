#include <bits/stdc++.h>

using namespace std;

void solutionA(int n){
    int i=2;
    while(n>1){
        if(n%i==0){
            cout << i << " ";
            n=n/i;
        }
        else i++;
    }
    cout << endl;
}

void solutionB(int n){
    int k=0;
    for(int i=1;i<=n;++i){
        if(n%i==0) ++k;
    }
    cout << k << endl; 
}

void solutionC(int n){
    int s=0;
    for(int i=1;i<=n;++i){
        if(n%i==0) s=s+i;
    }
    cout << s << endl;
}

int main(){
    int n;
    cin >> n;
    solutionA(n);
    solutionB(n);
    solutionC(n);
    return 0;
}
/*1 2 3 4 6 9 12 16 32*/