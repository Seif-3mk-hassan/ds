#include <iostream>
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
#include "user.h"
#include "system_manger.h"
#include "login.h"
//#include<vector>
//#include<D:/ggggg/vcpkg/packages/nlohmann-json_x64-windows/include/nlohmann/json.hpp>
using namespace std;

#define ll long long
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ld long double
#define vi vector<ll>


//using json = nlohmann::json;

struct Node {
    string id;
    string name;
    string pass;
    vector<string> friends;
    stack<string> messages;
};
int main() {

    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    system_manager sys;
    login log(sys);
    log.mainMenu();
    //////
    unordered_map<string, Node> umap;


    return 0;
}

