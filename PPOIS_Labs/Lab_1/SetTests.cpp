#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_ppois/Set.h"	

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyTests
{
	TEST_CLASS(Set_test)
	{
	public:
		
		TEST_METHOD(Set_Test_1)
		{
			Set set; // ������� ������ ������ Set
			Assert::IsTrue(set.empty()); // ���������, ��� ��������� ������
		}
		TEST_METHOD(Set_Test_2)
		{
			Set set;
			set.add(42);

			// ���������, ��� ������� ��� �������� � ���������
			Assert::AreEqual(1, static_cast<int>(set.size()));
		}
		TEST_METHOD(Set_Test_3)
		{
			Set set;
			set.add(42);
			set.add(73);

			// ������� ������� �� ���������
			set.remove(42);

			// ���������, ��� ������� ������
			Assert::AreEqual(1, static_cast<int>(set.size()));
		}
		TEST_METHOD(Set_Test_4)
		{
			Set set;

			// ���������, ��� ������ ��������� ���������� ����� �������� ��������
			Assert::AreEqual(0, set.size());
		}
		TEST_METHOD(Set_Test_5)
		{
			Set set;
			set.add(42);

			// ���������, ��� ��������� �������� ����������� ��������
			Assert::IsTrue(set.contains(42));
		}
		TEST_METHOD(Set_Test_6)
		{
			Set set;
			set.add(42);
			set.add(73);

			// ���������, ��� ���������� ���������� false ��� ��������������� ��������
			Assert::IsFalse(set[99]);
		}
		TEST_METHOD(Set_Test_7)
		{
			Set set1;
			set1.add(42);
			set1.add(73);

			Set set2;
			set2.add(73);
			set2.add(99);

			Set result = set1 + set2;

			// ���������, ��� ����������� ���� �������� �������� ��� ���������� ��������
			Assert::IsTrue(result.contains(42));
			Assert::IsTrue(result.contains(73));
			Assert::IsTrue(result.contains(99));
			Assert::AreEqual(3, result.size());
		}
		TEST_METHOD(Set_Test_8)
		{
			Set set1;
			Set set2;
			set2.add(42);
			set2.add(73);

			set1 += set2;

			// ���������, ��� ����������� � ������������� ������� ��������� � �������� ���������� ����� ��������� ���������
			Assert::IsTrue(set1.contains(42));
			Assert::IsTrue(set1.contains(73));
			Assert::AreEqual(2, set1.size());
		}
		TEST_METHOD(Set_Test_9)
		{
			Set set1;
			set1.add(42);
			set1.add(73);
			set1.add(99);

			Set set2;
			set2.add(73);
			set2.add(99);
			set2.add(123);

			Set result = set1 * set2;

			// ���������, ��� ��������� �������� ������ ����� �������� �� ����� ��������
			Assert::IsTrue(result.contains(73));
			Assert::IsTrue(result.contains(99));
			Assert::AreEqual(2, result.size());
		}
		TEST_METHOD(Set_Test_10)
		{
			Set set1;
			Set set2;
			set2.add(42);
			set2.add(73);

			set1 *= set2;

			// ���������, ��� set1 �������� ������, ��� ��� ��� ����� ��������� � ������ ��������� � �������� ����������
			Assert::IsTrue(set1.empty());
		}
		TEST_METHOD(Set_Test_11)
		{
			Set set1;
			set1.add(42);
			set1.add(73);
			set1.add(99);

			Set set2;
			set2.add(73);
			set2.add(99);
			set2.add(100);

			Set result = set1 - set2;

			// ���������, ��� result �������� ������ �� ��������, ������� ���� � set1, �� �� � set2
			Assert::IsTrue(result.contains(42));
			Assert::AreEqual(1, result.size());
		}
		TEST_METHOD(Set_Test_12)
		{
			Set set1;
			set1.add(42);
			set1.add(73);
			set1.add(99);

			Set set2;
			set2.add(73);
			set2.add(99);
			set2.add(101);

			set1 -= set2;

			// ���������, ��� set1 ������ �������� ������ �� ��������, ������� ���� � set1, �� �� � set2
			Assert::IsTrue(set1.contains(42));
			Assert::AreEqual(1, set1.size());
		}
		TEST_METHOD(Set_Test_13)
		{
			Set set;
			set.add(1);
			set.add(2);

			Set result = set.boolean();

			// ���������, ��� ��������� �������� ��� ��������� ����� ��������� �� ��������� ���������
			Assert::IsTrue(result.contains(0));
			Assert::IsTrue(result.contains(1));
			Assert::IsTrue(result.contains(2));
			Assert::IsTrue(result.contains(3));
			Assert::IsTrue(result.size() == 4); // 2^n ��������� � ����������, ��� n - ���������� ��������� � �������� ���������
		}
	};
}
