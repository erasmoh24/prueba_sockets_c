#include <iostream>
#include <stdlib.h>
#include <vector>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

std::vector<std::string> getMessages(sql::Connection* conn) {
    std::vector<std::string> example;
    try {
        sql::Statement* stmt;
        sql::ResultSet* res;
        conn->setSchema("chatApp");

        stmt = conn->createStatement();
        res = stmt->executeQuery("SELECT * all_data FROM messages");

        while(res->next()) {
            std::cout << res->getString("all_data") << std::endl;
            std::cout << res->getString(1) << std::endl;
        }

        delete stmt;
        delete res;
        delete conn;

    } catch(sql::SQLException& err) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << "MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return example;
}