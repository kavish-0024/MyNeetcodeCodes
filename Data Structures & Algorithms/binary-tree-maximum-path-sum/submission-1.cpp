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
    int h(TreeNode* root,int &ans)
    {
        if(root==nullptr)
        return 0;

        int left=0,right=0;
        if(root->left)
        left=max(0,h(root->left,ans));
        if(root->right)
        right=max(0,h(root->right,ans));

        ans=max(ans,root->val+left+right);
        return root->val+max(left,right);
    }
    int maxPathSum(TreeNode* root) 
    {
        if(root==nullptr)
        return 0;

       int ans=INT_MIN;

       h(root,ans);

       return ans;
    }
};
