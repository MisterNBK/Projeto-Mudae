#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define endl "\n"
#define set(arr, x) memset(arr, x, sizeof(arr))
#define copy(start, dest) memcpy(dest, start, sizeof(start));
#define check(set, element) (set.find(element) != set.end())
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

//------------------------------------------------------------------------
const int mxSize = 1947; //Total number of bundles, don't change unless the dataset updates
//----------------------------SETTINGS------------------------------------
const bool WaifuAnime = false, HusbandAnime = false, WaifuGames = false, HusbandGames = true; //Set the ones you want to optimize for to true (supports multiple options)
const int maxD = 21000; //Max size of disable list
const int maxSeries = 10; //Max number series that can be chosen
//------------------------------------------------------------------------

pair<int, string> dp[2][maxD+3][maxSeries+3];
vector<string> split(string s, string delim){
    vector<string> v;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delim)) != std::string::npos) {
        token = s.substr(0, pos);
        v.pb(token);
        s.erase(0, pos + delim.length());
    }
    v.pb(s);
    return v;
}
int32_t main(void) {
    freopen ("owo.txt","r",stdin);
    cout << "---------------------------------------------" << endl;
    cout << "The program has started! Here are the settings..." << endl;
    cout << "Desired categories: ";
    if(WaifuAnime) cout << "Anime Waifus, ";
    if(HusbandAnime) cout << "Anime Husbands, ";
    if(WaifuGames) cout << "Game Waifus, ";
    if(HusbandGames) cout << "Game Husbands";
    cout << endl;
    cout << "Disablelist size: " << maxD << endl;
    cout << "Maximum number of series: " << maxSeries << endl;
    cout << "---------------------------------------------" << endl;
    for(int i = 0; i < mxSize; i++){
        if(i%10==0){
            cout << "Currently at series #" << i << "... (" << fixed << setprecision(1) << ((double)i/mxSize*100) << "%)" << endl;
        }
        string s;
        getline(cin, s); vector<string> cur = split(s, ",");
        int cost = stoi(cur[1]);
        int value = 0;
        if(WaifuAnime) value+=stoi(cur[2]);
        if(HusbandAnime) value+=stoi(cur[3]);
        if(WaifuGames) value+=stoi(cur[4]);
        if(HusbandGames) value+=stoi(cur[5]);
        if(value == 0) continue;
        //DP state: Max size of <category> I can get with dp[i][j][k], where the first i series are considered,
        //the disable list is up to size j, and the max number of series is k. Series cannot be reused.

        //DP transition: dp[i][j][k] with cost (non-category) c and value (category) v:
        //dp[i][j][k] = dp[i-1][j-cost][k-1]+value
        for(int j = maxD; j >= 0; j--){
            for(int k = maxSeries+1; k >= 0; k--){
                dp[1][j][k] = dp[0][j][k];
                if(k-1 >= 0 && j-cost >= 0){
                    if(dp[0][j-cost][k-1].first+value > dp[1][j][k].first){
                        dp[1][j][k].first = dp[0][j-cost][k-1].first+value;
                        dp[1][j][k].second = dp[0][j-cost][k-1].second+", "+cur[0];
                    }
                }
            }
        }
        swap(dp[1], dp[0]);
    }
    cout << "Calculations are complete! Calculating results..." << endl;
    cout << "---------------------------------------------" << endl;
    pair<int, string> mxValue = {0, ""};
    int si, sj;
    for(int i = 0; i < maxD; i++){
        for(int j = 0; j < maxSeries+1; j++){
            if(mxValue.first < dp[0][i][j].first){
                mxValue = dp[0][i][j];
                si = i;
                sj = j;
            }
        }
    }
    cout << "The expected harem size is " << si << " with " << sj << " series in the list." << endl;
    cout << "The expected size of the desired category is " << mxValue.first << endl;
    cout << "Here are the disablelist commands:" << endl;
    vector<string> ans = split(mxValue.second, ", ");
    for(int i = 1; i < ans.size(); i++){
        cout << "$d " << ans[i] << endl;
    }
    return 0;
}