#include "commentsdatabasecontroller.h"

#include <code/control/ClassDatabaseBaseController/databasebasecontroller.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>



const QString CommentsDatabaseController::templateQueryAddNewCommentaryForGame{
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

const QString CommentsDatabaseController::templateQueryModifyCommentaryForGame{
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

const QString CommentsDatabaseController::templateQueryDeleteCommentaryForGame{
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

const QString CommentsDatabaseController::templateQueryDeleteUserCommentaryForGame{".................."};

void CommentsDatabaseController::deleteUserCommentaryForGame( const CurrentUser& user
                                                            , const BaseUser& targetUser
                                                            , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryAddNewCommentaryForGameNews{"..................."};

void CommentsDatabaseController::addNewCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryModifyCommentaryForGameNews{"..................."};

void CommentsDatabaseController::modifyCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryDeleteCommentaryForGameNews{"..................."};

void CommentsDatabaseController::deleteCommentaryForGameNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryDeleteUserCommentaryForGameNews{"....................."};

void CommentsDatabaseController::deleteUserCommentaryForGameNews( const CurrentUser& user
                                                                , const BaseUser& targetUser
                                                                , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryAddNewCommentaryForGlobalNews{"....................."};

void CommentsDatabaseController::addNewCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryModifyCommentaryForGlobalNews{"....................."};

void CommentsDatabaseController::modifyCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryDeleteCommentaryForGlobalNews{"......................."};

void CommentsDatabaseController::deleteCommentaryForGlobalNews(const CurrentUser& user, Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryDeleteUserCommentaryForGlobalNews{"...................."};

void CommentsDatabaseController::deleteUserCommentaryForGlobalNews( const CurrentUser& user
                                                                  , const BaseUser& targetUser
                                                                  , const Commentary& commentary)
{
    throw QString("Function unavailable!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryGetGameCommetaries{
    "select * from public_function_get_game_commentaries('%1', '%2', '%3');"
};

QVector<Commentary> CommentsDatabaseController::getGameCommetaries(const BaseGame& game, int limit, int offset)
{
    auto connection = DatabaseBaseController::getConnection();
    QString queryString = templateQueryGetGameCommetaries
            .arg(game.gameName)
            .arg(limit)
            .arg(offset);

    QSqlQuery query(connection);
    if ( !query.exec(queryString) ) {
        throw query.lastError().databaseText().section('\n', 0, 0);
    }

    QVector<Commentary> result;
    if ( query.next() ) {
        result.push_back({
                             query.value(0).toString(),
                             query.value(1).toDateTime(),
                             query.value(2).toDateTime(),
                             query.value(3).toString(),
                             query.value(4).toUuid()
                         });
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString CommentsDatabaseController::templateQueryGetNewsCommetaries{
    "...................."
};

QVector<Commentary> CommentsDatabaseController::getNewsCommetaries(const BaseNews& news, int limit, int offset)
{
    throw QString("Function unavailable!");
}
