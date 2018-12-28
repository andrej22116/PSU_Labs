#ifndef USER_PROFILE_H
#define USER_PROFILE_H

enum UserRole : char {
    UserRole_User        = 0,
    UserRole_Moderator   = 1,
    UserRole_Admin       = 2
};

enum DeveloperStatus : char {
    DeveloperStatus_NotDeveloper    = 0,
    DeveloperStatus_Developer       = 1,
    DeveloperStatus_MainDeveloper   = 2
};

struct UserProfile {
    UserRole userRole = UserRole_User;
    DeveloperStatus developerStatus = DeveloperStatus_NotDeveloper;
};

#endif // USER_PROFILE_H
