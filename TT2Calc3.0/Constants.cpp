#include "Constants.hpp"
#include<fstream>
#include<regex>

std::istream& safeGetline(std::istream& is, std::string& t) //https://stackoverflow.com/a/6089413
{
	t.clear();
	std::istream::sentry se(is, true);
	std::streambuf* sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
		case '\n':
			return is;
		case '\r':
			if (sb->sgetc() == '\n')
				sb->sbumpc();
			return is;
		case std::streambuf::traits_type::eof():
			if (t.empty())
				is.setstate(std::ios::eofbit);
			return is;
		default:
			t += (char)c;
		}
	}
}


double Constants::dmg_expos[tt2::builds_size][tt2::dmgtypes_size] = { 0 };

bool Constants::loadSkillTreeCSV(std::string const& csv_path) {
	std::ifstream skilltree_csv(csv_path);
	if (!skilltree_csv) return false;
	std::string line;
	if (!safeGetline(skilltree_csv, line)) return false;

	std::string::const_iterator index = line.cbegin();
	std::string::const_iterator line_end = line.cend();

	for (;;) {
		std::regex array_type("[A-Za-z\\_]*(\\d)+");
		std::smatch matches;
		std::regex_search(index, line_end, matches, array_type);
		if (matches.empty()) { //Name of data

		}
		else { //array data

		}
	}

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