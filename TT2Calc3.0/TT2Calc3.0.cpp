#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"

int main()
{
	tt2::initExpos();

	Expression<double, TapDMG, AllDMG> test;
	test.add(TapDMG(4)).add(AllDMG(2));
	std::cout << test.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n";

	Expression<double, TapDMG, AllDMG, AllHeroDMG> test2;
	(test2 += TapDMG(3)) += AllHeroDMG(1);
	std::cout << test2.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n";

	Expression<double, TapDMG, AllDMG, AllHeroDMG> Exp;
	auto test3 = Exp + TapDMG(1) + AllDMG(1) + AllHeroDMG(5);
	std::cout << test3.getDamage(tt2::SC, 2, 0, tt2::PHOMGOLD) << "\n\n\n\n";

	std::string skilltree_csv = "SkillTreeInfo2.0.csv";
	if (tt2::loadSkillTreeCSV(skilltree_csv)) {
		std::cout << skilltree_csv << " loaded successfully\n";
	}
	else {
		std::cout << skilltree_csv << " couldn't be loaded\n";
		return 1;
	}
	Preprocessor preprocessor(0,1);
}

//TODO in buildimplementations: add way to make a skill add 0 damage: example lightning burst which is useless for pushing