#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
	Item(const std::string& name, int value);

	const std::string& name() const;
	int value() const;
	std::string Use() const;

private:
	std::string name_;
	int value_;
};

#endif  // ITEM_H