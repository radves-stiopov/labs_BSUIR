#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Set {
public:
    Set() : m_set() {}

    bool empty() const;

    void add(int element);

    void remove(int element);

    int size() const;

    bool contains(int element) const;

    bool operator[](int element) const;

    Set operator+(const Set& other) const;

    Set& operator+=(const Set& other);

    Set operator*(const Set& other) const;

    Set& operator*=(const Set& other);

    Set operator-(const Set& other) const;

    Set& operator-=(const Set& other);

    Set boolean() const;

private:
    std::vector<int> m_set;
};
class CantorSet {
private:
    vector<string> set;
public:
    CantorSet() {}
    CantorSet(const char* str);
    CantorSet(string str) : CantorSet(str.c_str()) {}
    void print();
};
