/*
 * @Author: Lei
 * @Date: 2021-03-18 19:23:50
 * @LastEditors: Lei
 * @LastEditTime: 2021-03-18 20:05:59
 */
#include <bits/stdc++.h>
#include <direct.h>
using namespace std;
vector<int> V;
void make_dir(string folderPath) {
    // string folderPath = "input";

    if (0 != access(folderPath.c_str(), 0)) {
        mkdir(folderPath.c_str());
    }
    return;
}
void generate_data(string filename, int k = 0) {
    V.clear();
    // string s = "input/data.txt";
    ofstream outfile(filename);
    ostringstream outstring;
    srand(time(0) + k);
    int n = rand() % 23333 + k;
    // cout << n << '\n';
    outstring << n << "\n";
    for (int i = 0; i < n; i++) {
        V.push_back((rand() * rand() % 5000000));
        outstring << V[i] << " ";
    }
    // string str = outstring.str();
    outfile << outstring.str();
    return;
}
void calculation_result(string filename) {
    // string s = "output/ans.txt";
    sort(V.begin(), V.end());
    ofstream outfile(filename);
    ostringstream outstring;
    for (auto &i : V) {
        outstring << i << " ";
    }
    outfile << outstring.str();
    return;
}
int main() {
    make_dir("input");
    make_dir("output");
    int k = 1;
    cout << "Start generating data:\n";
    for (int i = 1; i < 9; i++) {
        cout << "Generate " << to_string(i) << " set of data:\n";
        string input = "input/data" + to_string(i) + ".in";
        string output = "output/ans" + to_string(i) + ".out";
        generate_data(input, k);
        calculation_result(output);
        k *= 10;
    }
    cout << "Generated\nGood luck!";

    return 0;
}