#pragma once
#include <iostream>
#include "Delivery.h"

#pragma region CALLBACKS
void print_tree_for_deliv_pair_str(const std::pair<std::string*, unsigned int>& key, Delivery* const& data, int depth)
{
	if (depth == 0)
	{
		std::cout << red << "ROOT: " << white << " ";
	}
	else
	{
		std::cout << azure << "Depth: " << depth << "." << white << " " << std::endl;
	}
	std::cout << red << "Key: " << green << *key.first << white << " " << red << "Hash: " << pink << key.second << white << " " << std::endl;
	std::cout << purple << "Data: " << std::endl << *data << white << std::endl;
}

void print_tree_for_deliv_pair_float(const std::pair<float, unsigned int>& key, Delivery* const& data, int depth)
{
	if (depth == 0)
	{
		std::cout << red << "ROOT: " << white << " ";
	}
	else
	{
		std::cout << azure << "Depth: " << depth << "." << white << " " << std::endl;
	}
	std::cout << red << "Key: " << green << key.first << white << " " << red << "Hash: " << pink << key.second << white << " " << std::endl;
	std::cout << purple << "Data: " << std::endl << *data << white << std::endl;
}

#pragma endregion

#pragma region CIN operation choice
int userChoice(const int left_edge, const int right_edge)
{
	std::string choice_str;
	int choice_number;
	while (true)
	{
		choice_str.clear();
		std::cout << blue << "Input a number:" << white <<std::endl <<  "> ";
		std::cin >> choice_str;
		choice_number = atoi(choice_str.c_str()); //return 0 in bad case. So i don`t need 0 in any case.

		if (choice_number < left_edge || choice_number > right_edge) {
			std::cout << red << "InputValueError: You have to choose value from <" << yellow << left_edge << red << "> to <" << yellow << right_edge
				<< red << ">." << white <<std::endl;
			continue;
		}
		break;
	}

	return choice_number;
}
#pragma endregion


#pragma region CONTROLLERS
void chooseComparator()
{
	std::cout << cyan << "You have to choose the comparator by field for your tree (input 1-10):" << blue << std::endl;
	std::cout << "1. Name" << std::endl << "2. Content" << std::endl << "3. Weight" << std::endl
		<< "4. Price" << std::endl << "5. Delivery price" << std::endl << "6. Sender (from country)" << std::endl
		<< "7. Departure point (by company)" << std::endl << "8. Reciever (to country)" << std::endl
		<< "9. Destination point (for company)" << std::endl << "10. Type of transport" << std::endl << white;
}
void greetings() {
	std::cout << cyan << "Hello, my name is Kulikov Pavel, FIIT, M80-211B-20." << white << std::endl;
	std::cout << cyan << "This is a programm which can store and work with your data (" << green << "add" << cyan << " / "
		<< yellow << "find" << cyan << " / " << red << "delete" << cyan << " / " << azure << "generate" << cyan
		<< ")." << white << std::endl << std::endl;
}

void chooseCollection() {
	std::cout << cyan << "At first you have to choose the type of collection (input 1 or 2): " << std::endl
		<< blue << "1. Red Black tree." << std::endl << "2. Queue" << white << std::endl << white;
}

void chooseOperation()
{
	std::cout << cyan << "You have to choose one operation, which works with your comparator key:" << std::endl
		<< green << "1. Add data." << std::endl << yellow << "2. Find data."
		<< std::endl << pink << "3. Delete data." << std::endl << red << "4. Exit." <<  white << std::endl;
}
#pragma endregion