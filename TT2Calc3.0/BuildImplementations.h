#pragma once
#include"Build.hpp"
#include"Constants.hpp"
#include<iostream>

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

class Invert : public DMGType<double> {
protected:
	double base = 0;
public:
	Invert() {};
	Invert(double const& _base) :base(_base) {};
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "Invert::getDamage\n";
		return base / (base - value);
	}
};

class Linear : public DMGType<double> {
protected:
	double base = 0;
public:
	Linear() {};
	Linear(double const& _base) :base(_base) {};
	virtual double getDamage(std::size_t const& build, double const& value) {
		std::cout << "Linear::getDamage\n";
		return base + value;
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

