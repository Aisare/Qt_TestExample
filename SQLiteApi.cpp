#include "SQLiteApi.h"

bool SQLiteApi::connect(const std::string& db_path_name)
{
    db_name = db_path_name;

    int res = sqlite3_open(db_name.c_str(), &dataBase);

    is_open_db = res == SQLITE_OK;

    return is_open_db;
}

bool SQLiteApi::disconnect()
{
    int res = 0;
    if(is_open_db)
        res = sqlite3_close(dataBase);
    return res == SQLITE_OK;
}

SQLiteApi::ResultRows SQLiteApi::Exec(const std::string& query, const std::vector<std::string>& params)
{
    if (!is_open_db || query.empty()) return {};

    SQLiteApi::ResultRows result = {};
    sqlite3_stmt* stmt;
    int res = !SQLITE_OK;

    res = sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, nullptr);
    if (res == SQLITE_OK)
    {
        for (size_t i = 0; i < params.size(); ++i)
        {
            sqlite3_bind_text(stmt, static_cast<int>(i + 1), params[i].c_str(), -1, SQLITE_TRANSIENT);
        }

        bool isSelect = (query.find("SELECT") == 0 || query.find("select") == 0);
        if (isSelect)
        {
            int cols = sqlite3_column_count(stmt);
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                std::vector<std::string> row;
                for (int i = 0; i < cols; ++i)
                {
                    row.emplace_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
                }
                result.push_back(row);
            }
        }
        else
        {
            res = sqlite3_step(stmt);
        }
    }

    sqlite3_finalize(stmt);

    return result;
}


