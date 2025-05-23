/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/laywin.h
// Purpose:     Implements a simple layout algorithm, plus
//              wxSashLayoutWindow which is an example of a window with
//              layout-awareness (via event handlers). This is suited to
//              IDE-style window layout.
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_LAYWIN_H_G_
#  define _WX_LAYWIN_H_G_
#  if  wxUSE_SASH
#    include "wx/sashwin.h"
#  endif
#  include "wx/event.h"
class WXDLLIMPEXP_FWD_CORE wxQueryLayoutInfoEvent;
class WXDLLIMPEXP_FWD_CORE wxCalculateLayoutEvent;
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_CORE, wxEVT_QUERY_LAYOUT_INFO, wxQueryLayoutInfoEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_CORE, wxEVT_CALCULATE_LAYOUT,  wxCalculateLayoutEvent );
enum wxLayoutOrientation {
    wxLAYOUT_HORIZONTAL,
    wxLAYOUT_VERTICAL
};
enum wxLayoutAlignment {
    wxLAYOUT_NONE,
    wxLAYOUT_TOP,
    wxLAYOUT_LEFT,
    wxLAYOUT_RIGHT,
    wxLAYOUT_BOTTOM
};
// Not sure this is necessary
// Tell window which dimension we're sizing on
#  define wxLAYOUT_LENGTH_Y	0x0008
#  define wxLAYOUT_LENGTH_X	0x0000
// Use most recently used length
#  define wxLAYOUT_MRU_LENGTH	0x0010
// Only a query, so don't actually move it.
#  define wxLAYOUT_QUERY	0x0100
/*
 * This event is used to get information about window alignment,
 * orientation and size.
 */
class WXDLLIMPEXP_CORE wxQueryLayoutInfoEvent : public wxEvent
{
public:
  wxQueryLayoutInfoEvent(wxWindowID id = 0)
  {
    SetEventType(wxEVT_QUERY_LAYOUT_INFO);
    m_requestedLength = 0;
    m_flags = 0;
    m_id = id;
    m_alignment = wxLAYOUT_TOP;
    m_orientation = wxLAYOUT_HORIZONTAL;
  }
    // Read by the app
  void SetRequestedLength(int length)
  {
    m_requestedLength = length;
  }
  int GetRequestedLength() const
  {
    return m_requestedLength;
  }
  void SetFlags(int flags)
  {
    m_flags = flags;
  }
  int GetFlags() const
  {
    return m_flags;
  }
    // Set by the app
  void SetSize(const wxSize& size)
  {
    m_size = size;
  }
  wxSize GetSize() const
  {
    return m_size;
  }
  void SetOrientation(wxLayoutOrientation orient)
  {
    m_orientation = orient;
  }
  wxLayoutOrientation GetOrientation() const
  {
    return m_orientation;
  }
  void SetAlignment(wxLayoutAlignment align)
  {
    m_alignment = align;
  }
  wxLayoutAlignment GetAlignment() const
  {
    return m_alignment;
  }
  wxEvent* Clone() const override
  {
    return new wxQueryLayoutInfoEvent(*this);
  }
protected:
  int m_flags;
  int m_requestedLength;
  wxSize m_size;
  wxLayoutOrientation m_orientation;
  wxLayoutAlignment m_alignment;
private:
  wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxQueryLayoutInfoEvent);
};
typedef void (*wxQueryLayoutInfoEventFunction) (wxQueryLayoutInfoEvent&);
#  define wxQueryLayoutInfoEventHandler( func ) \
    wxEVENT_HANDLER_CAST( wxQueryLayoutInfoEventFunction, func )
#  define EVT_QUERY_LAYOUT_INFO(func)	 \
    wxDECLARE_EVENT_TABLE_ENTRY( wxEVT_QUERY_LAYOUT_INFO, wxID_ANY, wxID_ANY, wxQueryLayoutInfoEventHandler( func ), NULL ),
/*
 * This event is used to take a bite out of the available client area.
 */
class WXDLLIMPEXP_CORE wxCalculateLayoutEvent : public wxEvent
{
public:
  wxCalculateLayoutEvent(wxWindowID id = 0)
  {
    SetEventType(wxEVT_CALCULATE_LAYOUT);
    m_flags = 0;
    m_id = id;
  }
    // Read by the app
  void SetFlags(int flags)
  {
    m_flags = flags;
  }
  int GetFlags() const
  {
    return m_flags;
  }
    // Set by the app
  void SetRect(const wxRect& rect)
  {
    m_rect = rect;
  }
  wxRect GetRect() const
  {
    return m_rect;
  }
  wxEvent* Clone() const override
  {
    return new wxCalculateLayoutEvent(*this);
  }
protected:
  int m_flags;
  wxRect m_rect;
private:
  wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxCalculateLayoutEvent);
};
typedef void (*wxCalculateLayoutEventFunction) (wxCalculateLayoutEvent&);
#  define wxCalculateLayoutEventHandler( func ) wxEVENT_HANDLER_CAST(wxCalculateLayoutEventFunction, func)
#  define EVT_CALCULATE_LAYOUT(func)	 \
    wxDECLARE_EVENT_TABLE_ENTRY( wxEVT_CALCULATE_LAYOUT, wxID_ANY, wxID_ANY, wxCalculateLayoutEventHandler( func ), NULL ),
#  if  wxUSE_SASH
// This is window that can remember alignment/orientation, does its own layout,
// and can provide sashes too. Useful for implementing docked windows with sashes in
// an IDE-style interface.
class WXDLLIMPEXP_CORE wxSashLayoutWindow : public wxSashWindow
{
public:
  wxSashLayoutWindow()
  {
    Init();
  }
  wxSashLayoutWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSW_3D | wxCLIP_CHILDREN, const wxString& name = wxT("layoutWindow"))
  {
    Create(parent, id, pos, size, style, name);
  }
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSW_3D | wxCLIP_CHILDREN, const wxString& name = wxT("layoutWindow"));
// Accessors
  inline wxLayoutAlignment GetAlignment() const
  {
    return m_alignment;
  }
  inline wxLayoutOrientation GetOrientation() const
  {
    return m_orientation;
  }
  inline void SetAlignment(wxLayoutAlignment align)
  {
    m_alignment = align;
  }
  inline void SetOrientation(wxLayoutOrientation orient)
  {
    m_orientation = orient;
  }
    // Give the window default dimensions
  inline void SetDefaultSize(const wxSize& size)
  {
    m_defaultSize = size;
  }
// Event handlers
    // Called by layout algorithm to allow window to take a bit out of the
    // client rectangle, and size itself if not in wxLAYOUT_QUERY mode.
  void OnCalculateLayout(wxCalculateLayoutEvent& event);
    // Called by layout algorithm to retrieve information about the window.
  void OnQueryLayoutInfo(wxQueryLayoutInfoEvent& event);
private:
  void Init();
  wxLayoutAlignment m_alignment;
  wxLayoutOrientation m_orientation;
  wxSize m_defaultSize;
private:
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxSashLayoutWindow);
  wxDECLARE_EVENT_TABLE();
};
#  endif
class WXDLLIMPEXP_FWD_CORE wxMDIParentFrame;
class WXDLLIMPEXP_FWD_CORE wxFrame;
// This class implements the layout algorithm
class WXDLLIMPEXP_CORE wxLayoutAlgorithm : public wxObject
{
public:
  wxLayoutAlgorithm()
  {
  }
#  if  wxUSE_MDI_ARCHITECTURE
    // The MDI client window is sized to whatever's left over.
  bool LayoutMDIFrame(wxMDIParentFrame* frame, wxRect* rect = NULL);
#  endif
    // mainWindow is sized to whatever's left over. This function for backward
    // compatibility; use LayoutWindow.
  bool LayoutFrame(wxFrame* frame, wxWindow* mainWindow = NULL);
    // mainWindow is sized to whatever's left over.
  bool LayoutWindow(wxWindow* frame, wxWindow* mainWindow = NULL);
};
#endif
    // _WX_LAYWIN_H_G_
