#pragma once

#include "event_sender.hpp"
#include "i_event_arguments.hpp"

namespace core {

	class IEvent {
	public:
		/// <summary>
		/// 
		/// </summary>
		virtual ~IEvent();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual Sender GetSender();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual IEventArguments* GetEventArgs();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		virtual size_t GetArgTypeHash();
	};

}