#include <iostream>
#include <vector>

using namespace std;

int n;

int bolting(int nut){
    return nut;
}

bool fits_more(int bolt, int nut){
    return bolt > bolting(nut);
}

bool fits_less(int bolt, int nut){
    return bolt < bolting(nut);
}

bool fits_equal(int bolt, int nut){
    return bolt == bolting(nut);
}

void quicksort(vector <int> &bolts, vector <int> &nuts, int left, int right) {
    if (left >= right)
        return;
    int pivot = bolts[left];
    int p = left;
    for (int i = left; i <= right; i++) {
        if (fits_more(pivot, nuts[i])) {
            swap(nuts[i], nuts[p]);
            p++;
        }
    }
    for (int i = p; i <= right; i++) {
        if (fits_equal(pivot, nuts[i])) {
            swap(nuts[i], nuts[p]);
            break;
        }
    }
    swap(bolts[left], bolts[p]);
    pivot = nuts[p];
    p = left;
    for (int i = left; i <= right; i++){
        if (fits_less(bolts[i], pivot)) {
            swap(bolts[i], bolts[p]);
            p++;
        }
    }
    quicksort(bolts, nuts,left,p-1);
    quicksort(bolts, nuts, p+1, right);

}

int main() {
    vector <int> bolt;
    vector <int> nut;
    cin >> n;
    bolt.resize(n);
    nut.resize(n);
    for(int i = 0; i < n; i++)
        cin >> bolt[i];
    for(int i = 0; i < n; i++)
        cin >> nut[i];
    quicksort(bolt,nut,0,n-1);
    for(int i = 0; i < n; i++)
        cout << bolt[i] << " ";
    cout << endl;
    for(int i = 0; i < n; i++)
        cout << nut[i] << " ";

    return 0;
}
