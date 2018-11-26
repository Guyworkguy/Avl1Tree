#pragma once
#include <iostream>
#include <string>
using namespace std;
typedef enum { LH, EH, RH } Balfactor;


template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode *left;
	TreeNode *right;
	Balfactor bf;
};

template<class ItemType>
class TreeType
{
public:
	TreeType();
	~TreeType();
	void InsertItem(ItemType item);
	void Print();
	void SearchItem(ItemType item);
	void DeleteItem(ItemType item);


private:
	TreeNode<ItemType> * root;
};

template <class ItemType>
void TreeType<ItemType> ::Print()
{
	PrintPostorder(root);
}

template <class ItemType>
void PrintPostorder(TreeNode<ItemType>*&  tree)
{
	if (tree == NULL)
		return;
	// first recur on left subtree
	PrintPostorder(tree->left);

	// then recur on right subtree
	PrintPostorder(tree->right);

	// now deal with the node
	

	cout << tree->info << "  BF= " << tree->bf;
	if (tree->left == NULL)
	{
		cout << " Left = NULL ";
	}
	else
	{
		cout <<" Left = " <<tree->left->info << " ";
	}
	if (tree->right == NULL)
	{
		cout << " Right = NULL ";
	}
	else
	{
		cout <<" Right = " << tree->right->info << " ";
	}
	cout << "\n";

}

template<class ItemType> // constructor
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template<class ItemType>  // destructor
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

template<class ItemType>
void Destroy(TreeNode<ItemType>*& tree)
// Post: tree is empty; nodes have been deallocated.
{
	if (tree != NULL)
	{
		Destroy<ItemType>(tree->left);
		Destroy<ItemType>(tree->right);
		delete tree;
	}
}

template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller = false;
	Insert(root, item, taller);
}


template <class ItemType>
void RotateLeft(TreeNode<ItemType> * & tree)
{

	TreeNode<ItemType> * rs;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateLeft"
		<< endl;
	else if (tree->right == NULL)
		cerr << "Cannot make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

template <class ItemType>
void RotateRight(TreeNode<ItemType> * & tree)
{

	TreeNode<ItemType> * ls;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateRight"
		<< endl;
	else if (tree->left == NULL)
		cerr << "Cannot make an empty subtree the root in "
		"RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

template <class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller)
// Inserts item into tree.
// Post:	item is in tree; search property is maintained.
{
	if (tree == NULL)
	{					// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = EH;
		taller = true;
	}
	else if (item == tree->info)
	{
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case LH: LeftBalance(tree, taller); break;
			case EH: tree->bf = LH; break;
			case RH: tree->bf = EH; taller = false; break;
			}
	}
	else if (item > tree->info)
	{
		Insert(tree->right, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case RH: RightBalance(tree, taller);
				break;
			case EH: tree->bf = RH; break;
			case LH: tree->bf = EH; taller =
				false; break;
			}
	}
}

template <class ItemType>
void RightBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;

	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH:	cerr << "Tree already balanced " << endl;
		break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH;		break;
		case EH:	tree->bf = rs->bf = EH;	break;
		case LH:	tree->bf = EH;
			rs->bf = RH;		break;
		}
		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template <class ItemType>
void LeftBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;


	switch (ls->bf)
	{
	case LH:	tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:	cerr << "Tree already balanced " << endl;
		break;
	case RH:	rs = ls->right;
		switch (rs->bf)
		{
		case LH:	tree->bf = RH;
			ls->bf = EH;		break;
		case EH:	tree->bf = ls->bf = EH;	break;
		case RH:	tree->bf = EH;
			ls->bf = LH;		break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

template <class ItemType>
void Search(TreeNode<ItemType>*& tree, ItemType item)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Search(tree->left, item);

		}
		else if (item > tree->info)
		{
			Search(tree->right, item);

		}
		else
			cout << item << " is in Tree";
	}
	else
	{
		cout << "\nNOTE: " << item << " not in the tree.";
	}
}
template <class ItemType>
void TreeType<ItemType> ::SearchItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	Search(root, item);
}

template <class ItemType>
void DelRightBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;
	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		shorter = true; break;
	case EH:	tree->bf = RH;
		rs->bf = LH;
		RotateLeft(tree);
		shorter = false; break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH; break;
		case EH:	tree->bf = rs->bf = EH;
			break;
		case LH:	tree->bf = EH;
			rs->bf = RH; break;
		} // END SWITCH

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}


template <class ItemType>
void DelLeftBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;
	switch (ls->bf)
	{
	case LH:	tree->bf = ls->bf = EH;
		RotateRight(tree);
		shorter = true; break;
	case EH:	tree->bf = LH;
		ls->bf = RH;
		RotateRight(tree);
		shorter = false; break;
	case RH:	rs = ls->right;
		switch (rs->bf)
		{
		case LH:	tree->bf = RH;
			ls->bf = EH; break;
		case EH:	tree->bf = ls->bf = EH;
			break;
		case RH:	tree->bf = EH;
			ls->bf = LH; break;
		} // END SWITCH
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}

template <class ItemType>
void TreeType<ItemType> ::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool shorter;
	Delete(root, item, shorter);
}

template <class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item, bool & shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: tree->bf = EH; break;
				case EH: tree->bf = RH; shorter = false;
					break;
				case RH: DelRightBalance(tree, shorter);
				} // END SWITCH	
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: DelLeftBalance(tree, shorter);
				break;				case EH: tree->bf = LH; shorter = false; 							break;
				case RH: tree->bf = EH; break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
}

template <class ItemType>
void DeleteNode(TreeNode <ItemType> * & tree, bool & shorter)

{
	ItemType data;	TreeNode <ItemType> * tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
			switch (tree->bf)
			{
			case LH: tree->bf = EH; break;
			case EH: tree->bf = RH; shorter = false;
				break;
			case RH: DelRightBalance(tree, shorter);
			}
	}
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType> * tree, ItemType & data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}
 











