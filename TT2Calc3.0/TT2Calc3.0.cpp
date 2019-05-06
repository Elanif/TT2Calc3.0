#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.hpp"
#include"Preprocessor.hpp"

int main()
{
	tt2::initExpos();

	Expression<double, TapDMG, AllDMG> test;
	test.add(TapDMG(4)).add(AllDMG(2));
	std::cout << test.getDamage(tt2::SC, 2) << "\n";

	Expression<double, TapDMG, AllDMG, HeroDMG> test2;
	(test2 += TapDMG(3)) += HeroDMG(1);
	std::cout << test2.getDamage(tt2::SC, 2) << "\n";

	Expression<double, TapDMG, AllDMG, HeroDMG> Exp;
	decltype(Exp) test3;
	test3 = Exp + TapDMG(1) + AllDMG(1) + HeroDMG(5);
	std::cout << test3.getDamage(tt2::SC, 2) << "\n\n\n\n";

	std::string skilltree_csv = "SkillTreeInfo2.0.csv";
	if (tt2::loadSkillTreeCSV(skilltree_csv)) {
		std::cout << skilltree_csv << " loaded successfully\n";
	}
	else {
		std::cout << skilltree_csv << " couldn't be loaded\n";
		return 1;
	}
	Preprocessor preprocessor(0);
}
