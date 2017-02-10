#pragma once

namespace events {

	struct Sender {
		Sender(void* pSender);

		bool operator==(const Sender& other);

		bool operator!=(const Sender& other);

	private:
		void* m_sender;
	};

}