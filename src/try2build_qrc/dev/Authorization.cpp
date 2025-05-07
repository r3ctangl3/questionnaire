//
// Created by elizaveta on 04.05.2025.
//

#include "Authorization.h"

namespace application
{
namespace authorization
{
Authorization::Authorization( QObject* parent )
    : QObject( parent )
    , accountExists( false )
{
}

void Authorization::initialize()
{
    //todo some crypto work
    //todo if( crypto.is_signed_up  )
    // {
    // accountExists = true;
    // emit accountExistsChanged();
    // }
}

bool Authorization::getAccountExists() const noexcept //Q_PROPERTY READ oblige to define method
{
    return accountExists;
}

} // authorization
} // application
