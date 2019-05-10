#include "Skill.hpp"
#include<iostream>
#include<algorithm>
std::tuple<std::size_t, std::size_t> Skill::branch_range[Branch_size] = { std::make_tuple<std::size_t, std::size_t>(0,0) };

bool Skill::setBranch(std::string const& _Branch) {
	static std::size_t last_branch = 0;
	static std::size_t index = 0;

	const std::string branch_names[] = { "BranchRed","BranchYellow","BranchBlue","BranchGreen" }; //should be fetched elsewhere
	Branch = (BRANCH)0;
	const std::string* position = std::find(branch_names, branch_names + Branch_size, _Branch);
	if (branch_names>position || position >= branch_names + Branch_size) {
		std::cout << "BRANCH RANGE " << std::get<0>(branch_range[Branch]) << " " << std::get<1>(branch_range[Branch]) << "\n";
		return false;
	}
	std::size_t branch_t = (std::size_t) (branch_names - position);
	Branch = (BRANCH)branch_t;

	if (branch_t > last_branch) {
		std::get<0>(branch_range[branch_t]) = index;
	}
	std::get<1>(branch_range[branch_t]) = index + 1;

	++index;
	return true;
}
