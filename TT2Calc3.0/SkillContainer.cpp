#include "SkillContainer.hpp"
#include"Globals.hpp"

SkillContainer::SkillContainer(Skill const& _skill, std::size_t const& _maxLevel)
	: SkillContainerBase<vtype, ctype, Skill>(_skill, _maxLevel)
{
}

bool SkillContainer::unlocked(std::vector<SkillContainer> const& _skillcont) const{
	if (skill.TalentReq == nullptr) return true; //root of skilltree
	else {
		const std::size_t indexreq = skill.TalentReq->index;
		//if (!_skillcont[indexreq].unlocked(_skillcont)) return false;
		if (_skillcont[indexreq].level <= 0) return false;
		if (gettingTo(_skillcont) < skill.SPReq) return false;
	}
	return true;
}
ctype SkillContainer::gettingTo(std::vector<SkillContainer> const& _skillcont) const { //called from skill to end of branch 
	//get current branch, work on all the previous skills but not the ones on the same level
	ctype result = 0;
	for (const auto& i : skill.GettingToArray)
		result += _skillcont[i->index].getCurrentCost();
	return result;
}

std::size_t SkillContainer::getMaxLevel() {
	return maxLevel;
}

vtype SkillContainer::getCurrentEffect() const{
	if (ArrayGuards) {
		if (level > maxLevel) throw "oob";
	}
	return skill.skillEffects[level];
}

ctype SkillContainer::getCurrentCost() const {
	if (ArrayGuards) {
		if (level > maxLevel) throw "oob";
	}
	return skill.skillCosts[level];
}