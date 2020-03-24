#include <iostream>
#include <vector>

using namespace std;

const int HASH = 2;

const long long cnt_powers = 100001, MODULO = 1000000007;

long long prime_powers[cnt_powers];

long long power;

long long mega_power;

void count_powers(int m){
    prime_powers[0] = 1;
    for(int i = 1; i < cnt_powers; i++){
        prime_powers[i] = (prime_powers[i-1] * HASH) % MODULO;
    }
    power = prime_powers[m-1];
    mega_power = prime_powers[0];
}

vector <vector <long long>> translate_matrix(vector <vector <char>> a, int n){
    vector <vector <long long>> result(n, vector <long long> (n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            result[i][j] = (int) (a[i][j] - 'a');
        //    cout << result[i][j] << " ";
        }
       // cout << endl;
    }
    return result;
}

bool Rabin_Carp(vector <vector <long long>> matrix, int n, vector <vector <long long>> temp, int m){
    long long sum = 0;
    vector <vector <long long>> row_sum(n, vector <long long> (n-m+1));

    for(int i = 0; i < n; i++){
        row_sum[i][0] = 0;

        for(int j = 0; j < m; j++)
            row_sum[i][0] += matrix[i][j] * prime_powers[m-j-1];

        for(int j = 1; j <= n-m; j++)
            row_sum[i][j] = (row_sum[i][j-1] - matrix[i][j-1]*prime_powers[m-1])*HASH + matrix[i][j+m-1];

    }

    // now we have a row_sum array;

    long long hash  = 0;
    for(int i = m-1; i >= 0; i--){
        for(int j = m-1; j >=0; j--){
            hash += (temp[i][j] * prime_powers[(m-i-1)*m+(m-j-1)]);
        }
    }

    vector <vector <long long>> dp(n, vector <long long> (n-m+1));
    for(int j = 0; j <= n-m; j++){
        dp[0][j] = 0;

        for(int i = 0; i < m; i++)
            dp[0][j] += row_sum[i][j]*prime_powers[(m-i-1)*(m)];
    }
    for(int j = 0; j <= n-m; j++)
        if(dp[0][j] == hash)
            return true;

    for(int i = 1; i <= (n-m); i++){
        for(int j = 0; j <= (n-m); j++){
            dp[i][j] = (dp[i-1][j] - row_sum[i-1][j]*prime_powers[m*(m-1)]) * prime_powers[m] + row_sum[i+m-1][j];
            if(dp[i][j] == hash)
                return true;
        }
    }
    return false;
}


int main() {
    int n, m;
    cin >> n >> m;
    count_powers(m);
    vector <vector <char>> matrix(n, vector <char> (n)), temp(m, vector <char> (m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
    for(int i = 0 ; i < m; i++)
        for(int j = 0; j < m; j++)
            cin >> temp[i][j];
    cout << (Rabin_Carp(translate_matrix(matrix,n),n,translate_matrix(temp,m), m) ? "Yes.\n" : "No.\n");

    return 0;
}

/*
4
3
a a b a
a a b b
a a b b
a a b a
a b a
a b b
a b b
 */
