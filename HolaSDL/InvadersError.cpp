#include "InvadersError.h"
#include "InvadersError.h"
#include "checkML.h"

InvadersError::InvadersError(const std::string& msg) : logic_error(msg), message(msg) {}

char const* InvadersError::what() const {
	return message.c_str();
}
