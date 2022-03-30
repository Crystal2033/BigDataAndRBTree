#pragma once
#include "Container.h"
#include "Comparator.h"
#include "Exceptions.h"
#include <list>
typedef enum {RED, BLACK} COLOR;


template <typename TKey, typename TData>
class RedBlackTree : public Container<TKey, TData>
{
private:
	class RBNode
	{
	public: //anyway we can`t get this class outside the tree.
		COLOR color;
		RBNode* left;
		RBNode* right;
		TKey key;
		TData data;
		std::list<RBNode*>* repeat_keys_nodes;

		RBNode() = default;
		RBNode(const TKey&, const TData&);
		RBNode(const TKey&, const TData&, COLOR);
	};
	RBNode* root;
	Comparator<TKey>* comparator;

	void find_way(const TKey, std::list<RBNode**>&) ; //const
	void insertFixUp(std::list<RBNode**>&);
	void addRepeatKey(const RBNode* node, std::list<RBNode**>& way);


	void prefix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth = 0) const;
	void infix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth = 0) const;
	void postfix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth = 0) const;
public:
	RedBlackTree(Comparator<TKey>* const &);
	void add(const TKey&, const TData&) override;
	

	void remove(const TKey&) override;
	TData& find(const TKey&) const override;
	

	void prefix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const;
	void infix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const;
	void postfix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const;
	~RedBlackTree() = default; // TODO
};

#pragma region Constructor Node and RedBlackTree
template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RBNode::RBNode(const TKey& key, const TData& data)
{
	this->key = key;
	this->data = data;
	this->right = nullptr;
	this->left = nullptr;
	repeat_keys_nodes = nullptr;
	color = RED;
}

template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RBNode::RBNode(const TKey& key, const TData& data, COLOR color)
{
	this->key = key;
	this->data = data;
	this->color = color;
	this->right = nullptr;
	this->left = nullptr;
	repeat_keys_nodes = nullptr;
}

template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RedBlackTree(Comparator<TKey>* const& cmp)
{
	root = nullptr;
	comparator = cmp;
}
#pragma endregion

#pragma region assist methods
/// ’ран€тс€ точные указатели на узлы. ѕри вставке в листе остаетс€ указатель (пуста€ веточка) на который нужно навесить вставл€емый узел.
/// Ќужно учитывать, что может добавитьс€ повторный ключ -> в добавлении нужно это обработать и добавить повтор€ющийс€ по ключу узел в лист в узле.
/// ѕри поиске (например, в удалении) в конце листа указатель на блок, который совпадает с ключом. ѕроверки после выполнени€ find_way не нужны!!!
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::find_way(const TKey key, std::list<RBNode**>& way)
{
	RBNode** iterator = &root;
	way.push_back(iterator);
	while (*iterator)
	{
		int compare_result = comparator->compare(key, (*iterator)->key);
		if (compare_result > 0) {
			iterator = &((*iterator)->right);
			way.push_back(iterator);
		}
		else if (compare_result < 0) {
			iterator = &((*iterator)->right);
			way.push_back(iterator);
		}
		else { // if insert: last element is parent of curr key kid. If find: have to check last in list children and find key, else throw
			return;
		}
	}
}


template <typename TKey, typename TData>
void print_tree(const TKey& key, const TData& data, int depth = 0)
{
	if (depth == 0)
	{
		std::cout << red << "ROOT: " << white << " ";
	}
	else
	{
		std::cout << azure << "Depth: " << depth << "." << white << " ";
	}
	std::cout << green << "Key: " << key << "." << white << " ";
	std::cout << blue << "Data: " << data << "." << white << std::endl;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::insertFixUp(std::list<RBNode**>& way)
{
	root->color = BLACK;
}

template <typename TKey, typename TData>
void RedBlackTree < TKey, TData>::addRepeatKey(const RBNode* node, std::list<RBNode**>& way)
{
	if ((*(way.back()))->repeat_keys_nodes == nullptr)
	{
		(*(way.back()))->repeat_keys_nodes = new std::list<RBNode*>;
	}
	(*(way.back()))->repeat_keys_nodes->push_back(const_cast<RBNode*>(node));
}
#pragma endregion

#pragma region ADD
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::add(const TKey& key, const TData& data)
{
	std::list<RBNode**> way;
	find_way(key, way);
	
	if (*(way.back()) != nullptr){ //“о есть указатель указывает на узел, а если при вставке он не пуст, значит, там повторный ключ.
		RBNode* repeat_key_node = new RBNode(key, data, RED);
		addRepeatKey(repeat_key_node, way);
	}
	else{
		*(way.back()) = new RBNode(key, data, RED);
	}

	insertFixUp(way);
	return;
	
}
#pragma endregion

#pragma region FIND
template <typename TKey, typename TData>
TData& RedBlackTree<TKey, TData>::find(const TKey& key) const // TODO: можно через find_way, наверное, сделать
{
	if (root == nullptr){
		throw KeyNotFoundException<TKey>("Key doesn`t exist", key);
	}
	RBNode* iterator = root;
	while (iterator){
		int compare_result = comparator->compare(key, iterator->key);
		if (compare_result > 0){
			iterator = iterator->right;
		}
		else if (compare_result < 0){
			iterator = iterator->left;
		}
		else{ // == 0
			return iterator->data;
		}
	}
	throw KeyNotFoundException<TKey>("Key doesn`t exist", key);
}
#pragma endregion

#pragma region REMOVE
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::remove(const TKey& key)
{

}
#pragma endregion


#pragma region stepovers
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::prefix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth) const
{
	if (cur_root != nullptr)
	{
		call_back(cur_root->key, cur_root->data, depth++);
		//depth++;
		prefix(call_back, cur_root->left, depth);
		prefix(call_back, cur_root->right, depth--);
		//depth--;
	}
	return;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::infix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth) const
{
	if (cur_root != nullptr)
	{
		//depth++;
		infix(call_back, cur_root->left, ++depth);
		//depth--;
		call_back(cur_root->key, cur_root->data, --depth);
		//depth++;
		infix(call_back, cur_root->right, ++depth);
	}
	return;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::postfix(void(*call_back)(const TKey&, const TData&, int), RBNode* cur_root, int depth) const
{
	if (cur_root != nullptr)
	{
		//depth++;
		postfix(call_back, cur_root->left, ++depth);
		postfix(call_back, cur_root->right, depth--);
		//depth--;

		call_back(cur_root->key, cur_root->data, depth++);
		//depth++;
	}
	return;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::prefix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const
{
	prefix(call_back, this->root);
	return;
}

template <typename TKey, typename TData>
void  RedBlackTree<TKey, TData>::infix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const
{
	infix(call_back, this->root);
	return;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::postfix_stepover_tree(void(*call_back)(const TKey&, const TData&, int)) const
{
	postfix(call_back, this->root);
	return;
}

#pragma endregion