/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/glcanvas.h
// Purpose:     wxGLCanvas, for using OpenGL/Mesa with wxWidgets and GTK
// Author:      Robert Roebling
// Modified by:
// Created:     17/8/98
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GLCANVAS_H_
#  define _WX_GLCANVAS_H_
#  include "wx/setup.h"
#  if  wxUSE_GLCANVAS_EGL
#    include "wx/unix/glegl.h"
typedef wxGLCanvasEGL wxGLCanvasImpl;
#  else 
#    include "wx/unix/glx11.h"
typedef wxGLCanvasX11 wxGLCanvasImpl;
#  endif
//---------------------------------------------------------------------------
// wxGLCanvas
//---------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLCanvas : public wxGLCanvasImpl
{
  typedef wxGLCanvasImpl BaseType;
public:
  wxGLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  explicit wxGLCanvas(wxWindow* parent, wxWindowID id = wxID_ANY, const int* attribList = NULL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  bool Create(wxWindow* parent, const wxGLAttributes& dispAttrs, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const int* attribList = NULL, const wxPalette& palette = wxNullPalette);
  bool SetBackgroundStyle(wxBackgroundStyle style) override;
    // implement wxGLCanvasX11 methods
    // --------------------------------
  unsigned long GetXWindow() const override;
  void* GetNativeWindow() const;
    // deprecated methods
    // ------------------

#if WXWIN_COMPATIBILITY_2_8
    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               const wxGLContext *shared,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    wxDEPRECATED(
    wxGLCanvas(wxWindow *parent,
               const wxGLCanvas *shared,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const int *attribList = NULL,
               const wxPalette& palette = wxNullPalette)
    );

    // called from "realized" callback to create the implicit context if needed
    void GTKInitImplicitContext();
#endif // WXWIN_COMPATIBILITY_2_8

    // implementation from now on
  void GTKHandleRealized() override;
#  ifdef __WXGTK3__
  wxSize m_size;
#  endif
private:
  wxDECLARE_CLASS(wxGLCanvas);
};
#endif
