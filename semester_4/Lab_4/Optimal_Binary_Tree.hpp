#include "Optimal_Binary_Tree.h"

const double INF = 1e9+7;

vector <double> random_vector(int len, double capacity){
    vector <int> distribution;
    int sum = 0;
    for(int i = 0; i < len; i++){
        distribution.push_back(randomInt(1,10));
        sum += distribution[i];
    }
    double part = capacity/(1.0*sum);
    vector <double> result;
    for(int i = 0; i < len; i++)
        result.push_back(part*distribution[i]);
    return result;
}

template <class T>
double Optimal_Binary_Tree<T>::sum(int i, int j){
    if(j < i) return (i == j+1 ? _miss_probabilities[i] : 0);
    double node_sum = _partial_sum[j + 1] - _partial_sum[i];
    if(i > 0)
        node_sum += _partial_error_sum[j + 1] - _partial_error_sum[i-1];
    else
        node_sum += _partial_error_sum[j + 1];
    return node_sum;
}

int c = 0;
int cc = 0;

template <class T>
double Optimal_Binary_Tree<T>::go(int i, int j)
{
    c++;
    double temp;
    if (i > j)
        return (i == j+1 ? _miss_probabilities[i] : 0);
    if (DP[i][j] == INF){
        for (int k = i; k <= j; k++){
            cc++;
            if(k == 0)
                temp = _partial_error_sum[0];
            else
                temp = go(i,k-1);
            temp += go(k+1,j);
            temp += sum(i,j);
            //temp -= _values_probabilities[k];
            if (temp < DP[i][j]) {
                DP[i][j] = temp;
                _root[i][j] = k;
            }
        }
    }


    return DP[i][j];
}

template <class T>
Node<T>* Optimal_Binary_Tree<T>::build_optimal_tree(const vector<shared_ptr<T>> &included, int left, int right) {
    if(left > right)
        return nullptr;
    int root_id = _root[left][right];
    auto new_root = new Node<T>(included[root_id]);
    new_root->left = build_optimal_tree(included, left, root_id-1);
    new_root->right = build_optimal_tree(included, root_id + 1, right);
    return new_root;
}

template <class T>
bool lesser(shared_ptr<T> a, shared_ptr<T> b){
    return (*a) < (*b);
}

template <class T>
Optimal_Binary_Tree<T>::Optimal_Binary_Tree(const vector <shared_ptr<T>>& included,
                                             std::vector <double> value_probabilities,
                                             std::vector <double> miss_value_probabilities)  {
    int n = included.size();

    if(value_probabilities.empty()){
        //sort(included.begin(), included.end(), lesser);
        cout << "Генерація імовірностей для пошуку елементів дерева:\n";
        double silver_line = 0.8;


        if(value_probabilities.empty() && miss_value_probabilities.empty()){
            value_probabilities = random_vector(n, silver_line);
            miss_value_probabilities = random_vector(n+1, 1-silver_line);
        }
        else if(miss_value_probabilities.empty()){
            silver_line = 0;
            for(int i = 0; i < n; i++)
                silver_line += value_probabilities[i];
            miss_value_probabilities = random_vector(n+1, 1-silver_line);
        }
    }
    cout << "Less than " << convert_to_string(included[0]) << " : " <<   miss_value_probabilities[0] << endl;
    for(int i = 0; i < n-1; i++){
        cout << convert_to_string(included[i]) << " : " << value_probabilities[i] << endl;
        cout << "Lies in (" << convert_to_string(included[i]) << "; " << convert_to_string(included[i+1]) << ") : " << miss_value_probabilities[i+1] << endl;
    }
    cout << convert_to_string(included[n - 1]) << " : " << value_probabilities[n - 1] << endl;
    cout << "Greater than"  << convert_to_string(included[n - 1]) << " : " <<   miss_value_probabilities[n - 1];


    _values_probabilities = value_probabilities;
    _miss_probabilities = miss_value_probabilities;

    DP.resize(n+1, vector <double>(n+1,0));
    _partial_sum.resize(n+1, 0);
    _partial_error_sum.resize(n+1, 0);
    _root.resize(n+1, vector <int>(n+1, -1));
    _partial_error_sum[0] = _miss_probabilities[0];


    for(int i = 0; i <= n; i++){
        if(i > 0){
            _partial_sum[i] = _partial_sum[i-1] + _values_probabilities[i-1];
            _partial_error_sum[i] = _partial_error_sum[i-1] + _miss_probabilities[i];
        }
        for(int j = 0; j <= n; j++){
            if(i == j+1)
                DP[i][j] = _miss_probabilities[i];
            else
                DP[i][j] = INF;
        }
    }
    go(0,n-1);
    cout << "NUMBER OF \'GO\': " << c << endl;
    cout << "NUMBER OF \'GO++\': " << cc << endl;
    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << "(" << DP[i][j] << ", "  << _root[i][j] << ") ";
        }
        cout << endl;
    }*/
    root = build_optimal_tree(included, 0, n-1);
}

template <class T>
Optimal_Binary_Tree<T>::~Optimal_Binary_Tree(){
    TreeInterface<T>::delete_subtree(root);
}


template <class T>
void Optimal_Binary_Tree<T>::print(){
    if(!root)
        std::cout << "Tree is empty!\n";
    else
        Optimal_Binary_Tree<T>::print_node(root);
}

template <class T>
bool Optimal_Binary_Tree<T>::find_element(shared_ptr<T> elem){
    return TreeInterface<T>::find_node(root, elem);
}

template <class T>
bool Optimal_Binary_Tree<T>::insert_element(shared_ptr<T>) {
    std::cout << "Не можна вставляти елементи в оптимальне бінарне дерево.\n";
    std::cout << "Для збереження властивостей дерево має бути статичним." << endl;

    return false;
}

template <class T>
void Optimal_Binary_Tree<T>::delete_element(shared_ptr<T>) {
    std::cout << "Не можна видаляти елементи з оптимального бінарного дерева.\n";
    std::cout << "Для збереження властивостей дерево має бути статичним." << endl;
}

template <class T>
void Optimal_Binary_Tree<T>::print_node(Node<T>* cur, int depth, bool left, vector<bool> draw) {
    if (cur == nullptr)
        return;
    vector<bool> new_draw = draw;
    new_draw.push_back(false);
    if (depth > 0)
        new_draw[depth] = left;
    if(cur->right != nullptr){
        print_node(cur->right, depth + 1, false, new_draw);
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
    }
    for (int i = 0; i < depth; i++) {
        cout << (draw[i] ? "|" : " ") << "\t";
    }

//    cout <<  "(" << _values_probabilities[0] << ")";
    cout << convert_to_string(cur->value) << std::endl;


    if(depth > 0)
        new_draw[depth] = !left;
    if(cur->left != nullptr){
        for (int i = 0; i <= depth; i++) {
            cout << (new_draw[i] ? "|" : " ") << "\t";
        }
        cout << "|\n";
        print_node(cur->left, depth + 1, true, new_draw);
    }
}


template <class T>
Node<T>* Optimal_Binary_Tree<T>::minimum(Node<T>* cur){
    while(cur->left)
        cur = cur->left;
    return cur;
}

template<class T>
void Optimal_Binary_Tree<T>::perform(const string &command) {
}

