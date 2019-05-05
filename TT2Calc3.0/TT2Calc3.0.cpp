#include <iostream>
#include"Build.hpp"
#include"BuildImplementations.h"















int main()
{
	Constants::initExpos();

	Expression<double, TapDMG, AllDMG> test;
	test.add(TapDMG(4)).add(AllDMG(2));
	std::cout << test.getDamage(tt2::SC, 2) << "\n";

	Expression<double, TapDMG, AllDMG, HeroDMG> test2;
	(test2 += TapDMG(3)) += HeroDMG(1);
	std::cout << test2.getDamage(tt2::SC, 2) << "\n";

	Expression<double, TapDMG, AllDMG, HeroDMG, Linear, Invert> Exp;
	decltype(Exp) test3;
	test3=Exp+TapDMG(1)+AllDMG(1)+HeroDMG(5)+Linear(0);
	std::cout << test3.getDamage(tt2::SC, 2) << "\n";

}
