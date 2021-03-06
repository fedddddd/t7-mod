#pragma once

#include "structs.hpp"

namespace game
{
	template <typename T>
	class symbol
	{
	public:
		symbol(const size_t address)
			: address_(reinterpret_cast<T*>(address))
		{
		}

		T* get() const
		{
			return reinterpret_cast<T*>(address_);
		}

		operator T* () const
		{
			return this->get();
		}

		T* operator->() const
		{
			return this->get();
		}

	private:
		T* address_;
	};

	struct cmd_args_t
	{
		CmdArgs* operator->() const;
	};

	extern cmd_args_t cmd_args;
}

#include "symbols.hpp"