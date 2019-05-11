#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>
#include<fstream>
#include"Optimizer.hpp"
#include "TT2Calc3.0.h"

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
	SkillPowers.push_back(Zero()+MidasGold(1));
	SkillPowers.push_back(Zero()+HSDMG(1));
	SkillPowers.push_back(Zero()+PhantomVengeance());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+LightningStrike());
	SkillPowers.push_back(Zero()+DimensionalShift());

	SkillPowers.push_back(Zero()+MasterThief());
	SkillPowers.push_back(Zero()+DSDamage(1));
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+TwilightVeil());
	SkillPowers.push_back(Zero()+GhostShip());
	SkillPowers.push_back(Zero()+ShadowAssassin());
	std::cout << SkillPowers.size()<< "skills\n";

	Preprocessor::preprocess(0, 0, SkillPowers);
	std::vector<SkillContainer>starting_container = Preprocessor::getSkillContainer();

	Build bad_build(starting_container);
	Build good_build(starting_container); 

	long double dmg;

	std::vector<std::size_t> build1{ 2, 1, 0, 15, 18 ,0 ,0 ,5 ,0 ,2 ,1 ,7 ,1 ,14 ,20 ,2 ,6 ,14 ,2 ,4 ,0 ,18 ,0 ,0 ,1 ,0 ,0 ,12 ,12 ,8 ,0 ,0 ,0 ,0 ,0 };
	for (std::size_t i = 0; i < build1.size(); ++i) bad_build.d[i].level = build1[i];
	bad_build.last_leveled_skill = build1.size() - 1;
	for (std::size_t i = 0; i < build1.size(); ++i) {
		if (bad_build.unlocked(i)) {
			std::cout << tt2::skills[i].Name << " is unlocked";
		}
		else std::cout << tt2::skills[i].Name << " is locked";
		std::cout << " & gettingto=" << bad_build.gettingTo(i) << "\n";
	}

	std::vector<std::size_t> build2{ 2,1,0,14,11,0,0,7,0, 3,1,6,1,14,0,1,0,8, 2,0,0,14,0,0,1,0,0,11, 10,6,0,1,0,0,4 };
	for (std::size_t i = 0; i < build2.size(); ++i) good_build.d[i].level = build2[i];
	good_build.last_leveled_skill = build2.size() - 1;

	for (std::size_t i = 0; i < build1.size(); ++i) {
		if (good_build.unlocked(i)) {
			std::cout << tt2::skills[i].Name << " is unlocked";
		}
		else std::cout << tt2::skills[i].Name << " is locked";
		std::cout << " & gettingto=" << good_build.gettingTo(i) << "\n";
	}

	bad_build.last_leveled_skill = build1.size() - 2;
	good_build.last_leveled_skill = build2.size() - 2;
	if (good_build <= bad_build) std::cout << "good_build <= bad_build \n\n\n";
	else if (bad_build <= good_build) std::cout << "good_build >= bad_build \n\n\n";
	else std::cout << "good build <> bad_build \n\n\n";
	bad_build.last_leveled_skill = build1.size() - 1;
	good_build.last_leveled_skill = build2.size() - 1;
	dmg = good_build.getValue();
	std::cout << "good_build.getValue()=" << dmg << "\n\n\n";
	dmg = bad_build.getValue();
	std::cout << "bad_build.getValue()=" << dmg << "\n\n\n";
	std::cout << "good_build.getCost()=" << good_build.getCost() << "\n\n\n";
	std::cout << "bad_build.getCost()=" << bad_build.getCost() << "\n\n\n";

	Build full_build(starting_container);
	std::vector<std::size_t> build3{ 10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10};
	for (std::size_t i = 0; i < build3.size(); ++i) full_build.d[i].level = build3[i];
	full_build.last_leveled_skill = build3.size() - 1;

	for (std::size_t i = 0; i < build1.size(); ++i) {
		std::cout << "maxlvl=" << tt2::skills[i].MaxLevel << "\n";
		if (full_build.unlocked(i)) {
			std::cout << tt2::skills[i].Name << " is unlocked";
		}
		else std::cout << tt2::skills[i].Name << " is locked";
		std::cout << " & gettingto=" << full_build.gettingTo(i) << "\n";
	}

	dmg = full_build.getValue();
	std::cout << "full_build.getValue()=" << dmg <<"\n\n\n";
	std::cin.get();

	for (const auto& i : Skill::branch_range) {
		std::cout << std::get<0>(i) << "," << std::get<1>(i) << "\n\n\n";
	}
	Skill::branch_range[0] = std::make_tuple(0, 9);
	Skill::branch_range[1] = std::make_tuple(9, 18);
	Skill::branch_range[2] = std::make_tuple(18, 28);
	Skill::branch_range[3] = std::make_tuple(28, 36);
	Skill::branch_range[4] = std::make_tuple(0, 0);

	Build first_child(starting_container);

	constexpr std::size_t max_skillpoints = 1500;

	tiercontainer <Build> tier_orderer(max_skillpoints, first_child);
	tier_orderer.order(max_skillpoints, 35);
	std::fstream output_text("output.txt", std::ios::out);

	auto value_less_equal = [](Build const& b1, Build const& b2) {return b1.getValue() <= b2.getValue(); };
	std::vector<Build> ordering=tier_orderer.print(value_less_equal);
	for (const auto& i : ordering)
		i.print(output_text);

}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing