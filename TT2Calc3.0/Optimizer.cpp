#include"Optimizer.hpp"
#include<functional>
#include<iterator>
template<class T>
tiercontainer<T>::tiercontainer(const size_t& _tiers) :tiers(_tiers) {
	tierlist = new std::list<T>[tiers + 1];
	_temptierlist = new std::list<T>[tiers + 1];
	tierlist[0].push_back(T());
}

template<class T>
tiercontainer<T>::tiercontainer(const tiercontainer<T>& cpy) {
	tiers = cpy.tiers;
	std::memcpy(tierlist, cpy.tierlist, tiers);
	std::memcpy(_temptierlist, cpy._temptierlist, tiers);
}

template<class T>
tiercontainer<T>& tiercontainer<T>::operator=(const tiercontainer<T>& cpy) {
	if (this == &cpy)
		return *this; //self assignment
	tiers = cpy.tiers;
	if (tierlist != NULL) {
		delete[] tierlist; //clean up already allocated memory
		tierlist = new std::list<T>[tiers];
	}
	if (_temptierlist != NULL) {
		delete[] _temptierlist; //clean up already allocated memory
		_temptierlist = new std::list<T>[tiers];
	}

	std::memcpy(tierlist, cpy.tierlist, tiers);
	std::memcpy(_temptierlist, cpy._temptierlist, tiers);
	return *this;
}

template<class T>
void tiercontainer<T>::populatetemp(const size_t& _tier, const T& pushedobj) {
	_temptierlist[_tier].push_back(pushedobj);
}

template<class T>
void tiercontainer<T>::swap() {
	delete[] tierlist;
	tierlist = _temptierlist;
	_temptierlist = new std::list<T>[tiers + 1];
}

template<class T>
tiercontainer<T>::~tiercontainer() {
	delete[] tierlist;
	delete[] _temptierlist;
};

template<class T>
T tiercontainer<T>::extract_front(const size_t& _tier) {
	T _temp = tierlist[_tier].front();
	tierlist[_tier].pop_front();
	return _temp;
}

template<class T>
bool tiercontainer<T>::inserttemp(const size_t& _tier, const T& candidate) {
	bool pushback = true;
	for (typename std::list<T>::iterator it = _temptierlist[_tier].begin(); it != _temptierlist[_tier].end(); ) {
		if ((*it) <= candidate) {
			_temptierlist[_tier].erase(it++);
		}
		else {
			if (candidate <= (*it)) {
				it = _temptierlist[_tier].end();
				pushback = false;
			}
			else ++it;
		}
	}
	if (pushback) populatetemp(_tier, candidate);
	return pushback;
}

template<class T>
bool tiercontainer<T>::empty(const size_t& _tier) {
	return tierlist[_tier].empty();
}

template<class T>
T* tiercontainer<T>::print(bool _lessequal(const T& a, const T& b)) {
	typename std::list<T>::iterator;
	T* maxdamage = new T[tiers];
	for (int k = 0; k < tiers; ++k) maxdamage[k] = T();
	for (int k = 1; k < tiers; ++k) {
		if (tierlist[k].size() > 0) {
			typename std::list<T>::iterator max = tierlist[k].begin();
			for (typename std::list<T>::iterator it = tierlist[k].begin(); it != tierlist[k].end(); ++it)
				if (distribution::valuelessequal(*max, *it)) max = it;
			maxdamage[k] = (*max);
		}
	}
	return maxdamage;
}

template<class T>
void tierordering(const size_t & tiers, const size_t T:: * _lvlprogression(const size_t&, const size_t&)) {
	tierordering<T>(tiers, T(), _lvlprogression);
}

template<class T>
void tierordering(const size_t & tiers, const T & firstchild, const size_t & skillnumber, const size_t(T:: * lvlprogression)(const size_t&, const size_t&), size_t(T:: * _build)(const size_t&, const size_t&)) {
	std::function < size_t(const size_t&, const size_t&) > build;
	tiercontainer<T> tcontainer(tiers, firstchild);
	for (size_t i = 0; i < skillnumber; ++i) {
		for (size_t cycle = 0; cycle < tiers; ++cycle) while (!tcontainer.empty(cycle)) {
			T d = tcontainer.extract_front();
			build = std::bind(_build, d);
			for (size_t j = 0; lvlprogression(i, j) >= 0; ++j) {
				size_t nextstep = d.build(i, d.lvlprogression(i, j));
				if (nextstep < tiers) {
					tcontainer.instert(nextstep, d);
				}
				else break;
			}
		}
		tcontainer.swap();
	}
	return tcontainer; //? copy constructor/ copy elision
}
