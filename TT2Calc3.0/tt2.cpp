#include "tt2.hpp"
#include<fstream>
#include<regex>
#include<iostream>
#include<sstream>
#include<tuple>
#include"Globals.hpp"

void tt2::init() {
	initExpos();
	initGoldExpos();
	initInsightMult();
}

vtype tt2::ancient_warrior = 2; 
vtype tt2::sc_base_aps = 4; 
vtype tt2::heroic_might_inspired_heroes = 6; //debatable
vtype tt2::clanshot_cooldown = 4;
vtype tt2::spawn_time = 0.6 * (1 - 0.1054 + 0.35);
vtype tt2::fight_duration = 4;
vtype tt2::crit_chance = 0.27;
vtype tt2::chesterson_chance = 0.3;
vtype tt2::tapdmgfromheroes = 0.4;
vtype tt2::sc_attempts = 169.9;
vtype tt2::ls_per_second = 2.2 / 100 * sc_attempts;
vtype tt2::dmg_expos[tt2::builds_size][tt2::dmgtypes_size] = { 0 };
vtype tt2::gold_expos[tt2::goldtypes_size][tt2::goldtypes_size] = { 0 };
std::size_t tt2::insight_count_gold[tt2::goldtypes_size] = { 0 };
std::size_t tt2::insight_count_dmg[tt2::dmgtypes_size] = { 0 };
std::vector<std::tuple<std::string, std::size_t> > tt2::skilltree_header;
std::vector<Skill> tt2::skills;

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



bool tt2::loadSkillTreeCSV(const char* csv_path) {
	return loadSkillTreeCSV(std::string(csv_path));
}

bool tt2::loadSkillTreeCSV(std::string const& csv_path) {
	std::ifstream skilltree_csv(csv_path);
	if (!skilltree_csv) {
		std::cerr << csv_path << " file not found\n";
		return false;
	}
	std::string line;
	if (!safeGetline(skilltree_csv, line)) return false;

	std::string header_name="";
	std::stringstream line_stream(line);

	while (std::getline(line_stream, header_name, ',')) {
		if (header_name.length() == 0) break;

		std::string::const_iterator it_index;
		std::string::const_iterator it_end;

		it_index = header_name.cbegin();
		it_end = header_name.cend();

		std::regex array_type("([A-Za-z\\_])*(\\d)+\\b");
		std::smatch matches;
		std::regex_search(it_index, it_end, matches, array_type);

		if (matches.empty()) { //Name of data(
			skilltree_header.push_back(std::make_tuple(header_name, 0));
		}
		else { //array data
			if (skilltree_header.size() == 0 || std::get<std::string>(skilltree_header[skilltree_header.size() - 1]) != matches[1]) {
				skilltree_header.push_back(std::make_tuple(matches[1].str(), 1));
			}
			else {
				std::get<std::size_t>(skilltree_header[skilltree_header.size() - 1])++;
			}

		}
	}
	/*for (const auto i : skilltree_header) {
		std::cout << std::get<std::string>(i) <<":"<<std::get<std::size_t>(i)<< "\n";
	}*/

	std::size_t skill_counter = 0;
	while (safeGetline(skilltree_csv, line)) {
		std::string TalentID="";
		std::stringstream line_stream(line);
		std::getline(line_stream, TalentID, ',');
		if (TalentID.length() == 0) break;
		else buildSkill(TalentID, line_stream,skill_counter);
		skill_counter++;
	}

	std::vector<const Skill*> GettingToArray;
	std::vector<std::size_t> last_slots;

	for (auto& skill: tt2::skills) {
		if (last_slots.size() == 0) { //first iteration
			last_slots.push_back(skill.Slot);
			GettingToArray.push_back(&skill);
		}
		else if (skill.Slot <= last_slots[last_slots.size() - 1]) { //end of branch
			GettingToArray.clear();
			last_slots.clear();
			last_slots.push_back(skill.Slot);
			GettingToArray.push_back(&skill);
		}
		else { //continuing through branch
			last_slots.push_back(skill.Slot);
			GettingToArray.push_back(&skill);
		}

		//result.push_back(SkillContainer(tt2::skills[i], skillMaxLevel[i], skillCost[i], skillEffect[i]));

		std::size_t max_slot = 0;

		switch (skill.Slot) {
		case 0:
			break;
		case 1:case 2:case 3:
			max_slot = 1;
			break;
		case 4:case 5:case 6:
			max_slot = 4;
			break;
		case 7:case 8:case 9:
			max_slot = 7;
			break;
		default:
			max_slot = 0;
			break;
		}
		for (std::size_t slot_it = 0; slot_it < last_slots.size(); ++slot_it) {
			if (last_slots[slot_it] < max_slot)
				skill.addGettingTo(GettingToArray[slot_it]);
		}
	}

	/*for (auto const& i : skills) {
		std::cout<<i.Name<<"\n";
	}*/
	return true;
}

bool tt2::buildSkill(std::string const& TalentID, std::stringstream& line_stream, std::size_t const& skill_counter)
{
	std::string s_Branch; 
	std::string s_Slot; 
	std::string s_SPReq; 
	std::string s_TalentReq; 
	std::string s_Tier; 
	std::string s_Name; 
	std::string s_Note; 
	std::string s_MaxLevel; 

	if (!std::getline(line_stream, s_Branch, ',')) return false;
	if (!std::getline(line_stream, s_Slot, ',')) return false;
	if (!std::getline(line_stream, s_SPReq, ',')) return false;
	if (!std::getline(line_stream, s_TalentReq, ',')) return false;
	if (!std::getline(line_stream, s_Tier, ',')) return false;
	if (!std::getline(line_stream, s_Name, ',')) return false;
	if (!std::getline(line_stream, s_Note, ',')) return false;
	if (!std::getline(line_stream, s_MaxLevel, ',')) return false;

	Skill skill(std::stoull(s_MaxLevel));

	skill.index = skill_counter;

	skill.setTalentID(TalentID);
	if (!skill.setBranch(s_Branch)) {
		std::cout << "Couldn't set branch "<< s_Branch<< "\n";
		return false;
	}
	
	skill.setSlot(s_Slot);

	skill.setSPReq(s_SPReq);

	skill.TalentReq = (std::size_t) -1;
	if (s_TalentReq != "None") {
		std::size_t found = 0;
		for (std::size_t i = 0; i < tt2::skills.size(); ++i) {
			if (skills[i].TalentID == s_TalentReq) {
				skill.setTalentReq(i);
				++found;
			}
		}
		if (found != 1) {
			if (found == 0) std::cout << "No TalentID requirement found";
			else std::cout << "Too many TalentID requirements found";
			std::cout << " looking for " << s_TalentReq << " from " << skill.TalentID << "\n";
			return false;
		}
	}

	if (!skill.setTier(s_Tier)) {
		std::cout << "Couldn't set tier\n";
		return false;
	}

	skill.setName(s_Name);
	if (DebugMode) {
		std::cout << s_Name << "\n";
	}

	skill.setNote(s_Note);


	std::string info = "";
	//trash useless data
	for (std::size_t i = 0; i < maxMaxLevel; ++i) {
		if (!std::getline(line_stream, info, ',')) return false;
	}

	skill.setCost(getArray<ctype>(line_stream, skill.MaxLevel));
	if (DebugMode) {
		for (auto const& i : skill.cost) {
			std::cout << i << " ";
		}
		std::cout << "\n";
	}

	while (std::getline(line_stream, info, ',')) {
		if (info.length() > 0 && info != "-") break;
	}
	skill.setBonusTypeAString(info);

	skill.setBonusTypeA(getArray<vtype>(line_stream, skill.MaxLevel));

	if (DebugMode) {
		for (auto const& i : skill.BonusTypeA) {
			std::cout << i << " ";
		}
		std::cout << "\n";
	}

	//trash useless data until BonusTypeBString
	while (std::getline(line_stream, info, ',')) {
		if (info.length() > 0 && info != "-") break;
	}
	skill.setBonusTypeBString(info);

	skill.setBonusTypeB(getArray<vtype>(line_stream, skill.MaxLevel));

	if (DebugMode) {
		for (auto const& i : skill.BonusTypeB) {
			std::cout << i << " ";
		}
		std::cout << "\n";
	}

	skills.push_back(skill);
	return true;
}

template<typename T>
std::vector<T> tt2::getArray(std::stringstream& line_stream, std::size_t const& MaxLevel)
{
	std::vector<T> result = {};
	std::string cost_string = "";
	if (!line_stream) return result;

	while (std::getline(line_stream, cost_string, ',')) {
		if (cost_string.length() > 0 && cost_string != "-") break;
	}
	T value = std::stoul(cost_string);
	result.push_back(value);
	for (std::size_t i = 0; i < MaxLevel; ++i) {
		if (!std::getline(line_stream, cost_string, ',') || cost_string.length() <= 0 || cost_string == "-") return result;
		value = (T)std::stold(cost_string); //TODO would be nice to specialize the thing for ctype or vtype
		result.push_back(value);
	}
	return result;

}

void tt2::initExpos() {
	dmg_expos[tt2::SC][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::TAPDAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::TAPDMGFROMHEROES] = 1;
	dmg_expos[tt2::SC][tt2::CRITCHANCE] = 1.5;
	dmg_expos[tt2::SC][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::FIRESWORDDAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::ALLHERODAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::WARCRYDAMAGE] = 0.6;
	dmg_expos[tt2::SC][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::SC][tt2::SCDAMAGE] = 1;
	dmg_expos[tt2::SC][tt2::DSDAMAGE] = 0.6;

	dmg_expos[tt2::HS][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::TAPDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::TAPDMGFROMHEROES] = 1;
	dmg_expos[tt2::HS][tt2::CRITCHANCE] = 0;
	dmg_expos[tt2::HS][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::FIRESWORDDAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::ALLHERODAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::WARCRYDAMAGE] = 0.5;
	dmg_expos[tt2::HS][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::HSDAMAGE] = 1;
	dmg_expos[tt2::HS][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::HS][tt2::DSDAMAGE] = 0;

	dmg_expos[tt2::CS][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::TAPDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::TAPDMGFROMHEROES] = 0;
	dmg_expos[tt2::CS][tt2::CRITCHANCE] = 0.5;
	dmg_expos[tt2::CS][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::FIRESWORDDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::PETDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::ALLHERODAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::WARCRYDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::CSDAMAGE] = 1;
	dmg_expos[tt2::CS][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::CS][tt2::DSDAMAGE] = 0.5;

	dmg_expos[tt2::Pet][tt2::ALLDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::TAPDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::TAPDMGFROMHEROES] = 1;
	dmg_expos[tt2::Pet][tt2::CRITCHANCE] = 1;
	dmg_expos[tt2::Pet][tt2::CRITDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::FIRESWORDDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::PETDAMAGE] = 1;
	dmg_expos[tt2::Pet][tt2::ALLHERODAMAGE] = 0.5;
	dmg_expos[tt2::Pet][tt2::WARCRYDAMAGE] = 0.5;
	dmg_expos[tt2::Pet][tt2::CSDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::HSDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::SCDAMAGE] = 0;
	dmg_expos[tt2::Pet][tt2::DSDAMAGE] = 0.7;
}

void tt2::initGoldExpos()
{
	for (std::size_t i = 0; i < tt2::goldtypes_size; ++i) {
		gold_expos[i][i] = goldExpo; //every gold type is 1:1 with itself
		gold_expos[i][tt2::ALLGOLD] = goldExpo; //and all gold works with everything
	}

	gold_expos[tt2::PHOMGOLD][tt2::BOSSGOLD] = goldExpo;
	gold_expos[tt2::PHOMGOLD][tt2::HOMGOLD] = 0.6*goldExpo;

	gold_expos[tt2::BOSSGOLD][tt2::HOMGOLD] = goldExpo;

	gold_expos[tt2::CHESTERSONGOLD][tt2::MULTISPAWNGOLD] = goldExpo;
	gold_expos[tt2::CHESTERSONGOLD][tt2::HOMGOLD] = goldExpo;
	gold_expos[tt2::CHESTERSONGOLD][tt2::CHESTERSONCHANCE] = goldExpo;

	gold_expos[tt2::FAIRYGOLD][tt2::CHESTERSONGOLD] = goldExpo;
	gold_expos[tt2::FAIRYGOLD][tt2::CHESTERSONCHANCE] = goldExpo;
	gold_expos[tt2::FAIRYGOLD][tt2::HOMGOLD] = 0.6 * goldExpo;
}

void tt2::initInsightMult() {
	insight_count_dmg[tt2::ALLDAMAGE] = 38;
	insight_count_dmg[tt2::TAPDAMAGE] = 26;
	insight_count_dmg[tt2::TAPDMGFROMHEROES] = 0;
	insight_count_dmg[tt2::CRITCHANCE] = 0;
	insight_count_dmg[tt2::CRITDAMAGE] = 22;
	insight_count_dmg[tt2::FIRESWORDDAMAGE] = 0;
	insight_count_dmg[tt2::PETDAMAGE] = 0;
	insight_count_dmg[tt2::ALLHERODAMAGE] = 25+21/3; // in media solo uno è attivo?
	insight_count_dmg[tt2::WARCRYDAMAGE] = 0;
	insight_count_dmg[tt2::CSDAMAGE] = 0;
	insight_count_dmg[tt2::HSDAMAGE] = 0;
	insight_count_dmg[tt2::SCDAMAGE] = 4;
	insight_count_dmg[tt2::DSDAMAGE] = 0;

	insight_count_gold[tt2::PHOMGOLD] = 0;
	insight_count_gold[tt2::BOSSGOLD] = 29;
	insight_count_gold[tt2::HOMGOLD] = 0;
	insight_count_gold[tt2::CHESTERSONGOLD] = 34;
	insight_count_gold[tt2::CHESTERSONCHANCE] = 0;
	insight_count_gold[tt2::MULTISPAWNGOLD] = 0;
	insight_count_gold[tt2::FAIRYGOLD] = 19;
	insight_count_gold[tt2::ALLGOLD] = 30;
}