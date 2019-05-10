#pragma once
#include"BuildImplementations.hpp"
#include"tt2.hpp"
#include"SkillContainer.hpp"

class Preprocessor
{
protected:

public:
	static void preprocess(std::size_t const& build, std::size_t const& gold, std::vector<Zero>& SkillPowers);
	static std::vector<SkillContainer> getSkillContainer();
};

