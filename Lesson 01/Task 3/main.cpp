#include <iostream>

#include "advanced_sql_select_query_builder.h"

void sendQuery(std::string& query) {
    std::cout << query << std::endl;
}

int main() {
	setlocale(LC_ALL, "");

    AdvancedSqlSelectQueryBuilder query_builder;
//    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42", SqlSelectCondition::IS_LOWER).AddWhere("name", "John");
//    query_builder.AddWhere({{"id", "42"}, {"name", "John"}});
    sendQuery(query_builder.BuildQuery());
    // static_assert(query_builder.BuildQuery(),
    //    "SELECT name, phone FROM students WHERE id=42 AND name=John;");


	return 0;
}