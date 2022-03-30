#include"Colours.h"
#include "RedBlackTree.h"
int main(int argc, char* argv[])
{
	Comparator<int>* comparator = new ComparatorInt(DECREASE);
	try
	{
		RedBlackTree<int, std::string>* tree = new RedBlackTree<int, std::string>(comparator);
		tree->add(15, "Pasha");
		tree->add(20, "Kesha");
		tree->add(20, "Lesha");
		tree->add(10, "Lena");
		tree->add(30, "Sema");
		tree->infix_stepover_tree(print_tree);
		std::cout << green << "Hello world!" << white << std::endl;
	}
	catch (KeyNotFoundException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (KeyAlreadyExistsException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	return 0;
}