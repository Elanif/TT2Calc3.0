#pragma once

#include<list>

template<class T>
class tiercontainer {
	tiercontainer(const size_t& _tiers);
	tiercontainer(const tiercontainer<T>& cpy);
	tiercontainer<T>& operator=(const tiercontainer<T>& cpy);
	void swap();
	void populatetemp(const size_t& _tier, const T& pushedobj); //copies pushedobj
	bool inserttemp(const size_t& _tier, const T& candidate); //copies candidate if found eligible and may delete items that are worse than candidate
	T extract_front(const size_t& _tier);
	bool empty(const size_t& _tier);
	T* print(bool _lessequal(const T& a, const T& b));
	~tiercontainer();
private:
	std::list<T>* tierlist;
	std::list<T>* _temptierlist;
	size_t tiers;
};

/*
tiers=the max cost
skillnum
*/
template<class T>
void tierordering(const size_t& tiers, const size_t T::* _lvlprogression(const size_t&, const size_t&));

template<class T>
void tierordering(const size_t& tiers, const T& firstchild, const size_t& skillnumber, const size_t(T::* lvlprogression)(const size_t&, const size_t&), size_t(T::* _build)(const size_t&, const size_t&));
