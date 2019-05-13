#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>
#include<fstream>
#include"Optimizer.hpp"
#include "TT2Calc3.0.h"
#include<thread>

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
	SkillPowers.push_back(Zero());
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

	constexpr tt2::BUILDS build = tt2::HS;
	constexpr tt2::GOLDTYPES gold=tt2::PHOMGOLD;

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

	constexpr std::size_t max_skillpoints = 1500;

	tiercontainer <Build> tier_orderer(max_skillpoints, first_child);
	std::size_t thread_number = std::thread::hardware_concurrency() / 2 > 0 ? std::thread::hardware_concurrency() / 2:1;
	tier_orderer.order(max_skillpoints, tt2::skills.size(),min_max_level, thread_number);

	std::cout << output_name;
	if (output_name.length() == 0) return 1;
	std::fstream output_text(output_name, std::ios::out);

	std::vector<Build> ordering=tier_orderer.print(Build::value_lessequal);
	for (const auto& i : ordering)
		i.print(output_text);
	output_text.close();
}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing