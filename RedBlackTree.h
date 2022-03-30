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


		RBNode() = default;
		RBNode(const TKey&, const TData&);
		RBNode(const TKey&, const TData&, COLOR);
	};
	RBNode* root;
	Comparator<TKey>* comparator;

	void find_way(const TKey, std::list<RBNode**>&) ; //const
public:
	RedBlackTree(Comparator<TKey>* const &);
	void add(const TKey&, const TData&) override;
	void remove(const TKey&) override;
	TData& find(const TKey&) const override;
	~RedBlackTree() = default; // TODO
};

#pragma region Constructor Node and RedBlackTree
template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RBNode::RBNode(const TKey& key, const TData& data)
{
	this->key = key;
	this->data = data;
	color = RED;
}

template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RBNode::RBNode(const TKey& key, const TData& data, COLOR color)
{
	this->key = key;
	this->data = data;
	this->color = color;
}

template <typename TKey, typename TData>
RedBlackTree<TKey, TData>::RedBlackTree(Comparator<TKey>* const& cmp)
{
	root = nullptr;
	comparator = cmp;
}
#pragma endregion

#pragma region assist methods
/// <summary>
/// 
/// ’ран€тс€ точные указатели на узлы. ѕри вставке в листе остаетс€ указатель (пуста€ веточка) на который нужно навесить вставл€емый узел.
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

#pragma endregion

#pragma region ADD
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::add(const TKey& key, const TData& data)
{
	std::list<RBNode**> way;
	find_way(key, way);
	if (way.size() == 1) //only root
	{
		*(way.back()) = new RBNode(key, data, BLACK);
		return;
	}
	RBNode* parent
	
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