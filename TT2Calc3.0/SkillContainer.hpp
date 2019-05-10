#pragma once
#include"Skill.hpp"
#include"tt2.hpp"
#include<vector>

template<typename ValueType, typename CostType, class SkillType>
class SkillContainerBase
{
public:
	std::size_t level = 0;
	const std::size_t maxLevel;
	const SkillType& skill;
	SkillContainerBase(SkillType const&, std::size_t const& _maxLevel);
	virtual ValueType getEffect(std::size_t const& level) = 0;
	virtual CostType getCost(std::size_t const& level) const = 0;
	virtual ValueType getCurrentEffect() = 0;
	virtual CostType getCurrentCost() const = 0;
	virtual std::size_t getMaxLevel() = 0;
	//virtual bool unlocked(std::vector<SkillContainerBase> const&) = 0;
	//virtual CostType gettingTo(std::vector<SkillContainerBase> const&) = 0;
};

class SkillContainer : public SkillContainerBase<vtype,ctype, Skill> {
public:
	bool unlocked(std::vector<SkillContainer> const&) const;
	ctype gettingTo(std::vector<SkillContainer> const&) const;
	SkillContainer(Skill const& _skill, std::size_t const& _maxLevel, std::vector<ctype> _skillCosts, std::vector<vtype> _skillEffects);
	vtype getEffect(std::size_t const& level);
	ctype getCost(std::size_t const& level) const;
	vtype getCurrentEffect();
	ctype getCurrentCost() const;
	std::size_t getMaxLevel();
private:
	std::vector<ctype> skillCosts;
	std::vector<vtype> skillEffects;
};

