#include "stdafx.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForMarkov
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			mystring first = "|*||";
			markov first_markov(first);
			AlgoritmMarkova(first_markov);
			Assert::IsTrue;
			system("pause");
		}

	};
}