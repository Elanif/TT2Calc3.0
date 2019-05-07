#pragma once
#include<unordered_map>
#include<string>
#include<vector>
#include"Skill.hpp"

class tt2 {
public:


	static constexpr std::size_t builds_size = 4;
	static constexpr const char* build_names[4] = {
		"SC",
		"HS",
		"CS",
		"Pet"
	};

	const enum BUILDS {
		SC = 0,
		HS,
		CS,
		Pet
	};


	static constexpr std::size_t dmgtypes_size = 13;
	const enum DMGTYPES {
		ALLDAMAGE = 0,
		TAPDAMAGE,
		TAPDMGFROMHEROES,
		CRITDAMAGE,
		CRITCHANCE,
		FIRESWORDDAMAGE,
		PETDAMAGE,
		ALLHERODAMAGE,
		WARCRYDAMAGE,
		CSDAMAGE,
		HSDAMAGE,
		SCDAMAGE,
		DSDAMAGE,
	};

	static constexpr std::size_t goldtypes_size = 8;
	const enum GOLDTYPES {
		PHOMGOLD = 0,
		BOSSGOLD,
		HOMGOLD,
		CHESTERSONGOLD,
		CHESTERSONCHANCE,
		MULTISPAWNGOLD,
		FAIRYGOLD,
		ALLGOLD
	};

	static constexpr double phom_cd = 75;
	static constexpr double pet_taps_to_attack = 20;
	static constexpr double gold_expo = 0.79;
	static constexpr double goldExpo = 0.79;
	static double heroic_might_inspired_heroes;
	static double fight_duration;
	static double crit_chance;
	static double chesterson_chance;
	static double tapdmgfromheroes;
	static double constexpr max_crit_damage_ratio = 6.7;


	static double dmg_expos[tt2::builds_size][tt2::dmgtypes_size];
	static void initExpos();

	static double gold_expos[tt2::goldtypes_size][tt2::goldtypes_size];
	static void initGoldExpos();

	static std::size_t insight_count_gold[tt2::goldtypes_size];
	static std::size_t insight_count_dmg[tt2::dmgtypes_size];
	static void initInsightMult();

	static bool loadSkillTreeCSV(const char* csv_path);
	static bool loadSkillTreeCSV(std::string const& csv_path);
	static bool buildSkill(std::string const& TalentID, std::stringstream& line_stream);

	template<typename T>
	static std::vector<T> getArray(std::stringstream& line_stream, std::size_t const& MaxLevel);
	//static std::unordered_map<std::string, std::array<std::vector<double>, 3 > > skills;

	static constexpr std::size_t maxMaxLevel = 26;
	static std::vector<std::tuple<std::string, std::size_t> > skilltree_header;
	static std::vector<Skill> skills;
};
