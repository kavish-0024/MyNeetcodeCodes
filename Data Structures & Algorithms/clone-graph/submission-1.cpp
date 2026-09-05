// /*
// // Definition for a Node.
// class Node {
// public:
//     int val;
//     vector<Node*> neighbors;
//     Node() {
//         val = 0;
//         neighbors = vector<Node*>();
//     }
//     Node(int _val) {
//         val = _val;
//         neighbors = vector<Node*>();
//     }
//     Node(int _val, vector<Node*> _neighbors) {
//         val = _val;
//         neighbors = _neighbors;
//     }
// };
// */

// class Solution {
// public:
//     Node* dfs(Node* node, unordered_map<Node*,Node*>&mp)
//     {
//         if(mp.contains(node))
//         return mp[node];
//         Node *root=new Node(node->val);
//         mp[node]=root;
//         for(auto &it:node->neighbors)
//         {
//             root->neighbors.push_back(dfs(it,mp));
//         }
//         return root;
//     }
//     Node* cloneGraph(Node* node) 
//     {
//         if(node==nullptr)
//         return nullptr;

//         unordered_map<Node*,Node*>mp;
//         return dfs(node,mp);
        
//     }
// };


class Solution {
public:
    Node* dfs(Node* node, vector<Node*>& visited)
    {
        if(visited[node->val] != nullptr)
            return visited[node->val];
            
        Node* root = new Node(node->val);
        visited[node->val] = root;
        
        for(auto &it : node->neighbors)
        {
            root->neighbors.push_back(dfs(it, visited));
        }
        
        return root;
    }
    
    Node* cloneGraph(Node* node) 
    {
        if(node == nullptr)
            return nullptr;
        vector<Node*> visited(101, nullptr); 
        return dfs(node, visited);
    }
};