#include "pch.h"
#include "CppUnitTest.h"
#include "../2AISTD_curs/Karp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace semestrprojecttest
{
	TEST_CLASS(semestrprojecttest)
	{
	public:

		TEST_METHOD(test)
		{
			Karp* t = new Karp();
			t->readList("input.txt");
			Assert::AreEqual(t->MaxFlow(), 1000);
		}
	};
}