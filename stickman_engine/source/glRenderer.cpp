#include "gl_Renderer.h"

#include <Windows.h>
#include <gl\GL.h>
#include <GL/glu.h> 	// OpenGL Helper/Utility functions
#include <math.h>

namespace stickman_engine
{
	gl_Renderer::gl_Renderer()
	{
		//_sg = 0;
		//_camera = 0;

		// Perspective defaults
		_fovy = 20.0;
		_nearClipping = 1.0;
		_farClipping = 300.0;
	}

	gl_Renderer::~gl_Renderer()
	{
		//if (_sg = 0)
		//{
		//	delete _sg;
		//	_sg = 0;
		//}

		//_camera = 0;
	}

	bool gl_Renderer::init(int w, int h)
	{ 

		GLuint VertexArrayID;

		//glGenVertexArrays(1, &VertexArrayID);

		//glBindVertexArray(VertexArrayID);



		//glClearColor(0.0, 0.0, 0.0, 0);

		// enables
		//glEnable(GL_DEPTH_TEST);
		
		//resize(_w, _h);

		//buildFont();

		////Allocate scene graph memory
		//_sg = new sceneGraph();

		////load up the sg
		//if (!_sg)
		//	return false;

		//_sg->load();

		return true;
	}

	//node * gl_Renderer::findNodeByName(std::string name)
	//{
	//	return _sg->findNode(name);
	//}

	//void gl_Renderer::addNode(node *child, node *parent)
	//{
	//	_sg->addNode(child, parent);
	//}

	void gl_Renderer::resize(int w, int h)
	{
		// Set the new viewport size
		glViewport(0, 0, w, h);
		_w = w;
		_h = h;

		// Use the projection matrix to setup/modify window params
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Perspective
		gluPerspective(_fovy, w / h, _nearClipping, _farClipping);
	}

	void gl_Renderer::render()
	{

	}

	//void gl_Renderer::render()
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();

	//	// Update the camera (add the view matrix to the current model matrix
	//	//glMultMatrixd(_camera->getViewMatrix().getData());

	//	// Camera transforms
	//	glRotatef(-20, 0, 1, 0);
	//	glRotatef(-70, 1, 0, 0);
	//	glRotatef(0, 0, 0, 1);
	//	glTranslatef(1,0,-120);

	//	// Ref grid
	//	drawReferenceGrid(-10.0, 10.0, 1.0, 0.0, -10.0, 10.0, 1.0, 0.0, -10.0, 10.0);


	//	// Switch to black, then draw the frame
	//	glColor3f(0.0, 0.0, 0.0);

	//	//_sg->frame();

	//	// Draw text
	//	//glLoadIdentity();
	//	//glColor3f(.9, .9, 0);
	//	//glRasterPos3f(-.87, .83, -5);
	//	//glPrint("fps: %.1f", _bufferedFPS);


	//	// Finalize the frame
	//	//SDL_GL_SwapBuffers();
	//}

	//void glRenderer::setFPS(float a)
	//{
	//	_bufferedFPS = a;
	//}

	//void glRenderer::setCamera(camera * cam)
	//{
	//	_camera = cam;
	//}

	//void glRenderer::killFont()
	//{
	//	glDeleteLists(base, 96);
	//}

	//void glRenderer::buildFont()
	//{
	//	HFONT	font;										// Windows Font ID
	//	HFONT	oldfont;									// Used For Good House Keeping

	//	base = glGenLists(96);								// Storage For 96 Characters

	//	font = CreateFont(16,							// Height Of Font
	//		0,								// Width Of Font
	//		0,								// Angle Of Escapement
	//		0,								// Orientation Angle
	//		FW_BOLD,						// Font Weight
	//		FALSE,							// Italic
	//		FALSE,							// Underline
	//		FALSE,							// Strikeout
	//		ANSI_CHARSET,					// Character Set Identifier
	//		OUT_TT_PRECIS,					// Output Precision
	//		CLIP_DEFAULT_PRECIS,			// Clipping Precision
	//		ANTIALIASED_QUALITY,			// Output Quality
	//		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
	//		TEXT("Courier New"));					// Font Name

	//	HDC hDC = wglGetCurrentDC();
	//	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	//	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	//	SelectObject(hDC, oldfont);							// Selects The Font We Want
	//	DeleteObject(font);
	//}

	//void glRenderer::glPrint(const char *fmt, ...)
	//{
	//	char		text[256];								// Holds Our String
	//	va_list		ap;										// Pointer To List Of Arguments

	//	if (fmt == NULL)									// If There's No Text
	//		return;											// Do Nothing

	//	va_start(ap, fmt);									// Parses The String For Variables
	//	vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	//	va_end(ap);											// Results Are Stored In Text

	//	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	//	glListBase(base - 32);								// Sets The Base Character to 32
	//	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	//	glPopAttrib();
	//}

	void gl_Renderer::drawReferenceGrid(float xlo, float xhi, float xinc, float xheavy,
		float ylo, float yhi, float yinc, float yheavy, float zlo, float zhi)
	{

		// We want to always draw the reference grid on the bottom of everything, disable the depth testing
		//  glDisable( GL_DEPTH_TEST );

		float xzero = xinc / 10.0f;
		float yzero = yinc / 10.0f;

		float xx = xhi + xzero;
		float yy = yhi + yzero;

		// Draw X grid
		for (float x = xlo; x<xx; x += xinc)
		{
			if (fabs(x) < xheavy + xzero)
				glColor3f(0.0f, 1.0f, 0.0f);         // Green
			else
				glColor3f(0.8f, 0.8f, 0.8f);         // Grey

			glBegin(GL_LINES);
			glVertex3f(x, ylo, 0);
			glVertex3f(x, yhi, 0);
			glEnd();
		}

		//Draw Y grid
		for (float y = ylo; y<yy; y += yinc) {
			if (fabs(y) < yheavy + yzero) {
				glColor3f(1.0, 0.0, 0.0);         // Red
			}
			else {
				glColor3f(0.8f, 0.8f, 0.8f);         // Grey
			}
			glBegin(GL_LINES);
			glVertex3f(xlo, y, 0);
			glVertex3f(xhi, y, 0);
			glEnd();
		}

		// Draw Z line
		glColor3f(0.0, 0.0, 1.0);                           // Blue
		glBegin(GL_LINES);
		glVertex3f(0, 0, zlo);
		glVertex3f(0, 0, zhi);
		glEnd();


		// glEnable( GL_DEPTH_TEST );          // re enable the depth test
	}



} // end namespace

