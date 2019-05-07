#pragma once

#include<cstddef>
#include<tuple>
#include<utility>

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
		std::get<std::pair<bool, DerivedClass> >(parameters).first = true;//this could be avoided if all base constructed dmg types had 1 dmg
		return *this;
	}

	template<class DerivedClass>
		Expression<ValueType, DMGTypesDerived...>& operator+=(DerivedClass const& dmg) {
		std::get<std::pair<bool, DerivedClass> >(parameters).second = dmg;
		std::get<std::pair<bool, DerivedClass> >(parameters).first = true;//this could be avoided if all base constructed dmg types had 1 dmg
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

template <typename ValueType, typename CostType, typename SkillType, std::size_t skillnumber, std::size_t buildnumber, std::size_t max_level_skill, std::size_t skill_value_number>
class Build {
public:

	virtual ValueType getValue() = 0;
	virtual CostType getCost() = 0;
	virtual bool operator <=(Build const&) = 0;
	virtual bool operator ==(Build const&) = 0;
	static bool lessequal(Build const&, Build const&);
	static bool valueLessequal(Build const&, Build const&);
	static bool costLessequal(Build const&, Build const&);

	virtual bool unlocked(SkillType const& skill) = 0;
	static ValueType skillpower[skillnumber][buildnumber];
	static ValueType skillvalues[skillnumber][1 + skill_value_number][max_level_skill]; //1+skill_value_number because it's SP requirement + values

protected:
	virtual CostType gettingTo(SkillType const& skill) = 0;


};