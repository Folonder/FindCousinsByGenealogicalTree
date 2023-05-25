#include <iostream>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../Exceptions/FileNotFoundException.h"
#include "../Exceptions/KinshipDegreeException.h"

using namespace std;
using namespace rapidxml;


string read_xml_file(char* file_name);


xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name);


unsigned int validate_node_attribute(xml_node<>* node, const string attribute_name);


tuple<xml_node<>*, xml_node<>*> get_parent_and_child_by_generation(xml_node<>* parent, xml_node<>* child, unsigned int generation);
