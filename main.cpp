#include"Colours.h"
#include "RedBlackTree.h"
int main(int argc, char* argv[])
{
	Comparator<int>* comparator = new ComparatorInt(DECREASE);
	try
	{
		Container<int, std::string>* tree = new RedBlackTree<int, std::string>(comparator);
		tree->add(15, "Pasha");
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