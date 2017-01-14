#pragma once

enum class eKeyboardInput {
	Backspace		= 0x08,	// VK_BACK		0x08
	Tab				= 0x09,	// VK_TAB		0x09
	Enter			= 0x0D,	// VK_RETURN	0x0D
	Shift			= 0x10,	// VK_SHIFT		0x10
	Ctrl			= 0x11,	// VK_CONTROL	0x11
	Alt				= 0x12,	// VK_MENU		0x12
	Pause			= 0x13,	// VK_PAUSE		0x13
	CapsLock		= 0x14,	// VK_CAPITAL	0x14
	Escape			= 0x1B,	// VK_ESCAPE	0x1B
	Space			= 0x20,	// VK_SPACE		0x20
	PageUp			= 0x21,	// VK_PRIOR		0x21
	PageDown		= 0x22,	// VK_NEXT		0x22
	End				= 0x23,	// VK_END		0x23
	Home			= 0x24,	// VK_HOME		0x24

	ArrowLeft		= 0x25,	// VK_LEFT		0x25
	ArrowUp			= 0x26,	// VK_UP		0x26
	ArrowRight		= 0x27,	// VK_RIGHT		0x27
	ArrowDown		= 0x28,	// VK_DOWN		0x28

	PrintScreen		= 0x2C,	// VK_SNAPSHOT	0x2C
	Insert			= 0x2D,	// VK_INSERT	0x2D
	Delete			= 0x2E,	// VK_DELETE	0x2E

	Zero			= 0x30,	//				0x30
	One				= 0x31,	//				0x31
	Two				= 0x32,	//				0x32
	Three			= 0x33,	//				0x33
	Four			= 0x34,	//				0x34
	Five			= 0x35,	//				0x35
	Six				= 0x36,	//				0x36
	Seven			= 0x37,	//				0x37
	Eight			= 0x38,	//				0x38
	Nine			= 0x39,	//				0x39

	A				= 0x41,	//				0x41
	B				= 0x42,	//				0x42
	C				= 0x43,	//				0x43
	D				= 0x44,	//				0x44
	E				= 0x45,	//				0x45
	F				= 0x46,	//				0x46
	G				= 0x47,	//				0x47
	H				= 0x48,	//				0x48
	I				= 0x49,	//				0x49
	J				= 0x4A,	//				0x4A
	K				= 0x4B,	//				0x4B
	L				= 0x4C,	//				0x4C
	M				= 0x4D,	//				0x4D
	N				= 0x4E,	//				0x4E
	O				= 0x4F,	//				0x4F
	P				= 0x50,	//				0x50
	Q				= 0x51,	//				0x51
	R				= 0x52,	//				0x52
	S				= 0x53,	//				0x53
	T				= 0x54,	//				0x54
	U				= 0x55,	//				0x55
	V				= 0x56,	//				0x56
	W				= 0x57,	//				0x57
	X				= 0x58,	//				0x58
	Y				= 0x59,	//				0x59
	Z				= 0x5a,	//				0x5a

	WindowsLeft		= 0x5B,	// VK_LWIN		0x5B
	WindowsRight	= 0x5C,	// VK_LWIN		0x5C

	NumZero			= 0x60,	// VK_NUMPAD0	0x60
	NumOne			= 0x61,	// VK_NUMPAD1	0x61
	NumTwo			= 0x62,	// VK_NUMPAD2	0x62
	NumThree		= 0x63,	// VK_NUMPAD3	0x63
	NumFour			= 0x64,	// VK_NUMPAD4	0x64
	NumFive			= 0x65,	// VK_NUMPAD5	0x65
	NumSix			= 0x66,	// VK_NUMPAD6	0x66
	NumSeven		= 0x67,	// VK_NUMPAD7	0x67
	NumEight		= 0x68,	// VK_NUMPAD8	0x68
	NumNine			= 0x69,	// VK_NUMPAD9	0x69

	NumMultiply		= 0x6A,	// VK_MULTIPLY	0x6A
	NumAdd			= 0x6B,	// VK_ADD		0x6B
	NumSubtract		= 0x6D,	// VK_SUBTRACT	0x6D
	NumDecimal		= 0x6E,	// VK_DECIMAL	0x6E
	NumDivide		= 0x6F,	// VK_DIVIDE	0x6F

	Function1		= 0x70,	// VK_F1		0x70
	Function2		= 0x71,	// VK_F2		0x71
	Function3		= 0x72,	// VK_F3		0x72
	Function4		= 0x73,	// VK_F4		0x73
	Function5		= 0x74,	// VK_F5		0x74
	Function6		= 0x75,	// VK_F6		0x75
	Function7		= 0x76,	// VK_F7		0x76
	Function8		= 0x77,	// VK_F8		0x77
	Function9		= 0x78,	// VK_F9		0x78
	Function10		= 0x79,	// VK_F10		0x79
	Function11		= 0x7A,	// VK_F11		0x7A
	Function12		= 0x7B,	// VK_F12		0x7B

	NumLock			= 0x90,	// VK_NUMLOCK	0x90
	Scroll			= 0x91,	// VK_SCROLL	0x91
	ShiftLeft		= 0xA0,	// VK_LSHIFT	0xA0
	ShiftRight		= 0xA1,	// VK_RSHIFT	0xA1
	ControlLeft		= 0xA2,	// VK_LCONTROL	0xA2
	ControlRight	= 0xA3,	// VK_RCONTROL	0xA3
	AltLeft			= 0xA4,	// VK_LMENU		0xA4
	AltRight		= 0xA5,	// VK_RMENU		0xA5
};

enum class eKeyState {
	Up,
	Down
};