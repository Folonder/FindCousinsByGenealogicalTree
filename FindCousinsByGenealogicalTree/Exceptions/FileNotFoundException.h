/*!
 * \file
 * \brief Основные исключения, необходимые для функционирования программы
*/


#include <iostream>
using namespace std;


/*!
* \brief Исключение отсутствия файла
*/
class FileNotFoundException : public std::exception {

private:
    /*!
     * \brief имя файла
    */
    string file_name;

public:
    /*!
     * \brief Конструктор исключения
     * \param[in] file_name - имя файла
    */
    FileNotFoundException(string file_name){
        this->file_name = file_name;
    }

    /*!
     * \brief Выводит сообщение исключения об отсутствии файла
     * \return сообщение
    */
    string what() {
        return "File not found: " + file_name;
    }

};