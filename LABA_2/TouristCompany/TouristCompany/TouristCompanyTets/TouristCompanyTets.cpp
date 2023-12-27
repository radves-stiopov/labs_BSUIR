#include "pch.h"
#include "CppUnitTest.h"
#include "TouristCompany.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TouristCompanyTets
{
	TEST_CLASS(TouristCompanyTets)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TouristCompany company("1");
			company.AddCar("Honda", "Civic", 72, 110.f, 2014);
			Assert::AreEqual(company.GetCarByModel("Civic").GetYear(), company.GetCarByPower(72).GetYear());
		}
		TEST_METHOD(TestMethod2)
		{
			TouristCompany company("1");
			company.AddCar("Honda", "Civic", 72, 110.f, 2014);
			Car car = company.GetCarByModel("Civic");
			std::string expected = "Honda";
			Assert::AreEqual(expected, car.GetBrand());
		}
		TEST_METHOD(TestMethod3)
		{
			TouristCompany company("1");
			company.AddPromotionManger("Sanya", 20, "33");
			int expected = 20;
			Assert::AreEqual(expected, company.GetManagerAge());
		}
		TEST_METHOD(TestMethod4)
		{
			TouristCompany company("1");
			company.AddPromotionManger("Sanya", 20, "33");
			company.ChangeManagerName("Alex");
			std::string expected = "Alex";
			Assert::AreEqual(expected, company.GetManagerName());
		}
		TEST_METHOD(TestMethod5)
		{
			TouristCompany company("1");
			company.AddPromotionManger("Sanya", 20, "33");
			company.ChangeManagerPhoneNumber("32");
			std::string expected = "32";
			Assert::AreEqual(expected, company.GetManagerPhoneNumber());
		}
		TEST_METHOD(TestMethod6)
		{
			TouristCompany company("1");
			company.AddReview(4);
			company.AddReview(3);
			float expected = ((float)4 + 3) / 2;
			Assert::AreEqual(expected, company.GetAvgRevies());
		}
		TEST_METHOD(TestMethod7)
		{
			TouristCompany company("1");
			company.AddReview(4);
			company.AddReview(3);
			float expected = ((float)4 + 3) / 2;
			Assert::AreEqual(expected, company.GetAvgRevies());
		}
		TEST_METHOD(TestMethod8)
		{
			TouristCompany company("1");
			company.ChangeCurrentStatus("Sunny");
			std::string expected = "Sunny";
			Assert::AreEqual(expected, company.GetCurrentStatus());
		}
		TEST_METHOD(TestMethod9)
		{
			TouristCompany company("1");
			company.ChangeTemperature(10);
			int expected = 10;
			Assert::AreEqual(expected, company.GetTemperature());
		}
		TEST_METHOD(TestMethod10)
		{
			TouristCompany company("1");
			company.AddTour("New york", "10.12");
			Tour tour = company.GetTour("New york");
			std::string expected = "10.12";
			
			Assert::AreEqual(expected, tour.GetDate());
		}
		TEST_METHOD(TestMethod11)
		{
			TouristCompany company("1");
			company.AddTourist("Alex", "33", 18);
			Tourist alex = company.GetTourist("Alex");
			
			int expected = 18;

			Assert::AreEqual(expected, alex.GetAge());
		}
		TEST_METHOD(TestMethod12)
		{
			TouristCompany company("1");
			company.AddTourGuide("Leny", 19);
			TourGuide leny = company.GetTourGuide("Leny");

			int expected = 19;

			Assert::AreEqual(expected, leny.GetAge());
		}
	};
}
