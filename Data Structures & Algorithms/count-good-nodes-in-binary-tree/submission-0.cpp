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
    int h(TreeNode* root, int mx)
    {
        if (root == nullptr)
            return 0;

        int ans = 0;
        if (root->val >= mx)
        {
            ans = 1;
        }

        mx = max(mx, root->val);

        ans += h(root->left, mx);
        ans += h(root->right, mx);

        return ans;
    }

    int goodNodes(TreeNode* root)
    {
        return h(root, root->val);
    }
};