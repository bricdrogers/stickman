/*
 * callback.h
 *
 *  Created on: Feb 28, 2016
 *      Author: Bric Rogers
 */

#ifndef CALLBACK_H
#define CALLBACK_H

namespace stickman_common
{
	// function signature supported:
	//	void func();
	//
	class callback0
	{
	private:

		//  Callback0 interface
		class ICallback0
		{
		public:
			virtual void execute() = 0;
		};

		// Callback1 func signature wrapper
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType>
		class callback0FuncSig : public ICallback0
		{
		public:
			typedef void (InstType::*FuncSigType)();

			callback0FuncSig(InstType* instan, FuncSigType funcPtr)
			{
				_instance = instan;
				_funcPtr = funcPtr;
			}

			void execute()
			{
				(_instance->*_funcPtr)();
			}

			InstType* _instance;
			FuncSigType _funcPtr;
		};

		ICallback0 *_funcSig;

	public:

		// Bind a instance::funcPtr to the callback
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType> void bind(InstType* instance, FuncSigType funcPtr)
		{
			_funcSig = new callback0FuncSig<InstType, FuncSigType>(instance, funcPtr);
		}

		// Execute the callback
		void execute()
		{
			_funcSig->execute();
		}
	};


	// function signature supported:
	//	void func(Type param);
	//
	//	P0 - param type
	//
	template<class P0>
	class callback1
	{
	private:

		//  Callback1 interface
		//
		//	P0 - param type
		template<class P0>
		class ICallback1
		{
		public:
			virtual void execute(P0 param) = 0;
		};

		// Callback1 func signature wrapper
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		// P0 - param type
		template<class InstType, class FuncSigType, typename P0>
		class callback1FuncSig : public ICallback1<P0>
		{
		public:
			typedef void (InstType::*FuncSigType)(P0 param);

			callback1FuncSig(InstType* instan, FuncSigType funcPtr)
			{
				_instance = instan;
				_funcPtr = funcPtr;
			}

			void execute(P0 param)
			{
				(_instance->*_funcPtr)(param);
			}

			InstType* _instance;
			FuncSigType _funcPtr;
		};

		ICallback1<P0> *_funcSig;

	public:

		// Bind a instance::funcPtr to the callback
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType> void bind(InstType* instance, FuncSigType funcPtr)
		{
			_funcSig = new callback1FuncSig<InstType, FuncSigType, P0>(instance, funcPtr);
		}

		// Execute the callback
		//
		// P0 - param type
		void execute(P0 param)
		{
			_funcSig->execute(param);
		}
	};


	// function signature supported:
	//	void func(Type param, Type param1);
	//
	//	P0 - param type
	//  P1- param1 type
	template<class P0, class P1>
	class callback2
	{
	private:

		//  Callback1 interface
		//
		//	P0 - param type
		//  P1 - param1 type
		template<class P0, class P1>
		class ICallback2
		{
		public:
			virtual void execute(P0 param, P1 param1) = 0;
		};

		// Callback2 func signature wrapper
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		// P0 - param type
		// P1 - param1 type
		template<class InstType, class FuncSigType, class P0, class P1>
		class callback2FuncSig : public ICallback2<P0, P1>
		{
		public:
			typedef void (InstType::*FuncSigType)(P0 param, P1 param1);

			callback2FuncSig(InstType* instan, FuncSigType funcPtr)
			{
				_instance = instan;
				_funcPtr = funcPtr;
			}

			void execute(P0 param, P1 param1)
			{
				(_instance->*_funcPtr)(param, param1);
			}

			InstType* _instance;
			FuncSigType _funcPtr;
		};

		ICallback2<P0, P1> *_funcSig;

	public:

		// Bind a instance::funcPtr to the callback
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType> void bind(InstType* instance, FuncSigType funcPtr)
		{
			_funcSig = new callback2FuncSig<InstType, FuncSigType, P0, P1>(instance, funcPtr);
		}

		// Execute the callback
		//
		// P0 - param type
		// P1 - param1 type
		void execute(P0 param, P1 param1)
		{
			_funcSig->execute(param, param1);
		}
	};


	// function signature supported:
	//	void func(Type param, Type param1, Type param2);
	//
	//	P0 - param type
	//  P1- param1 type
	//  P2- param2 type
	template<class P0, class P1, class P2>
	class callback3
	{
	private:

		//  Callback3 interface
		//
		//	P0 - param type
		//  P1 - param1 type
		//  P2 - param1 type
		template<class P0, class P1, class P2>
		class ICallback3
		{
		public:
			virtual void execute(P0 param, P1 param1, P2 param2) = 0;
		};

		// Callback3 func signature wrapper
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		// P0 - param type
		// P1 - param1 type
		// P2 - param2 type
		template<class InstType, class FuncSigType, class P0, class P1, class P2>
		class callback3FuncSig : public ICallback3<P0, P1, P2>
		{
		public:
			typedef void (InstType::*FuncSigType)(P0 param, P1 param1, P2 param2);

			callback3FuncSig(InstType* instan, FuncSigType funcPtr)
			{
				_instance = instan;
				_funcPtr = funcPtr;
			}

			void execute(P0 param, P1 param1, P2 param2)
			{
				(_instance->*_funcPtr)(param, param1, param2);
			}

			InstType* _instance;
			FuncSigType _funcPtr;
		};

		ICallback3<P0, P1, P2> *_funcSig;

	public:

		// Bind a instance::funcPtr to the callback
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType> void bind(InstType* instance, FuncSigType funcPtr)
		{
			_funcSig = new callback3FuncSig<InstType, FuncSigType, P0, P1, P2>(instance, funcPtr);
		}

		// Execute the callback
		//
		// P0 - param type
		// P1 - param1 type
		// P2 - param2 type
		void execute(P0 param, P1 param1, P2 param2)
		{
			_funcSig->execute(param, param1, param2);
		}
	};


	// function signature supported:
	//	void func(Type param, Type param1, Type param2, Type param3);
	//
	//	P0 - param type
	//  P1 - param1 type
	//  P2 - param2 type
	//  P3 - param3 type
	template<class P0, class P1, class P2, class P3>
	class callback4
	{
	private:

		//  Callback4 interface
		//
		//	P0 - param type
		//  P1 - param1 type
		//  P2 - param1 type
		//  P3 - param3 type
		template<class P0, class P1, class P2, class P3>
		class ICallback4
		{
		public:
			virtual void execute(P0 param, P1 param1, P2 param2, P3 param3) = 0;
		};

		// Callback4 func signature wrapper
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		// P0 - param type
		// P1 - param1 type
		// P2 - param2 type
		// P3 - param3 type
		template<class InstType, class FuncSigType, class P0, class P1, class P2, class P3>
		class callback4FuncSig : public ICallback4<P0, P1, P2, P3>
		{
		public:
			typedef void (InstType::*FuncSigType)(P0 param, P1 param1, P2 param2, P3 param3);

			callback4FuncSig(InstType* instan, FuncSigType funcPtr)
			{
				_instance = instan;
				_funcPtr = funcPtr;
			}

			void execute(P0 param, P1 param1, P2 param2, P3 param3)
			{
				(_instance->*_funcPtr)(param, param1, param2, param3);
			}

			InstType* _instance;
			FuncSigType _funcPtr;
		};

		ICallback4<P0, P1, P2, P3> *_funcSig;

	public:

		// Bind a instance::funcPtr to the callback
		//
		// InstType - Class instance type
		// FuncSigType - Func signature type
		template<class InstType, class FuncSigType> void bind(InstType* instance, FuncSigType funcPtr)
		{
			_funcSig = new callback4FuncSig<InstType, FuncSigType, P0, P1, P2, P3>(instance, funcPtr);
		}

		// Execute the callback
		//
		// P0 - param type
		// P1 - param1 type
		// P2 - param2 type
		// P3 - param3 type
		void execute(P0 param, P1 param1, P2 param2, P3 param3)
		{
			_funcSig->execute(param, param1, param2, param3);
		}
	};


} // end namespace

#endif // CALLBACK_H
