#include <iostream>
#include "FindCousinsByGenealogicalTree.h"


int main()
{
    try
    {
        char* input_file = (char*)"data.xml";
        xml_document<> doc;
        string xml = read_xml_file(input_file);
        doc.parse<0>((char*)xml.c_str());
    }
    catch (FileNotFoundException ex)
    {
        cout << ex.what();
    }
    catch (KinshipDegreeException ex)
    {
        cout << ex.what();
    }
    catch (runtime_error ex)
    {
        cout << ex.what();
    }
}


string read_xml_file(char* file_name) {
    if (!std::ifstream(file_name)) {
        throw FileNotFoundException(file_name);
    }
    file<> xml_file(file_name);
    return xml_file.data();
}