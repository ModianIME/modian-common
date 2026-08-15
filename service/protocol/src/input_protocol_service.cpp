#include "scriptorium/felt/service/protocol/input_protocol_service.h"

#include <nlohmann/json.hpp>

#include "scriptorium/felt/core/logger/logger_service.h"

namespace scriptorium::felt::service {
    namespace {
        nlohmann::json build_candidate_info(const core::protocol::input::v1::candidate_info& candidate_info) {
            return {
                {"word", candidate_info.word},
                {"spelling_path", candidate_info.spelling_path}
            };
        }

        core::protocol::input::v1::candidate_info parse_candidate_info(const nlohmann::json& j) {
            return core::protocol::input::v1::candidate_info{
                j.value("word", ""),
                j.value("spelling_path", std::vector<std::string>{})
            };
        }
    }

	std::string input_protocol_service::build_key_event_request(const core::protocol::input::v1::key_event& key_event) {
        return key_event.content;
	}

    core::protocol::input::v1::key_event input_protocol_service::parse_key_event_request(const std::string& request) {
		return core::protocol::input::v1::key_event{request};
	}

    std::string input_protocol_service::build_instruction_response(const core::protocol::input::v1::instruction& instruction) {
        nlohmann::json j;
	    j["type"] = std::string(1, static_cast<char>(instruction.type));
        j["candidate_info"] = build_candidate_info(instruction.candidate_info);

		return j.dump(-1);
	}

    core::protocol::input::v1::instruction input_protocol_service::parse_instruction_response(const std::string& response) {
        core::protocol::input::v1::instruction instruction{core::protocol::input::v1::message_type::NONE, { "" }};

        try {
            const auto j = nlohmann::json::parse(response);
            instruction.type = static_cast<core::protocol::input::v1::message_type>(j.value("type", "N").front());
            instruction.candidate_info = parse_candidate_info(j.value("candidate_info", nlohmann::json::object()));
        } catch (const nlohmann::json::parse_error& e) {
			core::logger_service::logger()->error("JSON parse failed: {}", e.what());
        }

        return instruction;
	}
}
