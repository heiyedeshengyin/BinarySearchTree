# BinarySearchTree
其它数据结构:[二叉树](https://github.com/heiyedeshengyin/BinaryTree) [链表](https://github.com/heiyedeshengyin/LinkedList) [双链表](https://github.com/heiyedeshengyin/DoublyLinkedList)

二叉树以及二叉排序树的实现  
这是我们学校数据结构试验的内容

### 使用方法
下载解压后直接编译运行src/BinarySearchTree.cpp  
注意里面的主函数仅供参考  
你可以编写自己的主函数  
### 二叉树结点的数据结构
```cpp
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
```
### 函数列表
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
