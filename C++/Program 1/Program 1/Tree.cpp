#include "Tree.h"
template <typename T>
void forEachTree(tree<T> entered_struct, pfunct func)
{
	DoWith(entered_struct.root);
}
//template <typename T>
//void forEachTree(tree<T> entered_struct, pfunct func)
//{
//	void DoWith(tree_slot* &root_)
//	{
//		if (root_ != nullptr)
//		{
//			DoWith(root_->left);
//			root_->value = func(root_->value);
//			DoWith(root_->right);
//		}
//	}
//	DoWith(entered_struct.root);
//}
