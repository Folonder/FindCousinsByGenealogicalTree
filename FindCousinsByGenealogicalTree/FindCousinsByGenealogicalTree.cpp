/*!
 * \file
 * \brief Данный файл содержит реализацию функций программы для нахождения кузенов человека по генеалогичесому дереву
*/


#include <iostream>
#include "FindCousinsByGenealogicalTree.h"


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    try {
        if (argc != 3) {
            throw runtime_error("Неверное количество аргументов");
        }
        //Прочитать файл
        char* input_file = (char*)argv[1];
        string xml = read_xml_file(input_file);

        xml_document<> doc;
        doc.parse<0>((char*)xml.c_str());

        vector<xml_node<>*> cousins;

        //Найти кузенов
        get_cousins(&doc, &cousins);

        //Вывести в файл
        write_cousins_in_file((char*)argv[2], cousins);
    }
    catch (FileNotFoundException ex) {
        cout << ex.what();
    }
    catch (KinshipDegreeException ex) {
        cout << ex.what();
    }
    catch (runtime_error ex) {
        cout << ex.what();
    }
	catch (parse_error ex)
    {
        cout << "Ошибка синтаксиса";
    }
	
    return 0;
}



string read_xml_file(char* file_name) 
{
    //Если файл не был открыт
    if (!std::ifstream(file_name)) 
    {
        throw FileNotFoundException(file_name);
    }
    file<> xml_file(file_name);
    return xml_file.data();
}


xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name) 
{
    //Если есть атрибут
    xml_attribute<>* attr = node->first_attribute(attribute_name.c_str());
    if (attr) 
    {
        return node;
    }
    //Для всех детей текущего звена повторить алгоритм
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
    //Если звена нет или нет атрибута
    if (node == NULL || !node->first_attribute(attribute_name.c_str()))
    {
        throw KinshipDegreeException("Степень родства не указана");
    }
    try
    {
        //Получить значение степени родства
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
    //Если предка нет, то степень родства оказалась больше глубины дерева
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
    //Дойти до нужого поколения
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
    //Открыть файл
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
    //Получить корень дерева
    xml_node<>* root = doc->first_node();

    //Найти человека, чьих кузенов необходимо найти
    xml_node<>* node = find_node_with_attribute(root, "kinship_degree");

    unsigned int kinship_degree = validate_node_attribute(node, "kinship_degree");

    //Найти общего предка
    auto [parent, banned_child] = get_parent_and_child_by_generation(node, nullptr, kinship_degree);

    //Для всех детей, кроме того, от которого пришли
    for (xml_node<>* child = parent->first_node(); child; child = child->next_sibling()) 
    {
        if (banned_child != child) 
        {
            get_children_at_generation(child, kinship_degree - 1, *cousins);
        }
    }
}