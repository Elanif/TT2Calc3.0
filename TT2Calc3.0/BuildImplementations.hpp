#pragma once
#include"Build.hpp"
#include"tt2.hpp"
#include<iostream>
#include<cmath>

class Expo : public DMGType<vtype> {
protected:
	vtype expo = 1;
public:
	Expo() {};
	Expo(vtype const& _expo) :expo(_expo) {};
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "Expo::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo);
	}
};

class Fraction : public DMGType<vtype> { //((ax+by)/(cx+dy))^e
protected:
	vtype a, b, c, d, e;
public:
	Fraction() { a = b = c = d = e = 1.; };
	Fraction(vtype const& _a, vtype const& _b, vtype const& _c, vtype const& _d, vtype const& _e) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "Fraction::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow((value1 * a + b * value2) / (value1 * c + d * value2), e);
	}
};

class ExpFraction : public DMGType<vtype> { //(ay+b)/(cy+d)^(x*e)
protected:
	vtype a, b, c, d, e;
public:
	ExpFraction() { a = b = c = d = e = 1.; };
	ExpFraction(vtype const& _a, vtype const& _b, vtype const& _c, vtype const& _d, vtype const& _e) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		return pow((value2 * a + b) / (value2 * c + d), value1 * e);
	}
};

class TapDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		return pow(value1, expo * tt2::dmg_expos[build][tt2::TAPDAMAGE]);
	}
};

class TapDmgFromHelpers : Fraction {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		return pow((tt2::tapdmgfromheroes + value1) / tt2::tapdmgfromheroes, tt2::dmg_expos[build][tt2::TAPDMGFROMHEROES]);
	}
};

class AllHeroDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "HeroDMG::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLHERODAMAGE]);
	}
};

class AllDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "AllDMG::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLDAMAGE]);
	}
};

class PetDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PetDMG::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class PetTapCountToAttack{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PetTapCountToAttack::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(tt2::pet_taps_to_attack / (tt2::pet_taps_to_attack - value2), tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class BossGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "BossGold::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::BOSSGOLD]);
	}
};

class pHoMGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "pHoMGold::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"expo="<< expo*tt2::gold_expos[gold][tt2::PHOMGOLD]<<"damage="<< pow(value1, expo * tt2::gold_expos[gold][tt2::PHOMGOLD]) <<"\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::PHOMGOLD]);
	}
};

class PHoMCooldown : Fraction {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PHoMCooldown::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(tt2::phom_cd / (tt2::phom_cd - value2), tt2::dmg_expos[build][tt2::PHOMGOLD]);
	}
};

class MaxCritDamageAndCritChance {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MaxCritDamageAndCritChance::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		if (tt2::crit_chance + value2 <= 0) return 1; // this also applies to HS even if it has an expo of 0
		return pow((tt2::crit_chance - value2) / tt2::crit_chance, tt2::dmg_expos[build][tt2::CRITCHANCE]) * pow((1 + tt2::max_crit_damage_ratio * value1) / (1 + tt2::max_crit_damage_ratio), tt2::dmg_expos[build][tt2::CRITDAMAGE]);
	}
};

class FireSwordDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "FireSwordDamage::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		expo = tt2::gold_expos[gold][tt2::FIRESWORDDAMAGE];
		return Expo::getDamage(build, value1, value2, gold);
	}
};

class ChestersonGoldAndChance{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ChestersonGoldAndChance::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		if (tt2::chesterson_chance + value2 <= 0) return 1;
		return pow(value1, (tt2::chesterson_chance + value2) / tt2::chesterson_chance* tt2::gold_expos[gold][tt2::CHESTERSONGOLD]);
	}
};

class WarCryDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "WarCryDamage::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::WARCRYDAMAGE]);
	}
};

class ClanShipDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ClanShipDamage::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::CSDAMAGE]);
	}
};

class TIMultiplicative {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TIMultiplicative::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		vtype expo{ 0 };
		for (std::size_t i = 0; i < tt2::dmgtypes_size; ++i) {
			expo+=tt2::insight_count_dmg[i] * tt2::dmg_expos[build][i];
		}
		for (std::size_t i = 0; i < tt2::goldtypes_size; ++i) {
			expo += tt2::insight_count_gold[i] * tt2::gold_expos[build][i];
		}
		return pow(1L+value1, expo);
	}
};

class SearingLight {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "SearingLight::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		return 1 + value1 * tt2::fight_duration * (tt2::heroic_might_inspired_heroes + value2) * 2.5;
	}
};

class AnchoringShot{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "AnchoringShot::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		vtype spawns = tt2::clanshot_cooldown / tt2::spawn_time;
		return (value1 - 1.) / spawns + 1.;
	}
};

class MidasGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MidasGold::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::HOMGOLD]);
	}
};

class FairyGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "FairyGold::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::FAIRYGOLD]);
	}
};

class HSDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "HSDMG::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::HSDAMAGE]);
	}
};

class PhantomVengeance{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PhantomVengeance::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";

		vtype sc_aps = tt2::sc_base_aps * tt2::ancient_warrior;
		const vtype base_efficiency = tt2::spawn_time / (ceil(tt2::spawn_time * sc_aps) / sc_aps);
		sc_aps = (tt2::sc_base_aps + value2) * tt2::ancient_warrior;
		const vtype skill_efficiency = tt2::spawn_time / (ceil(tt2::spawn_time * sc_aps) / sc_aps);
		vtype efficiency = pow(skill_efficiency / base_efficiency, 43.6);
		if (tt2::dmg_expos[build][tt2::SCDAMAGE] == 0) efficiency = 1;
		return pow(value1 * efficiency, tt2::dmg_expos[build][tt2::SCDAMAGE] ) ;
	}
};

class LightningStrike{ //not very good
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "LightningStrike::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"\n";
		typedef ctype ull;
		vtype efficiency = 1;
		vtype hp = 1;
		for (ull i = 0; i < (ull)(tt2::fight_duration * tt2::ls_per_second); ++i) {
			hp *= 1 - value1 * efficiency;
			efficiency *= value2;
		}
		return (.5 / hp) + .5;
	}
};

class DimensionalShift {
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "DimensionalShift::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"="<< pow(value1, (tt2::dmg_expos[build][tt2::DSDAMAGE] + tt2::gold_expos[gold][tt2::HOMGOLD] + tt2::dmg_expos[build][tt2::FIRESWORDDAMAGE] + tt2::dmg_expos[build][tt2::WARCRYDAMAGE] + tt2::dmg_expos[build][tt2::SCDAMAGE]))<<"\n";
		return pow(value1, tt2::dmg_expos[build][tt2::DSDAMAGE] + tt2::gold_expos[gold][tt2::HOMGOLD] + tt2::dmg_expos[build][tt2::FIRESWORDDAMAGE] + tt2::dmg_expos[build][tt2::WARCRYDAMAGE] + tt2::dmg_expos[build][tt2::SCDAMAGE]);
	}
};

class MasterThief{ 
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MasterThief::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"="<< pow(value1, tt2::gold_expos[gold][tt2::ALLGOLD]) * pow(value2,  tt2::gold_expos[gold][tt2::INACTIVEGOLD]) <<"\n";
		return pow(value1, tt2::gold_expos[gold][tt2::ALLGOLD])* pow(value2, tt2::gold_expos[gold][tt2::INACTIVEGOLD]);
	}
};

class DSDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "DSDamage::getDamage"<<build<<","<<value1<<","<<value2<<","<<gold<<"="<< pow(value1, expo * tt2::dmg_expos[build][tt2::DSDAMAGE]) <<"\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::DSDAMAGE]);
	}
};

class TwilightVeil{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TwilightVeil::getDamage"<<build<<","<<value1<<","<<value2<<"," << gold << "=" << pow(value2, tt2::dmg_expos[build][tt2::PETDAMAGE]) << "\n";
		return pow(value2, tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class GhostShip{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "GhostShip::getDamage"<<build<<","<<value1<<","<<value2<<"," << gold << "=" << pow(value2,tt2::dmg_expos[build][tt2::CSDAMAGE]) << "\n";
		return pow(value2,  tt2::dmg_expos[build][tt2::CSDAMAGE]);
	}
};

class ShadowAssassin{
public:
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ShadowAssassin::getDamage"<<build<<","<<value1<<","<<value2<<"," << gold << "=" << pow(value2,  tt2::dmg_expos[build][tt2::SCDAMAGE])<<"ecpo="<< tt2::dmg_expos[build][tt2::SCDAMAGE] << "\n";

		return pow(value2, tt2::dmg_expos[build][tt2::SCDAMAGE]);
	}
};
typedef Expression<vtype, TapDMG, TapDmgFromHelpers, AllHeroDMG, AllDMG, PetDMG, PetTapCountToAttack, BossGold, pHoMGold, PHoMCooldown, MaxCritDamageAndCritChance, FireSwordDamage,
	ChestersonGoldAndChance, WarCryDamage, ClanShipDamage, TIMultiplicative, SearingLight, AnchoringShot, MidasGold, FairyGold, HSDMG, PhantomVengeance,
	LightningStrike, DimensionalShift, MasterThief, DSDamage, TwilightVeil, GhostShip, ShadowAssassin> Zero;
//todo ALLPROBABILITIES 