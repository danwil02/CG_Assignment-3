/*
 * Wrapper Class for OpenGL Key State Change Functions
 *
 */

#ifndef MONITOR_GL_H
#define MONITOR_GL_H

#define DEBUG_GL_STATE false
#define DEBUG_GL_BUFFERS false
#define DEBUG_GL_DRAW false

#include "OpenGL_headers.h"

#include <iostream>
using namespace std;

inline void m_glutSwapBuffers()
{
	glutSwapBuffers();
	if(DEBUG_GL_STATE)
		cout << "glutSwapBuffers()" << endl << endl;
}

inline void m_glutPostRedisplay()
{
	glutPostRedisplay();
	if(DEBUG_GL_STATE)
		cout << "glutPostRedisplay()" << endl;
}

inline void m_glEnable(int args)
{
	glEnable(args);

	if(DEBUG_GL_STATE)
		cout << "glEnable(" << args << ")" << endl;
}

inline void m_glDisable(int args)
{
	glDisable(args);

	if(DEBUG_GL_STATE)
		cout << "glDisable(" << args << ")" << endl;
}

inline void m_glPolygonMode(int arg1, int arg2)
{
	glPolygonMode(arg1,arg2);

	if(DEBUG_GL_STATE)
		cout << "glPolygonMode(" << arg1 << ", " << arg2 << ")" << endl;
}

inline void m_glClear(int args)
{
	glClear(args);

	if(DEBUG_GL_STATE)
		cout << "glClear(" << args << ")" << endl;
}

inline void m_glUseProgram(GLuint shader)
{
	glUseProgram(shader);

	if(DEBUG_GL_STATE)
		cout << "glUseProgram(" << shader << ")" << endl;
}

inline void m_glBindVertexArray(GLuint array)
{
	glBindVertexArray(array);

	if(DEBUG_GL_BUFFERS)
		cout << "glBindVertexArray(" << array << ")" << endl;
}

inline void m_glDeleteVertexArrays(int size, const GLuint* arrays)
{
	glDeleteVertexArrays(size,arrays);

	if(DEBUG_GL_BUFFERS)
		cout << "glDeleteVertexArrays(" << size << ", " << arrays << ")" << endl;
}

inline void m_glDeleteBuffers(int size, const GLuint* arrays)
{
	glDeleteBuffers(size,arrays);

	if(DEBUG_GL_BUFFERS)
		cout << "glDeleteBuffers(" << size << ", " << arrays << ")" << endl;
}

inline void m_glDrawElements(GLenum mode,
	 	GLsizei count,
	 	GLenum type,
	 	const GLvoid * indices)
{
	glDrawElements(mode,count,type,indices);
	if(DEBUG_GL_DRAW)
	{
		cout << "glDrawElements(" << mode<<", ";
		cout <<count << ", " << type << ", " << indices << ")" << endl;
	}
}

inline void m_glDrawArrays(GLenum mode, int a, int b)
{
	glDrawArrays(mode,a,b);
	if(DEBUG_GL_DRAW)
		cout << "glDrawArrays(" << mode<<", " << a << ", " << b << ")"<< endl;
}

inline void m_glFlush()
{
	glFlush();
	if(DEBUG_GL_STATE)
		cout << "glFlush()" << endl;
}

#endif
