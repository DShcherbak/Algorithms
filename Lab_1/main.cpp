#include <iostream>
#include <vector>

using namespace std;

const int CNT_FILES = 3;

int n = 10, m = 2;

int read_int_from_binary(){
    return rand()%100;
}

int max_id(vector <int> a){
    int id = 0;
    for(int i = 1; i < CNT_FILES; i++){
        if(a[i] > a[id])
            id = i;
    }
    return id;
}

vector <int> cnt_files(){
    vector <int> cnt_in_file(CNT_FILES);
    cnt_in_file[0] = 1;
    for(int i = 1; i < CNT_FILES; i++)
        cnt_in_file[i] = 0;
    int sum_pieces = 1;
    int cnt_pieces = (n - 1)/m + 1;
    while(sum_pieces < cnt_pieces){
        cout << sum_pieces << " " << cnt_pieces << endl;
        int id_max = max_id(cnt_in_file);
        for(int i = 0; i < CNT_FILES; i++){
            if(i != id_max) {
                sum_pieces += cnt_in_file[id_max];
                cnt_in_file[i] += cnt_in_file[id_max];
            }
            sum_pieces -= cnt_in_file[id_max];
            cnt_in_file[id_max] = 0;
        }
    }
    return cnt_in_file;
}

int main() {

    srand(time(0));
    cout << read_int_from_binary() << endl;
    vector <int> cnt_in_file(CNT_FILES);
    cnt_in_file = cnt_files();
    for(int i = 0; i < CNT_FILES; i++)
        cout << cnt_in_file[i] << " ";

    return 0;
}