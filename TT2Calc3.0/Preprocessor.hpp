#pragma once
#include"BuildImplementations.hpp"
#include"tt2.hpp"
#include"SkillContainer.hpp"

class Preprocessor
{
protected:

public:
	Preprocessor(std::size_t const& build, std::size_t const& gold, std::vector<Zero>& SkillPowers);

	std::vector<ctype> skillMaxLevel;

	std::vector<std::vector<ctype> > skillCost;

	std::vector<std::vector<vtype> > skillEffect;

	std::vector<SkillContainer> getSkillContainer();
};

