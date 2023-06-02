/*!
 * \file
 * \brief Основные функции программы
 *
 * Данный файл содержит функции работы программы для нахождение X-юродных кузенов человека по генеалогическому дереву
*/


#include <iostream>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "Exceptions/FileNotFoundException.h"
#include "Exceptions/KinshipDegreeException.h"


using namespace std;
using namespace rapidxml;

/*!
 * \brief Считывает xml файл в виде строки
 * \param[in] file_name - путь к файлу 
 * \return содержание файла
 * \throw FileNotFoundException - файл отсутствует по заданному пути
*/
string read_xml_file(char* file_name);


/*!
 * \brief Находит звено с заданным атрибутом
 * \param[in] node - звено, от которого начать поиск
 * \param[in] attribute_name - имя атрибута
 * \return звено, содержащее заданный атрибут
*/
xml_node<>* find_node_with_attribute(xml_node<>* node, const string& attribute_name);


/*!
 * \brief Валидация значение атрибута на натуральное число
 * \param[in] node - звено для валидации
 * \param[in] attribute_name - атрибут для валидации
 * \return значение атрибута
 * \throw KinshipDegreeException - атрибут не был найден или его значение не натуральное число
*/
unsigned int validate_node_attribute(xml_node<>* node, const string attribute_name);


/*!
 * \brief По звену найти его предка на \p generation поколений выше, а также его потомка, от которого к этому звену пришли
 * \param[in] parent - звено, чьего предка нужно найти
 * \param[in] child - потомок, от которого к этому предку пришли
 * \param[in] generation - на сколько поколений выше нужно найти предка
 * \return потомок и предок
*/
tuple<xml_node<>*, xml_node<>*> get_parent_and_child_by_generation(xml_node<>* parent, xml_node<>* child, unsigned int generation);


/*!
 * \brief Получить всех потомков звена на \p generation поколений ниже
 * \param[in] parent - предок, чьих потомков нужно найти
 * \param[in] generation - на сколько поколений ниже должны быть дети
 * \param[out] children - список детей
*/
void get_children_at_generation(xml_node<>* parent, unsigned int generation, vector<xml_node<>*>& children);


/*!
 * \brief Записать список кузенов в выходной файл
 * \param[in] file_name - путь к файлу для записи
 * \param[in] cousins - список кузенов
*/
void write_cousins_in_file(char* file_name, vector<xml_node<>*> cousins);


/*! 
* \brief Найти кузенов человека по генеалогическому дереву
* \param[in] doc - генеалогическое дерево
* \param[out] cousins - список кузенов человека
*/
void get_cousins(xml_document<> *doc, vector<xml_node<>*>* cousins);