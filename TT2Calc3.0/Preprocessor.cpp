#include "Preprocessor.hpp"

Preprocessor::Preprocessor(std::size_t const& build)
{
	const std::vector<Skill>& skills=Constants::skills;
	skillMaxLevel.resize(skills.size());
	skillCost.resize(skills.size());
	skillEffect.resize(skills.size());
	for (std::size_t skill_iter = 0; skill_iter < skills.size(); ++skill_iter) {
		//maxlvl

		skillMaxLevel[skill_iter] = skills[skill_iter].MaxLevel;

		//skillcost

		skillCost[skill_iter].resize(skillMaxLevel[skill_iter]+1u);

		skillCost[skill_iter][0] = 0;
		for (std::size_t cost_iter = 1; cost_iter < skillCost[skill_iter].size(); ++cost_iter) {
			skillCost[skill_iter][cost_iter] = skillCost[skill_iter][cost_iter - 1] + skills[skill_iter].cost[cost_iter - 1];
			std::cout << skillCost[skill_iter][cost_iter] << " ";
		}
		std::cout << "\n";
	}
}
