## A_Line_Trip

You are given a number line with gas stations at certain positions. You start at position `0` and want to travel to position `x` and return to `0`. Your car consumes 1 liter of fuel per unit distance and can only refuel at gas stations (not at `0` or `x`). Determine the minimum gas tank capacity required to complete the round trip.

---

## Input Format

- The first line contains two integers, `n` and `x`:
    - `n`: Number of gas stations.
    - `x`: The destination point.
- The second line contains `n` integers, the positions of the gas stations in increasing order.

---

## Example Test Case

**Input:**
```
3 7
1 2 5
```

**Explanation:**

- Number of gas stations: `n = 3`
- Destination: `x = 7`
- Gas stations at positions: `1, 2, 5`

---

## Step-by-Step Analysis

### 1. List All Stops

Include the start (`0`), all gas stations, and the destination (`x`):

```
[0, 1, 2, 5, 7]
```

### 2. Calculate Distances Between Consecutive Stops

- 0 → 1: 1
- 1 → 2: 1
- 2 → 5: 3
- 5 → 7: 2

### 3. Consider the Return Trip

- You cannot refuel at `x`, so you must travel from the last gas station to `x` and back to the last gas station without refueling.
- This segment is `2 * (7 - 5) = 4`.

### 4. Find the Maximum Required Segment

The minimum tank capacity must be at least the maximum distance between any two consecutive refueling opportunities (including the round trip to `x`):

- 0 → 1: 1
- 1 → 2: 1
- 2 → 5: 3
- 5 → 7 and back: 4

**Minimum tank size required:** `4`

---

## Implementation

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int main(){
        int t;
        cin >> t;
        while(t > 0){
                int n, x;
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
```

---

## Complexity Analysis

- **Time Complexity:** O(n) per test case (for iterating through the points).
- **Space Complexity:** O(n) (for storing the points).

---

## Key Insights for Competitive Programming

- Always consider the edge case where you cannot refuel at the destination.
- The critical segment is the last stretch to `x` and back to the last gas station.
- Sorting the gas stations is not needed if input is already sorted.
- The answer is the maximum of all single-leg distances and the double distance for the last segment.

