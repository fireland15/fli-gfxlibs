#pragma once

#include "sender.hpp"

namespace events {

	template<typename TEventArgs>
	class Event {
	public:
		Event(Sender sender, TEventArgs args);

		Sender GetSender();

		TEventArgs GetArguments();

	private:
		Sender m_sender;

		TEventArgs m_args;
	};

}