#include "pch.h"
#include "CppUnitTest.h"
#include "Floats.h"
#include "DirectCode.h"
#include "ReverseCode.h"
#include "SupplementaryCode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aoisL1Test
{
	TEST_CLASS(aoisL1Test)
	{
	public:
		
		TEST_METHOD(DirectCodeTest)
		{
			DirectCode dc(127);
			std::string expectedString = "0000000001111111";
			float expectedNumber = 127.f;

			Assert::AreEqual(expectedString, dc.String());
			Assert::AreEqual(expectedNumber, dc.Number());
		}

		TEST_METHOD(ReverseCodeTest)
		{
			ReverseCode rc(127);
			std::string expectedString = "0000000001111111";
			short expectedNumber = 127;

			Assert::AreEqual(expectedString, rc.String());
			Assert::AreEqual(expectedNumber, rc.Number());
		}

		TEST_METHOD(SupplementaryCodeTest)
		{
			SupplementaryCode sc(127);
			std::string expectedString = "0000000001111111";
			short expectedNumber = 127;

			Assert::AreEqual(expectedString, sc.String());
			Assert::AreEqual(expectedNumber, sc.Number());
		}

		TEST_METHOD(NegativeDirectCodeTest)
		{
			DirectCode dc(-127);
			std::string expectedString = "1000000001111111";
			float expectedNumber = -127.f;

			Assert::AreEqual(expectedString, dc.String());
			Assert::AreEqual(expectedNumber, dc.Number());
		}

		TEST_METHOD(NegativeReverseCodeTest)
		{
			ReverseCode rc(-127);
			std::string expectedString = "1111111110000000";
			short expectedNumber = -127;

			Assert::AreEqual(expectedString, rc.String());
			Assert::AreEqual(expectedNumber, rc.Number());
		}

		TEST_METHOD(NegativeSupplementaryCodeTest)
		{
			SupplementaryCode sc(-127);
			std::string expectedString = "1111111110000001";
			short expectedNumber = -127;

			Assert::AreEqual(expectedString, sc.String());
			Assert::AreEqual(expectedNumber, sc.Number());
		}

		TEST_METHOD(SumTest1) {
			SupplementaryCode sc1(71);
			SupplementaryCode sc2(93);

			SupplementaryCode result = sc1 + sc2;
			std::string expectedString = "0000000010100100";
			short expectedNumber = 164;

			Assert::AreEqual(expectedString, result.String());
			Assert::AreEqual(expectedNumber, result.Number());
		}

		TEST_METHOD(SumTest2) {
			SupplementaryCode sc1(76);
			SupplementaryCode sc2(17);

			SupplementaryCode result = sc1 + sc2;
			std::string expectedString = "0000000001011101";
			short expectedNumber = 93;

			Assert::AreEqual(expectedString, result.String());
			Assert::AreEqual(expectedNumber, result.Number());
		}

		TEST_METHOD(SubtractTest1) {
			SupplementaryCode sc1(71);
			SupplementaryCode sc2(93);

			SupplementaryCode result = sc1 - sc2;
			std::string expectedString = "1111111111101010";
			short expectedNumber = -22;

			Assert::AreEqual(expectedString, result.String());
			Assert::AreEqual(expectedNumber, result.Number());
		}

		TEST_METHOD(SubtractTest2) {
			SupplementaryCode sc1(76);
			SupplementaryCode sc2(-17);

			SupplementaryCode result = sc1 - sc2;
			std::string expectedString = "0000000001011101";
			short expectedNumber = 93;

			Assert::AreEqual(expectedString, result.String());
			Assert::AreEqual(expectedNumber, result.Number());
		}

		TEST_METHOD(MultiplicationTest1)
		{
			DirectCode dc1(17);
			DirectCode dc2(-83);
			std::string expectedString = "1000010110000011";
			float expectedNumber = -1411,f;

			DirectCode result = dc1 * dc2;

			Assert::AreEqual(expectedNumber, result.Number());
			Assert::AreEqual(expectedString, result.String());
		}

		TEST_METHOD(MultiplicationTest2)
		{
			DirectCode dc1(3);
			DirectCode dc2(173);
			std::string expectedString = "0000001000000111";
			float expectedNumber = 519.f;

			DirectCode result = dc1 * dc2;

			Assert::AreEqual(expectedNumber, result.Number());
			Assert::AreEqual(expectedString, result.String());
		}

		TEST_METHOD(DivisionTest1) {
			DirectCode dc1(13);
			DirectCode dc2(8);
			std::string expectedString = "000000000000000110100";
			float expectedNumber = 1.625f;

			DirectCode result = dc1 / dc2;

			Assert::AreEqual(expectedNumber, result.Number());
			Assert::AreEqual(expectedString, result.String());
		}

		TEST_METHOD(DivisionTest2) {
			DirectCode dc1(75);
			DirectCode dc2(15);
			std::string expectedString = "000000000000010100000";
			float expectedNumber = 5.f;

			DirectCode result = dc1 / dc2;

			Assert::AreEqual(expectedNumber, result.Number());
			Assert::AreEqual(expectedString, result.String());
		}

		TEST_METHOD(FloatsCheck) {
			Floats fl(3.4f);
			Floats fl1(0.4f);
			Floats fl2(1000.00114f);
			Floats fl3(34000.f);
			std::string expectedStr1 = "01000000011100110011001100110011";
			std::string expectedStr2 = "01000100011110101101100110101100";
			std::string expectedStr3 = "01000111000001001101001101100110";
			float expectedNumber1 = 3.8f;
			float expectedNumber2 = 1003.4f;
			float expectedNumber3 = 34003.4f;

			Assert::AreEqual(expectedStr1, (fl + fl1).String());
			Assert::AreEqual(expectedNumber1, (fl + fl1).Number());
			Assert::AreEqual(expectedStr2, (fl2 + fl).String());
			Assert::IsTrue(fabs((fl2 + fl).Number() - expectedNumber2) < 0.01f);
			Assert::AreEqual(expectedStr3, (fl3 + fl).String());
			Assert::AreEqual(expectedNumber3, (fl3 + fl).Number());
		}
	};
}
