#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t>0){
        long long  n;
        long long k;
        cin>>n>>k;

        vector<long long> arr(n);
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        vector<long long> temp = arr;
        sort(temp.begin(),temp.end());

        if(arr == temp || k > 1){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }

        t--;
    }
    return 0;
}