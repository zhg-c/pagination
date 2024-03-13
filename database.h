#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <vector>
#include <QString>

#define ROWS_PER_PAGE 10

typedef struct
{
    QString user;
    int age;
} Info_t;
class Database
{
public:
    static Database &GetInstance()
    {
        static Database Instance;
        return Instance;
    }

    Database();
public:
    bool InitDB();
    bool SelDatas(int currpage,std::vector<Info_t> &vInfo);
    bool GetCount(int &Count);
private:
    sqlite3 *m_pDb;
};

#endif // DATABASE_H
