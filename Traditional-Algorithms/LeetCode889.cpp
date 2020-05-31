/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        return buildTree(pre, 0, pre.size()-1, post, 0, post.size()-1);
    }
    
    TreeNode* buildTree(vector<int>& pre, int preLeft, int preRight, vector<int>& post, int postLeft, int postRight){
        if(preLeft > preRight || postLeft > postRight) return nullptr;
        TreeNode * root = new TreeNode(pre[preLeft]);
        if (preLeft == preRight) return root;   //这里是一个关键的递归结束出口，这里和LeetCode105.cpp LeetCode106.cpp不同
        auto it = find(post.begin(), post.end(), pre[preLeft+1]);
        int i = distance(begin(post), it);
        root->left = buildTree(pre, preLeft+1, preLeft - postLeft + i + 1, post, postLeft, i);
        root->right = buildTree(pre, preLeft - postLeft + i + 2, preRight, post, i+1, postRight - 1);
        return root;
    }
};