#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

bool connectDatabase(void) {
    try {
        sql::Driver* driver;
        sql::Connection* con;

        driver = get_driver_instance(); 
        con = driver->connect("tcp://127.0.0.1:3306","root","password"); 
        con->setSchema("chatApp");

        //delete con;
    } catch(sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << "(MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }

    std::cout << std::endl;

    return true;
}