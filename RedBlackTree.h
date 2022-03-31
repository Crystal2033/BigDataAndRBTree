#pragma once
#include "Container.h"
#include "Comparator.h"
#include "Exceptions.h"
#include <stack>
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

	void findWay(const TKey, std::stack<RBNode**>&) ; //const
	void insertFixUp(std::stack<RBNode**>&);
	void addRepeatKey(const RBNode* node, std::stack<RBNode**>& way);
	//RBNode* getParentNode(const RBNode*, const std::stack<RBNode**>&);
	RBNode* leftRotation(RBNode* old_root);
	RBNode* rightRotation(RBNode* old_root);

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

#pragma region ROTATIONS
template <typename TKey, typename TData>
typename RedBlackTree<TKey, TData>::RBNode* RedBlackTree<TKey, TData>::leftRotation(RBNode* old_root)
{
	if (old_root == nullptr)
	{
		return old_root;
	}

	if (old_root->right_child == nullptr)
	{
		return old_root;
	}

	RBNode* old_root_temp = old_root;
	old_root = old_root->right;
	old_root_temp->right = old_root->left;
	old_root->left = old_root_temp;
	return old_root;
}

template <typename TKey, typename TData>
typename RedBlackTree<TKey, TData>::RBNode* RedBlackTree<TKey, TData>::rightRotation(RBNode* old_root)
{
	if (old_root == nullptr)
	{
		return old_root;
	}

	if (old_root->left_child == nullptr)
	{
		return old_root;
	}

	RBNode* old_root_temp = old_root;
	old_root = old_root->left_child;
	old_root_temp->left_child = old_root->right_child;
	old_root->right_child = old_root_temp;
	return old_root;
}
#pragma endregion

#pragma region assist methods
/// ’ран€тс€ точные указатели на узлы. ѕри вставке в листе остаетс€ указатель (пуста€ веточка) на который нужно навесить вставл€емый узел.
/// Ќужно учитывать, что может добавитьс€ повторный ключ -> в добавлении нужно это обработать и добавить повтор€ющийс€ по ключу узел в лист в узле.
/// ѕри поиске (например, в удалении) в конце листа указатель на блок, который совпадает с ключом. ѕроверки после выполнени€ find_way не нужны!!!
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::findWay(const TKey key, std::stack<RBNode**>& way)
{
	RBNode** iterator = &root;
	way.push(iterator);
	while (*iterator)
	{
		int compare_result = comparator->compare(key, (*iterator)->key);
		if (compare_result > 0) {
			iterator = &((*iterator)->right);
			way.push(iterator);
		}
		else if (compare_result < 0) {
			iterator = &((*iterator)->right);
			way.push(iterator);
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
void RedBlackTree<TKey, TData>::insertFixUp(std::stack<RBNode**>& way)
{
	RBNode* checking_node = *(way.top());
	RBNode* parent_node;
	RBNode* grandpa_node;
	way.pop();
	if (way.size() != 0)
	{
		parent_node = *(way.top());
	}
	
	//RBNode* parent_node = getParentNode(checking_node, way);
	
	//if (parent_node != nullptr)
	//{
		//while (parent_node != nullptr && parent_node->color != RED)
		//{
		//	grandpa_node = getParentNode(parent_node, way); //100% exists, because parent is RED and inserted is RED, grandpa -- BLACK
		//	if ((grandpa_node != nullptr) && checking_node == grandpa_node->left)
		//	{
		//		RBNode* uncle_node = grandpa_node->right; //he is exist, because our tree is balanced
		//		if (uncle_node->color == RED)
		//		{
		//			parent_node->color = BLACK;
		//			uncle_node->color = BLACK;
		//			grandpa_node->color = RED;
		//			checking_node = grandpa_node;
		//			parent_node = getParentNode(checking_node, way);
		//		}
		//	}
		//	else if (checking_node == parent_node->right)
		//	{
		//		checking_node = parent_node;
		//		grandpa_node->left = leftRotation(checking_node);
		//		parent_node = getParentNode(checking_node, way);
		//	}

		//}
	//}
	
	root->color = BLACK;
}

template <typename TKey, typename TData>
void RedBlackTree <TKey, TData>::addRepeatKey(const RBNode* node, std::stack<RBNode**>& way)
{
	if ((*(way.top()))->repeat_keys_nodes == nullptr)
	{
		(*(way.top()))->repeat_keys_nodes = new std::list<RBNode*>;
	}
	(*(way.top()))->repeat_keys_nodes->push_back(const_cast<RBNode*>(node));
}


//template <typename TKey, typename TData>
//typename RedBlackTree<TKey, TData>::RBNode* RedBlackTree<TKey, TData>::getParentNode(const RBNode* child_node, const std::list<RBNode**>& way)
//{
//	RBNode* parent_node;
//	for (auto iter : way){
//		if (*iter == child_node) {
//			if (iter == *(way.begin())){
//				return nullptr;
//				//throw ParentNodeNotExistsException("Parent node wasn`t found.");
//			}
//			return parent_node;
//		}
//		parent_node = *iter;
//	}
//	throw ParentNodeNotExistsException("Parent node wasn`t found.");
//}
#pragma endregion

#pragma region ADD
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::add(const TKey& key, const TData& data)
{
	std::stack<RBNode**> way;
	findWay(key, way);
	
	if (*(way.top()) != nullptr){ //“о есть указатель указывает на узел, а если при вставке он не пуст, значит, там повторный ключ.
		RBNode* repeat_key_node = new RBNode(key, data, RED);
		addRepeatKey(repeat_key_node, way);
	}
	else{
		*(way.top()) = new RBNode(key, data, RED);
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
			return iterator->data; //TODO: RETURN LIST OF KEYS(COULD REPEAT)
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