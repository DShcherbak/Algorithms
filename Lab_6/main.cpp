#include <iostream>
#include <string>
#include <vector>

using namespace std;

void z_function(std::string s, std::vector <long long> &z, std::string t){
    long long left = 0, right = 0, len = s.length();
    z[1] = 0;
    for(int i = 1; i < len; i++){
        if(i <= right)
            z[i] = std::min(right - i + 1, z[i - left]);
        while(i + z[i] < len && t[z[i]] == s[i + z[i]])
            z[i]++;
        if(i+z[i]-1 > right){
            left = i;
            right = i + z[i] - 1;
        }
    }
}

int main() {
    string s, t;
    cin >> s;
    cin >> t;
    long long hash1, hash2;
    if(s.length() != t.length()){
        cout << "No.\n";
        return 0;
    }
    s = s + s;
    int len = t.length();
    vector <long long> z(2*len);
    z_function(s,z,t);
    for(auto i : z)
        if(i >= len){
            cout << "Yes.\n";
            return 0;
        }
    cout << "No.\n";
    return 0;
}