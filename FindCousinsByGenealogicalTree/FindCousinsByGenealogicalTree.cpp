/*!
 * \file
 * \brief Данный файл содержит реализацию функций программы для нахождения кузенов человека по генеалогичесому дереву
*/


#include <iostream>
#include "FindCousinsByGenealogicalTree.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    try
    {
        char* input_file = (char*)"data.xml";
        string xml = read_xml_file(input_file);

        vector<xml_node<>*> cousins;

        xml_document<> doc;
        doc.parse<0>((char*)xml.c_str());

        get_cousins(&doc, &cousins);

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
    catch (parse_error ex)
    {
        cout << "Ошибка синтаксиса";
    }
}


string read_xml_file(char* file_name) 
{
    if (!std::ifstream(file_name)) 
    {
        throw FileNotFoundException(file_name);
    }
    file<> xml_file(file_name);
    return xml_file.data();
}


xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name) 
{
    xml_attribute<>* attr = node->first_attribute(attribute_name.c_str());
    if (attr) 
    {
        return node;
    }

    for (xml_node<>* child_node = node->first_node(); child_node; child_node = child_node->next_sibling()) 
    {
        xml_node<>* node = find_node_with_attribute(child_node, attribute_name);
        if (node) 
        {
            return node;
        }
    }

    return NULL;
}


unsigned int validate_node_attribute(xml_node<>* node, const string attribute_name) 
{
    if (node == NULL || !node->first_attribute(attribute_name.c_str()))
    {
        throw KinshipDegreeException("Степень родства не указана");
    }
    try
    {
        unsigned int value = stoul(node->first_attribute(attribute_name.c_str())->value());
        if (value == 0) {
            throw KinshipDegreeException("Степень родства не является натуральным числом или находится вне разрешенного диапазона");
        }
        return value;
    }
    catch (exception ex) 
    {
        throw KinshipDegreeException("Степень родства не является натуральным числом или находится вне разрешенного диапазона");
    }
}


tuple<xml_node<>*, xml_node<>*> get_parent_and_child_by_generation(xml_node<>* parent, xml_node<>* child, unsigned int generation) 
{
    if (parent == NULL)
    {
        throw KinshipDegreeException("Степень родства больше глубины дерева");
    }
    if (generation > 0) 
    {
        return get_parent_and_child_by_generation(parent->parent(), parent, generation - 1);
    }
    return { parent, child };
}


void get_children_at_generation(xml_node<>* parent, unsigned int generation, vector<xml_node<>*>& children) 
{
    if (generation > 0) 
    {
        for (xml_node<>* child = parent->first_node(); child; child = child->next_sibling()) 
        {
            get_children_at_generation(child, generation - 1, children);
        }
    }
    else 
    {
        children.push_back(parent);
    }
}


void write_cousins_in_file(char* file_name, vector<xml_node<>*> cousins) 
{
    std::ofstream outfile(file_name);

    if (!outfile.is_open()) 
    {
        throw runtime_error("Невозможно создать или открыть файл: " + string(file_name));
    }
    for (xml_node<>* cousin : cousins) 
    {
        outfile << cousin->name() << "\n";
    }

    outfile.close();
}


void get_cousins(xml_document<> *doc, vector<xml_node<>*> *cousins)
{
    
    xml_node<>* root = doc->first_node();

    xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

    unsigned int kinship_degree = validate_node_attribute(node, "kinship_degree");

    auto [parent, banned_child] = get_parent_and_child_by_generation(node, nullptr, kinship_degree);


    for (xml_node<>* child = parent->first_node(); child; child = child->next_sibling()) 
    {
        if (banned_child != child) 
        {
            get_children_at_generation(child, kinship_degree - 1, *cousins);
        }
    }
}