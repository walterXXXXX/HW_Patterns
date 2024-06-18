#include "advanced_sql_select_query_builder.h"

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhere(const std::string& varName, const std::string& value, const SqlSelectCondition condition) noexcept {
	switch (condition)
	{
	case SqlSelectCondition::IS_LOWER:
		_kv.push_back(varName + "<" + value);
		break;
	case SqlSelectCondition::IS_BIGGER:
		_kv.push_back(varName + ">" + value);
	default:
		_kv.push_back(varName + "=" + value);
		break;
	}
	return *this;
}