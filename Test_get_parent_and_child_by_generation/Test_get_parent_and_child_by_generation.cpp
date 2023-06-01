#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testgetparentandchildbygeneration
{
	TEST_CLASS(Testgetparentandchildbygeneration)
	{
	public:
		
		TEST_METHOD(DefaultTest)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3/><aab3 kinship_degree=\"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();
			xml_node<>* node = root->first_node()->last_node();

			auto [parent, banned_child] = get_parent_and_child_by_generation(node, nullptr, 2);

			Assert::AreEqual(root->name(), parent->name());
			Assert::AreEqual(root->first_node()->name(), banned_child->name());
		}

		TEST_METHOD(GenerationIs0)
		{
			xml_document<> doc;
			string xml = "<a/>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			auto [parent, banned_child] = get_parent_and_child_by_generation(root, nullptr, 0);

			Assert::AreEqual(root->name(), parent->name());
			Assert::IsNull(banned_child);
		}

		TEST_METHOD(GenerationHeigherThenNodeLevel)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3/><aab3 kinship_degree=\"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();
			xml_node<>* node = root->first_node()->last_node();

			try
			{
				auto [parent, banned_child] = get_parent_and_child_by_generation(root, nullptr, 3);
			}
			catch (runtime_error ex)
			{

			}
		}
	};
}
