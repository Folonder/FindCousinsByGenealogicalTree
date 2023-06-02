#include "pch.h"
#include "CppUnitTest.h"
#include "../FindCousinsByGenealogicalTree/FindCousinsByGenealogicalTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testreadxmlfile
{
	TEST_CLASS(Testreadxmlfile)
	{
	public:

		#define TEST_CASE_DIRECTORY get_directory_name(__FILE__)

		string get_directory_name(string path) {
			const size_t last_slash_idx = path.rfind('\\');
			if (std::string::npos != last_slash_idx)
			{
				return path.substr(0, last_slash_idx + 1);
			}
			return "";
		}
		
		TEST_METHOD(DefaulTest)
		{
			string exp_xml = "<a/>";
			string xml = read_xml_file((char*)(string(TEST_CASE_DIRECTORY) + "default.xml").c_str());
			Assert::IsTrue(exp_xml == xml);
		}

		TEST_METHOD(NoFile)
		{
			string exp_xml = "<a/>";
			try
			{
				string xml = read_xml_file((char*)(string(TEST_CASE_DIRECTORY) + "no_file.xml").c_str());
			}
			catch (FileNotFoundException ex)
			{

			}
		}

		TEST_METHOD(RelativePath)
		{
			string exp_xml = "<a/>";
			string xml = read_xml_file((char*)(string(TEST_CASE_DIRECTORY) + "default.xml").c_str());
			Assert::IsTrue(exp_xml == xml);
		}

		TEST_METHOD(AbsolutePath)
		{
			string exp_xml = "<a/>";
			string xml = read_xml_file("C:\\учеба\\4 семестр\\кинпо\\FindCousinsByGenealogicalTree\\Test_read_xml_file\\default.xml");
			Assert::IsTrue(exp_xml == xml);
		}

		TEST_METHOD(EmptyFile)
		{
			string exp_xml = "";
			string xml = read_xml_file((char*)(string(TEST_CASE_DIRECTORY) + "empty.xml").c_str());
			Assert::IsTrue(exp_xml == xml);
		}

		TEST_METHOD(NotXmlFile)
		{
			string exp_xml = "";
			try
			{
				string xml = read_xml_file((char*)(string(TEST_CASE_DIRECTORY) + "NotXml.txt").c_str());
			}
			catch (runtime_error ex)
			{

			}
		}
	};
}
