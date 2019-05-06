#include "Constants.hpp"
#include<fstream>
#include<regex>
#include<iostream>
#include<sstream>
#include<tuple>

double Constants::dmg_expos[tt2::builds_size][tt2::dmgtypes_size] = { 0 };
std::vector<std::tuple<std::string, std::size_t> > Constants::skilltree_header;
std::vector<Skill> Constants::skills;

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



bool Constants::loadSkillTreeCSV(const char* csv_path) {
	return loadSkillTreeCSV(std::string(csv_path));
}

bool Constants::loadSkillTreeCSV(std::string const& csv_path) {
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
	for (const auto i : skilltree_header) {
		std::cout << std::get<std::string>(i) <<":"<<std::get<std::size_t>(i)<< "\n";
	}

	while (safeGetline(skilltree_csv, line)) {
		std::string TalentID="";
		std::stringstream line_stream(line);
		std::getline(line_stream, TalentID, ',');
		if (TalentID.length() == 0) break;
		else buildSkill(TalentID, line_stream);
	}

	for (auto const& i : skills) {
		std::cout<<i.Name<<"\n";
	}
	return true;
}

bool Constants::buildSkill(std::string const& TalentID, std::stringstream& line_stream)
{
	Skill skill;
	skill.setTalentID(TalentID);
	std::string info = "";

	//Branch
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setBranch(info);
	//Slot
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setSlot(info);
	//SPReq
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setSPReq(info);
	//TalentReq
	if (!std::getline(line_stream, info, ',')) return false;
	skill.TalentReq = nullptr;
	for (auto const& i : skills) {
		if (i.TalentID == info) skill.setTalentReq(&i);
	}
	//Tier
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setTier(info);
	//Name
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setName(info);
	//Note
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setNote(info);
	//MaxLevel
	if (!std::getline(line_stream, info, ',')) return false;
	skill.setMaxLevel(info);

	//trash useless data
	for (std::size_t i = 0; i < maxMaxLevel; ++i) {
		if (!std::getline(line_stream, info, ',')) return false;
	}
	//SKill costs
	skill.setCost(getArray<unsigned int>(line_stream, skill.MaxLevel));
	for (auto const& i : skill.cost) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	//trash useless data until BonusTypeAString
	while (std::getline(line_stream, info, ',')) {
		if (info.length() > 0 && info != "-") break;
	}
	skill.setBonusTypeAString(info);

	//BonusTypeA
	skill.setBonusTypeA(getArray<double>(line_stream, skill.MaxLevel));
	for (auto const& i : skill.BonusTypeA) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	//trash useless data until BonusTypeBString
	while (std::getline(line_stream, info, ',')) {
		if (info.length() > 0 && info != "-") break;
	}
	skill.setBonusTypeBString(info);

	//BonusTypeB
	skill.setBonusTypeB(getArray<double>(line_stream, skill.MaxLevel));
	for (auto const& i : skill.BonusTypeB) {
		std::cout << i << " ";
	}
	std::cout << "\n";


	skills.push_back(skill);
	return true;
}

template<typename T>
std::vector<T> Constants::getArray(std::stringstream& line_stream, std::size_t const& MaxLevel)
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
		value = (T)std::stold(cost_string); //TODO would be nice to specialize the thing for unsigned int or double
		result.push_back(value);
	}
	return result;

}

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