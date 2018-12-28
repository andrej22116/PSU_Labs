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


    static void addNewGameNews(News& news);
    static void modifyGameNews(const News& news);
    static void deleteGameNews(const News& news);

    static void addNewGlobalNews(News& news);
    static void modifyGlobalNews(const News& news);
    static void deleteGlobalNews(const News& news);
};

#endif // NEWSDATABASECONTROLLER_H
