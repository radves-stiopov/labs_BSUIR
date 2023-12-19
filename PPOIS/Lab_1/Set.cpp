#include "Set.h"

bool Set::empty() const
{
	return m_set.empty();
}

void Set::add(int element)
{
	m_set.push_back(element);
}

void Set::remove(int element)
{
	auto it = std::find(m_set.begin(), m_set.end(), element);
	if (it != m_set.end()) {
		m_set.erase(it);
	}
}

int Set::size() const
{

	return m_set.size();

}

bool Set::contains(int element) const
{
	return std::find(m_set.begin(), m_set.end(), element) != m_set.end();
}

bool Set::operator[](int element) const
{

	return contains(element);
}

Set Set::operator+(const Set& other) const
{
	Set result;
	for (int element : m_set) {
		result.add(element);
	}
	for (int element : other.m_set) {
		if (!result.contains(element)) {
			result.add(element);
		}
	}
	return result;
}

Set& Set::operator+=(const Set& other)
{
	for (int element : other.m_set) {
		if (!contains(element)) {
			add(element);
		}
	}
	return *this;
}

Set Set::operator*(const Set& other) const
{
	Set result;
	for (int element : m_set) {
		if (other.contains(element)) {
			result.add(element);
		}
	}
	return result;
}

Set& Set::operator*=(const Set& other)
{
	std::vector<int> new_set;
	for (int element : m_set) {
		if (other.contains(element)) {
			new_set.push_back(element);
		}
	}
	m_set = new_set;
	return *this;
}

Set Set::operator-(const Set& other) const
{
	Set result;
	for (int element : m_set) {
		if (!other.contains(element)) {
			result.add(element);
		}
	}
	return result;
}

Set& Set::operator-=(const Set& other)
{
	std::vector<int> new_set;
	for (int element : m_set) {
		if (!other.contains(element)) {
			new_set.push_back(element);
		}
	}
	m_set = new_set;
	return *this;
}

Set Set::boolean() const
{
	Set result;
	result.add(0);
	for (int element : m_set) {
		Set temp = result;
		for (int e : temp.m_set) {
			result.add(e + element);
		}
	}
	return result;
}

CantorSet::CantorSet(const char* str)
{
	string s(str);
	int n = s.size();
	string temp = "";
	for (int i = 0; i < n; i++) {
		if (s[i] == '{' || s[i] == '}' || s[i] == ',') {
			if (temp != "") {
				set.push_back(temp);
				temp = "";
			}
		}
		else {
			temp += s[i];
		}
	}
	if (temp != "") {
		set.push_back(temp);
	}
}

void CantorSet::print()
{
	int n = set.size();
	cout << "{";
	for (int i = 0; i < n; i++) {
		cout << set[i];
		if (i < n - 1) {
			cout << ",";
		}
	}
	cout << "}" << endl;
}
