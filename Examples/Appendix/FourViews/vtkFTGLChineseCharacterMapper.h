/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkFTGLChineseCharacterMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/**********************************************************************

  文件名: vtkFTGLChineseCharacterMapper.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifndef __vtkFTGLChineseCharacterMapper_h
#define __vtkFTGLChineseCharacterMapper_h

#include "vtkTextMapper.h"
#include "vtkTextUnicodeProperty.h"

class vtkFTGLChineseCharacterMapper : public vtkTextMapper
{

public:
	vtkTypeMacro(vtkFTGLChineseCharacterMapper,vtkTextMapper);
	static vtkFTGLChineseCharacterMapper *New();
	virtual void PrintSelf(ostream& os, vtkIndent indent);

	// Description:
	// Actally draw the text.
	void RenderOverlay(vtkViewport* viewport, vtkActor2D* actor);

	// Description:
	// Release any graphics resources that are being consumed by this actor.
	// The parameter window could be used to determine which graphic
	// resources to release.
	virtual void ReleaseGraphicsResources(vtkWindow *);

	// Description:
	// Return the size[2]/width/height of the rectangle required to draw this
	// mapper (in pixels).
	virtual void GetSize(vtkViewport* viewport, int size[2]);

	virtual void SetInput(const char *inputString);

	// Description:
	// Shallow copy of an actor.
	void ShallowCopy(vtkFTGLChineseCharacterMapper *m);

	// Description:
	// Set/Get the text property.
	void SetTextProperty(vtkTextUnicodeProperty *p);
	vtkTextUnicodeProperty* GetTextProperty();

protected:
	vtkFTGLChineseCharacterMapper(void);
	~vtkFTGLChineseCharacterMapper(void);

	// These functions are used to parse, process, and render multiple lines 
	char *NextLine(const char *input, int lineNum);
	void GetMultiLineSize(vtkViewport* viewport, int size[2]);
	void RenderOverlayMultipleLines(vtkViewport *viewport, vtkActor2D *actor);

	vtkTimeStamp  SizeBuildTime;
	int LastSize[2];
	int LastLargestDescender;

	vtkFTGLChineseCharacterMapper **m_TextLines;
	vtkTextUnicodeProperty *m_TextUnicodeProperty;

private:
	vtkFTGLChineseCharacterMapper(const vtkFTGLChineseCharacterMapper&);  // Not implemented.
	void operator=(const vtkFTGLChineseCharacterMapper&);  // Not implemented.
};

#endif
