#include <iostream>

using namespace std;

int d_ary_heap[500];
int n;
int d;
bool custom = false;

void print_array(){
    cout << "Current array: ";
    for(int i = 0 ; i < n; i++)
        cout << d_ary_heap[i] << " ";
    cout << endl;

}

void print_tree(int cur = 0, int depth = 0){
    if(n == 0){
        cout << "Empty tree.\n";
        return;
    }
    if(depth == 0)
        cout << "Current heap: \n";
    cout << "|";
    for(int i = 0; i < depth; i++)
        cout << "\t|";
    cout << d_ary_heap[cur] << endl;
    for(int i = 1; i <= d; i++){
        if(cur*d + i < n)
            print_tree(cur*d+i,depth+1);
    }

}

void heapify(int cur){
    int left, right, largest;

    while(true){
        largest = cur;
        int cur_son;
        for(int i = 1; i <= d; i++){
            cur_son = d*cur+i;
            if(cur_son < n && d_ary_heap[cur_son] > d_ary_heap[largest])
                largest = cur_son;
        }
        if(largest == cur)
            break;
        swap(d_ary_heap[cur],d_ary_heap[largest]);
        cur = largest;


        /*
        left = 2*cur + 1;
        right = 2*cur + 2;

        if(left < n && ary_heap[left] > binary_heap[largest])
            largest = left;
        if(binary_heap[right] > binary_heap[largest])
            largest = right;
        if(largest == cur)
            break;
        swap(binary_heap[cur],binary_heap[largest]);
        cur = largest;*/
    }
}

void add_element(int new_ele){
    d_ary_heap[n] = new_ele;
    int cur = n;
    n++;
    while(cur > 0 && d_ary_heap[cur] > d_ary_heap[(cur-1)/d]){
        swap(d_ary_heap[cur],d_ary_heap[(cur-1)/d]);
        cur = (cur-1)/d;
    }
    print_array();
    print_tree();
}

void build_tree(){
    for(int i =  n / d + 1; i >= 0; i--){
        heapify(i);
    }
    print_tree();
}

void remove_max(){
    cout << "Removing " << d_ary_heap[0] << endl;
    n--;
    d_ary_heap[0] = d_ary_heap[n];
    heapify(0);

    print_array();
    print_tree();
}

int main() {
    srand(time(0));
    cout << "Enter the value of d(one element's son amount): ";
    cin >> d;
    cout << "Enter number of elements: ";
    cin >> n;
    int a[500];
    if(custom){
        cout << "Enter n elements: ";
        for(int i = 0; i < n; i++){
            cin >> d_ary_heap[i];
        }
    }
    else{
        for(int i = 0; i < n; i++)
            d_ary_heap[i] = rand()%1000;
        print_array();
    }

    build_tree();
    cout << "Enter new element: ";
    int x; cin >> x;
    add_element(x);

    while(n){
        remove_max();
        cin >> x;
    }
    return 0;
}