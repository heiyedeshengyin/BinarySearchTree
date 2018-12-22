/*	Copyright 2018 heiyedeshengyin All Rights Reserved.

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

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

//===============数据结构===============
typedef struct BiTNode	//结点
{
	int data;	//结点中储存的值
	struct BiTNode *lchild;	//结点的左孩子
	struct BiTNode *rchild;	//结点的右孩子
	BiTNode(const int x)
	{
		data = x;
		lchild = NULL;
		rchild = NULL;
	}
}*BiTree;	//结点的指针

//===============函数列表===============

void _BiTree(BiTree &root, int flag);	//类似于构造函数
void creat_BiTree(BiTree &root);	//创建一个二叉树
void _Per(BiTree &root, vector<int> &V);	//先序遍历的迭代
vector<int> PerOrderTraverse(BiTree &root);	//先序遍历
void _In(BiTree &root, vector<int> &V);	//中序遍历的迭代
vector<int> InOrderTraverse(BiTree &root);	//中序遍历
void _Post(BiTree &root, vector<int> &V);	//后序遍历的迭代
vector<int> PostOrderTraverse(BiTree &root);	//后序遍历
vector<vector<int>> LevelOrderTraverse(BiTree &root);	//层序遍历
int maxDepth(BiTree &root);	//二叉树的最大深度
bool isBST(BiTree &root, long min, long max);	//判断二叉树是否为二叉排序树的迭代
bool isValidBST(BiTree &root);	//判断二叉树是否为二叉排序树
BiTree searchBST(BiTree &root, int val);	//二叉排序树的搜索操作
BiTree insertIntoBST(BiTree &root, int val);	//二叉排序树的插入操作
BiTree deleteNode(BiTree &root, int key);	//二叉排序树的删除操作

//===============函数的实现===============
/*
	创建一个根结点
	只针对未初始化的结点
	BiTree &root:未初始化的结点
	int flag:若为1,则初始化结点;若为其它值,则直接赋值NULL

	@Return void
*/
void _BiTree(BiTree &root, int flag)
{
	if (flag == 1)
	{
		int a;
		cout << "请输入根结点的值:";
		cin >> a;
		root = new BiTNode(a);
		cout << endl;
	}
	else
		root = NULL;
}

/*
	创建一个二叉树
	注意根结点要初始化
	BiTree &root:已经初始化的根结点

	@Return void
*/
void creat_BiTree(BiTree &root)
{
	if (root)
	{
		cout << "是否创建" << root->data << "结点的左结点(1为是 0为否):";
		int al;
		cin >> al;
		cout << endl;
		if (al == 1)
		{
			int a;
			BiTree Node;
			cout << "请输入" << root->data << "结点的左结点的值:";
			cin >> a;
			cout << endl;
			Node = new BiTNode(a);
			root->lchild = Node;
			creat_BiTree(root->lchild);
		}

		cout << "是否创建" << root->data << "结点的右结点(1为是 0为否):";
		int ar;
		cin >> ar;
		cout << endl;
		if (ar == 1)
		{
			int a;
			BiTree Node;
			cout << "请输入" << root->data << "结点的右结点的值:";
			cin >> a;
			cout << endl;
			Node = new BiTNode(a);
			root->rchild = Node;
			creat_BiTree(root->rchild);
		}
	}
	else
		cout << "根结点未初始化!" << endl;
}

/*
	先序遍历的迭代部分
	BiTree &root:二叉树的根结点
	vector<int> &V:存储先序遍历结果的数组

	@Return void
*/
void _Per(BiTree &root, vector<int> &V)
{
	if (root)
	{
		V.push_back(root->data);
		_Per(root->lchild, V);
		_Per(root->rchild, V);
	}
}

/*
	二叉树的先序遍历
	相当于_Per函数的封装
	BiTree &root:二叉树的根结点

	@Return vector<int>
*/
vector<int> PerOrderTraverse(BiTree &root)
{
	vector<int> vs;
	_Per(root, vs);
	return vs;
}

/*
	中序遍历的迭代部分
	BiTree &root:二叉树的根结点
	vector<int> &V:存储中序遍历结果的数组

	@Return void
*/
void _In(BiTree &root, vector<int> &V)
{
	if (root)
	{
		_In(root->lchild, V);
		V.push_back(root->data);
		_In(root->rchild, V);
	}
}

/*
	二叉树的中序遍历
	相当于_In函数的封装
	BiTree &root:二叉树的根结点

	@Return vector<int>
*/
vector<int> InOrderTraverse(BiTree &root)
{
	vector<int> vs;
	_In(root, vs);
	return vs;
}

/*
	后序遍历的迭代部分
	BiTree &root:二叉树的根结点
	vector<int> &V:存储后序遍历结果的数组

	@Return void
*/
void _Post(BiTree &root, vector<int> &V)
{
	if (root)
	{
		_Post(root->lchild, V);
		_Post(root->rchild, V);
		V.push_back(root->data);
	}
}

/*
	二叉树的后序遍历
	相当于_Post函数的封装
	BiTree &root:二叉树的根结点

	@Return vector<int>
*/
vector<int> PostOrderTraverse(BiTree &root)
{
	vector<int> vs;
	_Post(root, vs);
	return vs;
}

/*
	二叉树的层序遍历
	遍历的结果返回到一个二维数组中
	BiTree &root:二叉树的根结点

	@Return vector<vector<int>>
*/
vector<vector<int>> LevelOrderTraverse(BiTree &root)
{
	vector<vector<int>> res;
	if (!root)
		return res;

	queue<BiTree> q;
	q.push(root);
	BiTree last = root;
	vector<int> a;
	while (!q.empty())
	{
		BiTree tmp = q.front();
		q.pop();
		if (tmp->lchild)
			q.push(tmp->lchild);
		if (tmp->rchild)
			q.push(tmp->rchild);
		if (tmp == last)
		{
			a.push_back(tmp->data);
			res.push_back(a);
			a.clear();
			last = q.back();
		}
		else
			a.push_back(tmp->data);
	}
	return res;
}

/*
	返回二叉树的最大深度
	BiTree &root:二叉树的根结点

	@Return int
*/
int maxDepth(BiTree &root)
{
	if (root)
		return 1 + max(maxDepth(root->lchild), maxDepth(root->rchild));
	else
		return 0;
}

/*
	判断二叉树是否为二叉排序树的迭代部分
	BiTree &root:二叉树的根结点
	long min:结点中的值不能低于的值
	long max:结点中的值不能高于的值

	@Return bool
*/
bool isBST(BiTree &root, long min, long max)
{
	if (!root)
		return true;
	if ((root->data) <= min || (root->data) >= max)
		return false;
	return isBST(root->lchild, min, root->data) && isBST(root->rchild, root->data, max);
}

/*
	判断二叉树是否为二叉排序树
	相当于isBST函数的封装
	BiTree &root:二叉树的根结点

	@Return bool
*/
bool isValidBST(BiTree &root)
{
	if (!root)
		return true;
	long min = LONG_MIN;
	long max = LONG_MAX;
	return isBST(root, min, max);
}

/*
	二叉排序树的搜索操作
	BiTree &root:二叉排序树的根结点
	int val:要搜索的值

	@Return BiTree
*/
BiTree searchBST(BiTree &root, int val)
{
	if (isValidBST(root))
	{
		if (!root)
			return NULL;
		if (root->data == val)
			return root;

		if (root->data > val)
			return searchBST(root->lchild, val);
		else
			return searchBST(root->rchild, val);
	}
	else
	{
		cout << "传入的不是二叉排序树!" << endl;
		return NULL;
	}
}

/*
	二叉排序树的插入操作
	BiTree &root:二叉排序树的根结点
	int val:要插入的值

	@Return BiTree
*/
BiTree insertIntoBST(BiTree &root, int val)
{
	if (isValidBST(root))
	{
		if (!root)
			return new BiTNode(val);

		if (root->data > val)
			root->lchild = insertIntoBST(root->lchild, val);
		else
			root->rchild = insertIntoBST(root->rchild, val);

		return root;
	}
	else
	{
		cout << "传入的不是二叉排序树!" << endl;
		return NULL;
	}
}

/*
	二叉排序树的删除操作
	BiTree &root:二叉排序树的根结点
	int val:要删除的值

	@Return BiTree
*/
BiTree deleteNode(BiTree &root, int key)
{
	if (isValidBST(root))
	{
		if (!root)
			return NULL;
		if (root->data > key)
			root->lchild = deleteNode(root->lchild, key);
		else if (root->data < key)
			root->rchild = deleteNode(root->rchild, key);
		else
		{
			if (!root->lchild || !root->rchild)
				root = (root->lchild) ? root->lchild : root->rchild;
			else
			{
				BiTree cur = root->rchild;
				while (cur->lchild)
					cur = cur->lchild;
				root->data = cur->data;
				root->rchild = deleteNode(root->rchild, cur->data);
			}
		}
		return root;
	}
	else
	{
		cout << "传入的不是二叉排序树!" << endl;
		return NULL;
	}
}

//===============主函数===============
/*
	主函数仅供参考
	你可以写自己的主函数
*/
int main()
{
	BiTree T;
	_BiTree(T, 1);
	creat_BiTree(T);

	vector<int> n;
	n = PerOrderTraverse(T);
	cout << n.size() << endl;
	for (int i = 0; i < n.size(); i++)
		cout << n[i] << " ";
	cout << endl;

	vector<int> m;
	m = InOrderTraverse(T);
	cout << m.size() << endl;
	for (int i = 0; i < m.size(); i++)
		cout << m[i] << " ";
	cout << endl;

	vector<int> l;
	l = PostOrderTraverse(T);
	cout << l.size() << endl;
	for (int i = 0; i < l.size(); i++)
		cout << l[i] << " ";
	cout << endl;

	int ser;
	cout << "请输入要搜索的值:";
	cin >> ser;
	cout << endl;
	BiTree N = searchBST(T, ser);

	vector<int> ln;
	ln = PerOrderTraverse(N);
	cout << ln.size() << endl;
	for (int i = 0; i < ln.size(); i++)
		cout << ln[i] << " ";
	cout << endl;

	int insert;
	cout << "请输入要插入的值:";
	cin >> insert;
	cout << endl;
	BiTree Ln = insertIntoBST(T, insert);

	vector<int> mn;
	mn = PerOrderTraverse(Ln);
	cout << mn.size() << endl;
	for (int i = 0; i < mn.size(); i++)
		cout << mn[i] << " ";
	cout << endl;

	int delet;
	cout << "请输入要删除的值:";
	cin >> delet;
	cout << endl;
	BiTree Dn = deleteNode(T, delet);

	vector<int> dn;
	dn = PerOrderTraverse(Dn);
	cout << dn.size() << endl;
	for (int i = 0; i < dn.size(); i++)
		cout << dn[i] << " ";
	cout << endl;

	return 0;
}
