#include "Preprocessor.hpp"
#include"BuildImplementations.hpp"

std::string Preprocessor::getStringBuildAndInit(tt2::BUILDS build, tt2::GOLDTYPES gold)
{
	std::string output_name = "";
	switch (build) {
	case tt2::SC:
		tt2::fight_duration = 4;
		output_name += "SC ";
		break;
	case tt2::HS:
		output_name += "HS ";
		tt2::fight_duration = 34./12.*4.;
		break;
	case tt2::Pet:
		output_name += "Pet ";
		tt2::fight_duration = 4;
		break;
	case tt2::CS:
		output_name += "CS ";
		tt2::fight_duration = 4;
		break;
	}

	switch (gold) {
	case tt2::PHOMGOLD:
		output_name += "pHoM";
		break;
	case tt2::FAIRYGOLD:
		output_name += "Fairy";
		break;
	}

	output_name += ".txt";
	return output_name;
}

std::vector<std::tuple<std::size_t, std::size_t > > Preprocessor::init(tt2::BUILDS build, tt2::GOLDTYPES gold)
{
	std::vector<std::tuple<std::size_t, std::size_t > >min_max_level(35, std::make_tuple(0, 26));
	switch (build) {
	case tt2::SC:
		tt2::fight_duration = 4;
		min_max_level[16]={ 0,0 };
		min_max_level[24]={ 13,25 };
		min_max_level[27]={ 1,25 };
		min_max_level[31] = { 1,25 };
		min_max_level[34] = { 1,25 };
		break;
	case tt2::HS:
		tt2::fight_duration = 34. / 12. * 4.;
		min_max_level[16] = { 0,0 };
		min_max_level[20] = { 24,25 };
		min_max_level[31] = { 1,25 };
		min_max_level[34] = { 1,25 };
		min_max_level[27] = { 1,25 };
		break;
	case tt2::Pet:
		min_max_level[6] = { 0,1 };
		min_max_level[32] = { 1,25 };
		min_max_level[29] = { 1,25 };
		tt2::fight_duration = 4;
		break;
	case tt2::CS:
		tt2::fight_duration = 4;
		break;
	}

	switch (gold) {
	case tt2::PHOMGOLD:
		min_max_level[3] = { 1,25 };
		break;
	case tt2::FAIRYGOLD:
		break;
	}
	return min_max_level;
}

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
			skill_it.skillEffects[level] = SkillPowers[skill_iter].getDamage(build, skill_it.BonusTypeA[level], skill_it.BonusTypeB[level], gold);
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
