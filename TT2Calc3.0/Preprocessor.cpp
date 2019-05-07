#include "Preprocessor.hpp"
#include"BuildImplementations.hpp"

Preprocessor::Preprocessor(std::size_t const& build, std::size_t const& gold)
{
	const std::vector<Skill>& skills=tt2::skills;
	skillMaxLevel.resize(skills.size());
	skillCost.resize(skills.size());
	skillEffect.resize(skills.size());
	for (std::size_t skill_iter = 0; skill_iter < skills.size(); ++skill_iter) {
		//maxlvl

		skillMaxLevel[skill_iter] = skills[skill_iter].MaxLevel;

		//skillcost

		skillCost[skill_iter].resize(skillMaxLevel[skill_iter]+1ull);

		skillCost[skill_iter][0] = 0;
		for (std::size_t cost_iter = 1; cost_iter < skillCost[skill_iter].size(); ++cost_iter) {
			skillCost[skill_iter][cost_iter] = skillCost[skill_iter][cost_iter - 1] + skills[skill_iter].cost[cost_iter - 1];
		}
		
		skillEffect[skill_iter].resize(skillMaxLevel[skill_iter] + 1ull);
		for (std::size_t level = 0; level < skillCost[skill_iter].size(); ++level) {
			auto exp = Zero() + PhantomVengeance(1); 
			skillEffect[skill_iter][level] = exp.getDamage(build, skills[skill_iter].BonusTypeA[level], skills[skill_iter].BonusTypeB[level], gold);
			//if (skills[skill_iter].Name == std::string("Phantom Vengeance")) std::cout << level<<":"<<pow(skillEffect[skill_iter][level],1./ skillCost[skill_iter][level]) << "\n";// value1 = "<< skills[skill_iter].BonusTypeA[level]<<" value2 = "<< skills[skill_iter].BonusTypeB[level] <<"\n";
		}
		//std::cout << "\n";
		std::cout << skills[skill_iter].BonusTypeAString;//
		
		//<< " " << skills[skill_iter].BonusTypeBString << "\n";
	}
}
