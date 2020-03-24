#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector <pair <int, int>> arr, brr;
int n;

void copy(vector<pair<int,int>> &a, vector<pair<int,int>> b){
    for(int i = 0; i < n; i++)
        a[i] = b[i];
}

int len(int m){
    int cnt = 0;
    while(m){
        m/=10;
        cnt++;
    }
    return cnt;
}

void print(vector <pair <int, int>> a){
    for(int i = 0; i < n; i++){
        cout << setw(len(a[i].second)) << a[i].first;
        cout << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        cout << a[i].second << " ";
    }
    cout << "\n---------------------------------\n";
}

void first_sort(vector <pair <int, int>> &a){ // O(n) and stable
    vector <pair <int, int>> result;
    int p = 0;
    for(int i = 0; i < n; i++) {
        if(a[i].first == 0)
            result.push_back(a[i]);
    }
    for(int i = 0; i < n; i++) {
        if(a[i].first == 1)
            result.push_back(a[i]);
    }

    copy(a,result);
}

void second_sort_cool(vector <pair <int, int>> &a){ // stable and O(1) additional memory
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(a[i].first == 0)
            cnt++;
    }
    int p = 0, q = cnt;
    for(int i = 0; i < n; i++){
        if(a[i].first == 0){
            a[i].first = p++;
        }
        else{
            a[i].first = q++;
        }
    }
    p = 0;
    while(p < n){
        if(a[p].first == p)
            p++;
        else
            swap(a[a[p].first], a[p]);
    }
    for(int i = 0; i < n; i++)
        a[i].first = (i < cnt ? 0 : 1);

}

void second_sort(vector <pair <int, int>> &a){ // stable and O(1) additional memory
    int cnt = 0;
    bool flag = true;
    while(flag){
        flag = false;
        for(int j = 0; j < n-1; j++){
            if(a[j].first > a[j+1].first){
                swap(a[j],a[j+1]);
                flag = true;
            }
        }
    }
}

void third_sort(vector <pair <int, int>> &a){ // O(n) of time and O(1) memory
    int p = 0;
    for(int i = 0; i < n; i++){
        if(a[i].first == 0){
            swap(a[p],a[i]);
            p++;
        }
    }
}



int main() {

    srand(time(0));
    cin >> n;
    arr.resize(n);
    brr.resize(n);
    for(int i = 0; i < n; i++){
        arr[i] = {rand()%2,i};
    }
    print(arr);

    copy(brr,arr);
    first_sort(arr);
    print(arr);


    copy(arr,brr);
    second_sort_cool(arr);
    print(arr);


    copy(arr,brr);
    third_sort(arr);
    print(arr);

    return 0;
}