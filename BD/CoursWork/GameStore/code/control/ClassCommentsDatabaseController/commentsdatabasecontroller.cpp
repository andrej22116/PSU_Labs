#include "commentsdatabasecontroller.h"

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>



const QString templateQueryAddNewCommentaryForGame{
    "select public_function_add_comment_for_game('%1', '%2', '%3');"
};

void CommentsDatabaseController::addNewCommentaryForGame( const CurrentUser& user
                                                        , const BaseGame& game
                                                        , Commentary& commentary)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryAddNewCommentaryForGame
            .arg(user.token)
            .arg(game.gameName)
            .arg(commentary.text);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    if ( query.next() ) {
        commentary.id = query.value(0).toUuid();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryModifyCommentaryForGame{
    "select public_function_modify_comment_for_game('%1', '%2', '%3');"
};

void CommentsDatabaseController::modifyCommentaryForGame( const CurrentUser& user
                                                        , const Commentary& commentary)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryModifyCommentaryForGame
            .arg(user.token)
            .arg(commentary.id.toString())
            .arg(commentary.text);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteCommentaryForGame{
    "select public_function_delete_comment_for_game('%1', '%2');"
};

void CommentsDatabaseController::deleteCommentaryForGame( const CurrentUser& user
                                                        , const Commentary& commentary)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryDeleteCommentaryForGame
            .arg(user.token)
            .arg(commentary.id.toString());

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteUserCommentaryForGame{".................."};

void CommentsDatabaseController::deleteUserCommentaryForGame( const CurrentUser& user
                                                            , const BaseUser& targetUser
                                                            , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryAddNewCommentaryForGameNews{"..................."};

void CommentsDatabaseController::addNewCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryModifyCommentaryForGameNews{"..................."};

void CommentsDatabaseController::modifyCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteCommentaryForGameNews{"..................."};

void CommentsDatabaseController::deleteCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteUserCommentaryForGameNews{"....................."};

void CommentsDatabaseController::deleteUserCommentaryForGameNews( const CurrentUser& user
                                                                , const BaseUser& targetUser
                                                                , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryAddNewCommentaryForGlobalNews{"....................."};

void CommentsDatabaseController::addNewCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryModifyCommentaryForGlobalNews{"....................."};

void CommentsDatabaseController::modifyCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteCommentaryForGlobalNews{"......................."};

void CommentsDatabaseController::deleteCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString templateQueryDeleteUserCommentaryForGlobalNews{"...................."};

void CommentsDatabaseController::deleteUserCommentaryForGlobalNews( const CurrentUser& user
                                                                  , const BaseUser& targetUser
                                                                  , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}
