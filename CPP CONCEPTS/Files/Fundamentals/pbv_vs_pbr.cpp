    #include<iostream>
    #include<vector>

    void passbyval(std::vector<int> arr){
        arr[0] = 100;
    }

    void passbyref(std::vector<int>& arr){
        arr[0] = 200;
    }


    int main(){
        std::vector<int> arr(100000000);
        std::fill(std::begin(arr), std::end(arr), 1);
        //passbyval(arr);
        passbyref(arr);
        return 0;
    }