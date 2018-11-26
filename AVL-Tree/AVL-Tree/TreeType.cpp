#include "stdafx.h"


//template<class ItemType> // constructor
//TreeType<ItemType>::TreeType()
//{
//	root = NULL;
//}

//template<class ItemType>  // destructor
//TreeType<ItemType>::~TreeType()
//// Calls recursive function Destroy to destroy the tree.
//{
//	Destroy(root);
//}



//template<class ItemType>
//void Destroy(TreeNode<ItemType>*& tree)
//// Post: tree is empty; nodes have been deallocated.
//{
//	if (tree != NULL)
//	{
//		Destroy<ItemType>(tree->left);
//		Destroy<ItemType>(tree->right);
//		delete tree;
//	}
//}

//template <class ItemType>
//void TreeType<ItemType> ::InsertItem(ItemType item)
//// Calls recursive function Insert to insert item into tree.
//{
//	bool taller = false;
//	Insert(root, item, taller);
//}
