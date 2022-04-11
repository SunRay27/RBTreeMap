#include "CppUnitTest.h"
#include "../RBTreeMap/RBTree.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RBTreeMapTests
{
	TEST_CLASS(RBTreeMapTests)
	{
	public:
		TEST_METHOD(TestFindInsert)
		{
			Map<int, int> map;

			for (size_t i = 0; i < 15; i++)
				map.Insert(i, i * 5712);

			Assert::IsTrue(map.GetKeys().GetSize());

			for (size_t i = 0; i < 15; i++)
				Assert::IsTrue(map.Find(i) == i * 5712);

			try
			{
				map.Insert(1, 5712);
				Assert::Fail();
			}
			catch (invalid_argument e)
			{
				return;
			}

			Assert::Fail();
		}

		TEST_METHOD(TestRemove)
		{
			Map<int, int> map;

			for (size_t i = 0; i < 150; i++)
				map.Insert(i, i);

			for (size_t i = 0; i < 15; i++)
				map.Remove(i);

			Assert::IsTrue(map.GetKeys().GetSize() == 135);

			for (size_t i = 0; i < 15; i++)
				Assert::IsTrue(!map.GetKeys().Contains(i));

			try
			{
				map.Remove(5);
				Assert::Fail();
			}
			catch (invalid_argument e)
			{
				return;
			}

			Assert::Fail();
		}
		TEST_METHOD(TestClear)
		{
			Map<int, string> map;
			map.Insert(5, "first");
			map.Insert(3, "second");
			map.Insert(7, "third");
			map.Clear();

			Assert::IsTrue(map.GetKeys().IsEmpty());
		}
		TEST_METHOD(TestGetKeys)
		{
			Map<int, string> map;
			map.Insert(5, "first");
			map.Insert(3, "second");
			map.Insert(7, "third");
			map.Insert(9, "fourth");
			map.Insert(15, "fifth");


			List<int> keys = map.GetKeys();

			Assert::IsTrue(keys.GetSize() == 5);
			Assert::IsTrue(map.Find(5) == "first");
			Assert::IsTrue(map.Find(3) == "second");
			Assert::IsTrue(map.Find(7) == "third");
			Assert::IsTrue(map.Find(9) == "fourth");
			Assert::IsTrue(map.Find(15) == "fifth");
		}
		TEST_METHOD(TestGetValues)
		{
			Map<int, string> map;
			map.Insert(5, "first");
			map.Insert(3, "second");
			map.Insert(7, "third");
			map.Insert(9, "fourth");
			map.Insert(15, "fifth");

			List<int> keys = map.GetKeys();
			List<string> values = map.GetValues();

			for (size_t i = 0; i < keys.GetSize(); i++)
				if (map.Find(keys[i]) != values[i])
					Assert::Fail();
		}

		TEST_METHOD(TestKeyExistsException)
		{
			Map<int, string> map;
			map.Insert(5, "first");
			map.Insert(3, "second");
			map.Insert(7, "third");
			map.Insert(9, "fourth");
			map.Insert(15, "fifth");

			try
			{
				string valueByKey = map.Find(1);
				Assert::Fail();
			}
			catch (invalid_argument e)
			{
				try
				{
					map.Insert(5, "second_first");
					Assert::Fail();
				}
				catch (invalid_argument e2)
				{

				}
			}
		}
	};
}
