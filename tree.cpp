#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    // Binary Tree Traversals
    TreeNode* inorder(TreeNode* root){
        if (root == NULL) return NULL;
        TreeNode* left =inorder(root->left);
        cout<<root->val<<" ";
        TreeNode* right = inorder(root->right);
     }
    void inorderTraversal(TreeNode* root) {
        inorder(root);
    }
    TreeNode* preorder(TreeNode* root){
        if (root == NULL) return NULL;
        cout<<root->val<<" ";
        TreeNode* left =preorder(root->left);
        TreeNode* right = preorder(root->right);
    }
    void preorderTraversal(TreeNode* root) {
        preorder(root);
    }
    TreeNode* postorder(TreeNode* root){
        if (root == NULL) return NULL;
        TreeNode* left =postorder(root->left);
        TreeNode* right = postorder(root->right);
        cout<<root->val<<" ";
    }
    void postorderTraversal(TreeNode* root) {
        postorder(root);
    }
    //valid BST
    bool isbst(TreeNode* root){
        if(root == NULL) return true;
        if(root->left && root->left->val >= root->val) return false;
        if(root->right && root->right->val <= root->val) return false;
        return isbst(root->left) && isbst(root->right);
    }
    //
};
