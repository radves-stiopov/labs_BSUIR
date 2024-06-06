#include "pch.h"
#include "CppUnitTest.h"
#include "..//lb6/HashTable.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTest
{
	TEST_CLASS(HashTableTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable ht;
			ht.Insert("first", "1");
			Assert::AreEqual(std::string("1"), ht.Get("first"));
		}

		TEST_METHOD(TestMethod2)
		{
			HashTable ht;
			ht.Insert("first", "1");
			ht.Update("first", "not first");
			Assert::AreEqual(std::string("not first"), ht.Get("first"));
		}

		TEST_METHOD(TestMethod3)
		{
			HashTable ht;
			ht.Insert("first", "1");
			ht.Delete("first");
			std::string result;
			try {
				result = ht.Get("first");
			}
			catch (std::exception& ex) {
				result = "error";
			}
			Assert::AreEqual(std::string("error"), result);
		}

		TEST_METHOD(TestMethod4)
		{
			HashTable ht;
			ht.Insert("first", "1");
			
			std::string result;
			try {
				ht.Insert("first", "not first");
			}
			catch (std::exception& ex) {
				result = "error";
			}
			Assert::AreEqual(std::string("error"), result);
		}

		TEST_METHOD(TestMethod5)
		{
			HashTable ht;
			for (int i = 0; i < 50; i++) {
				ht.Insert(std::to_string(i), "+");
			}

			std::string result = ht.Get("25");
			Assert::AreEqual(std::string("+"), result);
		}
	};
}
