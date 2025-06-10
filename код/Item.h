#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& name, int value);
    std::string GetName() const;
    int GetValue() const;

private:
    std::string name_;
    int value_;
};

#endif // ITEM_H