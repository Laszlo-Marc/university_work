#include "Exceptions.h"


Exceptions::Exceptions(string MessageException) {
    this->message = move(MessageException);
}

const char* Exceptions::what() const noexcept {
    return this->message.c_str();
}

ExceptionsValidator::ExceptionsValidator(string MessageException) : Exceptions(move(MessageException)) {

}

ExceptionsRepository::ExceptionsRepository(string MessageException) : Exceptions(move(MessageException)) {

}