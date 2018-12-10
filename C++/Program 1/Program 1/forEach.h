#pragma once
#include <iostream>
typedef double(*pfunct)(double);
//template <typename strukt>
//template <typename T>
//void forEach(strukt<T> entered_struct, pfunct func)
//{
//	if (is_same<decltype(entered_struct), class tree<T>>::value)
//	{
//		void DoWith(tree_slot* &root_)
//		{
//			if (root_ != nullptr)
//			{
//				DoWith(root_->left);
//				root_->value=func(root_->value);
//				DoWith(root_->right);
//			}
//		}
//		DoWith(entered_struct.root);
//	}
//	else if (is_same<decltype(entered_struct), class list<T>>::value)
//	{
//		list_slot temp = slotentered_struct.first;
//		for (int i = 0;i < entered_struct.num;i++)
//		{
//			temp->value=func(temp->value);
//			temp = temp->next;
//		}
//	}
//}