#include "sql_select_query_builder.h"

#include <iterator>

//SqlSelectQueryBuilder::SqlSelectQueryBuilder() {
//}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& columnName) noexcept {
	_columns.insert(columnName);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept {
	_columns.insert(columns.begin(), columns.end());
	return *this;
}


SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& tableName) noexcept {
	_from = tableName;
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& varName, const std::string& value) noexcept {
	_kv.push_back(varName+"="+value);
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept {
	for (const auto& where : kv)
		AddWhere(where.first, where.second);
	return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() noexcept {
	std::string res = "SELECT ";
	if (_columns.empty())
		res += "* ";
	else
		for (auto it = _columns.cbegin(); it != _columns.cend(); it++) {
			res += *it;
			if (std::next(it) != _columns.cend()) res += ", ";
		}
	res += " FROM " + _from;
	if (_kv.empty()) {
		res += ";";
		return res;
	}
	res += " WHERE ";
	for (auto it = _kv.begin(); it != _kv.end(); ++it) {
		res += *it;
		if (it == _kv.end()-1)
			res += ";";
		else
			res += " AND ";
	}
	return res;
}