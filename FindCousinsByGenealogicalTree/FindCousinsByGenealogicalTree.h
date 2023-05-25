#include <iostream>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../Exceptions/FileNotFoundException.h"
#include "../Exceptions/KinshipDegreeException.h"

using namespace std;
using namespace rapidxml;


string read_xml_file(char* file_name);

xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name);
