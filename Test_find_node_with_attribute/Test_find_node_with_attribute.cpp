#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testfindnodewithattribute
{
	TEST_CLASS(Testfindnodewithattribute)
	{
	public:
		TEST_METHOD(DefaultTest)
		{
			xml_document<> doc;
			string xml = "<a><b kinship_degree=\"2\"/></a>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NoAttributeWithTag)
		{
			xml_document<> doc;
			string xml = "<a>\r\n\t<b attribute=\"2\"/>\r\n</a>\r\n";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsNull(node);
		}

		TEST_METHOD(NodeLevel1)
		{
			xml_document<> doc;
			string xml = "<a>\r\n\t<b kinship_degree=\"2\"/>\r\n</a>\r\n";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NodeLevel2)
		{
			xml_document<> doc;
			string xml = "<a><c><b kinship_degree=\"2\"/></c></a>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NodeLevel3)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3><aab3 kinship_degree=\"2\"/></aaa3></aa2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(AttributeOnFirstPlace)
		{
			xml_document<> doc;
			string xml = "<a>\r\n\t<b kinship_degree=\"2\"/>\r\n</a>\r\n";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(AttributeOnSecondPlace)
		{
			xml_document<> doc;
			string xml = "<a>\r\n\t<b attribute=\"4\" kinship_degree=\"2\"/>\r\n</a>\r\n";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NodeOnLeftSide)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aab3 kinship_degree=\"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NodeOnRightSide)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><abb3/></aa2><ab2><aba3/><aab3 kinship_degree=\"2\"/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}

		TEST_METHOD(NodeInAnyPlace)
		{
			xml_document<> doc;
			string xml = "<a1><aa2><aaa3/><aab3 kinship_degree = \"2\"/></aa2><ab2><aba3/><abb3/></ab2></a1>";
			doc.parse<0>((char*)xml.c_str());
			xml_node<>* root = doc.first_node();

			xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

			Assert::IsTrue(node->first_attribute("kinship_degree"));
		}
	};
}
