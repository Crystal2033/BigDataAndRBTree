#pragma once
#include "Delivery.h"
#include <list>
class InterfaceGenerator {
public:
	virtual std::list<Cargo*>* generateData() const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator {
public:
	std::list<Cargo*>* generateData() const override;
	DeliGenerator() = default;
	~DeliGenerator() = default;
};

std::list<Cargo*>* DeliGenerator::generateData() const
{
	std::list<Cargo*>* delivs = new std::list<Cargo*>;
	return delivs;
}