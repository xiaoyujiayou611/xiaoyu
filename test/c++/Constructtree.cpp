#include <iostream>
#include <cstdlib>
using namespace std;
#define LEN 8
struct treenode
{
	int value;
	treenode *left;
	treenode *right;
};
treenode* Construct(int *preorder,int *inorder,int length);
treenode* ConstructCore(int *startpreorder,int *endpreorder,int *startinorder,int *endinorder);
int  print(treenode *r);
int main()
{
	int pre[LEN]={1,2,4,7,3,5,6,8};
	int ino[LEN]={4,7,2,1,5,3,8,6};
	int post[LEN];
	
	treenode *root=Construct(pre,ino,LEN);
	
	print(root);
	return 0;
}

treenode* Construct(int *preorder,int *inorder,int length)
{
	if(preorder == NULL || inorder == NULL || length <= 0)
		return NULL;
	return ConstructCore(preorder,preorder+length-1,inorder,inorder+length-1);
}

treenode* ConstructCore(int *startpreorder,int *endpreorder,int *startinorder,int *endinorder)
{
	int rootvalue=startpreorder[0];
	treenode *root = new treenode();
	root->value=rootvalue;
	root->left=root->right=NULL;
	if(startpreorder==endpreorder)
	{
		if(startinorder == endinorder && *startinorder == *startpreorder)
			return root;
		else 
			cout<<"Invalid input!"<<endl;
	}

	int *inorderroot=startinorder;
	while(inorderroot<=endinorder && *inorderroot != rootvalue)
		inorderroot++;
	if(inorderroot == endinorder && *inorderroot != rootvalue)
		cout<<"Invalid input!"<<endl;
	int leftlen=inorderroot-startinorder;
	if(leftlen>0)
		root->left=ConstructCore(startpreorder+1,startpreorder+leftlen,startinorder,inorderroot-1);
	if(leftlen < endpreorder-startpreorder)
		root->right=ConstructCore(startpreorder+leftlen+1,endpreorder,inorderroot+1,endinorder);
	return root;
}

int  print(treenode *r)
{
	if(r==NULL)
		return 0;
	print(r->left);
	print(r->right);
	cout<<r->value<<endl;
	return r->value;
}

