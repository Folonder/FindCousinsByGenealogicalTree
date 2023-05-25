#include <iostream>
#include "FindCousinsByGenealogicalTree.h"


int main()
{
    try
    {
        char* input_file = (char*)"data.xml";
        string xml = read_xml_file(input_file);

        vector<xml_node<>*> cousins = get_cousins(xml);

        write_cousins_in_file((char*)"output.txt", cousins);
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


tuple<xml_node<>*, xml_node<>*> get_parent_and_child_by_generation(xml_node<>* parent, xml_node<>* child, unsigned int generation) {
    if (generation > 0) {
        return get_parent_and_child_by_generation(parent->parent(), parent, generation - 1);
    }
    return { parent, child };
}


void get_children_at_generation(xml_node<>* parent, unsigned int generation, vector<xml_node<>*>& cousins) {
    if (generation > 0) {
        for (xml_node<>* child = parent->first_node(); child; child = child->next_sibling()) {
            get_children_at_generation(child, generation - 1, cousins);
        }
    }
    else {
        cousins.push_back(parent);
    }
}


void write_cousins_in_file(char* file_name, vector<xml_node<>*> cousins) {
    std::ofstream outfile(file_name);

    if (!outfile.is_open()) {
        throw runtime_error(file_name);
    }
    for (xml_node<>* cousin : cousins) {
        outfile << cousin->name() << "\n";
    }

    outfile.close();
}


xml_node<>* copy_node_to_heap(xml_document<>& doc, xml_node<>* node) {
    xml_node<>* new_node = doc.allocate_node(node->type());

    
    const char* src_name = node->name();
    size_t name_size = strlen(src_name) + 1;
    char* new_name = doc.allocate_string(src_name, name_size);
    new_node->name(new_name, name_size - 1);

    
    const char* src_value = node->value();
    size_t value_size = strlen(src_value) + 1;
    char* new_value = doc.allocate_string(src_value, value_size);
    new_node->value(new_value, value_size - 1);

    
    for (xml_attribute<>* src_attr = node->first_attribute(); src_attr; src_attr = src_attr->next_attribute()) {
        const char* src_attr_name = src_attr->name();
        size_t attr_name_size = strlen(src_attr_name) + 1;
        char* new_attr_name = doc.allocate_string(src_attr_name, attr_name_size);

        const char* src_attr_value = src_attr->value();
        size_t attr_value_size = strlen(src_attr_value) + 1;
        char* new_attr_value = doc.allocate_string(src_attr_value, attr_value_size);

        xml_attribute<>* new_attr = doc.allocate_attribute(new_attr_name, new_attr_value);
        new_node->append_attribute(new_attr);
    }

    
    for (xml_node<>* src_child = node->first_node(); src_child; src_child = src_child->next_sibling()) {
        xml_node<>* new_child = copy_node_to_heap(doc, src_child);
        new_node->append_node(new_child);
    }

    return new_node;
}


vector<xml_node<>*> get_cousins(string xml) {
    vector<xml_node<>*> cousins;
    xml_document<> doc;
    doc.parse<0>((char*)xml.c_str());
    xml_node<>* root = doc.first_node();

    xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

    unsigned int kinship_degree = validate_node_attribute(node, "kinship_degree");

    auto [parent, banned_child] = get_parent_and_child_by_generation(node, nullptr, kinship_degree);


    for (xml_node<>* child = parent->first_node(); child; child = child->next_sibling()) {
        if (banned_child != child) {
            get_children_at_generation(child, kinship_degree - 1, cousins);
        }
    }

    for (int i = 0; i < cousins.size(); i++)
    {
        cousins[i] = copy_node_to_heap(doc, cousins[i]);
    }
    return cousins;
}