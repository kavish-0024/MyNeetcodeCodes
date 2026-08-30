/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Codec {
   public:
    string serialize(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        string ans = "";
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                TreeNode* node = q.front();
                q.pop();
                if (node == nullptr) {
                    ans += "*,";
                    continue;
                }
                q.push(node->left);
                q.push(node->right);
                ans += to_string(node->val);
                ans += ',';
            }
        }
        return ans;
    }

    TreeNode* deserialize(string data) 
    {
        stringstream ss(data);
        string a;
        vector<string>ans;
        while (getline(ss,a, ',')) {
            ans.push_back(a);
        }
        int n=ans.size();
        if(ans.size()==1)
        return nullptr;
        int levels=log2(n+1);
        TreeNode*root=new TreeNode(stoi(ans[0]));
        queue<TreeNode*>q;
        q.push(root);
        int i=0;
        while(!q.empty())
        {
            TreeNode*node=q.front();
            q.pop();
            if(ans[2*i+1]=="*")
            node->left=nullptr;
            else
            {node->left=new TreeNode(stoi(ans[2*i+1]));
            q.push(node->left);}

            if(ans[2*i+2]=="*")
            node->right=nullptr;
            else
            {node->right=new TreeNode(stoi(ans[2*i+2]));
            q.push(node->right);}

            i++;

        }
        return root;
        
    }
};
