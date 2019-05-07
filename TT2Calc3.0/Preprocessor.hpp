#pragma once
#include"BuildImplementations.hpp"
#include"tt2.hpp"

class Preprocessor
{
public:
	Preprocessor(std::size_t const& build, std::size_t const& gold);

	std::vector<unsigned int> skillMaxLevel;

	std::vector<std::vector<unsigned int> > skillCost;

	std::vector<std::vector<double> > skillEffect;
};

