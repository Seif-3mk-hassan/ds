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

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    //User::;
    system_manager sys;
    login log(sys);
    log.mainMenu();
    //////
    unordered_map<string, Node> umap;

    //json j;
    for (int i = 0; i < 3; i++)
    {
        Node d;
        umap[to_string(i)]={d.id=to_string(i), d.name="seif "+to_string(i), d.pass="pass"+to_string(i),{},{}};
    }
    for (auto j:umap)
    {
        cout << j.first << " : " << j.second.name <<" "<< j.second.pass <<" "<<j.second.messages.size()<<" "<<j.second.friends.size()<<endl;
    }
    
    //cout << "Hello World" << endl;
    
    return 0;
}

