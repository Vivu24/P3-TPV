#pragma once
#include <stdexcept>

class InvadersError : std::logic_error
{
protected:
	std::string message;

public:
	InvadersError(const std::string& msg);

	char const* what() const override;
};

