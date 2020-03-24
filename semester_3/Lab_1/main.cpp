#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int CNT_FILES = 4;
const char* filenames[8] =  {"file0.txt", "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "file6.txt", "file7.txt"};
const char* bin_filenames[8] =  {"file0.bin", "file1.bin", "file2.bin", "file3.bin", "file4.bin", "file5.bin", "file6.bin", "file7.bin"};
bool binary = true;

int n = 100000, m = 5, mod = 100000;
bool testing = false;

vector <fstream> files;

struct Node{
    int val;
    int file_num;
    Node* prevs;
    Node* next;

    Node(int f, int v){
        file_num = f;
        val = v;// = read_int_from_binary(file_num);
        if(testing) cout << "Creating a Node from file " << file_num << " with value: " << val << endl;
        int p = 0;
        prevs = nullptr;
        next = nullptr;
    }
};

int read_int_from_file(int file_num){
    int r;
    if(binary)
        files[file_num].read(reinterpret_cast<char *>(&r), sizeof(r));
    else
        files[file_num] >> r;
 //   cout << "read " << r << endl;
    return r;
}

void write_int_to_file(int file_num, int a){
    if(binary)
        files[file_num].write((char*)&a,sizeof(a));
    else
        files[file_num] << a << " ";
}

void generate_random_binary(int file_num, int n){
    int a;
    write_int_to_file(0,n);
    for(int i = 0; i < n; i++) {
        a = rand() % mod;
 //       cout << a << " ";
        if(i % 100 == 70)
            cout << endl;
        write_int_to_file(0, a);
    }
    cout << endl;
    cout << endl;
}

void print_that_binary(int file_num, int n){
    int a;
    for(int i  = 0; i < n; i++){
        a = read_int_from_file(file_num);
        cout << a << " ";
        if(i % 100 == 70)
            cout << endl;
    }
    cout << endl;
    cout << endl;
}

void add_to_list(Node* &head, int file_num){
    int v;

    v = read_int_from_file(file_num);
    if(v == -1)
        return;
    if(!head){
        head = new Node(file_num, v);
        return;
    }


    Node* new_node = new Node(file_num ,v);

    if(new_node->val < head->val){
        head->prevs = new_node;
        new_node->next = head;
        head = new_node;
        return;
    }
    Node* cur = head;
    while(cur->next && cur->next->val < new_node->val)
        cur = cur->next;
    new_node->next = cur->next;
    if(cur->next) cur->next->prevs = new_node;
    new_node->prevs = cur;
    cur->next = new_node;

}

int max_id(vector <int> a){
    int id = 0;
    for(int i = 1; i < CNT_FILES; i++){
        if(a[i] > a[id])
            id = i;
    }
    return id;
}

int min_id(vector <int> a){
    int id = 0;
    while(a[id] == 0) id++;
    for(int i = 1; i < CNT_FILES; i++){
        if(a[i] != 0 && a[i] < a[id])
            id = i;
    }
    return id;
}

int find_dest(vector <int> a){
    int len = a.size();
    for(int i = 0; i < len; i++)
        if(a[i] == 0)
            return i;
}

int precount_files(vector <int> &pieces_in_file){
    pieces_in_file[0] = 1;
    for(int i = 1; i < CNT_FILES; i++)
        pieces_in_file[i] = 0;
    int sum_pieces = 1;
    int cnt_pieces = (n - 1)/m + 1;
    while(sum_pieces < cnt_pieces){
        int id_max = max_id(pieces_in_file);
        for(int i = 0; i < CNT_FILES; i++) {
            if (i != id_max) {
                sum_pieces += pieces_in_file[id_max];
                pieces_in_file[i] += pieces_in_file[id_max];
            }
        }
        sum_pieces -= pieces_in_file[id_max];
        pieces_in_file[id_max] = 0;
    }

    return sum_pieces;
}

void quick(vector <int> &a, int l, int r)
{
    if(l >= r)
        return;
    int pivot = r;
    int p = l, q = l;
    while(p < r){
        while(a[p] > a[r]) p++;
        swap(a[p],a[q]);
        p++;
        q++;
    }
    //swap(a[m],a[q]);
    quick(a,l,q-1);
    quick(a,q,r);

}

void quick_sort(vector <int> &a, int n = -1){
    if(n == -1)
        n = a.size();
    quick(a,0,n-1);
}


int main() {
    srand(time(0));

    files.resize(CNT_FILES);
    if(binary) {
        files[0].open(bin_filenames[0], ios::in | ios::out | ios::binary);
        generate_random_binary(0, n);
        files[0].seekg(0, ios::beg);
        //  print_that_binary(0, 100);
    }else {
        files[0].close();
        files[0].open(filenames[0], ios::in);
    }
    for(int i = 1; i < CNT_FILES; i++)
        if(binary)
            files[i].open(bin_filenames[i],  ios::in | ios::out | ios::binary | ios::trunc);
        else
            files[i].open(filenames[i],  ios::in | ios::out | ios::trunc);
    n = read_int_from_file(0);
    vector <int> pieces_in_file(CNT_FILES);

    //Count how many chunks should be in each file

    int cnt_pieces = precount_files(pieces_in_file);

    //put 0 chunks into 0-th file

    for(int i = 0; i < CNT_FILES; i++){
        if(pieces_in_file[i] == 0) {
            swap(pieces_in_file[0], pieces_in_file[i]);
            break;
        }
    }

    int cnt_in_piece = min(m,(n-1)/cnt_pieces + 1);

    if(testing){
    for(int i = 0; i < CNT_FILES; i++)
        cout << pieces_in_file[i] << endl;

    }

    int read_numbers = 0;
    int a;
    int file_id = 0;

    if(testing){
        cout << "CURRENT VALUES:\n";
        cout << "Number of pieces: " << cnt_pieces << endl;
        cout << "Number of integers in one piece: " << cnt_in_piece << endl;
    }

    int normal_pieces = 0;

    while(read_numbers < cnt_in_piece*cnt_pieces){
        if(testing) cout << read_numbers << " ... " << file_id << " .. " << n << endl;
        vector <int> operative_memory(m);
        int cnt_in_current_file = 0;
        while(file_id < CNT_FILES && cnt_in_current_file < pieces_in_file[file_id]){
            int cnt_in_current_piece = 0;
            for(int i = 0; i < cnt_in_piece && read_numbers < n; i++){
                read_numbers++;
                cnt_in_current_piece++;
                operative_memory[i] = read_int_from_file(0);
            }
            if(cnt_in_current_piece) normal_pieces++;
            quick_sort(operative_memory, cnt_in_current_piece);
            for(int i = 0; i < cnt_in_current_piece; i++) {
                write_int_to_file(file_id,operative_memory[i]);
            }
            write_int_to_file(file_id,-1);

            cnt_in_current_file++;
        }
        if(read_numbers < n)

            file_id++;
        else{
            if(file_id < CNT_FILES) file_id++;
            read_numbers++;
        }
    }

    for(int i = 0; i < CNT_FILES; i++)
        files[i].seekg(0, ios::beg);
    //files[0].clear();
    if(testing) cout << "Dividing is done!" << endl;
    int id_dest, id_min, times_repeat;
    cnt_pieces = normal_pieces;
    while(cnt_pieces > 1) {

        id_min = min_id(pieces_in_file);
        id_dest = find_dest(pieces_in_file);

        files[id_dest].close();
        if(binary)
            files[id_dest].open(bin_filenames[id_dest],  ios::in | ios::out | ios::binary | ios::trunc);
        else
            files[id_dest].open(filenames[id_dest],  ios::in | ios::out | ios::trunc);

        times_repeat = pieces_in_file[id_min];
        if(testing) cout << id_min << " -> " << id_dest << ": " << times_repeat << endl;
        while (times_repeat) {

            //Create a new list

            Node *head = nullptr;
            Node *cur;
            for (int i = 0; i < CNT_FILES; i++) {
                if (i != id_dest) {
                    add_to_list(head, i);
                }
            }

            //Go through list and add elelments

            while (head) {

                //Write the lowest integer into destination

                write_int_to_file(id_dest,head->val);
                head->val = read_int_from_file(head->file_num);

                //if the file is over - forget it

                if (head->val == -1) {
                    cur = head;
                    head = head->next;
                    cnt_pieces--;
                    delete cur;
                    continue;
                }

                //If our current head turned out to be not the smallest - push it down the list

                cur = head;
                while (cur->next && cur->next->val < head->val)
                    cur = cur->next;
                if (cur != head) {
                    Node *temp = head;
                    head = head->next;
                    temp->next = cur->next;
                    cur->next = temp;

                }

            }

            write_int_to_file(id_dest, -1);
            cnt_pieces++;
            //repeat
            times_repeat--;
        }

        int old_min = pieces_in_file[id_min];
        pieces_in_file[id_dest] = old_min;
        for (int i = 0; i < CNT_FILES; i++) {
            if (i != id_dest)
                pieces_in_file[i] -= old_min;
        }


        files[id_dest].seekg(0, ios::beg);

        if(testing){
            cout << "Current state of pieces in files:\n";
            for (int i = 0; i < CNT_FILES; i++)
                cout << pieces_in_file[i] << " ";
            cout << endl;
        }
    }
   // cout << "Final file: ";
   // print_that_binary(id_dest, n);
    cout << "Output file number: " << id_dest << endl;
    return 0;
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
