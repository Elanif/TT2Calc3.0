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

class Fraction : public DMGType<double> { //(ax+b)/(cx+d)
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
		c = 0;
		e = 0;
	}
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "TapDmgFromHelpers::getDamage\n";
		e = tt2::dmg_expos[build][tt2::TAPDAMAGE];
		return Fraction::getDamage(build, value1, value2, gold);
	}
};

class HeroDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "HeroDMG::getDamage\n";
		return pow(value1, expo * tt2::dmg_expos[build][tt2::HERODAMAGE]);
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
		e = tt2::dmg_expos[build][tt2::PETDAMAGE];
		return Fraction::getDamage(build, value1, value2, gold);
	}
};

class BossGold : Expo { //TODO FIX GOLD
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "BossGold::getDamage\n";
		return pow(value1, tt2::gold_expo*tt2::gold_expos[gold][tt2::BOSSGOLD]);
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
		e = tt2::gold_expo * tt2::gold_expos[gold][tt2::BOSSGOLD];
		return Fraction::getDamage(build, value1, value2, gold);
	}
};


class MaxCritDamage : Fraction {
public:
	using Fraction::Fraction;
	MaxCritDamage() {
		a = tt2::max_crit_damage_ratio*tt2::crit_chance;
		b = 1-tt2::crit_chance;
		c = -1;
		d = tt2::phom_cd;
		e = 1;
	}
	virtual double getDamage(std::size_t const& build, double const& value1, double const& value2, size_t const& gold) {
		std::cout << "PetGoldQTECooldown::getDamage\n";
		return 1 / 0;
		e = tt2::dmg_expos[build][tt2::PETDAMAGE]; //TODO FIX
		return Fraction::getDamage(build, value);
	}
};