#include "pch.h"
#include "CppUnitTest.h"
#include "..\\lb3\Methods.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lb3Test
{
	TEST_CLASS(lb3Test)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string result = MinimizeSDNFChisl("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(b&c)|(a)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod2)
		{
			std::string result = MinimizeSDNFTable("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(b&c)|(a)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod3)
		{
			std::string result = MinimizeSDNFKarno("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(a)|(b&c)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod4)
		{
			std::string result = MinimizeSKNFChisl("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(a|b)&(a|c)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod5)
		{
			std::string result = MinimizeSKNFTable("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(a|b)&(a|c)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod6)
		{
			std::string result = MinimizeSKNFKarno("(!a&b&c)|(a&!b&!c)|(a&!b&c)|(a&b&!c)|(a&b&c)");
			std::string expected = "(a|b)&(a|c)";
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TestMethod7)
		{
			std::string result = MinimizeSDNFChisl("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(d)|(b)|(a)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod8)
		{
			std::string result = MinimizeSDNFTable("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(d)|(b)|(a)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod9)
		{
			std::string result = MinimizeSDNFKarno("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(d)|(b)|(a)";
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TestMethod10)
		{
			std::string result = MinimizeSKNFChisl("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(a|b|d)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod11)
		{
			std::string result = MinimizeSKNFTable("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(a|b|d)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod12)
		{
			std::string result = MinimizeSKNFKarno("(!a&!b&!c&d)|(!a&!b&c&d)|(!a&b&!c&!d)|(!a&b&!c&d)|(!a&b&c&!d)|(!a&b&c&d)|(a&!b&!c&!d)|(a&!b&!c&d)|(a&!b&c&!d)|(a&!b&c&d)|(a&b&!c&!d)|(a&b&!c&d)|(a&b&c&!d)|(a&b&c&d)");
			std::string expected = "(a|b|d)";
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TestMethod13)
		{
			std::string result = MinimizeSKNFChisl("a|b&c->d|e");
			std::string expected = "(!c|!b|d|e)&(!a|d|e)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod14)
		{
			std::string result = MinimizeSKNFTable("a|b&c->d|e");
			std::string expected = "(!c|!b|d|e)&(!a|d|e)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod15)
		{
			std::string result = MinimizeSKNFKarno("a|b&c->d");
			std::string expected = "(!a|d)&(!b|!c|d)";
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TestMethod16)
		{
			std::string result = MinimizeSDNFChisl("a|b&c->d|e");
			std::string expected = "(!b&!a)|(!c&!a)|(e)|(d)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod17)
		{
			std::string result = MinimizeSDNFTable("a|b&c->d|e");
			std::string expected = "(!b&!a)|(!c&!a)|(e)|(d)";
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(TestMethod18)
		{
			std::string result = MinimizeSDNFKarno("a|b&c->d");
			std::string expected = "(d)|(!a&!c)|(!a&!b)";
			Assert::AreEqual(expected, result);
		}
	};
}
