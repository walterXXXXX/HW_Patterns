#pragma once

#include "sql_select_query_builder.h"

enum class SqlSelectCondition {
	IS_LOWER,
	IS_BIGGER,
	IS_EQUAL,
};

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
public:
	// сохраняем возможность использования родительских перегрузок метода AddWhere
	// и добавляем свою перегрузку с условием
	using SqlSelectQueryBuilder::AddWhere;
	AdvancedSqlSelectQueryBuilder& AddWhere(const std::string& varName, const std::string& value, const SqlSelectCondition condition) noexcept;

private:

};	