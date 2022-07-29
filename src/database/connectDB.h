#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


int main(void) {
    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        driver = get_driver_instance(); 
        con = driver->connect("tcp://127.0.0.1:3306","root","root"); 
        con->setSchema("chatApp");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * AS all_data FROM messages");
        while(res->next()) {
            std::cout << "\t Mysql replies: ";           
            std::cout << res->getString("all_Data") << std::endl;
            std::cout << "\t MySQL says it again: ";
            std::cout << res->getString(1) << endl;
        }

        delete res;
        delete stmt;
        delete con;
    } catch(sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << "(MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}