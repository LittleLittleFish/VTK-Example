/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCornerChineseAnnotation.h 

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/**********************************************************************

  文件名: vtkCornerChineseAnnotation.h
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

// .NAME vtkCornerChineseAnnotation - text annotation in four corners
// .SECTION Description
// This is an annotation object that manages four text actors / mappers
// to provide annotation in the four corners of a viewport
//
// .SECTION Special input text:
// - <image> : will be replaced with slice number (relative number)
// - <slice> : will be replaced with slice number (relative number)
// - <image_and_max> : will be replaced with slice number and slice max (relative)
// - <slice_and_max> : will be replaced with slice number and slice max (relative)
// - <slice_pos> : will be replaced by the position of the current slice
// - <window> : will be replaced with window value
// - <level> : will be replaced with level value
// - <window_level> : will be replaced with window and level value
//
// .SECTION See Also
// vtkActor2D vtkFTGLChineseCharacterMapper

#ifndef __vtkCornerChineseAnnotation_h
#define __vtkCornerChineseAnnotation_h

#include "vtkActor2D.h"

class vtkFTGLChineseCharacterMapper;
class vtkImageMapToWindowLevelColors;
class vtkImageActor;
class vtkTextUnicodeProperty;

class vtkCornerChineseAnnotation : public vtkActor2D
{
public:
  vtkTypeMacro(vtkCornerChineseAnnotation,vtkActor2D);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Instantiate object with a rectangle in normaled view coordinates
  // of (0.2,0.85, 0.8, 0.95).
  static vtkCornerChineseAnnotation *New();
  
  // Description:
  // Draw the scalar bar and annotation text to the screen.
  int RenderOpaqueGeometry(vtkViewport* viewport);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport* ) {return 0;};
  int RenderOverlay(vtkViewport* viewport);

  // Description:
  // Does this prop have some translucent polygonal geometry?
  virtual int HasTranslucentPolygonalGeometry();
  
  // Description:
  // Set/Get the maximum height of a line of text as a 
  // percentage of the vertical area allocated to this
  // scaled text actor. Defaults to 1.0
  vtkSetMacro(MaximumLineHeight,double);
  vtkGetMacro(MaximumLineHeight,double);
  
  // Description:
  // Set/Get the minimum/maximum size font that will be shown.
  // If the font drops below the minimum size it will not be rendered.
  vtkSetMacro(MinimumFontSize,int);
  vtkGetMacro(MinimumFontSize,int);
  vtkSetMacro(MaximumFontSize,int);
  vtkGetMacro(MaximumFontSize,int);

  // Description:
  // Set/Get font scaling factors
  // The font size, f, is calculated as the largest possible value
  // such that the annotations for the given viewport do not overlap. 
  // This font size is scaled non-linearly with the viewport size,
  // to maintain an acceptable readable size at larger viewport sizes, 
  // without being too big.
  // f' = linearScale * pow(f,nonlinearScale)
  vtkSetMacro( LinearFontScaleFactor, double );
  vtkGetMacro( LinearFontScaleFactor, double );
  vtkSetMacro( NonlinearFontScaleFactor, double );
  vtkGetMacro( NonlinearFontScaleFactor, double );

  // Description:
  // Release any graphics resources that are being consumed by this actor.
  // The parameter window could be used to determine which graphic
  // resources to release.
  virtual void ReleaseGraphicsResources(vtkWindow *);

  // Description:
  // Set/Get the text to be displayed for each corner
  void SetText(int i, const char *text);
  const char* GetText(int i);
  void ClearAllTexts();
  void CopyAllTextsFrom(vtkCornerChineseAnnotation *ca);

  // Description:
  // Set an image actor to look at for slice information
  void SetImageActor(vtkImageActor*);
  vtkGetObjectMacro(ImageActor,vtkImageActor);
  
  // Description:
  // Set an instance of vtkImageMapToWindowLevelColors to use for
  // looking at window level changes
  void SetWindowLevel(vtkImageMapToWindowLevelColors*);
  vtkGetObjectMacro(WindowLevel,vtkImageMapToWindowLevelColors);

  // Description:
  // Set the value to shift the level by.
  vtkSetMacro(LevelShift, double);
  vtkGetMacro(LevelShift, double);
  
  // Description:
  // Set the value to scale the level by.
  vtkSetMacro(LevelScale, double);
  vtkGetMacro(LevelScale, double);
  
  // Description:
  // Set/Get the text property of all corners.
  virtual void SetTextProperty(vtkTextUnicodeProperty *p);
  vtkGetObjectMacro(TextProperty,vtkTextUnicodeProperty);

  // Description:
  // Even if there is an image actor, should `slice' and `image' be displayed?
  vtkBooleanMacro(ShowSliceAndImage, int);
  vtkSetMacro(ShowSliceAndImage, int);
  vtkGetMacro(ShowSliceAndImage, int);
  
protected:
  vtkCornerChineseAnnotation();
  ~vtkCornerChineseAnnotation();

  double MaximumLineHeight;

  vtkTextUnicodeProperty *TextProperty;

  vtkImageMapToWindowLevelColors *WindowLevel;
  double LevelShift;
  double LevelScale;
  vtkImageActor *ImageActor;
  vtkImageActor *LastImageActor;

  char *CornerText[4];
  
  int FontSize;
  vtkActor2D    *TextActor[4];
  vtkTimeStamp   BuildTime;
  int            LastSize[2];
  vtkFTGLChineseCharacterMapper *TextMapper[4];

  int MinimumFontSize;
  int MaximumFontSize;

  double LinearFontScaleFactor;
  double NonlinearFontScaleFactor;
  
  int ShowSliceAndImage;
  
  // Description:
  // Search for replacable tokens and replace
  virtual void TextReplace(
    vtkImageActor *ia, vtkImageMapToWindowLevelColors *wl);

  // Description:
  // Set text actor positions given a viewport size and justification
  virtual void SetTextActorsPosition(int vsize[2]);
  virtual void SetTextActorsJustification();

private:
  vtkCornerChineseAnnotation(const vtkCornerChineseAnnotation&);  // Not implemented.
  void operator=(const vtkCornerChineseAnnotation&);  // Not implemented.
};


#endif



