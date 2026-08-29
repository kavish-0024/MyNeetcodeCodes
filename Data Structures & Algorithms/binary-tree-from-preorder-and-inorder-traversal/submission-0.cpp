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
class Solution {
public:
    TreeNode* build(vector<int>& pre, vector<int>& in, unordered_map<int, int>& mp, int l, int r, int pl, int pr) {
        if (l > r || pl > pr) return nullptr;
        
        int val = pre[pl];
        int idx = mp[val];
        TreeNode *root = new TreeNode(val);
        
        root->left = build(pre, in, mp, l, idx - 1, pl + 1, pl + idx - l);
        root->right = build(pre, in, mp, idx + 1, r, pl + idx - l + 1, pr);
        
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return nullptr;
        
        unordered_map<int, int> mp;
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }
        return build(preorder, inorder, mp, 0, preorder.size() - 1, 0, preorder.size() - 1);
    }
};
