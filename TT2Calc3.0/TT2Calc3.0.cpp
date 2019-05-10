#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"
#include<vector>

int main()
{
	tt2::initExpos();

	Zero test = Zero()+ LightningStrike();
	Zero test2 = Zero()+ AnchoringShot();
	std::cout <<"LS "<< test .getDamage(tt2::SC, 0.1532, 0.941, tt2::PHOMGOLD) << "\n";
	std::cout <<"AS "<< test2 .getDamage(tt2::SC, 10, 0.941, tt2::PHOMGOLD) << "\n\n";

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
	std::vector<SkillContainer>starting_build= preprocessor.getSkillContainer();
	starting_build[0].level = 2;
	starting_build[1].level = 1;
	starting_build[2].level = 0;
	starting_build[3].level = 9;
	starting_build[4].level = 6;
	for (std::size_t i = 0; i < 9; ++i) {
		std::cout << tt2::skills[i].Name;
		if (starting_build[i].unlocked(starting_build)) std::cout << " is unlocked";
		else std::cout << " isn't unlocked";
		std::cout << " and has a gettingTo of " << starting_build[i].gettingTo(starting_build) << "\n";
	}
}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing