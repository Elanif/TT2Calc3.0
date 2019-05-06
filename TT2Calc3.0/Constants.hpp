#pragma once
#include<unordered_map>
#include<string>
#include<vector>

namespace tt2 {

	constexpr std::size_t builds_size = 4;
	/*const char* build_names[] = {
		"SC",
		"HS",
		"CS",
		"Pet"
	};*/

	const enum BUILDS {
		SC = 0,
		HS,
		CS,
		Pet
	};

	constexpr std::size_t dmgtypes_size = 13;
	const enum DMGTYPES {
		ALLDAMAGE = 0,
		TAPDMG,
		TAPFROMHEROES,
		CRITDAMAGE,
		CRITCHANCE,
		FIRESWORDDAMAGE,
		PETDAMAGE,
		HERODAMAGE,
		WARCRYDAMAGE,
		CSDAMAGE,
		HSDAMAGE,
		SCDAMAGE,
		DSDAMAGE,
	};

	constexpr std::size_t goldtypes_size = 4;
	const enum GOLDTYPES {
		PHOMGOLD = 0,
		CHESTERSONGOLD,
		FAIRYGOLD,
		ALLGOLD
	};


};

class Constants {
public:

	static void initExpos();
	static double dmg_expos[tt2::builds_size][tt2::dmgtypes_size];

	static bool loadSkillTreeCSV(const char* csv_path);
	static bool loadSkillTreeCSV(std::string const& csv_path);
	static std::unordered_map<std::string, std::array<std::vector<double>, 3 > > skills;
};