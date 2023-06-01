#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testgetchildrenatthegeneration
{
	TEST_CLASS(Testgetchildrenatthegeneration)
	{
	public:
		
		TEST_METHOD(DefaultTest)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3/></aa2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();
			vector<xml_node<>*> cousins;
			get_children_at_generation(root, 2, cousins);
			Assert::AreEqual("aaa3", cousins[0]->name());
		}

		TEST_METHOD(GenerationHigherThenTreeDeep)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3/></aa2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();
			vector<xml_node<>*> cousins;
			get_children_at_generation(root, 3, cousins);
			Assert::IsTrue(0 == cousins.size());
		}

		TEST_METHOD(CousinsOnRight)
		{
			xml_document<> doc;
			string xml = "<a1><aa2></aa2><ab2><aba3/><aab3/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();
			vector<xml_node<>*> cousins;
			get_children_at_generation(root, 2, cousins);
			Assert::AreEqual("aba3", cousins[0]->name());
			Assert::AreEqual("aab3", cousins[1]->name());
		}
	};
}
