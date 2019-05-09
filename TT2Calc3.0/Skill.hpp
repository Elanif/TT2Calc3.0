#pragma once
#include<string>
#include<vector>
#include"Globals.hpp"
#include<tuple>

class Skill
{
public:
	std::size_t index = 0;
	std::string TalentID="";
	void setTalentID(std::string const& _TalentID) { TalentID = _TalentID; }

	static constexpr std::size_t Branch_size = 4;
	enum BRANCH {
		KNIGHT=0,
		WARLORD,
		SORCERER,
		ASSASSIN
	} Branch=(BRANCH)0;

	static std::tuple<std::size_t, std::size_t> branch_range[Branch_size];

	bool setBranch(std::string const& _Branch);

	std::size_t Slot=0;
	void setSlot(std::string const& _slot) { Slot = std::stoul(_slot); }

	std::size_t SPReq=0;
	void setSPReq(std::string const& _spReq) { SPReq = std::stoul(_spReq); }

	Skill const* TalentReq=nullptr;
	void setTalentReq(Skill const* _TalentReq) { TalentReq = _TalentReq; }

	static constexpr ctype Tier_size = 4;
	ctype Tier=0;
	bool setTier(std::string const& _Tier) {
		const std::string tiers[] = { "I","II","III","IV" };
		Tier = 0;
		while (tiers[Tier] != _Tier) {
			Tier++;
			if (Tier >= Tier_size) {
				Tier = 0;
				return false;
			}
		}
		return true;
	}

	std::string Name = "";
	void setName(std::string const& _Name) { Name = _Name; }

	std::string Note = "";
	void setNote(std::string const& _Note) { Note = _Note; }

	std::size_t MaxLevel = 0;
	void setMaxLevel(std::string const& _MaxLevel) { MaxLevel = std::stoul(_MaxLevel); }

	std::vector<ctype> cost;
	void setCost(std::vector<ctype> const& cost_vector) { cost = cost_vector; }

	std::string BonusTypeAString;
	void setBonusTypeAString(std::string const& _BonusTypeAString) { BonusTypeAString = _BonusTypeAString; }

	std::vector<vtype> BonusTypeA;
	void setBonusTypeA(std::vector<vtype> const& _BonusTypeA) { BonusTypeA = _BonusTypeA; }

	std::string BonusTypeBString;
	void setBonusTypeBString(std::string const& _BonusTypeBString) { BonusTypeBString = _BonusTypeBString; }

	std::vector<vtype> BonusTypeB;
	void setBonusTypeB(std::vector<vtype> const& _BonusTypeB) { BonusTypeB = _BonusTypeB; }
};

