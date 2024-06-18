#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <vector>

class SqlSelectQueryBuilder {
public:
	SqlSelectQueryBuilder() = default;

	SqlSelectQueryBuilder& AddColumn(const std::string& columnName) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
	SqlSelectQueryBuilder& AddFrom(const std::string& tableName) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::string& varName, const std::string& value) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;

	std::string BuildQuery() noexcept;

protected:
	std::unordered_set<std::string> _columns; // позволяет игнорировать повторяющиеся столбцы
	std::string _from;
	std::vector<std::string> _kv; // для одной и той же переменной допустимо несколько условий
};	