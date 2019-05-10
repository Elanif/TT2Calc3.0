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

std::vector<SkillContainer> Preprocessor::getSkillContainer()
{
	std::vector<SkillContainer> result;
	std::size_t skillNumber = skillMaxLevel.size();

	std::vector<const Skill*> GettingToArray;
	std::vector<std::size_t> last_slots;

	for (std::size_t i = 0; i < skillNumber; ++i) {
		if (last_slots.size() == 0) { //first iteration
			last_slots.push_back(tt2::skills[i].Slot);
			GettingToArray.push_back(&tt2::skills[i]);
		}
		else if (tt2::skills[i].Slot <= last_slots[last_slots.size() - 1]) { //end of branch
			GettingToArray.clear();
			last_slots.clear();
		}
		else { //continuing through branch
			last_slots.push_back(tt2::skills[i].Slot);
			GettingToArray.push_back(&tt2::skills[i]);
		}

		result.push_back(SkillContainer(tt2::skills[i], skillMaxLevel[i], skillCost[i], skillEffect[i]));

		std::size_t max_slot = 0;

		switch (tt2::skills[i].Slot) {
		case 0:
			break;
		case 1:case 2:case 3:
			max_slot = 1;
			break;
		case 4:case 5:case 6:
			max_slot = 4;
			break;
		case 7:case 8:case 9:
			max_slot = 7;
			break;
		default:
			max_slot = 0;
			break;
		}
		for (std::size_t slot_it = 0; slot_it < last_slots.size(); ++slot_it) {
			if (last_slots[slot_it] < max_slot)
				tt2::skills[i].addGettingTo(GettingToArray[slot_it]);
		}
	}
	return result;
}
