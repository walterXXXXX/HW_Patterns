#include <iostream>

#include "sql_select_query_builder.h"

void sendQuery(std::string& query) {
    std::cout << query << std::endl;
}

int main() {
	setlocale(LC_ALL, "");

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    sendQuery(query_builder.BuildQuery());

    // static_assert(query_builder.BuildQuery(),
    //    "SELECT name, phone FROM students WHERE id=42 AND name=John;");


	return 0;
}