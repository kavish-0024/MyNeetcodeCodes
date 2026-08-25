class LRUCache {
    // 1. Define the custom Doubly Linked List Node
    struct Node {
        int key;
        int val;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> mp;
    
    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);

    void addNode(Node* newNode) {
        Node* temp = head->next;
        
        newNode->next = temp;
        newNode->prev = head;
        
        head->next = newNode;
        temp->prev = newNode;
    }

    void deleteNode(Node* delNode) {
        Node* prevNode = delNode->prev;
        Node* nextNode = delNode->next;
        
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (mp.find(key) != mp.end()) {
            Node* resNode = mp[key];
            int res = resNode->val;
            
            deleteNode(resNode);
            addNode(resNode);
            
            return res;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            Node* existingNode = mp[key];
            mp.erase(key);
            deleteNode(existingNode);
            delete existingNode; 
        }
        
        if (mp.size() == capacity) {
            Node* lruNode = tail->prev;
            mp.erase(lruNode->key);
            deleteNode(lruNode);
            delete lruNode; 
        }
        
        Node* newNode = new Node(key, value);
        addNode(newNode);
        mp[key] = newNode;
    }
};