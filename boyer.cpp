#include <bits/stdc++.h>
using namespace std;

int char_in_string(const char a, const string b){
    int n=b.size();
    for(int i=0;i<n;++i){
        if(a==b[i]) return i;
    }
    return -1;
}

bool boyer_moore_horspool(const string a, const string b){
    int n=a.size();
    int m=b.size();
    int i=m-1;
    while(i<n){
        int k=m-1;
        while(k>-1 && a[i]==b[k]){
            i--;
            k--;
        }
        if(k<0) return true;
        else{
            int x = char_in_string(a[i],b);
            if(x<0)
                i=i+m;
            else
                i=i+m-x-1;
        }
    }
    return false;
}

void z_algorithm(const string s, int *z){
    int n=s.size();
    int left,right;
    left=right=0;
    for(int i=1;i<n;++i){
        if(i>right){
            left=right=i;
            while(right<n && s[right-left]==s[right]) right++;
            z[i]=right-left;
            right--;
        }
        else if(z[i-left]<right-i+1) z[i]=z[i-left];
        else{
            left=i;
            while(right<n && s[right-left]==s[right]) right++;
            z[i]=right-left;
            right--;
        }   
    }
}

const int N = 1e3 + 10;
int f[N], a[N], n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        f[i] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[j] <= a[i])
                f[i] = max(f[i], f[j] + 1);
    int mx = f[1];
    for (int i = 2; i <= n; i++)
        mx = max(mx, f[i]);
    cout << mx;
}

int tinhTongSoLe_ChiaDeTri(const vector<int>& arr, int left, int right) {
    // Trường hợp cơ bản: chỉ còn 1 phần tử
    if (left == right) {
        if (arr[left] % 2 != 0) return arr[left]; // Nếu số lẻ, trả về chính nó
        else return 0; // Nếu không phải số lẻ, trả về 0
    }

    // Chia mảng thành 2 nửa
    int mid = (left + right) / 2;

    // Tính tổng các số lẻ ở nửa trái và nửa phải
    int tongTrai = tinhTongSoLe_ChiaDeTri(arr, left, mid);
    int tongPhai = tinhTongSoLe_ChiaDeTri(arr, mid + 1, right);

    // Kết hợp kết quả từ 2 nửa
    return tongTrai + tongPhai;
}

void quickSort(int a[], int left, int right) {
    int i = left, j = right;
    int pivot = a[left + rand() % (right - left)];
    // chia dãy thành 2 phần
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;

        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    // Gọi đệ quy để sắp xếp các nửa
    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}


int a[MAXN]; // mảng trung gian cho việc sắp xếp

// Sắp xếp các phần tử có chỉ số từ left đến right của mảng data.
void mergeSort(int data[MAXN], int left, int right) {
    if (data.length == 1) {
        // Dãy chỉ gồm 1 phần tử, ta không cần sắp xếp.
        return ;
    }
    int mid = (left + right) / 2;
    // Sắp xếp 2 phần
    mergeSort(data, left, mid);
    mergeSort(data, mid+1, right);

    // Trộn 2 phần đã sắp xếp lại
    int i = left, j = mid + 1; // phần tử đang xét của mỗi nửa
    int cur = 0; // chỉ số trên mảng a

    while (i <= mid || j <= right) { // chừng nào còn 1 phần chưa hết phần tử.
        if (i > mid) {
            // bên trái không còn phần tử nào
            a[cur++] = data[j++];
        } else if (j > right) {
            // bên phải không còn phần tử nào
            a[cur++] = data[i++];
        } else if (data[i] < data[j]) {
            // phần tử bên trái nhỏ hơn
            a[cur++] = data[i++];
        } else {
            a[cur++] = data[j++];
        }
    }

    // copy mảng a về mảng data
    for (int i = 0; i < cur; i++)
        data[left + i] = a[i];
}