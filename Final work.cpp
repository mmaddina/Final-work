#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;
// Объявление узла
struct avl_node
{
    int data;
    struct avl_node* left;
    struct avl_node* right;
}*root;

//Объявление класса
class avlTree
{
public:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    avl_node* insert(avl_node*, int);
    void inorder(avl_node*);
    void display(avl_node*, int);
    avlTree()
    {
        root = NULL;
    }
};
int main()
{
    int option, num;
    avlTree avl;
    while (1)
    {
        setlocale(LC_ALL, "Russian");
        cout << "\n-----------------------" << endl;
        cout << "Реализация АВЛ-деревья" << endl;
        cout << "-----------------------\n" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "1.Вставить элемент в дерево" << endl;
        cout << "2.Отображенме сбалансированного АВЛ-деревья" << endl;
        cout << "3.Последовательность ввода" << endl;
        cout << "4.Выход" << endl;
        cout << "--------------------------------------------\n" << endl;
        cout << "Введите свой выбор: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Введите значение, которое будет вставлено: ";
            cin >> num;
            root = avl.insert(root, num);
            break;
        case 2:
            if (root == NULL)
            {
                cout << "Дерево пусто" << endl;
                continue;
            }
            cout << "Сбалансированное АВЛ-дерево:" << endl;
            avl.display(root, 1);
            break;
        case 3:
            cout << "Последовательность:" << endl;
            avl.inorder(root);
            cout << endl;
            break;
        case 4:
            exit(1);
            break;
        default:
            cout << "Неправильный выбор" << endl;
        }
    }
    return 0;
}

// Высота дерева AVL //
int avlTree::height(avl_node* temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

// Разница в высоте //
int avlTree::diff(avl_node* temp)
{
    int l_height = height(temp->left);
    int r_height = height(temp->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

// Поворот вправо-Вправо //
avl_node* avlTree::rr_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

// Поворот влево-влево //
avl_node* avlTree::ll_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

// Поворот влево - вправо //
avl_node* avlTree::lr_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

// Поворот вправо-влево //
avl_node* avlTree::rl_rotation(avl_node* parent)
{
    avl_node* temp;
    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

// Балансирующее АВЛ-дерево //
avl_node* avlTree::balance(avl_node* temp)
{
    int balance_factor = diff(temp);
    if (balance_factor > 1)
    {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (balance_factor < -1)
    {
        if (diff(temp->right) > 0)
            temp = rl_rotation(temp);
        else
            temp = rr_rotation(temp);
    }
    return temp;
}

// Вставить элемент в дерево //
avl_node* avlTree::insert(avl_node* root, int value)
{
    if (root == NULL)
    {
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance(root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance(root);
    }
    return root;
}

// Отобразить АВЛ-дерево //
void avlTree::display(avl_node* ptr, int level)
{
    int m;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
            cout << "Корень -> ";

        for (m = 0; m < level && ptr != root; m++)
            cout << "        ";
        cout << ptr->data;
        display(ptr->left, level + 1);
    }
}

// Отобразить последоватльность ввода чисел //
void avlTree::inorder(avl_node* tree)
{
    if (tree == NULL)
        return;
    inorder(tree->left);
    cout << tree->data << "  ";
    inorder(tree->right);
}

