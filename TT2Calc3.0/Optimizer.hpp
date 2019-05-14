#pragma once
#include<cstddef>
#include<list>
#include<iterator>
#include<functional>
#include<vector>
#include"Globals.hpp"
#include<mutex>
#include<thread>
template<class T>
class tiercontainer {
public:
	void order(std::size_t const& tiers, std::size_t const& skillnumber);
	void order(const std::size_t& tiers, std::size_t const& skillnumber, std::vector<std::tuple<std::size_t, std::size_t > > const& min_max_level, std::size_t const& thread_number=1);
	void eatCycle(const std::size_t& tiers, std::size_t const& skillnumber, std::vector<std::tuple<std::size_t, std::size_t > > const& min_max_level,
		std::size_t const& skill_it, bool const& add_instead_of_insert, std::size_t const& start = 0, std::size_t const& step = 1);

	tiercontainer(std::size_t const& _tiers);
	tiercontainer(std::size_t const& _tiers, T const& root);
	tiercontainer(const tiercontainer<T>& cpy);
	tiercontainer<T>& operator=(const tiercontainer<T>& cpy);
	void swap(std::size_t const& tiers);
	void add(std::size_t const& _tier, const T& pushedobj); //copies pushedobj
	bool insert(std::size_t const& _tier, const T& candidate); //copies candidate if found eligible and may delete items that are worse than candidate
	T extract_front(std::size_t const& _tier);
	bool empty(std::size_t const& _tier) const;
	std::vector<T> print(bool _lessequal(const T& a, const T& b)) const;
	~tiercontainer();
	std::list<T>* tierlist;
	std::list<T>* _temptierlist;
private:
	std::vector<std::mutex> tier_mutex;
	std::size_t tiers;
	T root;
};

//CONSTRUCTORS
template<class T>
tiercontainer<T>::tiercontainer(const std::size_t& _tiers, T const& _root)
	:tiers(_tiers), root(_root)
{
	tierlist = new std::list<T>[tiers + 1];
	_temptierlist = new std::list<T>[tiers + 1];
	tierlist[0].push_back(root);
}

template<class T>
tiercontainer<T>::tiercontainer(const std::size_t& _tiers)
	:tiercontainer(_tiers, T())
{
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
tiercontainer<T>::~tiercontainer() {
	if (tierlist)	delete[] tierlist;
	if (_temptierlist)	delete[] _temptierlist;
};
//END CONSTRUCTORS

template<class T>
void tiercontainer<T>::order(const std::size_t& tiers, std::size_t const& skillnumber)
{
	std::vector<std::tuple<std::size_t, std::size_t > > default_min_max(25, { 0,25 });
	order(tiers, skillnumber, default_min_max);
}

template<class T>
void tiercontainer<T>::eatCycle(const std::size_t& tiers, std::size_t const& skillnumber, std::vector<std::tuple<std::size_t, std::size_t > > const& min_max_level, 
	std::size_t const& skill_it, bool const& add_instead_of_insert, std::size_t const& start, std::size_t const& step) {
	for (size_t cycle = start; cycle < tiers; cycle+=step) while (!empty(cycle)) {
		T cycle_root = extract_front(cycle);
		T modified_root = cycle_root;
		if (std::get<0>(min_max_level[skill_it]) <= 0)
		{
			modified_root.levelUp(skill_it, 0);

			if (add_instead_of_insert) add(modified_root.getCost(), modified_root);
			else insert(modified_root.getCost(), modified_root);
		}
		if (cycle_root.unlocked(skill_it)) for (std::size_t skill_level_it = std::get<0>(min_max_level[skill_it]); skill_level_it <= std::get<1>(min_max_level[skill_it]); ++skill_level_it) {

			modified_root = cycle_root;

			if (!modified_root.levelUp(skill_it, skill_level_it)) break;
			std::size_t tier_cost = modified_root.getCost(); // always call this after levelUp

			if (tier_cost > tiers) break;
			if (add_instead_of_insert) add(modified_root.getCost(), modified_root);
			else insert(modified_root.getCost(), modified_root);
		}
	}
}
template<class T>
void tiercontainer<T>::order(const std::size_t & tiers, std::size_t const& skillnumber, std::vector<std::tuple<std::size_t, std::size_t > > const& min_max_level, std::size_t const& thread_number)
{
	if (tierlist) delete[] tierlist;
	if (_temptierlist) delete[] _temptierlist;
	tier_mutex.clear();
	std::vector<std::mutex> temp_tier_mutex(tiers + 1);
	tier_mutex.swap(temp_tier_mutex);
	tierlist = new std::list<T>[tiers + 1];
	_temptierlist = new std::list<T>[tiers + 1];
	tierlist[0].push_front(root);

	for (std::size_t skill_it = 0; skill_it < skillnumber - 1; ++skill_it) { // do it for skillnumber-1 and in the last iteration use value_lessequal since unlocking doesnt matter
		std::cout << "Skill number " << skill_it << "\n";
		std::vector<std::thread> thread_vector;
		for (std::size_t thread_it = 1; thread_it < thread_number; ++thread_it) {
			thread_vector.push_back(std::thread(&tiercontainer<T>::eatCycle, this, tiers, skillnumber, min_max_level, skill_it, false, thread_it, thread_number));
		}
		eatCycle(tiers, skillnumber, min_max_level, skill_it, false, 0, thread_number);
		for (auto& thread_it : thread_vector)
			if (thread_it.joinable()) thread_it.join();
		swap(tiers);
	}
	{
		std::size_t last_skill = skillnumber - 1;
		std::cout << "Skill number " << last_skill << "\n";
		std::vector<std::thread> thread_vector;
		for (std::size_t thread_it = 1; thread_it < thread_number; ++thread_it) {
			thread_vector.push_back(std::thread(&tiercontainer<T>::eatCycle, this, tiers, skillnumber, min_max_level, last_skill, true, thread_it, thread_number));
		}
		eatCycle(tiers, skillnumber, min_max_level, last_skill, true, 0, thread_number);
		for (auto& thread_it : thread_vector)
			if (thread_it.joinable()) thread_it.join();
		swap(tiers);
	}
}

template<class T>
void tiercontainer<T>::add(const std::size_t & _tier, const T & pushedobj) {
	std::unique_lock<std::mutex> add_mutex(tier_mutex[_tier]);
	_temptierlist[_tier].push_back(pushedobj);
}

template<class T>
void tiercontainer<T>::swap(std::size_t const& _tiers) {
	delete[] tierlist;
	tierlist = _temptierlist;
	_temptierlist = new std::list<T>[_tiers + 1];
}


template<class T>
T tiercontainer<T>::extract_front(const std::size_t & _tier) {
	std::unique_lock<std::mutex> pop_mutex(tier_mutex[_tier]);
	T _temp = tierlist[_tier].front();
	tierlist[_tier].pop_front();
	pop_mutex.unlock();
	return _temp;
}

template<class T>
bool tiercontainer<T>::insert(const std::size_t & _tier, const T & candidate) {
	std::unique_lock<std::mutex> insert_mutex(tier_mutex[_tier]);
	for (typename std::list<T>::iterator it = _temptierlist[_tier].begin(); it != _temptierlist[_tier].end(); ) {
		if ((*it) <= candidate) {
			_temptierlist[_tier].erase(it++);
		}
		else {
			if (candidate <= (*it)) {
				return false;
			}
			else ++it;
		}
	}
	_temptierlist[_tier].push_back(candidate);
	return true;
}

template<class T>
bool tiercontainer<T>::empty(const std::size_t & _tier) const{
	return tierlist[_tier].empty();
}

template<class T>
std::vector<T> tiercontainer<T>::print(bool _lessequal(const T & a, const T & b)) const{
	std::vector<T> maxdamage(tiers, root);
	for (int k = 1; k < tiers; ++k) {
		if (tierlist[k].size() > 0) {
			typename std::list<T>::iterator max = tierlist[k].begin();
			for (typename std::list<T>::iterator it = tierlist[k].begin(); it != tierlist[k].end(); ++it)
				if (_lessequal(*max, *it)) max = it;
			maxdamage[k] = (*max);
		}
	}
	return maxdamage;
}