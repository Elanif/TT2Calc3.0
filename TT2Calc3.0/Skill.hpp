#pragma once
#include<string>
#include<vector>
class Skill
{
public:
	std::string TalentID="";
	void setTalentID(std::string const& _TalentID) { TalentID = _TalentID; }

	static constexpr std::size_t Branch_size = 4;
	enum BRANCH {
		KNIGHT=0,
		WARLORD,
		SORCERER,
		ASSASSIN
	} Branch=(BRANCH)0;
	bool setBranch(std::string const& _Branch) {
		const std::string branch_names[] = {"BranchRed","BranchYellow","BranchBlue","BranchGreen"};
		Branch = (BRANCH)0;
		while (branch_names[Branch] != _Branch) {
			Branch = (BRANCH) ((std::size_t) Branch + 1);
			if ((std::size_t) Branch >= Branch_size) {
				Branch = (BRANCH)0;
				return false;
			}
		}
		return true;
	}

	std::size_t Slot=0;
	void setSlot(std::string const& _slot) { Slot = std::stoul(_slot); }

	std::size_t SPReq=0;
	void setSPReq(std::string const& _spReq) { SPReq = std::stoul(_spReq); }

	Skill const* TalentReq=nullptr;
	void setTalentReq(Skill const* _TalentReq) { TalentReq = _TalentReq; }

	static constexpr unsigned int Tier_size = 4;
	unsigned int Tier=0;
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

	std::vector<unsigned int> cost;
	void setCost(std::vector<unsigned int> const& cost_vector) { cost = cost_vector; }

	std::string BonusTypeAString;
	void setBonusTypeAString(std::string const& _BonusTypeAString) { BonusTypeAString = _BonusTypeAString; }

	std::vector<double> BonusTypeA;
	void setBonusTypeA(std::vector<double> const& _BonusTypeA) { BonusTypeA = _BonusTypeA; }

	std::string BonusTypeBString;
	void setBonusTypeBString(std::string const& _BonusTypeBString) { BonusTypeBString = _BonusTypeBString; }

	std::vector<double> BonusTypeB;
	void setBonusTypeB(std::vector<double> const& _BonusTypeB) { BonusTypeB = _BonusTypeB; }
};

