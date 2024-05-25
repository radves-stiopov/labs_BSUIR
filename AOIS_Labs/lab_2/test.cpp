#include "pch.h"
#include "CppUnitTest.h"
#include "..\\l2\RPNEvaluator.h"
#include "..\\l2\Table.h"
#include "..\\l2\RPNFormer.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace l2Test
{
	TEST_CLASS(l2Test)
	{
	public:

		TEST_METHOD(FirstSDNF)
		{
			Table t("(y&!t)|t->c");
			std::string result = t.SDNF();
			std::string expected_result = "(!c&!t&!y) | (c&!t&!y) | (c&!t&y) | (c&t&!y) | (c&t&y) ";

			Assert::AreEqual(expected_result, result);
		}

		TEST_METHOD(FirstSKNF)
		{
			Table t("(y&!t)|t->c");
			std::string result = t.SKNF();
			std::string expected_result = "(c|t|!y) & (c|!t|y) & (c|!t|!y) ";

			Assert::AreEqual(expected_result, result);
		}

		TEST_METHOD(FirstForms) {
			Table t("(y&!t)|t->c");
			std::string result1 = t.DecimalFormConjunction();
			std::string result2 = t.DecimalFormDisjunction();
			std::string expected_result1 = "(1, 2, 3) and";
			std::string expected_result2 = "(0, 4, 5, 6, 7) or";

			Assert::AreEqual(expected_result1, result1);
			Assert::AreEqual(expected_result2, result2);
		}

		TEST_METHOD(FirstIndex) {
			Table t("(y&!t)|t->c");
			std::string result = t.IndexForm();
			std::string expected_result = "143: 10001111";

			Assert::AreEqual(expected_result, result);
		}


		TEST_METHOD(SecondSDNF)
		{
			Table t("b&r->!q");
			std::string result = t.SDNF();
			std::string expected_result = "(!b&!q&!r) | (!b&!q&r) | (!b&q&!r) | (!b&q&r) | (b&!q&!r) | (b&!q&r) | (b&q&!r) ";

			Assert::AreEqual(expected_result, result);
		}

		TEST_METHOD(SecondSKNF)
		{
			Table t("b&r->!q");
			std::string result = t.SKNF();
			std::string expected_result = "(!b|!q|!r) ";

			Assert::AreEqual(expected_result, result);
		}

		TEST_METHOD(SecondForms) {
			Table t("b&r->!q");
			std::string result1 = t.DecimalFormConjunction();
			std::string result2 = t.DecimalFormDisjunction();
			std::string expected_result1 = "(7) and";
			std::string expected_result2 = "(0, 1, 2, 3, 4, 5, 6) or";

			Assert::AreEqual(expected_result1, result1);
			Assert::AreEqual(expected_result2, result2);
		}

		TEST_METHOD(SecondIndex) {
			Table t("b&r->!q");
			std::string result = t.IndexForm();
			std::string expected_result = "254: 11111110";

			Assert::AreEqual(expected_result, result);
		}
	};
}

