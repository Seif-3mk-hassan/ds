#include<iostream>
#include<cmath>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<stack>
#include<deque>
#include<string>

using namespace std;

#define ll long long
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ld long double
#define vi vector<ll>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    fileman fileManager;
fileManager.readFromFile("users.json");

user newUser("001", "ahmed", "1234");
fileManager.addUser(newUser);

fileManager.writeToFile("users.json");

    cout << "Hello World" << endl;
    return 0;
}
// This code finds the minimum absolute difference between elements of two arrays a and b.
//And this is zyad testing github
// abdallah
//seif
// omar
