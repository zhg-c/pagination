#include "database.h"
#include <QString>

Database::Database()
{

}

bool Database::InitDB()
{
    bool bRet = false;
    sqlite3_stmt *pStmt = nullptr;
    const char *Sql[] = {
        "CREATE TABLE info(name TEXT,age TINYINT)",
        "INSERT INTO info VALUES(@1,@2)",
        nullptr
    };
    do
    {
        if(sqlite3_open("/tmp/test.db",&m_pDb) != SQLITE_OK)
        {
            break;
        }
        if(sqlite3_exec(m_pDb,Sql[0],nullptr,nullptr,nullptr) != SQLITE_OK)
        {
            break;
        }
        for(int i = 1;i < 1000;i++)
        {
            do
            {
                bRet = false;
                if(sqlite3_prepare(m_pDb,Sql[1],-1,&pStmt,nullptr) != SQLITE_OK)
                {
                    break;
                }
                int Index = 1;
                if(sqlite3_bind_text(pStmt,Index++,QString::number(i).toStdString().c_str(),-1,nullptr) != SQLITE_OK)
                {
                    break;
                }
                if(sqlite3_bind_int(pStmt,Index++,i % 100) != SQLITE_OK)
                {
                    break;
                }
                if(sqlite3_step(pStmt) != SQLITE_DONE)
                {
                    break;
                }
                bRet = true;
            }while(false);
            if(!bRet)
            {
                break;
            }
        }
        bRet = true;
    }while(false);
    if(pStmt)
    {
        sqlite3_finalize(pStmt);
    }
    return bRet;
}

bool Database::SelDatas(int currpage,std::vector<Info_t> &vInfo)
{
    bool bRet = false;
    sqlite3_stmt *pStmt = nullptr;
    const char *Sql = "SELECT * FROM info LIMIT @1 OFFSET @2";
    do
    {
        if(sqlite3_prepare(m_pDb,Sql,-1,&pStmt,nullptr) != SQLITE_OK)
        {
            break;
        }
        int Index = 1;
        if(sqlite3_bind_int(pStmt,Index++,ROWS_PER_PAGE) != SQLITE_OK)
        {
            break;
        }
        if(sqlite3_bind_int(pStmt,Index++,currpage * ROWS_PER_PAGE) != SQLITE_OK)
        {
            break;
        }
        int Res = SQLITE_ERROR;
        while((Res = sqlite3_step(pStmt)) == SQLITE_ROW)
        {
            Info_t Info;
            int Index = 0;
            Info.user = (const char *)sqlite3_column_text(pStmt,Index++);
            Info.age = sqlite3_column_int(pStmt,Index++);
            vInfo.push_back(Info);
        }
        if(Res != SQLITE_DONE)
        {
            break;
        }
        bRet = true;
    }while(false);
    if(pStmt)
    {
        sqlite3_finalize(pStmt);
    }
    return bRet;
}

bool Database::GetCount(int &Count)
{
    bool bRet = false;
    const char *Sql = "SELECT COUNT(*) FROM info";
    sqlite3_stmt *pStmt = nullptr;
    do
    {
        if(sqlite3_prepare(m_pDb,Sql,-1,&pStmt,nullptr) != SQLITE_OK)
        {
            break;
        }
        int Res = SQLITE_ERROR;
        while((Res = sqlite3_step(pStmt)) == SQLITE_ROW)
        {
            Count = sqlite3_column_int(pStmt,0);
        }
        if(Res != SQLITE_DONE)
        {
            break;
        }
        bRet = true;
    }while(false);
    if(pStmt)
    {
        sqlite3_finalize(pStmt);
    }
    return bRet;
}














