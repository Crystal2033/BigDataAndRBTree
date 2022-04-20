#pragma once
#include "Generator.h"
class InterfaceFactory {
public:
	virtual InterfaceGenerator* createGenerator() const = 0;
	virtual ~InterfaceFactory() = default;
};

class DeliGeneratorFactory : public InterfaceFactory {
public:
	InterfaceGenerator* createGenerator() const override {
		return new DeliGenerator;
	}
};

