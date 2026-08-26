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
    int ans=0;
    int h(TreeNode* root)
    {
        if(root==nullptr)
        return 0;

        int left=h(root->left);
        int right=h(root->right);

        ans=max(ans,1+left+right);
        return 1+max(left,right);
    }
    int diameterOfBinaryTree(TreeNode* root) 
    {
        if(root==nullptr)
        return 0;

        h(root);
        return ans-1;
    }
};
