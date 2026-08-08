#pragma once

#include <string>
#include <string_view>
#include <mutex>

#include "scriptorium/felt/core/ipc/isync_ipc_client.h"

namespace scriptorium::felt::infra::ipc {
	class sync_named_pipe_client : public core::ipc::isync_ipc_client<std::string, std::string> {
	public:
		explicit sync_named_pipe_client(std::string_view pipe_name);
		~sync_named_pipe_client() override;

		sync_named_pipe_client(const sync_named_pipe_client&) = delete;
		sync_named_pipe_client& operator=(const sync_named_pipe_client&) = delete;

		std::string sync_send(const std::string& message) override;

	private:
		bool ensure_connection();
		void close();

		std::string pipe_name_;
		void* pipe_handle_;
		std::mutex mutex_;
	};
}
