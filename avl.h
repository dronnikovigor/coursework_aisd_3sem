#ifndef _AVL_H
#define _AVL_H
 
struct node { // структура для представления узлов дерева
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { //конструктор
		key = k;
		left = right = 0;
		height = 1;
	}
};
 
unsigned char height(node* p); //определение нулевого дерева
int bfactor(node* p); //разность высот правой и левой ветки
void fixheight(node* p); //подсчёт корректной высоты для заданного узла
node* rotateright(node* p); //правый поворот вокруг заданного узла
node* rotateleft(node* q); //левый поворот вокруг заданного узла
node* balance(node* p); //балансировка узлов
node* insert(node* p, int k); //вставка ключа в дерево с заданным корнем
node* inputAVL(node* &avl); //считывание дерева из заданного файла
bool searchElem(node*avl, int elem); //провека на содержание элемента в дереве
node* findmin(node* p); //поиск узла с минимальным ключом в дереве
node* removemin(node* p); //удаление узла с минимальным ключом из дерева
node* remove(node* p, int k); //удаление ключа k из дерева
 
#endif
