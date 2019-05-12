#pragma once
#include"BuildImplementations.hpp"
#include"tt2.hpp"
#include"SkillContainer.hpp"
#include<string>
#include<vector>
#include<tuple>

class Preprocessor
{
protected:

public:
	static std::vector<std::tuple<std::size_t, std::size_t > > init(tt2::BUILDS build, tt2::GOLDTYPES gold);
	static std::string getStringBuildAndInit(tt2::BUILDS build, tt2::GOLDTYPES gold);
	static void preprocess(std::size_t const& build, std::size_t const& gold, std::vector<Zero>& SkillPowers);
	static std::vector<SkillContainer> getSkillContainer();
};

