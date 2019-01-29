/*	Copyright 2019 heiyedeshengyin All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//===========二叉搜索树的结点===========
template <typename T>
struct TreeNode
{
	T data;	//结点中存储的数据
	TreeNode<T> *left;	//结点的左孩子
	TreeNode<T> *right;	//结点的右孩子
	//结点的构造函数
	TreeNode(T x)
	{
		data = x;
		left = nullptr;
		right = nullptr;
	}
};

//===========二叉搜索树===========
template <typename T>
class BinarySearchTree
{
private:
	TreeNode<T> *root;	//根结点
public:
	BinarySearchTree();	//无参构造函数
	BinarySearchTree(T x);	//创建一个根结点
	BinarySearchTree(TreeNode<T>* _root);	//用一个已有的根结点赋值给根结点
	BinarySearchTree(BinarySearchTree<T> &_root);	//拷贝构造函数
	BinarySearchTree(vector<T> v);	//用一个数组来创建二叉搜索树
	~BinarySearchTree();	//析构函数
	vector<T> PerOrderTraverse();	//先序遍历
	vector<T> InOrderTraverse();	//中序遍历
	vector<T> PostOrderTraverse();	//后序遍历
	vector<T> LevelOrderTraverse();	//层序遍历
	void clear();	//清空二叉树
	bool isEmpty();	//判断二叉树是否为空
	int height();	//获取树的高度
	int size();	//获取元素个数
	TreeNode<T>* search(T e);	//搜索结点
	bool insert(T e);	//插入节点
	bool remove(T e);	//删除结点
	T operator[] (int r);	//重载[]操作符
};

//===========函数的具体实现===========
/*
	无参构造函数
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}

//------------------------------------------------------
/*
	有参构造函数
	T x:二叉树根结点的值
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(T x)
{
	root = new TreeNode<T>(x);
}

//------------------------------------------------------
/*
	复制一个二叉树到新的内存中
	TreeNode<T>* &_root:被复制的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* copyBitree(TreeNode<T>* &_root)
{
	if (_root)
	{
		TreeNode<T>* another_root;
		another_root = new TreeNode<T>(_root->data);
		if (_root->left)
			another_root->left = copyBitree(_root->left);
		if (_root->right)
			another_root->right = copyBitree(_root->right);

		return another_root;
	}
	else
		return nullptr;
}

//------------------------------------------------------
/*
	用一个已有的根结点赋值给根结点
	TreeNode<T>* _root:已有的根结点
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(TreeNode<T>* _root)
{
	root = copyBitree(_root);
}

//------------------------------------------------------
/*
	拷贝构造函数
	BinarySearchTree<T> &_root:被拷贝的二叉搜索树
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &_root)
{
	root = copyBitree(_root.root);
}

//------------------------------------------------------
/*
	用一个数组来创建二叉搜索树
	vector<T> v:用来创建二叉搜索树的数组
*/
template <typename T>
BinarySearchTree<T>::BinarySearchTree(vector<T> v)
{
	root = new TreeNode<T>(v.front());
	for (unsigned int i = 1; i < v.size(); i++)
		insert(v[i]);
}

//------------------------------------------------------
/*
	销毁一个二叉树
	TreeNode<T>* &root:二叉树的根结点

	@Return void
*/
template <typename T>
void distoryBiTree(TreeNode<T>* &root)
{
	if (root)
	{
		TreeNode<T> *left;
		TreeNode<T> *right;
		left = root->left;
		right = root->right;
		delete root;
		root = nullptr;
		if (left)
			distoryBiTree(left);
		if (right)
			distoryBiTree(right);
	}
}

//------------------------------------------------------
/*
	析构函数
*/
template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	distoryBiTree(root);
}

//------------------------------------------------------
/*
	先序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void Per(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		v.push_back(root->data);
		Per(root->left, v);
		Per(root->right, v);
	}
}

//------------------------------------------------------
/*
	先序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> BinarySearchTree<T>::PerOrderTraverse()
{
	vector<T> v;
	Per(root, v);
	return v;
}

//------------------------------------------------------
/*
	中序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void In(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		In(root->left, v);
		v.push_back(root->data);
		In(root->right, v);
	}
}

//------------------------------------------------------
/*
	中序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> BinarySearchTree<T>::InOrderTraverse()
{
	vector<T> v;
	In(root, v);
	return v;
}

//------------------------------------------------------
/*
	后序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void Post(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		Post(root->left, v);
		Post(root->right, v);
		v.push_back(root->data);
	}
}

//------------------------------------------------------
/*
	后序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> BinarySearchTree<T>::PostOrderTraverse()
{
	vector<T> v;
	Post(root, v);
	return v;
}

//------------------------------------------------------
/*
	层序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> BinarySearchTree<T>::LevelOrderTraverse()
{
	vector<T> v;
	if (!root)
		return v;

	queue<TreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		TreeNode<T>* Node;
		Node = q.front();
		v.push_back(Node->data);
		q.pop();
		if (Node->left)
			q.push(Node->left);
		if (Node->right)
			q.push(Node->right);
	}
	return v;
}

//------------------------------------------------------
/*
	清空二叉树

	@Return void
*/
template <typename T>
void BinarySearchTree<T>::clear()
{
	distoryBiTree(root);
}

//------------------------------------------------------
/*
	判断二叉树是否为空

	@Return bool
*/
template <typename T>
bool BinarySearchTree<T>::isEmpty()
{
	if (root)
		return true;
	else
		return false;
}

//------------------------------------------------------
/*
	返回二叉树的高度
	TreeNode<T>* &root:二叉树的根结点

	@Return int
*/
template <typename T>
int getHeight(TreeNode<T>* &root)
{
	if (root)
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;
}

//------------------------------------------------------
/*
	返回二叉树的高度

	@Return int
*/
template <typename T>
int BinarySearchTree<T>::height()
{
	return getHeight(root);
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数
	TreeNode<T>* &root:二叉树的根结点

	@Return int
*/
template <typename T>
int getSize(TreeNode<T>* &root)
{
	if (root)
		return 1 + getSize(root->left) + getSize(root->right);
	else
		return 0;
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数

	@Return int
*/
template <typename T>
int BinarySearchTree<T>::size()
{
	return getSize(root);
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	TreeNode<T>* &root:二叉搜索树的根结点
	T val:要搜索的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* searchIn(TreeNode<T>* &root, T val)
{
	if (root == nullptr)
		return nullptr;

	if (root->data == val)
		return root;
	else
		if (root->data > val)
			return searchIn(root->left, val);
		else
			return searchIn(root->right, val);
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	T e:要搜索的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* BinarySearchTree<T>::search(T e)
{
	return searchIn(root, e);
}

//------------------------------------------------------
/*
	插入结点,并返回插入后的根结点
	TreeNode<T>* &root:二叉搜索树的根结点
	T val:要插入的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* insertIn(TreeNode<T>* &root, T val)
{
	if (root == nullptr)
		return new TreeNode<T>(val);

	if (root->data > val)
		root->left = insertIn(root->left, val);
	else if (root->data < val)
		root->right = insertIn(root->right, val);

	return root;
}

//------------------------------------------------------
/*
	插入结点,若插入成功则返回true,失败则返回false
	T e:要插入的值

	@Return bool
*/
template <typename T>
bool BinarySearchTree<T>::insert(T e)
{
	if (search(e))
		return false;

	insertIn(root, e);
	return true;
}

//------------------------------------------------------
/*
	删除结点,并返回删除后的根结点
	TreeNode<T>* &root:二叉搜索树的根结点
	T val:要删除的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* removeAt(TreeNode<T>* &root, T val)
{
	if (root == nullptr)
		return nullptr;

	if (root->data > val)
		root->left = removeAt(root->left, val);
	else if (root->data < val)
		root->right = removeAt(root->right, val);
	else
	{
		if (root->left == nullptr&&root->right == nullptr)
			root = nullptr;
		else if (root->left == nullptr)
			root = root->right;
		else if (root->right == nullptr)
			root = root->left;
		else
		{
			TreeNode<T> *minnode = root->right;
			while (minnode->left != nullptr)
				minnode = minnode->left;
			root->data = minnode->data;
			root->right = removeAt(root->right, minnode->data);
		}
	}
	return root;
}

//------------------------------------------------------
/*
	删除结点,若删除成功则返回true,失败则返回false
	T e:要删除的值

	@Return bool
*/
template <typename T>
bool BinarySearchTree<T>::remove(T e)
{
	if (!search(e))
		return false;

	removeAt(root, e);
	return true;
}

//------------------------------------------------------
/*
	重载[]操作符,按中序遍历输出
	int r:索引

	@Return T
*/
template <typename T>
T BinarySearchTree<T>::operator[] (int r)
{
	if (r < 0 || r >= size())
		return NULL;
	
	vector<T> v = InOrderTraverse();
	return v[r];
}

//------------------------------------------------------
/*
	重载<<操作符,按中序遍历输出
	ostream &os:输出流
	BinarySearchTree<T> &m:要输出的二叉搜索树

	@Return ostream
*/
template <typename T>
ostream &operator<<(ostream &os, BinarySearchTree<T> &m)
{
	vector<T> v = m.InOrderTraverse();
	if (v.size() == 0)
		return os;

	if (v.size() == 1)
	{
		os << v.front();
		return os;
	}
	else
	{
		for (unsigned int i = 0; i < v.size() - 1; i++)
			os << v[i] << " ";
		os << v.back();
		return os;
	}
}

#endif // !BINARYSEARCHTREE
