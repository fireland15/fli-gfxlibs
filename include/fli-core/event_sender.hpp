#pragma once

namespace core {

	class Sender {
	public:
		Sender(void* pSender);

	private:
		void* m_pSender;
	};

}