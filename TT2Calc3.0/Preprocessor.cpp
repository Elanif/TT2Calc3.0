#include "Preprocessor.hpp"
#include"BuildImplementations.hpp"

Preprocessor::Preprocessor(std::size_t const& build, std::size_t const& gold, std::vector<Zero>& SkillPowers)
{
	const std::vector<Skill>& skills=tt2::skills;
	skillMaxLevel.resize(skills.size());
	skillCost.resize(skills.size());
	skillEffect.resize(skills.size());
	for (std::size_t skill_iter = 0; skill_iter < skills.size(); ++skill_iter) {
		//maxlvl
		std::cout << skills[skill_iter].Name << "\n";
		skillMaxLevel[skill_iter] = skills[skill_iter].MaxLevel;

		//skillcost

		skillCost[skill_iter].resize(skillMaxLevel[skill_iter]+1ull);

		skillCost[skill_iter][0] = 0;
		for (std::size_t cost_iter = 1; cost_iter < skillCost[skill_iter].size(); ++cost_iter) {
			skillCost[skill_iter][cost_iter] = skillCost[skill_iter][cost_iter - 1] + skills[skill_iter].cost[cost_iter - 1];
		}
		
		skillEffect[skill_iter].resize(skillMaxLevel[skill_iter] + 1ull);
		skillEffect[skill_iter][0] = 1;
		for (std::size_t level = 1; level < skillCost[skill_iter].size(); ++level) {
			skillEffect[skill_iter][level] = SkillPowers[skill_iter].getDamage(skill_iter, skills[skill_iter].BonusTypeA[level], skills[skill_iter].BonusTypeB[level], gold);
		}
	}
}
