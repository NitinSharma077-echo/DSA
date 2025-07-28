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
    //same tree
    bool sametree(TreeNode* p, TreeNode* q) {
        if(p==nullptr || q==nullptr){
            return false;
        }
        if (!p && !q) return true;
        if (p->val != q->val) return false;
        return sametree(p->left,q->left) && sametree(p->right,q->right);
    }
    //max depth
    int maxdepth(TreeNode* root){
        if(root == NULL) return 0;
        return 1+max(maxdepth(root->left), maxdepth(root->right));
    } 
    //min depth
    int mindepth(TreeNode* root){
        if(root == NULL) return 0;
        return 1+min(mindepth(root->left), mindepth(root->right));
    }    
    //symmetric tree
    bool symmetric(TreeNode* root){
        
    } 
};
