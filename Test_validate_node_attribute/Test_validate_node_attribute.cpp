#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testvalidatenodeattribute
{
	TEST_CLASS(Testvalidatenodeattribute)
	{
	public:
		
		TEST_METHOD(DefaultTest)
		{
			xml_document<> doc;
			string xml = "<b kinship_degree=\"2\"/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			unsigned int exp_result = 2;
			unsigned int result = validate_node_attribute(root, "kinship_degree");
			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(NodeIsNull)
		{
			try
			{
				unsigned int result = validate_node_attribute(NULL, "attribute");
				Assert::Fail(L"Ожидаемое исключение не было выброшено");
			}
			catch (KinshipDegreeException ex)
			{
				Assert::IsTrue(ex.what() == "Степень родства не указана");
			}
			
		}

		TEST_METHOD(NoAttribute)
		{
			xml_document<> doc;
			string xml = "<b/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			try
			{
				unsigned int result = validate_node_attribute(root, "attribute");
				Assert::Fail(L"Ожидаемое исключение не было выброшено");
			}
			catch (KinshipDegreeException ex)
			{
				Assert::IsTrue(ex.what() == "Степень родства не указана");
			}
		}

		TEST_METHOD(AttributeOnFirstPlace)
		{
			xml_document<> doc;
			string xml = "<b kinship_degree=\"2\"/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			unsigned int exp_result = 2;
			unsigned int result = validate_node_attribute(root, "kinship_degree");
			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(AttributeOnSecondPlace)
		{
			xml_document<> doc;
			string xml = "<b attribute=\"3\" kinship_degree=\"2\"/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			unsigned int exp_result = 2;
			unsigned int result = validate_node_attribute(root, "kinship_degree");
			Assert::AreEqual(exp_result, result);
		}

		TEST_METHOD(NotUIntValue)
		{
			xml_document<> doc;
			string xml = "<b kinship_degree=\"0\"/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			try
			{
				unsigned int result = validate_node_attribute(root, "kinship_degree");
				Assert::Fail(L"Ожидаемое исключение не было выброшено");
			}
			catch (KinshipDegreeException ex)
			{
				Assert::IsTrue(ex.what() == "Степень родства не является натуральным числом");
			}
		}
	};
}
