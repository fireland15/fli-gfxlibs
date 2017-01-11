#include "OpenGlContext.h"


namespace fli {
	namespace gfx {
		namespace render {
			OpenGlContext::OpenGlContext(HWND hWnd)
				: m_hWnd(hWnd) {
				InitializeGlew();
				InitializeOpenGl();
			}

			OpenGlContext::~OpenGlContext() {
				wglMakeCurrent(m_hDc, 0);
				wglDeleteContext(m_hRc);
				ReleaseDC(m_hWnd, m_hDc);
			}

			void OpenGlContext::Present() {
				SwapBuffers(m_hDc);
			}

			int OpenGlContext::MajorVersion() {
				return m_contextVersionMajor;
			}

			int OpenGlContext::MinorVersion() {
				return m_contextVersionMinor;
			}

			void OpenGlContext::InitializeGlew() {
				HINSTANCE hInstance = GetModuleHandleA(0);

				if (!hInstance) {
					throw std::exception("Could not get instance handle");
				}

				WNDCLASSEX windowClass;
				windowClass.cbSize = sizeof(WNDCLASSEX);
				windowClass.style = CS_OWNDC;
				windowClass.lpfnWndProc = DefWindowProc;
				windowClass.cbClsExtra = 0;
				windowClass.cbWndExtra = 0;
				windowClass.hInstance = hInstance;
				windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
				windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
				windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
				windowClass.lpszMenuName = NULL;
				windowClass.lpszClassName = "fake";
				windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

				RegisterClassEx(&windowClass);

				HWND hWndFake = CreateWindow("fake", "FAKE", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_CLIPCHILDREN,
					0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
					NULL, hInstance, NULL);

				if (!hWndFake) {
					throw std::exception("Unable to create window for GLEW initialization");
				}

				HDC tempDc = GetDC(hWndFake);

				PIXELFORMATDESCRIPTOR pfd;
				memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
				pfd.iPixelType = PFD_TYPE_RGBA;
				pfd.cColorBits = 32;
				pfd.cDepthBits = 32;
				pfd.iLayerType = PFD_MAIN_PLANE;

				int iPixelFormat = ChoosePixelFormat(tempDc, &pfd);
				if (iPixelFormat == 0) {
					throw std::exception("Unable to choose pixel format GLEW initialization");
				}

				if (!SetPixelFormat(tempDc, iPixelFormat, &pfd)) {
					throw std::exception("Unable to set pixel format for GLEW initialization");
				}

				HGLRC hRCFake = wglCreateContext(tempDc);
				wglMakeCurrent(tempDc, hRCFake);

				if (glewInit() != GLEW_OK)
				{
					throw std::exception("GLEW initialization failed");
				}

				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hRCFake);
				ReleaseDC(hWndFake, tempDc);
				DestroyWindow(hWndFake);
			}

			void OpenGlContext::InitializeOpenGl() {
				m_hDc = GetDC(m_hWnd);

				int pixelFormat;

				PIXELFORMATDESCRIPTOR pfd = {
					sizeof(PIXELFORMATDESCRIPTOR),		  //size of the structure	
					1,									  //version, always set to 1,
					PFD_DRAW_TO_WINDOW |				  //support window
					PFD_SUPPORT_OPENGL |				  //support OpenGl
					PFD_DOUBLEBUFFER,					  //support double buffering  
					PFD_TYPE_RGBA,						  //RGBA color mode
					24,									  //go for 32bit color mode		
					0, 0, 0, 0, 0, 0,					  //ignore color bits, not used
					0,									  //no alpha buffer	
					0,									  //ignore shift bit
					0,									  //no accumulation buffer 
					0, 0, 0, 0,							  //ignore accumulation bits
					16,									  //16-bits z-buffer size
					0,									  //no stencil buffer
					0,									  //no auxiliary buffer 	
					PFD_MAIN_PLANE,						  //main drawing plane
					0,									  //reserved 	
					0, 0, 0 };							  //layer masks ignored

				pixelFormat = ChoosePixelFormat(m_hDc, &pfd);

				if (pixelFormat == 0) {
					throw std::exception("Unable to get pixel format to create context");
				}

				if (!SetPixelFormat(m_hDc, pixelFormat, &pfd)) {
					throw std::exception("Failed to set pixel format");
				}

				m_hRc = wglCreateContext(m_hDc);
				if (!wglMakeCurrent(m_hDc, m_hRc)) {
					throw std::exception("Failed to make render context current.");
				}
				
				glGetIntegerv(GL_MAJOR_VERSION, &m_contextVersionMajor);
				glGetIntegerv(GL_MINOR_VERSION, &m_contextVersionMinor);
			}
		}
	}
}