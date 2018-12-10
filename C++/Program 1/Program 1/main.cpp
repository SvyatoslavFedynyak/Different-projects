
#include "Tree.h"
#include "List.h"
using namespace std;
double sqrt(double val)
{
	return val * val;
}
int main()
{
	list <double> first;
	first.Add(10.5);
	first.Add(5.67);
	first.Add(8.33);
	first.AddInto(2, 2.89);
	first.Show();
	forEachList(first, sqrt);
	first.Show();
	tree <double> second;
	second.Add(4.66);
	second.Add(4.57);
	second.Add(2.22);
	forEachTree(second, sqrt);
	second.Show();
	system("pause");
}