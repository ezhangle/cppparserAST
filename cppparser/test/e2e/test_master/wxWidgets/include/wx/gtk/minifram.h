/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/minifram.h
// Purpose:     wxMiniFrame class
// Author:      Robert Roebling
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_MINIFRAME_H_
#  define _WX_GTK_MINIFRAME_H_
#  include "wx/bitmap.h"
#  include "wx/frame.h"
//-----------------------------------------------------------------------------
// wxMiniFrame
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxMiniFrame : public wxFrame
{
  wxDECLARE_DYNAMIC_CLASS(wxMiniFrame);
public:
  wxMiniFrame()
  {
  }
  wxMiniFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION | wxRESIZE_BORDER, const wxString& name = wxASCII_STR(wxFrameNameStr))
  {
    Create(parent, id, title, pos, size, style, name);
  }
  ~wxMiniFrame();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION | wxRESIZE_BORDER, const wxString& name = wxASCII_STR(wxFrameNameStr));
  void SetTitle(const wxString& title) override;
protected:
  void DoSetSizeHints(int minW, int minH, int maxW, int maxH, int incW, int incH) override;
  void DoGetClientSize(int* width, int* height) const override;
 // implementation
public:
#  ifndef __WXGTK4__
  bool m_isDragMove;
  wxSize m_dragOffset;
#  endif
  wxBitmap m_closeButton;
  int m_miniEdge;
  int m_miniTitle;
};
#endif
