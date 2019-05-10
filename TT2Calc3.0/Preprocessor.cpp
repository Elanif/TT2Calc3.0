#include "Preprocessor.hpp"
#include"BuildImplementations.hpp"

void Preprocessor::preprocess(std::size_t const& build, std::size_t const& gold, std::vector<Zero>& SkillPowers)
{
	for (std::size_t skill_iter = 0; skill_iter < tt2::skills.size(); ++skill_iter) {
		Skill& skill_it = tt2::skills[skill_iter];
		std::cout << skill_it.Name << "\n";

		skill_it.skillCosts.resize(skill_it.MaxLevel+1ull);

		skill_it.skillCosts[0] = 0;
		for (std::size_t cost_iter = 1; cost_iter < skill_it.skillCosts.size(); ++cost_iter) {
			skill_it.skillCosts[cost_iter] = skill_it.skillCosts[cost_iter - 1] + skill_it.cost[cost_iter - 1];
		}
		
		skill_it.skillEffects.resize(skill_it.MaxLevel + 1ull);
		skill_it.skillEffects[0] = 1;
		for (std::size_t level = 1; level < skill_it.skillEffects.size(); ++level) {
			skill_it.skillEffects[level] = SkillPowers[skill_iter].getDamage(skill_iter, skill_it.BonusTypeA[level], skill_it.BonusTypeB[level], gold);
		}
	}
}

std::vector<SkillContainer> Preprocessor::getSkillContainer() {
	std::vector<SkillContainer> result;
	std::size_t skillNumber = tt2::skills.size();

	std::vector<const Skill*> GettingToArray;
	std::vector<std::size_t> last_slots;

	for (std::size_t i = 0; i < skillNumber; ++i) {
		result.push_back(SkillContainer(tt2::skills[i], tt2::skills[i].MaxLevel));
	}
	return result;
}
