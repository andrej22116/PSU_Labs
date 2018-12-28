#ifndef COMMENTSDATABASECONTROLLER_H
#define COMMENTSDATABASECONTROLLER_H

#include "code/model/commentary.h"
#include "code/model/user.h"
#include "code/model/game.h"
#include "code/model/news.h"

#include <QVector>

class CommentsDatabaseController
{
    static const QString templateQueryAddNewCommentaryForGame;
    static const QString templateQueryModifyCommentaryForGame;
    static const QString templateQueryDeleteCommentaryForGame;
    static const QString templateQueryDeleteUserCommentaryForGame;
    static const QString templateQueryAddNewCommentaryForGameNews;
    static const QString templateQueryModifyCommentaryForGameNews;
    static const QString templateQueryDeleteCommentaryForGameNews;
    static const QString templateQueryDeleteUserCommentaryForGameNews;
    static const QString templateQueryAddNewCommentaryForGlobalNews;
    static const QString templateQueryModifyCommentaryForGlobalNews;
    static const QString templateQueryDeleteCommentaryForGlobalNews;
    static const QString templateQueryDeleteUserCommentaryForGlobalNews;
    static const QString templateQueryGetGameCommetaries;
    static const QString templateQueryGetNewsCommetaries;

public:
    CommentsDatabaseController() = delete;
    ~CommentsDatabaseController() = delete;
    CommentsDatabaseController(const CommentsDatabaseController&) = delete;
    CommentsDatabaseController(const CommentsDatabaseController&&) = delete;
    CommentsDatabaseController& operator = (const CommentsDatabaseController&) = delete;
    CommentsDatabaseController& operator = (const CommentsDatabaseController&&) = delete;


    static void addNewCommentaryForGame( const CurrentUser& user
                                       , const BaseGame& game
                                       , Commentary& commentary);

    static void modifyCommentaryForGame( const CurrentUser& user
                                       , const Commentary& commentary);

    static void deleteCommentaryForGame( const CurrentUser& user
                                       , const Commentary& commentary);

    static void deleteUserCommentaryForGame( const CurrentUser& user
                                           , const BaseUser& targetUser
                                           , const Commentary& commentary);

    static void addNewCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    static void modifyCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    static void deleteCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    static void deleteUserCommentaryForGameNews( const CurrentUser& user
                                               , const BaseUser& targetUser
                                               , const Commentary& commentary);

    static void addNewCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    static void modifyCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    static void deleteCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    static void deleteUserCommentaryForGlobalNews( const CurrentUser& user
                                                 , const BaseUser& targetUser
                                                 , const Commentary& commentary);

    static QVector<Commentary> getGameCommetaries(const BaseGame& game, int limit, int offset);
    static QVector<Commentary> getNewsCommetaries(const BaseNews& news, int limit, int offset);
};

#endif // COMMENTSDATABASECONTROLLER_H
