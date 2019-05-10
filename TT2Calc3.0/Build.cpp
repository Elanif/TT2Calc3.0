#include "Build.hpp"

vtype Build::getValue() const
{
	vtype result = 1;
	for (std::size_t i = 0; i < last_leveled_skill; ++i)
		result *= d[i].getCurrentEffect();
	return result;
}

ctype Build::getCost() const
{
	ctype result = 0;
	for (std::size_t i = 0; i < last_leveled_skill; ++i)
		result += d[i].getCurrentCost();
	return result;
}

bool Build::unlocked(std::size_t const& skill_index) const
{
	return d[skill_index].unlocked(d);
}

ctype Build::gettingTo(std::size_t const& skill_index) const
{
	return d[skill_index].gettingTo(d);
}

bool Build::operator<=(Build const&) const
{
	return false;
}

bool Build::operator==(Build const& build) const
{
	for (std::size_t i = 0; i < d.size(); ++i)
		if (this->d[i].level != build.d[i].level) return false;
	return true;
}

bool Build::lessequal(Build const& build1, Build const& build2)
{
	if (build1.getValue()>build2.getValue()) return false;
	const Skill& last_skill = build1.d[build1.last_leveled_skill+1].skill;
	std::size_t block_end = std::get<1>(last_skill.branch_range[last_skill.Branch]);
	for (std::size_t i = build1.last_leveled_skill + 1; i < block_end; ++i) {
		if (build1.unlocked(i)) {
			if (!build2.unlocked(i)) return false;
		}
		else if (build1.gettingTo(i) < build2.gettingTo(i)) return false;
	}
	return true;
}
