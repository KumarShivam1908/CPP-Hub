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