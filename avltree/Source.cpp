#include <iostream>
#include<ctype.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;


struct node
{
	int element;
	node* left;
	node* right;
	int height;
};

typedef struct node* nodeptr;

class bstree
{
public:
	void insert(int, nodeptr&);
	void del(int, nodeptr&);
	int deletemin(nodeptr&);
	void find(int, nodeptr&);
	nodeptr findmin(nodeptr);
	nodeptr findmax(nodeptr);
	void makeempty(nodeptr&);
	void copy(nodeptr&, nodeptr&);
	nodeptr nodecopy(nodeptr&);
	void preorder(nodeptr);
	void inorder(nodeptr);
	void postorder(nodeptr);
	int bsheight(nodeptr);
	nodeptr srl(nodeptr&);
	nodeptr drl(nodeptr&);
	nodeptr srr(nodeptr&);
	nodeptr drr(nodeptr&);
	int max(int, int);
	int nonodes(nodeptr);
};
// ������� ����
void bstree::insert(int x, nodeptr& p)
{
	if (p == NULL)
	{
		p = new node;
		p->element = x;
		p->left = NULL;
		p->right = NULL;
		p->height = 0;
		if (p == NULL)
		{
			cout << "Out of Space\n" << endl;
		}
	}
	else
	{
		if (x < p->element)
		{
			insert(x, p->left);
			if ((bsheight(p->left) - bsheight(p->right)) == 2)
			{
				if (x < p->left->element)
				{
					p = srl(p);
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x > p->element)
		{
			insert(x, p->right);
			if ((bsheight(p->right) - bsheight(p->left)) == 2)
			{
				if (x > p->right->element)
				{
					p = srr(p);
				}
				else
				{
					p = drr(p);
				}
			}
		}
		else
		{
			cout << "������ ����������\n" << endl;
		}
	}
	int m, n, d;
	m = bsheight(p->left);
	n = bsheight(p->right);
	d = max(m, n);
	p->height = d + 1;
}
// ����� ��������
nodeptr bstree::findmin(nodeptr p)
{
	if (p == NULL)
	{
		cout << "� ������ ��� ���������\n" << endl;
		return p;
	}
	else
	{
		while (p->left != NULL)
		{
			p = p->left;
			
		}
		return p;
	}
}
// ����� ���������
nodeptr bstree::findmax(nodeptr p)
{
	if (p == NULL)
	{
		cout << "� ������ ��� ���������\n" << endl;
		return p;
	}
	else
	{
		while (p->right != NULL)
		{
			p = p->right;
			
		}
		return p;
	}
}
// ����� ��������
void bstree::find(int x, nodeptr& p)
{
	if (p == NULL)
	{
		cout << "��������, �� ������ �������� ���\n" << endl;
	}
	else
	{
		if (x < p->element)
		{
			find(x, p->left);
		}
		else
		{
			if (x > p->element)
			{
				find(x, p->right);
			}
			else
			{
				cout << "�������, ������� �� ������ ���� � ������!\n" << endl;
			}
		}
	}
}
// ����������� ������
void bstree::copy(nodeptr& p, nodeptr& p1)
{
	makeempty(p1);
	p1 = nodecopy(p);
}
// ������� ������
void bstree::makeempty(nodeptr& p)
{
	nodeptr d;
	if (p != NULL)
	{
		makeempty(p->left);
		makeempty(p->right);
		d = p;
		free(d);
		p = NULL;
	}
}
// ����������� �����
nodeptr bstree::nodecopy(nodeptr& p)
{
	nodeptr temp;
	if (p == NULL)
	{
		return p;
	}
	else
	{
		temp = new node;
		temp->element = p->element;
		temp->left = nodecopy(p->left);
		temp->right = nodecopy(p->right);
		return temp;
	}
}

// �������� �����
void bstree::del(int x, nodeptr& p)
{
	nodeptr d;
	if (p == NULL)
	{
		cout << "��������, �� ������ �������� ���\n" << endl;
	}
	else if (x < p->element)
	{
		del(x, p->left);
	}
	else if (x > p->element)
	{
		del(x, p->right);
	}
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d = p;
		free(d);
		p = NULL;
		cout << "������� ������\n" << endl;
	}
	else if (p->left == NULL)
	{
		d = p;
		free(d);
		p = p->right;
		cout << "������� ������\n" << endl;
	}
	else if (p->right == NULL)
	{
		d = p;
		p = p->left;
		free(d);
		cout << "������� ������\n" << endl;
	}
	else
	{
		p->element = deletemin(p->right);
	}
}

int bstree::deletemin(nodeptr& p)
{
	int c;
	cout << "������� �������� ������������ ��������\n" << endl;
	if (p->left == NULL)
	{
		c = p->element;
		p = p->right;
		return c;
	}
	else
	{
		c = deletemin(p->left);
		return c;
	}
}

void bstree::preorder(nodeptr p)
{
	if (p != NULL)
	{
		cout << p->element << "\t";
		preorder(p->left);
		preorder(p->right);
	}
}

// ������ �� �������
void bstree::inorder(nodeptr p)
{
	if (p != NULL)
	{
		inorder(p->left);
		cout << p->element << "\t";
		inorder(p->right);
	}
}

void bstree::postorder(nodeptr p)
{
	if (p != NULL)
	{
		postorder(p->left);
		postorder(p->right);
		cout << p->element << "\t";
	}
}

int bstree::max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}

int bstree::bsheight(nodeptr p)
{
	int t;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		t = p->height;
		return t;
	}
}

nodeptr bstree::srl(nodeptr& p1)
{
	nodeptr p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(bsheight(p2->left), p1->height) + 1;
	return p2;
}
nodeptr bstree::srr(nodeptr& p1)
{
	nodeptr p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(bsheight(p1->left), bsheight(p1->right)) + 1;
	p2->height = max(p1->height, bsheight(p2->right)) + 1;
	return p2;
}
nodeptr bstree::drl(nodeptr& p1)
{
	p1->left = srr(p1->left);
	return srl(p1);
}
nodeptr bstree::drr(nodeptr& p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

int bstree::nonodes(nodeptr p)
{
	int count = 0;
	if (p != NULL)
	{
		nonodes(p->left);
		nonodes(p->right);
		count++;
	}
	return count;
}

void avltree_print_dfs(struct node* p, int level)
{
	int i;
	if (p == NULL)
		return;
	for (i = 0; i < level; i++)
		printf(" ");
	printf("%d\n", p->element);
	avltree_print_dfs(p->left, level + 1);
	avltree_print_dfs(p->right, level + 1);
}

void print(nodeptr p, int& k, int t)
{
	if (p != NULL)
	{	
		for (int i = 0; i < 3 * (t - k / 4); i++)	cout << "-";

		cout << p->element;
		cout << "(" << k << ")";
		
		if (k % 2 == 0)
		{	
			cout << endl;			
		}
		k++;
		print(p->left, k, t);
		print(p->right, k, t);
		
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");

	nodeptr root, root1, min, max;
	int a, choice, findele, delele;
	char ch = 'y';
	bstree bst;

	system("clear");
	root = NULL;
	root1 = NULL;

	int m;
	cout << "������� ���������� �����: ";
	cin >> m;
	for (int i = 0; i < m; i++) {
		cout << "������� ������� " << i + 1 << ": ";
		cin >> a;
		bst.insert(a, root);
	}
	system("cls");

	cout << "\n\t\t\t\t��� ������" << endl;
	cout << "\t\t\t\t:::::::::::::::::::\n" << endl;

	do
	{
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::1  �������� ����� ����::::::::::::::::::::::" << endl;
		cout << "\t\t::::2  ����� ����������� �������::::::::::::::::" << endl;
		cout << "\t\t::::3  ����� ������������ �������:::::::::::::::" << endl;
		cout << "\t\t::::4  ����� �� ��������::::::::::::::::::::::::" << endl;
		cout << "\t\t::::5  ������� �������::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::6  ������� ������1::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::7  ������� ������2::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::8  ������� ������3::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::9  �������� ������ ������:::::::::::::::::::" << endl;
		cout << "\t\t::::10 ����� ������:::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::0 �����:::::::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

		cout << "\n�������� ������ �������� � ������� Enter: ";
		cin >> choice;

		int asd;
		int t;

		switch (choice)
		{
		case 1:
			cout << "\n\t\t���������� ������ ����" << endl;
			cout << "\t\t:::::::::::::\n" << endl;
			cout << "������� �������: ";
			cin >> a;
			bst.insert(a, root);
			cout << "\n����� ������� �������� �������\n" << endl;
			break;
		case 2:
			if (root != NULL)
			{
				min = bst.findmin(root);
				cout << "\n����������� ������� � ������: " << min->element << endl;
			}
			break;
		case 3:
			if (root != NULL)
			{
				max = bst.findmax(root);
				cout << "\n������������ ������� � ������: " << max->element << endl;
			}
			break;
		case 4:
			cout << "\n������� ������� �������: ";
			cin >> findele;
			if (root != NULL)
			{
				bst.find(findele, root);
			}
			break;
		case 5:
			cout << "\n����� ���� �������? : ";
			cin >> delele;
			bst.del(delele, root);
			bst.inorder(root);
			cout << endl;
			break;
		case 6:
			cout << "\n\t\t������� ������1" << endl;
			bst.preorder(root);
			cout << endl;
			break;
		case 7:
			cout << "\n\t\t������� ������2" << endl;
			bst.inorder(root);
			cout << endl;
			break;
		case 8:
			cout << "\n\t\t������ ������3" << endl;
			bst.postorder(root);
			cout << endl;
			break;
		case 9:
			cout << "\n\t\t������\n" << endl;
			cout << "T������ ����� ������: " << bst.bsheight(root) << endl;
			break;
		case 10:
			cout << "\n\t\t������\n" << endl;
			asd = 0;
			t = bst.bsheight(root);
			//print(root, asd, t);
			avltree_print_dfs(root, asd);
			break;
		case 0:
			cout << "\n\t���������� ��� �� ������������� ��������\n" << endl;
			break;
		default:
			cout << "Sorry! wrong input\n" << endl;
			break;
		}
		system("pause");
		system("cls");
	} while (choice != 0);
	return 0;
}