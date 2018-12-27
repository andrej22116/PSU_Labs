#ifndef NEWSDATABASECONTROLLER_H
#define NEWSDATABASECONTROLLER_H

#include <code/model/news.h>

class NewsDatabaseController
{
    static const QString templateQueryAddNewGameNews;
    static const QString templateQueryModifyGameNews;
    static const QString templateQueryDeleteGameNews;
    static const QString templateQueryAddNewGlobalNews;
    static const QString templateQueryModifyGlobalNews;
    static const QString templateQueryDeleteGlobalNews;

public:
    NewsDatabaseController() = delete;
    ~NewsDatabaseController() = delete;
    NewsDatabaseController(const NewsDatabaseController&) = delete;
    NewsDatabaseController(const NewsDatabaseController&&) = delete;
    NewsDatabaseController& operator = (const NewsDatabaseController&) = delete;
    NewsDatabaseController& operator = (const NewsDatabaseController&&) = delete;


    void addNewGameNews(News& news);
    void modifyGameNews(const News& news);
    void deleteGameNews(const News& news);

    void addNewGlobalNews(News& news);
    void modifyGlobalNews(const News& news);
    void deleteGlobalNews(const News& news);
};

#endif // NEWSDATABASECONTROLLER_H
