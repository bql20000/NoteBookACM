#include <string>

using namespace std;

class Trie {
public:
    struct Node {
        int cnt;
        Node* child[26];    // [a-z] only
        Node () : cnt(1) {}
    };
    
    Node* root;

    Trie() {
        root = new Node();
        root->cnt = 0;
    }

    // insert a string 
    void insert(string &s) {
        Node* cur = root;
        for (auto c : s) {
            int idx = c - 'a';
            if (cur->child[idx] == NULL) {
                cur->child[idx] = new Node();
            } 
            else {
                cur->child[idx]->cnt += 1; // cnt += 1 ????  
            }
            cur = cur->child[idx];
        }
    }
};

