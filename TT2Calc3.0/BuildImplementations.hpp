#pragma once
#include"Build.hpp"
#include"Constants.hpp"
#include<iostream>
#include<cmath>

class Expo : public DMGType<double> {
protected:
	double expo = 0;
public:
	Expo() {};
	Expo(double const& _expo) :expo(_expo) {};
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "Expo::getDamage\n";
		return pow(value, expo);
	}
};

class Fraction : public DMGType<double> { //(ax+b)/(cx+d)
protected:
	double a, b, c, d, e;
public:
	Fraction() { a = b = c = d = e = 1.; };
	Fraction(double const& _a, double const& _b, double const& _c, double const& _d) :a(_a), b(_b), c(_c), d(_d), e(_e) {};
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "Fraction::getDamage\n";
		return pow((value * a + b) / (value * c + d),e);
	}
};

class TapDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "TapDmg::getDamage\n";
		return pow(value, expo * Constants::dmg_expos[build][tt2::TAPDMG]);
	}
};

class TapDmgFromHelpers : Fraction {
public:
	TapDmgFromHelpers() {
		b = d = 0.4;
		a = 1;
		c = 0;
		e = 0;
	}
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "TapDmgFromHelpers::getDamage\n";
		e = Constants::dmg_expos[build][tt2::TAPDMG];
		return Fraction::getDamage(build, value);
	}
};

class HeroDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "HeroDMG::getDamage\n";
		return pow(value, expo * Constants::dmg_expos[build][tt2::HERODAMAGE]);
	}
};

class AllDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "AllDMG::getDamage\n";
		return pow(value, expo * Constants::dmg_expos[build][tt2::ALLDAMAGE]);
	}
};

class PetDMG : Expo {
public:
	using Expo::Expo;
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "PetDMG::getDamage\n";
		return pow(value, expo * Constants::dmg_expos[build][tt2::PETDAMAGE]);
	}
};

