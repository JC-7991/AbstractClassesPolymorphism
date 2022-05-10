#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

/*
Input:
3 1
set 1 2
get 1
get 2
Output:
2
-1
*/

struct Node{

  Node* next;
  Node* prev;
  
  int value;
  int key;
  
  Node(Node* p, Node* n, int k, int val): prev(p), next(n), key(k), value(val){};
  Node(int k, int val): prev(NULL), next(NULL), key(k), value(val){};

};

class Cache{
   
  protected:

    std::map<int, Node*> mp; //map the key to the node in the ll
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

#define key first
#define val second

class LRUCache {
    int cp;
    std::map<int, std::list<std::pair<int, int> >::iterator> mp;
    std::list<std::pair<int, int> > lru;
public:
    LRUCache(int capacity) : cp(capacity){}
    void set(int key, int val) {
        if(mp.find(key) != mp.end()) {
            mp[key]->key = key;
            mp[key]->val = val;
        }
        else {
            lru.push_front({key, val});
            mp[key] = lru.begin();
            if(lru.size() > cp) {
                mp.erase(lru.back().key);
                lru.pop_back();
            }
        }
    }
    int get(int key) {
        if(mp.find(key) != mp.end()) {
            lru.push_front(*mp[key]);
            lru.erase(mp[key]);
            mp[key] = lru.begin();
            return mp[key]->val;
        }
        else
            return -1;
    }
};
int main() {
   int n, capacity,i;
   std::cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      std::string command;
      std::cin >> command;
      if(command == "get") {
         int key;
         std::cin >> key;
         std::cout << l.get(key) << std::endl;
      } 
      else if(command == "set") {
         int key, value;
         std::cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}