/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2014 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef DGL_STANDALONE_WINDOW_HPP_INCLUDED
#define DGL_STANDALONE_WINDOW_HPP_INCLUDED

#include "App.hpp"
#include "Widget.hpp"
#include "Window.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class StandaloneWindow : public App,
                         public Window
{
public:
    StandaloneWindow()
        : App(),
          Window((App&)*this),
          fWidget(nullptr) {}

    void exec()
    {
        Window::show();
        App::exec();
    }

protected:
    void onReshape(uint width, uint height) override
    {
        if (fWidget != nullptr)
            fWidget->setSize(width, height);
        Window::onReshape(width, height);
    }

private:
    Widget* fWidget;

    void _addWidget(Widget* widget) override
    {
        if (fWidget == nullptr)
        {
            fWidget = widget;
            fWidget->setNeedsFullViewport(true);
        }
        Window::_addWidget(widget);
    }

    void _removeWidget(Widget* widget) override
    {
        if (fWidget == widget)
        {
            fWidget->setNeedsFullViewport(false);
            fWidget = nullptr;
        }
        Window::_removeWidget(widget);
    }

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StandaloneWindow)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif // DGL_STANDALONE_WINDOW_HPP_INCLUDED
