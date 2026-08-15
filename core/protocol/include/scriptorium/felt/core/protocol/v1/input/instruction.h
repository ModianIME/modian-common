#pragma once

#include <string>
#include <vector>

namespace scriptorium::felt::core::protocol::input::v1 {
	enum class message_type {
		NONE = 'N',
		UPDATE = 'U',
		COMMIT = 'C'
	};

    struct candidate_info {
        std::string word{};
        std::vector<std::string> spelling_path{};
    };

	struct instruction {
		message_type type{message_type::NONE};
	    candidate_info candidate_info;
	};
}
