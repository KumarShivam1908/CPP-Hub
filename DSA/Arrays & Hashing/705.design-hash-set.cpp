/*
 * @lc app=leetcode id=705 lang=cpp
 *
 * [705] Design HashSet
 */

// @lc code=start
#include <vector>
#include <algorithm>
class MyHashSet {
    private:
        vector<int> hashSet;
    public:
    MyHashSet() {
        // whenever this is call make sure to create a new hashset
}
    
    void add(int key) {
        if(find(hashSet.begin(),hashSet.end(),key)==hashSet.end()){
            hashSet.push_back(key);
        }
    }
    
    void remove(int key) {
        auto it = find(hashSet.begin(),hashSet.end(),key);
        if(it != hashSet.end()){
            hashSet.erase(it);
        }
    }
    
    bool contains(int key) {
        auto it = find(hashSet.begin(),hashSet.end(),key);
        if(it != hashSet.end()){
            return true;
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
// @lc code=end

