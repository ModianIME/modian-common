#pragma once

#include <string>

namespace scriptorium::felt::core::protocol::input::v1 {
	enum class message_type {
		NONE = 'N',
		UPDATE = 'U',
		COMMIT = 'C'
	};

    struct candidate_info {
        std::string word{};
    };

	struct instruction {
		message_type type{message_type::NONE};
	    candidate_info candidate_info;
	};
}
