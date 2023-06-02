/*!
 * \file
 * \brief Исключение неправильности степени родства
*/


#include <iostream>
using namespace std;


/*!
 * \brief Исключение неправильности степени родства
*/
class KinshipDegreeException : public std::exception {

private:
    /*!
     * \brief сообщение исключения
    */
    string message;


public:
    /*!
     * \brief Конструктор исключения
     * \param[in] msg сообщение исключения
    */
    KinshipDegreeException(string msg) {
        this->message = msg;
    }

    /*!
     * \brief Возвращает сообщение исключения
     * \return сообщение исключения
    */
    string what() {
        return message;
    }

};