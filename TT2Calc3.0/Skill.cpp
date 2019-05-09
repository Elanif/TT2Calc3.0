#include "Skill.hpp"
#include<iostream>
std::tuple<std::size_t, std::size_t> Skill::branch_range[Branch_size] = { std::make_tuple<std::size_t, std::size_t>(0,0) };

bool Skill::setBranch(std::string const& _Branch) {
	static std::size_t last_branch = 0;
	const std::string branch_names[] = { "BranchRed","BranchYellow","BranchBlue","BranchGreen" };
	Branch = (BRANCH)0;
	bool trovato = true;
	while (branch_names[Branch] != _Branch) {
		Branch = (BRANCH)((std::size_t) Branch + 1);
		if ((std::size_t) Branch >= Branch_size) {
			Branch = (BRANCH)0;
			trovato = false;
		}
	}
	if (trovato) { //TODO FIX
		std::size_t branch_t = (std::size_t)Branch;
		std::get<1>(branch_range[last_branch]) = index - 1; //was inside the if, but then it doesnt update for the last element of the last branch
		if (branch_t > last_branch) {
			if (branch_t < Branch_size) std::get<0>(branch_range[branch_t]) = index;
		}
		last_branch = branch_t;
	}
	std::cout << "BRANCH RANGE " << std::get<0>(branch_range[Branch]) << " "<< std::get<1>(branch_range[Branch])<<"\n";
	return trovato;
}
