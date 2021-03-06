/**********************************************************************

  文件名: vtkDisplayChinese.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageMapper3D.h>
#include <vtkTextMapper.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include "vtkFTGLChineseCharacterMapper.h"
#include "vtkTextUnicodeProperty.h"

int main(int argc, char *argv[])
{
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	renWin->Render();
	renWin->SetWindowName("Display Chinese Characters");
	renWin->AddRenderer(renderer);
	renWin->SetSize(640,480);
	renderer->SetBackground(1.0, 1.0, 1.0);
	interactor->SetInteractorStyle(style);
	interactor->SetRenderWindow(renWin);

	//////////////////////////////////////////////////////////////////////////
	// single line text property
	vtkSmartPointer< vtkTextUnicodeProperty > singleLineTextProp = vtkSmartPointer< vtkTextUnicodeProperty >::New();
	singleLineTextProp->SetFontSize(30);
	singleLineTextProp->BoldOff();
	singleLineTextProp->ItalicOff();
	singleLineTextProp->ShadowOff();
	singleLineTextProp->SetColor(1,0,0);
	singleLineTextProp->SetVerticalJustificationToBottom();
	singleLineTextProp->SetFontFileName("C:\\Windows\\Fonts\\simhei.ttf"); 

	 // the text is on a single line
	vtkSmartPointer<vtkFTGLChineseCharacterMapper> singleLineText = vtkSmartPointer<vtkFTGLChineseCharacterMapper>::New();
	singleLineText->SetInput("单行中文- http://www.vtkchina.org");
	singleLineText->SetTextProperty(singleLineTextProp);

	// single line text actor
	vtkSmartPointer< vtkActor2D > singleLineTextActor = vtkSmartPointer< vtkActor2D >::New();
	singleLineTextActor->SetMapper(singleLineText);
	singleLineTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
	singleLineTextActor->GetPositionCoordinate()->SetValue(0.01, 0.2);

	//////////////////////////////////////////////////////////////////////////
	// multi-line text property
	vtkSmartPointer< vtkTextUnicodeProperty > multiLineTextProp = vtkSmartPointer< vtkTextUnicodeProperty >::New();
	multiLineTextProp->SetFontSize(30);
	multiLineTextProp->BoldOff();
	multiLineTextProp->ItalicOff();
	multiLineTextProp->ShadowOff();
	multiLineTextProp->SetColor(0,0,1);
	multiLineTextProp->SetVerticalJustificationToBottom();
	multiLineTextProp->SetFontFileName("C:\\Windows\\Fonts\\simhei.ttf"); 

	// the text is on multi lines
	vtkSmartPointer<vtkFTGLChineseCharacterMapper> multiLineText = vtkSmartPointer<vtkFTGLChineseCharacterMapper>::New();
	multiLineText->SetInput("  静夜思\n   李白\n窗前明月光\n疑是地上霜\n举头望明月\n低头思故乡");
	multiLineText->SetTextProperty(multiLineTextProp);

	// multi lines text actor
	vtkSmartPointer< vtkActor2D > multiLineTextActor = vtkSmartPointer< vtkActor2D >::New();
	multiLineTextActor->SetMapper(multiLineText);
	multiLineTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
	multiLineTextActor->GetPositionCoordinate()->SetValue(0.35, 0.5);

	renderer->AddActor2D(singleLineTextActor);
	renderer->AddActor2D(multiLineTextActor);

	renWin->Render();
	interactor->Initialize();
	interactor->Start();

	return EXIT_SUCCESS;
}