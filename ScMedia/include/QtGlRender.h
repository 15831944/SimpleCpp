#pragma once
#ifndef QT_GL_RENDER_H
#define QT_GL_RENDER_H
#include "Render.h"
#include "MediaSdkDef.h"

#ifdef QT_OPENGL
#include <gl/glew.h>
#include <QGLWidget>
#include "glwindow.h"

#pragma  comment(lib, "QtGuid4.lib");
#pragma comment(lib, "QtOpenGLd4.lib");
#pragma comment(lib, "QtCored4.lib");
#pragma comment(lib, "opengl32.lib");
#pragma comment(lib, "glu32.lib");

class QWidget;
class QGLWidget;
//qt ��opengl render
class CQtGlRender :
	public CRender
{
public:
	CQtGlRender(void);
	virtual ~CQtGlRender(void);
	
	int Open(HWND pParent, int nPlayBuffer=5);
	
	virtual int DoFilter();
protected:
	CGlWindow *m_pGlWidget;

	//��һ֡���ŵ�ʱ���, ms
	long m_nTimeLastFrame;
	//ƽ��ÿ֡��Ҫ��ʱ��, ms
	long m_nTimePerFrame;
	//ʱ��ͳ��
	long m_nTimeStatBegin;
	long m_nFrameCount;
};
#endif

#endif
