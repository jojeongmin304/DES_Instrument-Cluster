#ifndef ERROR_H
# define ERROR_H

# include <stdexcept>
# include <string>

enum error_e {
	INIT_FAIL_DOMAIN_SOCKET,
	INIT_FAIL_CAN_INTERFACE,
	INIT_FAIL_BIND
};

const std::string error_message[3] = {
	"Failed to create domain socket",
	"Failed to find CAN interface",
	"Failed to bind CAN socket"
};

class Error : public std::runtime_error {
public:
	explicit Error(error_e code)
		: std::runtime_error(error_message[static_cast<size_t>(code)]), _code(code) {}	

	int code() const noexcept {
		return static_cast<int>(_code);
	}

private:
	error_e _code;
};


#endif