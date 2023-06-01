#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testgetcousins
{
	TEST_CLASS(Testgetcousins)
	{
	public:
		
		TEST_METHOD(DefaultTest)
		{
			string xml = "<a><b kinship_degree = \"1\"/><c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("c", cousins[0]->name());
		}

		TEST_METHOD(EmptyString)
		{
			string xml = "<a><b kinship_degree = \"1\"/>\n<c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("c", cousins[0]->name());
		}

		TEST_METHOD(NoKinshipDegreeTest)
		{
			string xml = "<a><b attribute = \"1\"/><c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			try
			{
				get_cousins(&doc, &cousins);
			}
			catch (KinshipDegreeException ex)
			{
				Assert::IsTrue("Степень родства не указана" == ex.what());
			}
		}

		TEST_METHOD(KinshipDegreeOnSecondPlace)
		{
			string xml = "<a><b attribute = \"1\" kinship_degree = \"1\"/><c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("c", cousins[0]->name());
		}

		TEST_METHOD(FoundedNodeOnLeft)
		{
			string xml = "<a1><aa2><aab3 kinship_degree = \"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("aba3", cousins[0]->name());
			Assert::AreEqual("abb3", cousins[1]->name());
		}

		TEST_METHOD(FoundedNodeOnRight)
		{
			string xml = "<a1><aa2><abb3/></aa2><ab2><aba3/><aab3 kinship_degree = \"2\"/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("abb3", cousins[0]->name());
		}

		TEST_METHOD(FoundedNodeOnAnyPlace)
		{
			string xml = "<a1><aa2><aaa3/><aab3 kinship_degree = \"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("aba3", cousins[0]->name());
			Assert::AreEqual("abb3", cousins[1]->name());
		}

		TEST_METHOD(KinshipDegreeIsNotNaturalNumber)
		{
			string xml = "<a><b kinship_degree = \"0\"/><c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			try
			{
				get_cousins(&doc, &cousins);
			}
			catch (KinshipDegreeException ex)
			{
				Assert::IsTrue("Степень родства не является натуральным числом" == ex.what());
			}
		}

		TEST_METHOD(KinshipDegreeHigherThenTreeDepth)
		{
			string xml = "<a><b kinship_degree = \"2\"/><c/></a>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			try
			{
				get_cousins(&doc, &cousins);
			}
			catch (runtime_error ex)
			{
				Assert::IsTrue("Степень родства больше текущего поколения" == ex.what());
			}
		}

		TEST_METHOD(CousinsOnRightSide)
		{
			string xml = "<a1><aa2><aab3 kinship_degree = \"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("aba3", cousins[0]->name());
			Assert::AreEqual("abb3", cousins[1]->name());
		}

		TEST_METHOD(CousinsOnLeftSide)
		{
			string xml = "<a1><aa2><abb3/></aa2><ab2><aba3/><aab3 kinship_degree = \"2\"/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("abb3", cousins[0]->name());
		}

		TEST_METHOD(CousinsOnAnyPlace)
		{
			string xml = "<a1><aa2><aaa3/><aab3 kinship_degree = \"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			xml_document<> doc;
			doc.parse<0>((char*)xml.c_str());
			vector<xml_node<>*> cousins;

			get_cousins(&doc, &cousins);

			Assert::AreEqual("aba3", cousins[0]->name());
			Assert::AreEqual("abb3", cousins[1]->name());
		}
	};
}
