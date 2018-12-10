#pragma once
#include "forEach.h"
using namespace std;
template <typename T>
class tree
{
private:
	struct tree_slot
	{
		T value;
		tree_slot* left;
		tree_slot* right;
		tree_slot() :value(0), left(nullptr), right(nullptr) {};
		tree_slot(T value_)
		{
			value = value_;
			right = nullptr;
			left = nullptr;
		};
	};
	int num;
	tree_slot* root;
	void AddTo(T ent_value, tree_slot* &root_);
	void RemoveThe(tree_slot* &root_, T ent_value);
	void ShowThe(tree_slot* &root_);
	friend void DoWith(tree_slot* &root_)
	{
		if (root_ != nullptr)
		{
			DoWith(root_->left);
			root_->value = func(root_->value);
			DoWith(root_->right);
		}
	}
public:
	tree() :num(0), root(nullptr) {};
	int returnNumber() { return num; }
	friend void forEachTree(tree<T> entered_struct, pfunct func);
	void Remove(T ent_value);
	void Add(T ent_value);
	void Show();
};
template <typename T>
void tree<T>::AddTo(T ent_value, tree_slot* &root_)
{
	if (root_ == nullptr)
	{
		root_ = new tree_slot(ent_value);
	}
	else
	{
		if (ent_value > root_->value)
		{
			this->AddTo(ent_value, root_->left);
		}
		else if (ent_value < root_->value)
		{
			this->AddTo(ent_value, root_->right);
		}
	}
	num++;
}
template <typename T>
void tree<T>::Add(T ent_value)
{
	this->AddTo(ent_value, root);
}
//slot* tree<T>::min(slot*&root_)
//{
//	if (root->left == nullptr)
//	{
//		return root_;
//	}
//	else
//	{
//		return min(root->left);
//	}
//}
template <typename T>
void tree<T>::ShowThe(tree_slot* &root_)
{
	if (root_ != nullptr)
	{
		ShowThe(root_->left);
		cout << " " << root_->value;
		ShowThe(root_->right);
	}
}
template <typename T>
void tree<T>::Show()
{
	ShowThe(root);
	cout << endl;
}
template <typename T>
void tree<T>::RemoveThe(tree_slot* &root_, T ent_value)
{
	if (ent_value == root_->value)
	{
		if (root_->left == nullptr && root_->right == nullptr)
		{
			root_ = nullptr;
		}
		else if (root_->left == nullptr)
		{
			root_ = root->right;
		}
		else if (root_->right == nullptr)
		{
			root_ = root_->left;
		}
		else
		{
			root_ = min(root_->left);
		}
	}
	else if (ent_value > root_->value)
	{
		RemoveThe(root_->left, ent_value);
	}
	else if (ent_value < root_->value)
	{
		RemoveThe(root_->right, ent_value);
	}
}
template <typename T>
void tree<T>::Remove(T ent_value)
{
	RemoveThe(root, ent_value);
}

