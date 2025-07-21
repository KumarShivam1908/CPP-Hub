#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t > 0){
        int n;
        int x;
        cin >> n >> x;
        vector<long long> points;
        points.push_back(0);
        for(int i = 0; i < n; i++){
            long long point;
            cin >> point;
            points.push_back(point);
        }
        points.push_back(x);
        int sz = points.size();

        long long max_distance = LLONG_MIN;
        for(int i = 1; i < sz; i++){
            if(i == sz - 1){
                max_distance = max(max_distance, 2LL * (points[i] - points[i-1]));
            }else{
                max_distance = max(max_distance, points[i] - points[i-1]);
            }   
        }
        cout << max_distance << endl;
        t--;
    }
}