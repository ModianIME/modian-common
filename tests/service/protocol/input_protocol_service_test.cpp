#include "gtest/gtest.h"

#include "scriptorium/felt/service/protocol/input_protocol_service.h"

TEST(input_protocol_service_test, should_return_U_message_when_build_update_response) {
	const scriptorium::felt::core::protocol::input::v1::instruction instruction { scriptorium::felt::core::protocol::input::v1::message_type::UPDATE, "ni" };
	const auto message = scriptorium::felt::service::input_protocol_service::build_instruction_response(instruction);
	ASSERT_EQ(message, R"({"candidate_info":{"word":"ni"},"type":"U"})");
}

TEST(input_protocol_service_test, should_return_empty_string_when_build_response_with_null) {
	const scriptorium::felt::core::protocol::input::v1::instruction instruction { scriptorium::felt::core::protocol::input::v1::message_type::UPDATE, "" };
	const auto message = scriptorium::felt::service::input_protocol_service::build_instruction_response(instruction);
	ASSERT_EQ(message, R"({"candidate_info":{"word":""},"type":"U"})");
}

TEST(input_protocol_service_test, should_return_C_message_when_when_build_commit_response) {
	const scriptorium::felt::core::protocol::input::v1::instruction instruction { scriptorium::felt::core::protocol::input::v1::message_type::COMMIT, "你" };
	const auto message = scriptorium::felt::service::input_protocol_service::build_instruction_response(instruction);
	ASSERT_EQ(message, R"({"candidate_info":{"word":"你"},"type":"C"})");
}

TEST(input_protocol_service_test, should_return_N_message_when_build_none_response) {
    const scriptorium::felt::core::protocol::input::v1::instruction instruction { scriptorium::felt::core::protocol::input::v1::message_type::NONE, "" };
    const auto message = scriptorium::felt::service::input_protocol_service::build_instruction_response(instruction);
    ASSERT_EQ(message, R"({"candidate_info":{"word":""},"type":"N"})");
}

TEST(input_protocol_service_test, should_get_commit_and_correct_candidate_when_decode) {
	const auto& protocol = scriptorium::felt::service::input_protocol_service::parse_instruction_response(R"({"candidate_info":{"word":"你"},"type":"C"})");
	ASSERT_EQ(protocol.type, scriptorium::felt::core::protocol::input::v1::message_type::COMMIT);
	ASSERT_EQ(protocol.candidate_info.word, "你");
}

TEST(input_protocol_service_test, should_get_update_and_correct_message_when_decode) {
	const auto& protocol = scriptorium::felt::service::input_protocol_service::parse_instruction_response(R"({"candidate_info":{"word":"dia"},"type":"U"})");
	ASSERT_EQ(protocol.type, scriptorium::felt::core::protocol::input::v1::message_type::UPDATE);
	ASSERT_EQ(protocol.candidate_info.word, "dia");
}

TEST(input_protocol_service_test, should_get_none_when_decode_empty_message) {
	const auto& protocol = scriptorium::felt::service::input_protocol_service::parse_instruction_response(R"({"candidate_info":{"word":""},"type":"N"})");
	ASSERT_EQ(protocol.type, scriptorium::felt::core::protocol::input::v1::message_type::NONE);
	ASSERT_EQ(protocol.candidate_info.word, "");
}
