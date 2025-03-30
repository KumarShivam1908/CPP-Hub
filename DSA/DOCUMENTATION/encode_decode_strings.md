---
comments: true
difficulty: Medium
tags:
    - Design
    - Array
    - String
---


# [271. Encode and Decode Strings 🔒](https://leetcode.com/problems/encode-and-decode-strings)

## Description

<!-- description:start -->

<p>Design an algorithm to encode <b>a list of strings</b> to <b>a string</b>. The encoded string is then sent over the network and is decoded back to the original list of strings.</p>

<p>Machine 1 (sender) has the function:</p>

<pre>
string encode(vector&lt;string&gt; strs) {
  // ... your code
  return encoded_string;
}</pre>

Machine 2 (receiver) has the function:

<pre>
vector&lt;string&gt; decode(string s) {
  //... your code
  return strs;
}
</pre>

<p>So Machine 1 does:</p>

<pre>
string encoded_string = encode(strs);
</pre>

<p>and Machine 2 does:</p>

<pre>
vector&lt;string&gt; strs2 = decode(encoded_string);
</pre>

<p><code>strs2</code> in Machine 2 should be the same as <code>strs</code> in Machine 1.</p>

<p>Implement the <code>encode</code> and <code>decode</code> methods.</p>

<p>You are not allowed to&nbsp;solve the problem using any serialize methods (such as <code>eval</code>).</p>

<p>&nbsp;</p>
<p><strong class="example">Example 1:</strong></p>

<pre>
<strong>Input:</strong> dummy_input = [&quot;Hello&quot;,&quot;World&quot;]
<strong>Output:</strong> [&quot;Hello&quot;,&quot;World&quot;]
<strong>Explanation:</strong>
Machine 1:
Codec encoder = new Codec();
String msg = encoder.encode(strs);
Machine 1 ---msg---&gt; Machine 2

Machine 2:
Codec decoder = new Codec();
String[] strs = decoder.decode(msg);
</pre>

<p><strong class="example">Example 2:</strong></p>

<pre>
<strong>Input:</strong> dummy_input = [&quot;&quot;]
<strong>Output:</strong> [&quot;&quot;]
</pre>

<p>&nbsp;</p>
<p><strong>Constraints:</strong></p>

<ul>
	<li><code>1 &lt;= strs.length &lt;= 200</code></li>
	<li><code>0 &lt;= strs[i].length &lt;= 200</code></li>
	<li><code>strs[i]</code> contains any possible characters out of <code>256</code> valid ASCII characters.</li>
</ul>

<p>&nbsp;</p>
<p><strong>Follow up: </strong>Could you write a generalized algorithm to work on any possible set of characters?</p>

<!-- description:end -->

## Solutions

<!-- solution:start -->

### Solution 1: Encode String Length

During encoding, we convert the length of the string into a fixed 4-digit string, add the string itself, and append it to the result string in sequence.

During decoding, we first take the first four digits of the string to get the length, and then cut the following string according to the length. We cut it in sequence until we get the list of strings.

The time complexity is $O(n)$.

<!-- tabs:start -->


#### C++

```cpp
class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string ans;
        for (string s : strs) {
            int size = s.size();
            ans += string((const char*) &size, sizeof(size));
            ans += s;
        }
        return ans;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> ans;
        int i = 0, n = s.size();
        int size = 0;
        while (i < n) {
            memcpy(&size, s.data() + i, sizeof(size));
            i += sizeof(size);
            ans.push_back(s.substr(i, size));
            i += size;
        }
        return ans;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
```

## Length Prefixing Approach

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Codec {
    public:
        // Encodes a list of strings to a single string.
        string encode(vector<string>& strs) {
            // use the concept of sepeator to encode the strings

            if(strs.size() == 0){
                return "";
            }
            string encoded = "";
            for(int i=0;i<strs.size();i++){
                encoded += strs[i] + "#";
            }
            // remove the last sepeator
            encoded = encoded.substr(0, encoded.length()-1);
            return encoded;
            
        }
    
        // Decodes a single string to a list of strings.
        vector<string> decode(string s) {
            vector<string> decoded;
            if(s.length() == 0){
                return decoded;
            }
            // hello#world => hello, world
            string str = "";
            for(int i=0;i<s.length();i++){
                if(s[i] == '#'){
                    decoded.push_back(str);
                    str = "";
                }else{
                    str += s[i];
                }
            }
            // Add the last segment if it's not empty
            if(!str.empty()){
                decoded.push_back(str);
            }
            return decoded;
        }
    };
    
    int main() {
        Codec codec;
        vector<string> strs = {"Hello", "World", "Codec", "Test"};
        string encoded = codec.encode(strs);
        cout << "Encoded: " << encoded << endl;
        vector<string> decoded = codec.decode(encoded);
        cout << "Decoded: ";
        for (const string& str : decoded) {
            cout << str << " ";
        }
        cout << endl;
        return 0;
    }
```

