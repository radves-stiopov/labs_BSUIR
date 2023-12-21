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
			Set set; // создаем объект класса Set
			Assert::IsTrue(set.empty()); // проверяем, что множество пустое
		}
		TEST_METHOD(Set_Test_2)
		{
			Set set;
			set.add(42);

			// Проверяем, что элемент был добавлен в множество
			Assert::AreEqual(1, static_cast<int>(set.size()));
		}
		TEST_METHOD(Set_Test_3)
		{
			Set set;
			set.add(42);
			set.add(73);

			// Удаляем элемент из множества
			set.remove(42);

			// Проверяем, что элемент удален
			Assert::AreEqual(1, static_cast<int>(set.size()));
		}
		TEST_METHOD(Set_Test_4)
		{
			Set set;

			// Проверяем, что размер множества уменьшился после удаления элемента
			Assert::AreEqual(0, set.size());
		}
		TEST_METHOD(Set_Test_5)
		{
			Set set;
			set.add(42);

			// Проверяем, что множество содержит добавленные элементы
			Assert::IsTrue(set.contains(42));
		}
		TEST_METHOD(Set_Test_6)
		{
			Set set;
			set.add(42);
			set.add(73);

			// Проверяем, что индексация возвращает false для несуществующего элемента
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

			// Проверяем, что объединение двух множеств содержит все уникальные элементы
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

			// Проверяем, что объединение с присваиванием пустого множества с непустым множеством равно непустому множеству
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

			// Проверяем, что результат содержит только общие элементы из обоих множеств
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

			// Проверяем, что set1 остается пустым, так как нет общих элементов в пустом множестве с непустым множеством
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

			// Проверяем, что result содержит только те элементы, которые есть в set1, но не в set2
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

			// Проверяем, что set1 теперь содержит только те элементы, которые есть в set1, но не в set2
			Assert::IsTrue(set1.contains(42));
			Assert::AreEqual(1, set1.size());
		}
		TEST_METHOD(Set_Test_13)
		{
			Set set;
			set.add(1);
			set.add(2);

			Set result = set.boolean();

			// Проверяем, что результат содержит все возможные суммы элементов из исходного множества
			Assert::IsTrue(result.contains(0));
			Assert::IsTrue(result.contains(1));
			Assert::IsTrue(result.contains(2));
			Assert::IsTrue(result.contains(3));
			Assert::IsTrue(result.size() == 4); // 2^n элементов в результате, где n - количество элементов в исходном множестве
		}
	};
}
