#pragma once
#include"Build.hpp"
#include"tt2.hpp"
#include<iostream>
#include<cmath>

class Expo : public DMGType<vtype> {
protected:
	vtype expo = 0;
public:
	Expo() {};
	Expo(vtype const& _expo) :expo(_expo) {};
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "Expo::getDamage\n";

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
		if (DebugMode) std::cout << "Fraction::getDamage\n";

		return pow((value1 * a + b*value2) / (value1 * c + d*value2),e);
	}
};

class ExpFraction : public DMGType<vtype> { //(ay+b)/(cy+d)^(x*e)
protected:
	vtype a, b, c, d, e;
public:
	ExpFraction() { a = b = c = d = e = 1.; };
	ExpFraction(vtype const& _a, vtype const& _b, vtype const& _c, vtype const& _d, vtype const& _e) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "Fraction::getDamage\n";

		return pow((value2 * a + b) / (value2 * c + d), value1*e);
	}
};

class TapDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TapDmg::getDamage\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::TAPDAMAGE]);
	}
};

class TapDmgFromHelpers : Fraction {
public:
	TapDmgFromHelpers():Fraction(){
		b = d = tt2::tapdmgfromheroes;
		c = 0;
		e = 0;
	}
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TapDmgFromHelpers::getDamage\n";

		return pow(((tt2::tapdmgfromheroes + value1) / tt2::tapdmgfromheroes), tt2::dmg_expos[build][tt2::TAPDMGFROMHEROES]);
		b = d = tt2::tapdmgfromheroes;
		e = tt2::dmg_expos[build][tt2::TAPDMGFROMHEROES];
		return Fraction::getDamage(build, value1, 1, gold);
	}
};

class AllHeroDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "HeroDMG::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLHERODAMAGE]);
	}
};

class AllDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "AllDMG::getDamage\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLDAMAGE]);
	}
};

class PetDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PetDMG::getDamage\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class PetTapCountToAttack : Fraction {
public:
	using Fraction::Fraction;
	PetTapCountToAttack():Fraction(){
		a = 0;
		c = -1;
	}
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PetTapCountToAttack::getDamage\n";

		return pow(tt2::pet_taps_to_attack / (tt2::pet_taps_to_attack-value2), tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class BossGold : Expo { 
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "BossGold::getDamage\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::BOSSGOLD]);
	}
};

class pHoMGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "pHoMGold::getDamage\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::PHOMGOLD]);
	}
};

class PHoMCooldown : Fraction {
public:
	using Fraction::Fraction;
	PHoMCooldown() :Fraction() {
		a = 0;
		c = -1;
	}
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PHoMCooldown::getDamage\n";

		return pow(tt2::phom_cd / (tt2::phom_cd - value2), tt2::dmg_expos[build][tt2::PHOMGOLD]);
	}
};

class MaxCritDamageAndCritChance : Fraction {
public:
	using Fraction::Fraction;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MaxCritDamageAndCritChance::getDamage\n";

		if (tt2::crit_chance + value2 <= 0) return 0; // this also applies to HS even if it has an expo of 0
		return pow((tt2::crit_chance - value2) / tt2::crit_chance, tt2::dmg_expos[build][tt2::CRITCHANCE] )* pow((1 + tt2::max_crit_damage_ratio * value1) / (1 + tt2::max_crit_damage_ratio), tt2::dmg_expos[build][tt2::CRITDAMAGE]);
	}
};

class FireSwordDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "FireSwordDamage::getDamage\n";

		expo = tt2::gold_expos[gold][tt2::FIRESWORDDAMAGE];
		return Expo::getDamage(build, value1, value2, gold);
	}
};

class ChestersonGoldAndChance : Fraction {
public:
	using Fraction::Fraction;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ChestersonGoldAndChance::getDamage\n";

		if (tt2::chesterson_chance + value2 <= 0) return 0; 
		return (tt2::chesterson_chance+value2)/tt2::chesterson_chance*pow(value1,tt2::gold_expos[gold][tt2::CHESTERSONGOLD]);
	}
};

class WarCryDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "WarCryDamage::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::WARCRYDAMAGE]);
	}
};

class ClanShipDamage : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ClanShipDamage::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::CSDAMAGE]);
	}
};

class TIMultiplicative : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TIMultiplicative::getDamage\n";
		vtype result = 1;
		for (std::size_t i = 0; i < tt2::dmgtypes_size; ++i) {
			result *= pow(value1,tt2::insight_count_dmg[i]*tt2::dmg_expos[build][i]);
		}
		for (std::size_t i = 0; i < tt2::goldtypes_size; ++i) {
			result *= pow(value1, tt2::insight_count_gold[i] * tt2::gold_expos[build][i]);
		}
		return result;
	}
};

class SearingLight : Fraction {
public:
	using Fraction::Fraction;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "SearingLight::getDamage\n";
		return 1 + value1 * tt2::fight_duration*(tt2::heroic_might_inspired_heroes+value2)*2.5;
	}
};

class AnchoringShot : ExpFraction {
public:
	using ExpFraction::ExpFraction;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "AnchoringShot::getDamage\n";
		vtype spawns = tt2::clanshot_cooldown / tt2::spawn_time;
		return (value1 - 1.) / spawns+ 1.;
	}
};

class MidasGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MidasGold::getDamage\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::HOMGOLD]);
	}
};

class FairyGold : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "FairyGold::getDamage\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::FAIRYGOLD]);
	}
};

class HSDMG : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "HSDMG::getDamage\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::HSDAMAGE]);
	}
};

class PhantomVengeance : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "PhantomVengeance::getDamage\n";

		vtype sc_aps = tt2::sc_base_aps*tt2::ancient_warrior;
		const vtype base_efficiency = tt2::spawn_time/(ceil(tt2::spawn_time * sc_aps)/sc_aps);
		sc_aps = (tt2::sc_base_aps+value2)* tt2::ancient_warrior;
		const vtype skill_efficiency = tt2::spawn_time / (ceil(tt2::spawn_time * sc_aps) / sc_aps);
		const vtype efficiency = pow(skill_efficiency/base_efficiency,48);
		return pow(value1, expo * tt2::dmg_expos[build][tt2::SCDAMAGE])*efficiency;
	}
};

class LightningStrike : Expo { //not very good
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "LightningStrike::getDamage\n";
		typedef ctype ull;
		vtype efficiency = 1;
		vtype hp = 1;
		for (ull i = 0; i < (ull)(tt2::fight_duration * tt2::ls_per_second); ++i) {
			hp *= 1 - value1 * efficiency;
			efficiency *= value2;
		}
		return (.5/hp)+.5;
	}
};

class DimensionalShift : Expo { 
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "DimensionalShift::getDamage\n";
		return pow(value1, expo * (tt2::dmg_expos[build][tt2::DSDAMAGE]+ tt2::gold_expos[gold][tt2::HOMGOLD]+ tt2::dmg_expos[build][tt2::FIRESWORDDAMAGE] + tt2::dmg_expos[build][tt2::WARCRYDAMAGE] + tt2::dmg_expos[build][tt2::SCDAMAGE]));
	}
};

class MasterThief : Expo { //not very good
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "MasterThief::getDamage\n";
		return pow(value1, expo * tt2::gold_expos[gold][tt2::ALLGOLD])* pow(value2, expo*tt2::gold_expos[gold][tt2::INACTIVEGOLD]);
	}
};

class DSDamage : Expo { 
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "DSDamage::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[gold][tt2::DSDAMAGE]);
	}
};

class TwilightVeil : Expo {
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "TwilightVeil::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[gold][tt2::PETDAMAGE]);
	}
}; 

class GhostShip : Expo { 
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "GhostShip::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[gold][tt2::CSDAMAGE]);
	}
};

class ShadowAssassin : Expo { 
public:
	using Expo::Expo;
	virtual vtype getDamage(std::size_t const& build, vtype const& value1, vtype const& value2, size_t const& gold) {
		if (DebugMode) std::cout << "ShadowAssassin::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[gold][tt2::SCDAMAGE]);
	}
};
typedef Expression<vtype, TapDMG, TapDmgFromHelpers, AllHeroDMG, AllDMG, PetDMG, PetTapCountToAttack, BossGold, pHoMGold, PHoMCooldown, MaxCritDamageAndCritChance, FireSwordDamage,
						   ChestersonGoldAndChance, WarCryDamage, ClanShipDamage, TIMultiplicative, SearingLight, AnchoringShot, MidasGold, FairyGold, HSDMG, PhantomVengeance, 
						   LightningStrike, DimensionalShift, MasterThief, DSDamage, TwilightVeil, GhostShip, ShadowAssassin> Zero;
//todo ALLPROBABILITIES 