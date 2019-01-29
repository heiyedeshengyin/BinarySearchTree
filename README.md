# BinarySearchTree
其它数据结构:[二叉树](https://github.com/heiyedeshengyin/BinaryTree) [链表](https://github.com/heiyedeshengyin/LinkedList) [双链表](https://github.com/heiyedeshengyin/DoublyLinkedList)

二叉搜索树的实现  
注意二叉搜索树中只能存储重载了>,<,==,>=,<=,!=这些运算符的对象  
中序遍历二叉搜索树会从小到大输出这些对象  
这是我们学校数据结构试验的内容

### 使用方法
下载解压后打开src/BinarySearchTree.cpp    
在后面编写自己的主函数后编译运行
### 数据结构
二叉搜索树结点
```cpp
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
```
二叉搜索树
```cpp
template <typename T>
class BinarySearchTree
{
	TreeNode<T> *root;	//根结点
}
```
### 函数列表
BinarySearchTree();	//无参构造函数  
BinarySearchTree(T x);	//创建一个根结点  
BinarySearchTree(TreeNode\<T\>* _root);	//用一个已有的根结点赋值给根结点  
BinarySearchTree(BinarySearchTree\<T\> &_root);	//拷贝构造函数  
BinarySearchTree(vector\<T\> v);	//用一个数组来创建二叉搜索树  
~BinarySearchTree();	//析构函数  
vector\<T\> PerOrderTraverse();	//先序遍历  
vector\<T\> InOrderTraverse();	//中序遍历  
vector\<T\> PostOrderTraverse();	//后序遍历  
vector\<T\> LevelOrderTraverse();	//层序遍历  
void clear();	//清空二叉树  
bool isEmpty();	//判断二叉树是否为空  
int height();	//获取树的高度  
int size();	//获取元素个数  
TreeNode\<T\>* search(T e);	//搜索结点  
bool insert(T e);	//插入节点  
bool remove(T e);	//删除结点  
T operator[] (int r);	//重载[]操作符  

### 一个主函数的例子
```cpp
#include"BinarySearchTree.cpp"

int main()
{
	BinarySearchTree<int> bst1(142);
	bst1.insert(124);
	bst1.insert(235);
	bst1.insert(12456);
	bst1.insert(6224);
	bst1.insert(12);

	cout << bst1 << endl;
	cout << bst1.size() << endl;
	cout << bst1.height() << endl;

	cout << bst1.insert(6224) << endl;
	cout << bst1 << endl;
	cout << bst1.size() << endl;
	cout << bst1.height() << endl;

	BinarySearchTree<int> bst2(bst1.search(235));
	cout << bst2 << endl;
	cout << bst2.size() << endl;
	cout << bst2.height() << endl;

	vector<int> v;
	v.push_back(123);
	v.push_back(12415);
	v.push_back(8325);
	v.push_back(124);
	BinarySearchTree<int> bst3(v);
	cout << bst3 << endl;
	cout << bst3.size() << endl;
	cout << bst3.height() << endl;

	BinarySearchTree<int> bst4(bst3);
	cout << bst4 << endl;
	cout << bst4.size() << endl;
	cout << bst4.height() << endl;

	return 0;
}
```
