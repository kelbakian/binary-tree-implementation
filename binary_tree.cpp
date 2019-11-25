#include <iostream>
#include <stddef.h>
#include <vector>
#include <climits>

using namespace std;

class TreeNode
{
public:
	void insert_node(TreeNode* new_node);
	void print_nodes() const;
	bool find(int value) const;
private:
	int data;
	TreeNode* left;
	TreeNode* right;
	friend class BinarySearchTree;
};

class BinarySearchTree
{
public:
	BinarySearchTree();
	void insert(int data);
	void erase(int data);
	int count(int data) const;
	void print() const;
	void exp_insert(int data ,vector<int> directions);

	void isBST();
	bool check_nodes(TreeNode* node, int min, int max);
	TreeNode* get_root();
private:
	TreeNode* root;
	friend class TreeNode;
};

BinarySearchTree::BinarySearchTree()
{
	 root = NULL;
}

void BinarySearchTree::print() const
{
	if (root != NULL)
		root->print_nodes();
}

void BinarySearchTree::insert(int data)
{
	TreeNode* new_node = new TreeNode;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	if (root == NULL) root = new_node;
	else root->insert_node(new_node);
}

void TreeNode::insert_node(TreeNode* new_node)
{
	if(new_node->data < data)
	{
		if (left == NULL) left = new_node;
		else left->insert_node(new_node);
	}
	else if (data < new_node->data)
	{
	if (right == NULL) right = new_node;
		else right->insert_node(new_node);
	}
}

int BinarySearchTree::count(int data) const
{
if (root == NULL) return 0;
	else if (root->find(data)) return 1;
	else return 0;
}

void BinarySearchTree::erase(int data)
{
	TreeNode* to_be_removed = root;
	TreeNode* parent = NULL;
	bool found = false;
	while (!found && to_be_removed != NULL)
	{
		if (to_be_removed->data < data)
		{
			parent = to_be_removed;
			to_be_removed = to_be_removed->right;
			}
		else if (data < to_be_removed->data)
		{
			parent = to_be_removed;
			to_be_removed = to_be_removed->left;
		}
		else found = true;
	}

	if (!found) return;

	if (to_be_removed->left == NULL || to_be_removed->right == NULL)
	{
		TreeNode* new_child;
		if (to_be_removed->left == NULL)
			new_child = to_be_removed->right;
		else
			new_child = to_be_removed->left;
		if (parent == NULL)
			root = new_child;
		else if (parent->left == to_be_removed)
			parent->left = new_child;
		else
			parent->right = new_child;
		return;
	}
	
	TreeNode* smallest_parent = to_be_removed;
	TreeNode* smallest = to_be_removed->right;
	while (smallest->left != NULL)
	{
		smallest_parent = smallest;
		smallest = smallest->left;
	}
	
	to_be_removed->data = smallest->data;
	if (smallest_parent == to_be_removed)
		smallest_parent->right = smallest->right;
	else
		smallest_parent->left = smallest->right;
}

bool TreeNode::find(int value) const
{
	if (value < data)
	{
		if (left == NULL) return false;
		else return left->find(value);
	}
	else if (data < value)
	{
		if (right == NULL) return false;
		else return right->find(value);
	}
	else
		return true;
}

void TreeNode::print_nodes() const
{
	if (left != NULL)
		left->print_nodes();
	cout << data << "\n";
	if (right != NULL)
		right->print_nodes();
}

bool BinarySearchTree::check_nodes(TreeNode* root, int min, int max) { //int min, int max replaced.
	if (root == NULL) {
		return true;
	}
	return root->data > min &&
		root->data < max &&
		check_nodes(root->left, min, root->data) &&
		check_nodes(root->right, root->data, max);
}

void BinarySearchTree::isBST()
{
	if (check_nodes(root, INT_MIN, INT_MAX)) {
		cout << "This is a binary search tree.";
	}
	else
		cout << "This is not a binary search tree.";
}

TreeNode* BinarySearchTree::get_root()
{
	return root;
}

void BinarySearchTree::exp_insert(int data, vector<int> directions) 
{
	TreeNode* new_node = new TreeNode;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	TreeNode* curr_node = root;
	while(directions.size() > 1) {
		if(directions[0] = 0) {
			curr_node = root->left;
		}
		else {
			curr_node = root->right;
		}
		directions.erase(directions.begin());
	}
	if(directions[0] = 0) {
			curr_node->left = new_node;
	}
	else {
		curr_node->right = new_node;
	}
}

int main() {
	BinarySearchTree tree;
	tree.insert(5);
	tree.insert(2);
	tree.insert(9);
	tree.insert(1);
	tree.insert(3);
	vector<int> directions(2, 1);
	tree.exp_insert(6, directions);
	cout << "Checking whether binary tree is binary search tree or not..." << endl;
	tree.isBST();
	cout << "\nPrinting elements of tree..." << endl;
	tree.print();

	return 0;
}