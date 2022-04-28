#pragma once
#include "Generator.h"
template <typename GenerType>
class InterfaceFactory {
public:
	virtual InterfaceGenerator<GenerType>* createGenerator() const = 0;
	virtual ~InterfaceFactory() = default;
};

class DeliGeneratorFactory : public InterfaceFactory<Delivery> {
public:
	InterfaceGenerator<Delivery>* createGenerator() const override {
		return new DeliGenerator;
	}
};

