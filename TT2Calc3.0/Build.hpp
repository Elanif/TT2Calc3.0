#pragma once

#include<cstddef>
#include<tuple>
#include<utility>
#include"Globals.hpp"
#include"tt2.hpp"
#include"Skill.hpp"
#include"SkillContainer.hpp"
#include<ostream>

template <typename ValueType>
class DMGType {
public:
	virtual ValueType getDamage(std::size_t const& build, ValueType const& value1, ValueType const& value2, size_t const& gold) = 0;
};

template<typename ValueType, class... DMGTypesDerived>
class Expression {
public:

	std::tuple<std::pair<bool, DMGTypesDerived>... > parameters;

	template<class DerivedClass>
	Expression<ValueType, DMGTypesDerived...>& add(DerivedClass const& dmg) {
		std::get<std::pair<bool, DerivedClass> >(parameters).second = dmg;
		std::get<std::pair<bool, DerivedClass> >(parameters).first = true;//this could be avoided if all base constructed dmg types had 1 dmg, but it' a dangerous proposition
		return *this;
	}

	template<class DerivedClass>
		Expression<ValueType, DMGTypesDerived...>& operator+=(DerivedClass const& dmg) {
		std::get<std::pair<bool, DerivedClass> >(parameters).second = dmg;
		std::get<std::pair<bool, DerivedClass> >(parameters).first = true;//this could be avoided if all base constructed dmg types had 1 dmg, but it' a dangerous proposition
		return *this;
	}

	template<class DerivedClass>
	Expression<ValueType, DMGTypesDerived...> operator+(DerivedClass const& dmg) {
		Expression<ValueType, DMGTypesDerived...> copy = *this;
		std::get<std::pair<bool, DerivedClass> >(copy.parameters).second = dmg;
		std::get<std::pair<bool, DerivedClass> >(copy.parameters).first = true;//this could be avoided if all base constructed dmg types had 1 dmg
		return copy;
	}

	ValueType getDamage(std::size_t const& build, ValueType const& value1, ValueType const& value2, size_t const& gold) {

		return
			(
				(
					std::get<std::pair<bool, DMGTypesDerived> >(parameters).first ? std::get<std::pair<bool, DMGTypesDerived> >(parameters).second.getDamage(build, value1, value2, gold) : 1
				) * ...
			);
	}
};


class Build {
public:
	Build(std::vector<SkillContainer> _d)
		:d(_d)
	{}

	vtype getValue() const; //could just multiply pure_vtype by the new value;

	ctype getCost() const;

	bool levelUp(std::size_t skill_to_levelup, std::size_t skill_level);

	bool unlocked(std::size_t const& skill_index) const;
	ctype gettingTo(std::size_t const& skill_index) const;

	std::size_t last_leveled_skill = 0;
	bool raw = true;

	std::vector<SkillContainer> d;//d cause thats how I called it in my old optimizer

	void print(std::ostream& out_stream) const;

	bool operator <=(Build const&) const;
	bool operator ==(Build const&) const;
	static bool lessequal(Build const&, Build const&);
	static bool value_lessequal(Build const&, Build const&);/*
	static bool costLessequal(Build const&, Build const&);*/

	vtype pure_vtype = 1;

};
