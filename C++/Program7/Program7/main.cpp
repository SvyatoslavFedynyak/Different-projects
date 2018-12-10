#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>
using namespace std;
int letter_size(int val)
{
	if (val >= 0 && val < 10)return 1;
	else if (val > 9 && val < 100)return 2;
	else if (val > 99)return 3;
}
map <int, vector<int>> restruct(map <int, vector<int>> box, int& _box_size)
{
	int new_box_size = 0;
	map <int, vector<int>> new_box;
	map <int, vector<int>>::iterator box_iter = box.begin();
	for (int i = 0; i < box.size();i++)
	{
		new_box.insert(make_pair(new_box_size, box_iter->second));
		new_box_size += box_iter->second.size();
		box_iter++;
	}
	_box_size = new_box_size;
	return new_box;
}
void free(map <int, vector<int>>& box, int key, int& _box_size)
{
	_box_size -= box.find(key)->second.size();
	box.erase(key);
	box = restruct(box, _box_size);
}
//void to_much_x(int x_cells, int _max_line_cell)
//{
//	if (x_cells > _max_line_cell)
//	{
//		for (int i = 0;i < _max_line_cell;i++)
//		{
//			cout << "x";
//		}
//		cout << "|" << endl << "|";
//		x_cells -= _max_line_cell;
//		if (x_cells > _max_line_cell)
//		{
//			to_much_x(x_cells, _max_line_cell);
//		}
//		else
//		{
//			for (int i = 0;i < x_cells;i++)
//			{
//				cout << "x";
//			}
//			cout << "|";
//		}
//	}
//}
//int end_x(int x_cells, int left_place, int _max_line_cell)
//{
//	for (int i = 0;i < left_place;i++)
//	{
//		cout << "x";
//	}
//	cout << "|" << endl << "|";
//	x_cells -= left_place;
//	int left_x = x_cells;
//	if (x_cells > _max_line_cell)
//	{
//		to_much_x(x_cells, _max_line_cell);
//	}
//	else
//	{
//		for (int i = 0;i < x_cells;i++)
//		{
//			cout << "x";
//		}
//		cout << "|";
//	}
//	return left_x%_max_line_cell;
//}
void help()
{
	cout <<
		"Available commands :" << endl <<
		"help - show this help" << endl <<
		"exit - exit this program" << endl <<
		"print - print memory blocks map" << endl <<
		"allocate <num> - allocate <num> cells.Returns block first cell number" << endl <<
		"free <num> - free block with first cell number <num>" << endl;
}
int print_line(map <int, vector<int>>::iterator& _box_iter, int _extra_symbols, int extra_x, int _max_line_cell, int _box_size, int& curr_iter_position)
{
	int box_size = _box_size;
	int curr_extra_symb = _extra_symbols;
	int free_cells = _max_line_cell;
	cout << "|";
	if (extra_x != 0)
	{
		if (extra_x < _max_line_cell)
		{
			for (int i = 0;i < extra_x;i++)
			{
				cout << "x";
			}
			cout << "|";
			curr_extra_symb -= 1;
			free_cells -= extra_x;
			curr_iter_position++;
			if (curr_iter_position == box_size + 1)
			{
				for (int i = 0;i < free_cells + curr_extra_symb;i++)
				{
					cout << " ";
				}
				cout << "|" << endl;
				return 0;
			}
			_box_iter++;
		}
		else if (extra_x == _max_line_cell)
		{
			for (int i = 0;i < _max_line_cell;i++)
			{
				cout << "x";
			}
			for (int i = 0;i < curr_extra_symb;i++)
			{
				cout << " ";
			}
			cout << "|" << endl;
			return 0;
		}
		else if (extra_x > _max_line_cell)
		{
			for (int i = 0;i < _max_line_cell;i++)
			{
				cout << "x";
			}
			for (int i = 0;i < curr_extra_symb;i++)
			{
				cout << " ";
			}
			cout << "|" << endl;
			return extra_x - _max_line_cell;
		}
	}
	do
	{
		if (curr_iter_position == box_size + 1)
		{
			for (int i = 0;i < free_cells + curr_extra_symb;i++)
			{
				cout << " ";
			}
			cout << "|" << endl;
			return 0;
		}
		if (free_cells != 0)
		{
			if (_box_iter->second.size() >= free_cells)
			{
				int e_x = 0;
				cout << _box_iter->first;
				for (int i = 0; i < free_cells;i++)
				{
					cout << "x";
				}
				curr_extra_symb -= (letter_size(_box_iter->first));
				e_x = _box_iter->second.size() - free_cells;
				if (e_x == 0)
				{
					curr_iter_position++;
					if (curr_iter_position == box_size + 1)
					{
						for (int i = 0;i < curr_extra_symb;i++)
						{
							cout << " ";
						}
						cout << "|" << endl;
						return 0;
					}
					for (int i = 0;i < curr_extra_symb;i++)
					{
						cout << " ";
					}
					cout << "|" << endl;
					_box_iter++;
					return 0;
				}
				else
				{
					for (int i = 0;i < curr_extra_symb;i++)
					{
						cout << " ";
					}
					cout << "|" << endl;
					return e_x;
				}
			}
			else
			{
				cout << _box_iter->first;
				for (int i = 0; i < _box_iter->second.size();i++)
				{
					cout << "x";
				}
				cout << "|";
				curr_extra_symb -= (1 + letter_size(_box_iter->first));
				free_cells -= _box_iter->second.size();
				curr_iter_position++;
				if (curr_iter_position == box_size + 1)
				{
					for (int i = 0;i < free_cells + curr_extra_symb;i++)
					{
						cout << " ";
					}
					cout << "|" << endl;
					return 0;
				}
				_box_iter++;
			}
		}
	} while (true);
}
void print(map <int, vector<int>> _box, int _max_cell, int _max_line_cell)
{
	int full_lines = (_max_cell - (_max_cell%_max_line_cell)) / _max_line_cell;
	int last_line_size = _max_cell%_max_line_cell;
	int free_cells = _max_cell;
	int extra_symbols = 0;
	map <int, vector<int>>::iterator box_iter = _box.begin();
	for (int i = 0;i < _box.size();i++)
	{
		extra_symbols += letter_size(box_iter->first) + 1;
		box_iter++;
	}
	if (_box.size() == 0)
	{
		do
		{
			if (free_cells >= _max_line_cell)
			{
				cout << "|";
				for (int i = 0;i < _max_line_cell;i++)
				{
					cout << " ";
				}
				cout << "|" << endl;
				free_cells -= _max_line_cell;
			}
			else
			{
				if (free_cells == 0)
				{
					break;
				}
				cout << "|";
				for (int i = 0;i < free_cells;i++)
				{
					cout << " ";
				}
				cout << "|" << endl;
				break;
			}
		} while (true);
	}
	else
	{
		int extra_x = 0, iter_pos = 1;
		box_iter = _box.begin();
		for (int i = 0;i < full_lines;i++)
		{
			extra_x = print_line(box_iter, extra_symbols, extra_x, _max_line_cell, _box.size(), iter_pos);
			if (iter_pos == _box.size() + 1)
			{
				for (int j = 0;j < full_lines - i - 1;j++)
				{
					cout << "|";
					for (int i = 0;i < _max_line_cell + extra_symbols;i++)
					{
						cout << " ";
					}
					cout << "|" << endl;
				}
				break;
			}
		}
		if (last_line_size == !0)
		{
			extra_x = print_line(box_iter, extra_symbols, extra_x, last_line_size, _box.size(), iter_pos);
		}
	}

	//else
	//{
	//	map <int, vector<int>>::iterator box_iterator = _box.begin();
	//	int lost_cells = 0, prev_cells = 0;
	//	cout << "|";
	//	for (int j = 0;j < _box.size();j++)
	//	{
	//		cout << box_iterator->first;
	//		if (box_iterator->second.size() > _max_line_cell - prev_cells)
	//		{
	//			prev_cells = end_x(box_iterator->second.size(), _max_line_cell - prev_cells, _max_line_cell);
	//			free_cells -= box_iterator->second.size();
	//			/*for (int i = 0;i < _max_line_cell - prev_cells;i++)
	//			{
	//				cout << "x";
	//			}
	//			cout << "|" << endl << "|";*/

	//			/*	free_cells -= _max_line_cell;
	//				lost_cells = box_iterator->second.size() - _max_line_cell;
	//				for (int i = 0;i < lost_cells;i++)
	//				{
	//					cout << "x";
	//				}
	//				cout << "|";
	//				prev_cells = lost_cells;
	//				free_cells -= lost_cells;*/
	//		}
	//		else
	//		{
	//			for (int i = 0;i < box_iterator->second.size();i++)
	//			{
	//				cout << "x";
	//			}
	//			cout << "|";
	//			prev_cells += box_iterator->second.size();
	//			free_cells -= box_iterator->second.size();
	//		}
	//		if (j == _box.size() - 1)
	//		{
	//			for (int i = 0;i < _max_line_cell - prev_cells;i++)
	//			{
	//				cout << " ";
	//			}
	//			cout << "|" << endl;
	//			free_cells -= _max_line_cell - prev_cells;
	//			do
	//			{
	//				if (free_cells >= _max_line_cell)
	//				{
	//					cout << "|";
	//					for (int i = 0;i < _max_line_cell;i++)
	//					{
	//						cout << " ";
	//					}
	//					cout << "|" << endl;
	//					free_cells -= _max_line_cell;
	//				}
	//				else
	//				{
	//					if (free_cells == 0)
	//					{
	//						break;
	//					}
	//					cout << "|";
	//					for (int i = 0;i < free_cells;i++)
	//					{
	//						cout << " ";
	//					}
	//					cout << "|" << endl;
	//					break;
	//				}
	//			} while (true);
	//		}
	//		box_iterator++;
	//	}
	//}
}
void allocate(map <int, vector<int>>& box, int _max_cell, int block_size, int& _box_size)
{
	if (_max_cell - _box_size >= block_size)
	{
		vector <int> block;
		block.resize(block_size);
		box.insert(make_pair(_box_size, block));
		_box_size += block_size;
	}
	else
	{
		cout << "Not enough place!" << endl;
	}
}
int main()
{
	int max_cell, max_line_cell;
	cout << "Enter max cells and max cells in line" << endl;
	cin >> max_cell >> max_line_cell;
	map <int, vector<int>> box;
	int box_size = 0;
	cout << "Type help to see additional commands" << endl;
	string command;
	do
	{
		cout << "Enter command:" << endl;
		cin >> command;
		if (command == "help")
		{
			help();
		}
		else if (command == "exit")
		{
			break;
		}
		else if (command == "allocate")
		{
			int block_id, block_size;
			cout << "Enter block size" << endl;
			cin >> block_size;
			allocate(box, max_cell, block_size, box_size);
		}
		else if (command == "free")
		{
			int key;
			cout << "Enter key" << endl;
			cin >> key;
			free(box, key, box_size);
		}
		else if (command == "print")
		{
			print(box, max_cell, max_line_cell);
		}
	} while (true);
}