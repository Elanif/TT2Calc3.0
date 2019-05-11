#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>
#include"Optimizer.hpp"

int main()
{
	tt2::initExpos();
	
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
	SkillPowers.push_back(Zero()+DimensionalShift(1));

	SkillPowers.push_back(Zero()+MasterThief());
	SkillPowers.push_back(Zero()+DSDamage(1));
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero());
	SkillPowers.push_back(Zero()+TwilightVeil(1));
	SkillPowers.push_back(Zero()+GhostShip(1));
	SkillPowers.push_back(Zero()+ShadowAssassin(1));
	std::cout << SkillPowers.size()<< "skills\n";

	Preprocessor::preprocess(0, 1, SkillPowers);
	std::vector<SkillContainer>starting_container = Preprocessor::getSkillContainer();

	Build test_unlock(starting_container);
	test_unlock.d[0].level =2 ;
	test_unlock.d[1].level = 1;
	test_unlock.d[2].level = 0;
	test_unlock.d[3].level = 9;
	test_unlock.d[4].level = 8;
	test_unlock.d[5].level = 0;
	test_unlock.d[6].level = 0;
	test_unlock.d[7].level = 5;
	test_unlock.d[8].level = 0;

	test_unlock.d[9].level = 2;
	std::cout << test_unlock.unlocked(9) << "\n";
	std::cout << test_unlock.unlocked(10) << "\n";
	std::cout << test_unlock.unlocked(11) << "\n";

	for (const auto& i : Skill::branch_range) {
		std::cout << std::get<0>(i) << "," << std::get<1>(i) << "\n";
	}
	Skill::branch_range[0] = std::make_tuple(0, 9);
	Skill::branch_range[1] = std::make_tuple(9, 18);
	Skill::branch_range[2] = std::make_tuple(18, 28);
	Skill::branch_range[3] = std::make_tuple(28, 36);
	Skill::branch_range[4] = std::make_tuple(0, 0);

	Build build1(starting_container);

	constexpr std::size_t max_skillpoints = 1500;

	tiercontainer <Build> tier_orderer(max_skillpoints, build1);
	tier_orderer.order(max_skillpoints, 35);
	if (DebugMode) {
		for (std::size_t i = 0; i < 100; i += 10) {
			std::cout << "COST:" << i << "\n";
			for (const auto& i : tier_orderer.tierlist[i])
				i.print(std::cout);
		}
	}
	auto value_less_equal = [](Build const& b1, Build const& b2) {return b1.getValue() <= b2.getValue(); };
	std::vector<Build> ordering=tier_orderer.print(value_less_equal);
	for (const auto& i : ordering)
		i.print(std::cout);

}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing