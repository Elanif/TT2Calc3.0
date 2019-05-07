#pragma once
#include"Build.hpp"
#include"tt2.hpp"
#include<iostream>
#include<cmath>

class Expo : public DMGType<double> {
protected:
	double expo = 0;
public:
	Expo() {};
	Expo(double const& _expo) :expo(_expo) {};
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "Expo::getDamage\n";

		return pow(value1, expo);
	}
};

class Fraction : public DMGType<double> { //((ax+by)/(cx+dy))^e
protected:
	double a, b, c, d, e;
public:
	Fraction() { a = b = c = d = e = 1.; };
	Fraction(double const& _a, double const& _b, double const& _c, double const& _d, double const& _e) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "Fraction::getDamage\n";

		return pow((value1 * a + b*value2) / (value1 * c + d*value2),e);
	}
};

class ExpFraction : public DMGType<double> { //(ay+b)/(cy+d)^(x*e)
protected:
	double a, b, c, d, e;
public:
	ExpFraction() { a = b = c = d = e = 1.; };
	ExpFraction(double const& _a, double const& _b, double const& _c, double const& _d, double const& _e) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "Fraction::getDamage\n";

		return pow((value2 * a + b) / (value2 * c + d), value1*e);
	}
};

class TapDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "TapDmg::getDamage\n";

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
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "TapDmgFromHelpers::getDamage\n";

		return pow(((tt2::tapdmgfromheroes + value1) / tt2::tapdmgfromheroes), tt2::dmg_expos[build][tt2::TAPDMGFROMHEROES]);
		b = d = tt2::tapdmgfromheroes;
		e = tt2::dmg_expos[build][tt2::TAPDMGFROMHEROES];
		return Fraction::getDamage(build, value1, 1, gold);
	}
};

class AllHeroDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "HeroDMG::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLHERODAMAGE]);
	}
};

class AllDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "AllDMG::getDamage\n";

		return pow(value1, expo * tt2::dmg_expos[build][tt2::ALLDAMAGE]);
	}
};

class PetDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "PetDMG::getDamage\n";

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
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "PetTapCountToAttack::getDamage\n";

		return pow(tt2::pet_taps_to_attack / (tt2::pet_taps_to_attack-value2), tt2::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

class BossGold : Expo { 
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "BossGold::getDamage\n";

		return pow(value1, expo * tt2::gold_expos[gold][tt2::BOSSGOLD]);
	}
};

class PHoMCooldown : Fraction {
public:
	using Fraction::Fraction;
	PHoMCooldown() :Fraction() {
		a = 0;
		c = -1;
	}
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "PHoMCooldown::getDamage\n";

		return pow(tt2::phom_cd / (tt2::phom_cd - value2), tt2::dmg_expos[build][tt2::PHOMGOLD]);
	}
};

class MaxCritDamageAndCritChance : Fraction {
public:
	using Fraction::Fraction;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "MaxCritDamageAndCritChance::getDamage\n";

		if (tt2::crit_chance + value2 <= 0) return 0; // this also applies to HS even if it has an expo of 0
		return pow((tt2::crit_chance - value2) / tt2::crit_chance, tt2::dmg_expos[build][tt2::CRITCHANCE] )* pow((1 + tt2::max_crit_damage_ratio * value1) / (1 + tt2::max_crit_damage_ratio), tt2::dmg_expos[build][tt2::CRITDAMAGE]);
	}
};

class FireSwordDamage : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "FireSwordDamage::getDamage\n";

		expo = tt2::gold_expos[gold][tt2::FIRESWORDDAMAGE];
		return Expo::getDamage(build, value1, value2, gold);
	}
};

class ChestersonGoldAndChance : Fraction {
public:
	using Fraction::Fraction;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "ChestersonGoldAndChance::getDamage\n";

		if (tt2::chesterson_chance + value2 <= 0) return 0; 
		return (tt2::chesterson_chance+value2)/tt2::chesterson_chance*pow(value1,tt2::gold_expos[gold][tt2::CHESTERSONGOLD]);
	}
};

//todo ALLPROBABILITIES 