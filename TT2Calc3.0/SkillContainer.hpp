#pragma once
#include"Skill.hpp"
#include"tt2.hpp"
#include<vector>
#include<functional>

template<typename ValueType, typename CostType, class SkillType>
class SkillContainerBase
{
public:
	std::size_t level = 0;
	std::size_t maxLevel;
	std::reference_wrapper<SkillType const> skill;
	SkillContainerBase(SkillType const& _skill, std::size_t const& _maxLevel) :skill(_skill), maxLevel(_maxLevel) {}
	virtual ValueType getCurrentEffect() const = 0;
	virtual CostType getCurrentCost() const = 0;
	virtual std::size_t getMaxLevel() = 0;
	//virtual bool unlocked(std::vector<SkillContainerBase> const&) = 0;
	//virtual CostType gettingTo(std::vector<SkillContainerBase> const&) = 0;
};

class SkillContainer : public SkillContainerBase<vtype,ctype, Skill> {
public:
	SkillContainer(Skill const& _skill, std::size_t const& _maxLevel);
	//SkillContainer() = delete;

	bool unlocked(std::vector<SkillContainer> const&) const;
	ctype gettingTo(std::vector<SkillContainer> const&) const;
	vtype getCurrentEffect() const;
	ctype getCurrentCost() const;
	std::size_t getMaxLevel();
};

