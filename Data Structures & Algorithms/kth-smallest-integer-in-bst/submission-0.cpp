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
    void h(TreeNode *root,int k,int &cnt,int &ans)
    {
        if(root==nullptr)
        return;
        if(cnt==k)
        return;

        h(root->left,k,cnt,ans);
        cnt++;
        if(cnt==k)
        {ans=root->val;
        return;}
        h(root->right,k,cnt,ans);

        return;
    }
    int kthSmallest(TreeNode* root, int k) 
    {
        int cnt=0;
        int ans=0;
        h(root,k,cnt,ans);
        return ans;
    }
};
