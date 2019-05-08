#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>

int main()
{
	tt2::initExpos();

	Expression<double, TapDMG, AllDMG> test;
	test.add(TapDMG(4)).add(AllDMG(2));
	std::cout << test.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n";

	Expression<double, TapDMG, AllDMG, AllHeroDMG> test2;
	(test2 += TapDMG(3)) += AllHeroDMG(1);
	std::cout << test2.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n";

	Expression<double, TapDMG, AllDMG, AllHeroDMG> Exp;
	auto test3 = Exp + TapDMG(1) + AllDMG(1) + AllHeroDMG(5);
	std::cout << test3.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n\n\n\n";

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
	std::cout << SkillPowers.size();

	Preprocessor preprocessor(0, 1, SkillPowers);
}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing