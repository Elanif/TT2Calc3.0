#pragma once

#include<cstddef>
#include<tuple>
#include<utility>
#include"Globals.hpp"
#include"tt2.hpp"
#include"Skill.hpp"
#include"SkillContainer.hpp"

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

template <typename ValueType, typename CostType, typename SkillType>
class BuildBase {
public:

	virtual ValueType getValue() = 0;
	virtual CostType getCost() = 0;
	virtual bool operator <=(BuildBase const&) = 0;
	virtual bool operator ==(BuildBase const&) = 0;
	static bool lessequal(BuildBase const&, BuildBase const&);
	static bool valueLessequal(BuildBase const&, BuildBase const&);
	static bool costLessequal(BuildBase const&, BuildBase const&);

	virtual bool unlocked(SkillType const& skill) = 0;

protected:
	virtual CostType gettingTo(SkillType const& skill) = 0;
};

class Build : public BuildBase<vtype, ctype, SkillContainer> {
protected:
	vtype pure_vtype = 1;
public:
	vtype getValue(); //could just multiply pure_vtype by the new value;


};
