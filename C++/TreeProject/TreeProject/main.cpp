#include <iostream>
using namespace std;
struct slot
{
	int value;
	slot* left;
	slot* right;
	slot() :value(0), left(nullptr), right(nullptr) {};
	slot(int value_)
	{
		value = value_;
		right = nullptr;
		left = nullptr;
	};
};
class tree
{
private:
	int num;
	slot* root;
public:
	tree() :num(0), root(nullptr) {};
	void AddTo(int ent_value, slot* &root_);
	void Add(int ent_value);
	void Show();
	void ShowThe(slot* &root_);
};
void tree::AddTo(int ent_value, slot* &root_)
{
	if (root_ == nullptr)
	{
		root_ = new slot(ent_value);
	}
	else
	{
		if (ent_value > root_->value)
		{
			if (root_->left != nullptr)
			{
				this->AddTo(ent_value, root_->left);
			}
			else
			{
				root_->left = new slot(ent_value);
			}
		}
		else if (ent_value < root_->value)
		{
			if (root_->right != nullptr)
			{
				this->AddTo(ent_value, root_->right);
			}
			else
			{
				root_->right = new slot(ent_value);
			}
		}
	}
	num++;
}
void tree::Add(int ent_value)
{
	this->AddTo(ent_value, root);
}
void tree::ShowThe(slot* &root_)
{

}
int main()
{
	int val;
	tree first;
	for (int i = 0; i < 5; i++)
	{
		cin >> val;
		first.Add(val);
	}
	system("pause");
}