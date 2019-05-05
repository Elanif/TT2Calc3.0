#include "Constants.hpp"
#include<fstream>

double Constants::dmg_expos[tt2::builds_size][tt2::dmgtypes_size] = { 0 };

bool Constants::loadSkillTreeCSV(std::string const& csv_path) {
	std::ifstream skilltree_csv(csv_path);
	if (!skilltree_csv) return false;


	return true;
};

void Constants::initExpos() {
	dmg_expos[tt2::SC][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::TAPDMG] = 0.6;
	dmg_expos[tt2::SC][tt2::TAPFROMHEROES] = 1;
	dmg_expos[tt2::SC][tt2::CRITCHANCE] = 1.5;
	dmg_expos[tt2::SC][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::FIRESWORDDAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::HERODAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::WARCRYDAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::SCDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::DSDAMAGE] = 0.6;

	dmg_expos[tt2::HS][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::TAPDMG] = 1;
	dmg_expos[tt2::HS][tt2::TAPFROMHEROES] = 1;
	dmg_expos[tt2::HS][tt2::CRITCHANCE] = 0;
	dmg_expos[tt2::HS][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::FIRESWORDDAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::HERODAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::WARCRYDAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::HSDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::DSDAMAGE] = 0;

	dmg_expos[tt2::CS][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::TAPDMG] = 0;
	dmg_expos[tt2::CS][tt2::TAPFROMHEROES] = 0;
	dmg_expos[tt2::CS][tt2::CRITCHANCE] = 0.5;
	dmg_expos[tt2::CS][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::FIRESWORDDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::HERODAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::WARCRYDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::CSDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::DSDAMAGE] = 0.5;

	dmg_expos[tt2::Pet][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::TAPDMG] = 1;
	dmg_expos[tt2::Pet][tt2::TAPFROMHEROES] = 1;
	dmg_expos[tt2::Pet][tt2::CRITCHANCE] = 1;
	dmg_expos[tt2::Pet][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::FIRESWORDDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::PETDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::HERODAMAGE] = 0.5;
	dmg_expos[tt2::Pet][tt2::WARCRYDAMAGE] = 0.5;
	dmg_expos[tt2::Pet][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::DSDAMAGE] = 0.5;
}