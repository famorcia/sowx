/**************************************************************************\
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Fabrizio Morciano
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#ifndef SOWX_SOWXGLAREA_H
#define SOWX_SOWXGLAREA_H

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/timer.h>
#include <vector>

class SoWxGLWidgetP;

class SoWxGLArea : public wxGLCanvas
{
public:

    typedef std::vector<int> GLFormat;

    SoWxGLArea(wxWindow *parent,
               const GLFormat& );

    virtual ~SoWxGLArea();

    const wxGLContext *context();

    void makeCurrent();

    static bool isGLFeatureAvailable(const GLFormat& ,
                                     int feature);

protected:
    void OnPaint(wxPaintEvent& event);
    void OnEraseBackground(wxEraseEvent& event);

private:
    void InitGL();

    bool is_gl_initialized;
    wxGLContext* gl_real_context;
    GLFormat gl_format;
    //wxGLAttributes  gl_attributes;

wxDECLARE_NO_COPY_CLASS(SoWxGLArea);
wxDECLARE_EVENT_TABLE();
};

wxDECLARE_EVENT(SO_WX_GL_INIT, wxCommandEvent);
wxDECLARE_EVENT(SO_WX_GL_DRAW, wxCommandEvent);

#endif //SOWX_SOWXGLAREA_H
