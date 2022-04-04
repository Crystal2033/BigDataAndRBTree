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

	void findWay(const TKey, std::stack<RBNode**>&) const;
	void insertFixUp(std::stack<RBNode**>&);
	void addRepeatKey(const RBNode* node, std::stack<RBNode**>& way);
	RBNode* leftRotation(RBNode* old_root);
	RBNode* rightRotation(RBNode* old_root);

	void transplant(RBNode* const& parent_u, RBNode* const& u_node, RBNode* const& v_node);
	void rb_delete(RBNode* z_node, std::stack<RBNode**>& way);
	std::pair<RBNode*, RBNode*> tree_minimum(RBNode* const& x_node);
	void delete_node(RBNode*& del_node);
	void deleteFixUp(RBNode* x_node, std::stack<RBNode**>& way);

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

	if (old_root->right == nullptr)
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

	if (old_root->left == nullptr)
	{
		return old_root;
	}

	RBNode* old_root_temp = old_root;
	old_root = old_root->left;
	old_root_temp->left = old_root->right;
	old_root->right = old_root_temp;
	return old_root;
}
#pragma endregion

#pragma region assist methods
/// Хранятся точные указатели на узлы. При вставке в листе остается указатель (пустая веточка) на который нужно навесить вставляемый узел.
/// Нужно учитывать, что может добавиться повторный ключ -> в добавлении нужно это обработать и добавить повторяющийся по ключу узел в лист в узле.
/// При поиске (например, в удалении) в конце листа указатель на блок, который совпадает с ключом. Проверки после выполнения find_way не нужны!!!
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::findWay(const TKey key, std::stack<RBNode**>& way) const
{
	RBNode** iterator = const_cast<RBNode**>(&root);
	way.push(iterator);
	while (*iterator)
	{
		int compare_result = comparator->compare(key, (*iterator)->key);
		if (compare_result > 0) {
			iterator = &((*iterator)->right);
			way.push(iterator);
		}
		else if (compare_result < 0) {
			iterator = &((*iterator)->left);
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
		way.pop();
		while ((parent_node != nullptr) && parent_node->color == RED)
		{
			grandpa_node = *(way.top());
			way.pop();
			if (parent_node == grandpa_node->left)
			{
				RBNode* uncle_node = grandpa_node->right;

				if ((uncle_node != nullptr) && uncle_node->color == RED)
				{
					parent_node->color = BLACK;
					uncle_node->color = BLACK;
					grandpa_node->color = RED;
					checking_node = grandpa_node;
					if (way.size() == 0)
					{
						parent_node = nullptr;
					}
					else
					{
						parent_node = *(way.top());
						way.pop();
					}
					continue;
				}
				else if (checking_node == parent_node->right)
				{
					RBNode* future_parent_node = checking_node;
					checking_node = parent_node;
					grandpa_node->left = leftRotation(checking_node);
					parent_node = future_parent_node;
				}
				parent_node->color = BLACK;
				grandpa_node->color = RED;
				if (way.size() == 0)
				{
					root = rightRotation(grandpa_node);
				}
				else
				{
					RBNode* great_grandpa_node = *(way.top());
					way.pop();
					if (great_grandpa_node->right == grandpa_node)
					{
						great_grandpa_node->right = rightRotation(grandpa_node);
					}
					else if (great_grandpa_node->left == grandpa_node)
					{
						great_grandpa_node->left = rightRotation(grandpa_node);
					}
				}
			}//TODO EVERYTHIN ELSE
			else
			{
				RBNode* uncle_node = grandpa_node->left; // Uncle exists because tree is balanced
				if ((uncle_node != nullptr) && uncle_node->color == RED)
				{
					parent_node->color = BLACK;
					uncle_node->color = BLACK;
					grandpa_node->color = RED;
					checking_node = grandpa_node;
					if (way.size() == 0)
					{
						parent_node = nullptr;
					}
					else
					{
						parent_node = *(way.top());
						way.pop();
					}
					continue;
				}
				else if (checking_node == parent_node->left)
				{
					RBNode* future_parent_node = checking_node;
					checking_node = parent_node;
					grandpa_node->right = rightRotation(checking_node);
					parent_node = future_parent_node;
				}
				parent_node->color = BLACK;
				grandpa_node->color = RED;
				if (way.size() == 0)
				{
					root = leftRotation(grandpa_node);
				}
				else
				{
					RBNode* great_grandpa_node = *(way.top());
					way.pop();
					if (great_grandpa_node->left == grandpa_node)
					{
						great_grandpa_node->left = leftRotation(grandpa_node);
					}
					else if (great_grandpa_node->right == grandpa_node)
					{
						great_grandpa_node->right = leftRotation(grandpa_node);
					}
				}
			}
		}
	}
	
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


#pragma endregion

#pragma region ADD
template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::add(const TKey& key, const TData& data)
{
	std::stack<RBNode**> way;
	findWay(key, way);
	std::cout << yellow << "INSERTING. " << cyan << key << " : " << data << white << std::endl;
	if (*(way.top()) != nullptr){ //То есть указатель указывает на узел, а если при вставке он не пуст, значит, там повторный ключ.
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

#pragma region assist methods for delete

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::transplant(RBNode* const& parent_u, RBNode* const& u_node, RBNode* const& v_node)
{
	if (parent_u == nullptr) {
		root = v_node;
	}
	else if (u_node == parent_u->left) {
		parent_u->left = v_node;
	}
	else {
		parent_u->right = v_node;
	}
}


template <typename TKey, typename TData>
std::pair<typename RedBlackTree<TKey, TData>::RBNode*, typename RedBlackTree<TKey, TData>::RBNode*> RedBlackTree<TKey, TData>::tree_minimum(RBNode* const& x_node)
{
	std::pair<RBNode*, RBNode*> y_node_and_y_parent;
	RBNode* y_node_iter = x_node;
	RBNode* y_parent_node = nullptr;
	while (y_node_iter->left != nullptr) {
		y_parent_node = y_node_iter;
		y_node_iter = y_node_iter->left;
	}
	y_node_and_y_parent.first = y_node_iter;
	y_node_and_y_parent.second = y_parent_node;
	return y_node_and_y_parent; // if y_parent_node == nullptr --> x_node is min. there are no loop iterations.
}
#pragma endregion

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::remove(const TKey& key) //like Kormen
{
	std::cout << purple << key << white << std::endl;
	if (root == nullptr){
		throw KeyNotFoundException<TKey>("Key wasn`t found. Tree is empty.", key);
	}
	std::stack<RBNode**> way;
	findWay(key, way);
	if (*(way.top()) == nullptr){
		throw KeyNotFoundException<TKey>("Key wasn`t found.", key);
	}
	rb_delete(*(way.top()), way);
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::delete_node(RBNode*& del_node)
{
	del_node->left = nullptr;
	del_node->right = nullptr;
	delete del_node;
	del_node = nullptr;
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::rb_delete(RBNode* z_node, std::stack<RBNode**>& way)
{
	way.pop();// delete z_node from stack.
	RBNode* y_node = z_node;
	COLOR y_orig_color = y_node->color;
	RBNode* parent_z_node = nullptr;
	RBNode* parent_x_node;
	RBNode* x_node;
	if (!way.empty()) {
		parent_z_node = *(way.top());
		way.pop();
	}

	if (z_node->left == nullptr){
		x_node = z_node->right;
		transplant(parent_z_node, z_node, z_node->right);
		parent_x_node = parent_z_node;
	}
	else if (z_node->right == nullptr) {
		x_node = z_node->left;
		transplant(parent_z_node, z_node, z_node->left);
		parent_x_node = parent_z_node;
	}
	else {
		std::pair<RBNode*, RBNode*> y_node_y_parent;
		RBNode* y_parent = z_node;
		y_node_y_parent = tree_minimum(z_node->right);
		y_node = y_node_y_parent.first;
		if (y_node_y_parent.second != nullptr) {
			y_parent = y_node_y_parent.second;
		}
		y_orig_color = y_node->color;
		x_node = y_node->right;
		if (y_parent == z_node){ //it means that z_node is a parent for the y_node.
			//x_node->parent = y_node; this is don`t need for us.
		}
		else
		{
			transplant(y_parent, y_node, y_node->right);
			y_node->right = z_node->right;
		}
		transplant(parent_z_node, z_node, y_node);
		y_node->left = z_node->left;
		y_node->color = z_node->color;
		if (y_parent != z_node)
		{
			parent_x_node = y_parent;
		}
		else {
			parent_x_node = y_node;
		}

	}
	
	delete_node(z_node); 

	if (root == nullptr) // parent_x_node and x_node are nullptr. То есть этот случай отрезает наш, возможно, пустой стек дальше.
	{
		return;
	}

	if (y_orig_color == BLACK)
	{
		std::stack<RBNode**> way_to_x_node;
		if (parent_x_node != nullptr)// two nodes in the tree. And deleting root
		{
			findWay(parent_x_node->key, way_to_x_node);
		}
		else
		{
			findWay(x_node->key, way_to_x_node);
		}
		deleteFixUp(x_node, way_to_x_node); // x_node is on the top of the stack.
	}
}

template <typename TKey, typename TData>
void RedBlackTree<TKey, TData>::deleteFixUp(RBNode* x_node, std::stack<RBNode**>& way)
{
	//if x_node == nullptr --> only parent exists. And x_node is BLACK sentinel.
	COLOR x_color;
	RBNode* parent_x_node = nullptr;
	std::stack<RBNode**> current_way = way;
	if (x_node == nullptr) {
		x_color = BLACK;
	}
	else {
		x_color = x_node->color;
	}

	while (x_node != root && x_color == BLACK) //if x_node != root --> we have parent for x.
	{
		if (!current_way.empty())
		{
			parent_x_node = *(current_way.top());
			current_way.pop();
		}
		if (x_node == parent_x_node->left)
		{
			RBNode* w_node = parent_x_node->right;
			COLOR w_node_color;
			if (w_node == nullptr)
			{
				w_node_color = BLACK;
			}
			else
			{
				w_node_color = w_node->color;
			}
			if (w_node_color== RED)
			{
				//////////////case1{
				w_node->color = BLACK;
				parent_x_node->color = RED;
				RBNode* grandpa_x = nullptr;
				if (current_way.empty())
				{
					root = leftRotation(parent_x_node);
				}
				else
				{
					grandpa_x = *(current_way.top());
					current_way.pop();
					if (parent_x_node == grandpa_x->left) {
						grandpa_x->left = leftRotation(parent_x_node);
					}
					else if (parent_x_node == grandpa_x->right) {
						grandpa_x->right = leftRotation(parent_x_node);
					}
				}

				current_way = std::stack<RBNode**>(); //clear stack
				if (x_node != nullptr)
				{
					findWay(x_node->key, current_way); // после поворота у нас уже может быть другой путь до корня. из-за case 1 (left_rotate)
					x_node = *(current_way.top());
					current_way.pop();
				}
				else //if (parent_x_node != nullptr)
				{
					findWay(parent_x_node->key, current_way);
				}

				if (!current_way.empty())
				{
					parent_x_node = *(current_way.top());
					current_way.pop();
				}
				w_node = parent_x_node->right;
			}
			//////////////case1}
			//////////////case2{
			COLOR w_node_right_color;
			COLOR w_node_left_color;
			if (w_node->right == nullptr)
			{
				w_node_right_color = BLACK;
			}
			else
			{
				w_node_right_color = w_node->right->color;
			}

			if (w_node->left == nullptr)
			{
				w_node_left_color = BLACK;
			}
			else
			{
				w_node_left_color = w_node->left->color;
			}
			if ( (w_node_left_color == BLACK) && (w_node_right_color == BLACK))
			{

				w_node->color = RED;
				x_node = parent_x_node;
				if (x_node == nullptr) {
					x_color = BLACK;
				}
				else {
					x_color = x_node->color;
				}

			}
			//////////////case2}

			else
			{
				//////////////case3{
				if ((w_node->right == nullptr) || w_node->right->color == BLACK)
				{
					if (w_node->left != nullptr)
					{
						w_node->left->color = BLACK;
					}
					w_node->color = RED;
					parent_x_node->right = rightRotation(w_node);
					w_node = parent_x_node->right;
				}
				//////////////case3}
				//////////////case4{
				w_node->color = parent_x_node->color;
				parent_x_node->color = BLACK;
				w_node->right->color = BLACK;

				RBNode* grandpa_x = nullptr;
				if (current_way.empty())
				{
					root = leftRotation(parent_x_node);
				}
				else
				{
					grandpa_x = *(current_way.top());
					current_way.pop();
					if (parent_x_node == grandpa_x->left) {
						grandpa_x->left = leftRotation(parent_x_node);
					}
					else if (parent_x_node == grandpa_x->right) {
						grandpa_x->right = leftRotation(parent_x_node);
					}
					w_node = parent_x_node->right;
				}
				x_node = root;
				//////////////case4}

			}

		}
		else
		{
			RBNode* w_node = parent_x_node->left;
			COLOR w_node_color;
			if (w_node == nullptr)
			{
				w_node_color = BLACK;
			}
			else
			{
				w_node_color = w_node->color;
			}
			if (w_node_color == RED)
			{
				//////////////case1{
				w_node->color = BLACK;
				parent_x_node->color = RED;
				RBNode* grandpa_x = nullptr;
				if (current_way.empty())
				{
					root = rightRotation(parent_x_node);
				}
				else
				{
					grandpa_x = *(current_way.top());
					current_way.pop();
					if (parent_x_node == grandpa_x->right) {
						grandpa_x->right = rightRotation(parent_x_node);
					}
					else if (parent_x_node == grandpa_x->left) {
						grandpa_x->left = rightRotation(parent_x_node);
					}
				}

				current_way = std::stack<RBNode**>(); //clear stack
				if (x_node != nullptr)
				{
					findWay(x_node->key, current_way); // после поворота у нас уже может быть другой путь до корня. из-за case 1 (left_rotate)
					x_node = *(current_way.top());
					current_way.pop();
				}
				else //if (parent_x_node != nullptr)
				{
					findWay(parent_x_node->key, current_way);
				}
				
				if (!current_way.empty())
				{
					parent_x_node = *(current_way.top());
					current_way.pop();
				}
				w_node = parent_x_node->left;
			}
			//////////////case1}
			//////////////case2{
			COLOR w_node_right_color;
			COLOR w_node_left_color;
			if (w_node->right == nullptr)
			{
				w_node_right_color = BLACK;
			}
			else
			{
				w_node_right_color = w_node->right->color;
			}

			if (w_node->left == nullptr)
			{
				w_node_left_color = BLACK;
			}
			else
			{
				w_node_left_color = w_node->left->color;
			}
			if ((w_node_right_color == BLACK) && (w_node_left_color == BLACK))
			{

				w_node->color = RED;
				x_node = parent_x_node;
				if (x_node == nullptr) {
					x_color = BLACK;
				}
				else {
					x_color = x_node->color;
				}

			}
			//////////////case2}

			else
			{
				//////////////case3{
				if ((w_node->left == nullptr) || w_node->left->color == BLACK)
				{
					if (w_node->right != nullptr)
					{
						w_node->right->color = BLACK;
					}
					w_node->color = RED;
					parent_x_node->left = leftRotation(w_node);
					w_node = parent_x_node->left;
				}
				//////////////case3}
				//////////////case4{
				w_node->color = parent_x_node->color;
				parent_x_node->color = BLACK;
				w_node->left->color = BLACK;

				RBNode* grandpa_x = nullptr;
				if (current_way.empty())
				{
					root = rightRotation(parent_x_node);
				}
				else
				{
					grandpa_x = *(current_way.top());
					current_way.pop();
					if (parent_x_node == grandpa_x->right) {
						grandpa_x->right = rightRotation(parent_x_node);
					}
					else if (parent_x_node == grandpa_x->left) {
						grandpa_x->left = rightRotation(parent_x_node);
					}
					w_node = parent_x_node->left;
				}
				x_node = root;
				//////////////case4}

			}
		}
		
	}
	std::cout << red << "FIXING" << white << std::endl;
	if (x_node != nullptr)
	{
		x_node->color = BLACK;
	}
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