#ifndef COMMENTSDATABASECONTROLLER_H
#define COMMENTSDATABASECONTROLLER_H

#include "code/model/commentary.h"
#include "code/model/user.h"
#include "code/model/game.h"

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

public:
    CommentsDatabaseController() = delete;
    ~CommentsDatabaseController() = delete;
    CommentsDatabaseController(const CommentsDatabaseController&) = delete;
    CommentsDatabaseController(const CommentsDatabaseController&&) = delete;
    CommentsDatabaseController& operator = (const CommentsDatabaseController&) = delete;
    CommentsDatabaseController& operator = (const CommentsDatabaseController&&) = delete;


    void addNewCommentaryForGame( const CurrentUser& user
                                , const BaseGame& game
                                , Commentary& commentary);

    void modifyCommentaryForGame( const CurrentUser& user
                                , const Commentary& commentary);

    void deleteCommentaryForGame( const CurrentUser& user
                                , const Commentary& commentary);

    void deleteUserCommentaryForGame( const CurrentUser& user
                                    , const BaseUser& targetUser
                                    , const Commentary& commentary);

    void addNewCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    void modifyCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    void deleteCommentaryForGameNews(const CurrentUser& user, Commentary& commentary);
    void deleteUserCommentaryForGameNews( const CurrentUser& user
                                        , const BaseUser& targetUser
                                        , const Commentary& commentary);

    void addNewCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    void modifyCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    void deleteCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary);
    void deleteUserCommentaryForGlobalNews( const CurrentUser& user
                                          , const BaseUser& targetUser
                                          , const Commentary& commentary);
};

#endif // COMMENTSDATABASECONTROLLER_H
