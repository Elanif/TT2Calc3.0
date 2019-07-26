#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>
#include<fstream>
#include"Optimizer.hpp"
#include "TT2Calc3.0.h"
#include<thread>
#include<sstream>
#include<algorithm>

int main()
{
	tt2::init();
	
	std::string skilltree_csv = "SkillTreeInfo2.0.csv";
	if (tt2::loadSkillTreeCSV(skilltree_csv)) {
		std::cout << skilltree_csv << " loaded successfully\n";
	}
	else {
		std::cout << skilltree_csv << " couldn't be loaded\n";
		return 1;
	}
	std::vector<Zero> SkillPowers;// (tt2::skills.size());
	
	SkillPowers.push_back(Zero()+TapDMG(1));
	SkillPowers.push_back(Zero()+TapDmgFromHelpers());
	SkillPowers.push_back(Zero()+PetDMG(1));
	SkillPowers.push_back(Zero()+pHoMGold(1)+PHoMCooldown());
	SkillPowers.push_back(Zero()+MaxCritDamageAndCritChance());
	SkillPowers.push_back(Zero()+FireSwordDamage(1));
	SkillPowers.push_back(Zero()+PetDMG(1));
	SkillPowers.push_back(Zero()+TapDMG(1));
	SkillPowers.push_back(Zero()+PetDMG(1));

	SkillPowers.push_back(Zero()+AllHeroDMG(1));
	SkillPowers.push_back(Zero()+ChestersonGoldAndChance());
	SkillPowers.push_back(Zero()+WarCryDamage(1));
	SkillPowers.push_back(Zero()+ClanShipDamage(1));
	SkillPowers.push_back(Zero()+TIMultiplicative());
	SkillPowers.push_back(Zero()+SearingLight());
	SkillPowers.push_back(Zero()+AllHeroDMG(1));
	SkillPowers.push_back(Zero()+AllHeroDMG(5)); //debatable
	SkillPowers.push_back(Zero()+AnchoringShot());

	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+MidasGold(1)+FairyGoldSecond(1));
	SkillPowers.push_back(Zero()+HSDMG(1));
	SkillPowers.push_back(Zero()+PhantomVengeance());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+LightningStrike());
	SkillPowers.push_back(Zero()+HSDMG(1)+DSDamage(1)+MidasGold(1)+FireSwordDamage(1)+WarCryDamage(1)+SCDMG(1));

	SkillPowers.push_back(Zero()+MasterThief());
	SkillPowers.push_back(Zero()+DSDamage(1));
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+TwilightVeil());
	SkillPowers.push_back(Zero()+GhostShip());
	SkillPowers.push_back(Zero()+ShadowAssassin());

	constexpr tt2::BUILDS build = tt2::Pet;
	constexpr tt2::GOLDTYPES gold=tt2::FAIRYGOLD;

	std::string output_name = Preprocessor::getStringBuildAndInit(build, gold);

	std::vector<std::tuple<std::size_t, std::size_t > >min_max_level=Preprocessor::init(build, gold);

	Preprocessor::preprocess(build, gold, SkillPowers);
	std::vector<SkillContainer>starting_container = Preprocessor::getSkillContainer();

	Skill::branch_range[0] = std::make_tuple(0, 9);
	Skill::branch_range[1] = std::make_tuple(9, 18);
	Skill::branch_range[2] = std::make_tuple(18, 28);
	Skill::branch_range[3] = std::make_tuple(28, 36);
	Skill::branch_range[4] = std::make_tuple(0, 0);

	Build first_child(starting_container);

	std::cout << "Enter the max number of skillpoints, -1 for single skill leveling";
	long long int mode = 0;
	std::cin >> mode;
	if (mode < 0) {
		std::stringstream temp_stream("15 1 15 1 14 16 16 12 12		2 14 1 1 14 1 1 0 13		2 13 1 1 0 1 1 0 9 8		11 12 0 1 6 0 1");
		for (std::size_t i = 0; i < min_max_level.size(); ++i)
			temp_stream >> first_child.d[i].level;
		std::vector<std::pair<vtype, std::string> > best_levelups;
		for (std::size_t i = 0; i < min_max_level.size(); ++i) {
			const Skill& skill = first_child.d[i].skill.get();
			if (std::get<1>(min_max_level[i]) <= first_child.d[i].level) best_levelups.push_back(std::make_pair(0, skill.Name));
			else {
				if (first_child.d[i].level < skill.cost.size()) { //not max level
					auto cost = skill.cost[first_child.d[i].level];
					auto damage = first_child.d[i].getCurrentEffect();
					first_child.d[i].level++;
					damage = (first_child.d[i].getCurrentEffect() / damage);
					if (damage == 0) damage = 1;
					auto efficiency = pow(damage, 1. / cost);
					best_levelups.push_back(std::make_pair(efficiency, skill.Name));
				}
				else { //skill is already max level
					best_levelups.push_back(std::make_pair(1., skill.Name));
				}
			}
		}
		sort(best_levelups.begin(), best_levelups.end());
		for (const auto& i:best_levelups)	std::cout << i.first << "," << i.second << "\n";

	}
	else {
		std::size_t max_skillpoints = mode;

		tiercontainer <Build> tier_orderer(max_skillpoints, first_child);
		std::size_t thread_number = std::thread::hardware_concurrency() / 2 > 0 ? std::thread::hardware_concurrency() / 2 : 1;
		tier_orderer.order(max_skillpoints, tt2::skills.size(), min_max_level, thread_number);

		if (output_name.length() == 0) return 1;
		std::fstream output_text(output_name, std::ios::out);

		std::vector<Build> ordering = tier_orderer.print(Build::value_lessequal);
		for (const auto& i : ordering)
			i.print(output_text);
		output_text.close();
	}
}
