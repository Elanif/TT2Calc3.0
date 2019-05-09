#include "SkillContainer.hpp"
#include"Globals.hpp"

template<typename ValueType, typename CostType, class SkillType>
SkillContainerBase<ValueType, CostType, SkillType>::SkillContainerBase(SkillType const& _skill, std::size_t const& _maxLevel)
:skill(_skill), maxLevel(_maxLevel)
{
}

bool SkillContainer::unlocked(std::vector<SkillContainer> const& _skillcont) const{
	if (skill.TalentReq == nullptr) return true; //root of skilltree
	else {
		const std::size_t indexreq = skill.TalentReq->index;
		if (!_skillcont[indexreq].unlocked(_skillcont)) return false;
		if (_skillcont[indexreq].level <= 0) return false;
		if (gettingTo(_skillcont) < skill.SPReq) return false;
	}
	return true;
}
ctype SkillContainer::gettingTo(std::vector<SkillContainer> const& _skillcont) const { //called from skill to end of branch 
	//get current branch, work on all the previous skills but not the ones on the same level
	switch (skill.Branch) {

	};

	/*switch (skill.Slot) {
	case 0:
		return 0;
		break;
	case 1: case 2: case 3:

		return _skillcont[branch 0].cost
		break;
	case 4: case 5: case 6:
		break;
		return for sum from 0 to 3

	case 7: case 8: case 9:
		return for sum from 0 to 6
		break;
		create a list of pointers in skill.hpp/preprocessor
	}*/
	return 0;
}

SkillContainer::SkillContainer(Skill const& _skill, std::size_t const& _maxLevel, std::vector<ctype> _skillCosts, std::vector<vtype> _skillEffects)
	:SkillContainerBase<vtype, ctype, Skill>(_skill, _maxLevel)
{
	skillCosts = _skillCosts;
	skillEffects = _skillEffects;
}

ctype SkillContainer::getCost(std::size_t const& level) {
	if (ArrayGuards) {
		if (level > maxLevel) throw "oob";
	}
	return skillCosts[level];
}

vtype SkillContainer::getEffect(std::size_t const& level) {
	if (ArrayGuards) {
		if (level > maxLevel) throw "oob";
	}
	return skillEffects[level];
}

std::size_t SkillContainer::getMaxLevel() {
	return maxLevel;
}