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


xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name) {
    xml_attribute<>* attr = node->first_attribute(attribute_name.c_str());
    if (attr) {
        return node;
    }

    for (xml_node<>* child_node = node->first_node(); child_node; child_node = child_node->next_sibling()) {
        xml_node<>* node = find_node_with_attribute(child_node, attribute_name);
        if (node) {
            return node;
        }
    }

    return NULL;
}


unsigned int validate_node_attribute(xml_node<>* node, const string attribute_name) {
    if (node->first_attribute(attribute_name.c_str())->value()) {
        try {
            return stoul(node->first_attribute(attribute_name.c_str())->value());
        }
        catch (runtime_error ex) {
            throw KinshipDegreeException("Степень родства не является натуральным числом");
        }
    }
    throw KinshipDegreeException("Степень родства не указана");
}