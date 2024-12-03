// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Event.h>
#include <dtk/ui/WidgetOptions.h>

#include <list>

namespace dtk
{
    class IWindow;

    //! Base class for widgets.
    class IWidget : public std::enable_shared_from_this<IWidget>
    {
        DTK_NON_COPYABLE(IWidget);

    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent);

        IWidget();

    public:
        virtual ~IWidget() = 0;

        //! Get the context.
        std::shared_ptr<Context> getContext() const;

        //! Get the object name.
        const std::string& getObjectName() const;

        //! Set the object name.
        void setObjectName(const std::string&);

        //! Get the object path.
        std::string getObjectPath() const;

        //! Get the background role.
        ColorRole getBackgroundRole() const;

        //! Set the background role.
        void setBackgroundRole(ColorRole);

        //! Get whether updates are needed.
        int getUpdates() const;

        //! Hierarchy
        ///@{

        //! Get the parent widget.
        const std::weak_ptr<IWidget>& getParent() const;

        //! Set the parent widget.
        void setParent(const std::shared_ptr<IWidget>&);

        //! Get the children widgets.
        const std::list<std::shared_ptr<IWidget> >& getChildren() const;

        //! Get the first parent widget of the given type.
        template<typename T>
        std::shared_ptr<T> getParentT() const;

        //! Move the child widget to the front of the drawing order.
        void moveToFront(const std::shared_ptr<IWidget>&);

        //! Move the child widget to the back of the drawing order.
        void moveToBack(const std::shared_ptr<IWidget>&);

        //! Get the window.
        std::shared_ptr<IWindow> getWindow();

        ///@}

        //! Geometry
        ///@{

        //! Get the size hint.
        const Size2I& getSizeHint() const;

        //! Get the horizontal layout stretch.
        Stretch getHStretch() const;

        //! Set the horizontal layout stretch.
        void setHStretch(Stretch);

        //! Get the vertical layout stretch.
        Stretch getVStretch() const;

        //! Set the vertical layout stretch.
        void setVStretch(Stretch);

        //! Set the horizontal and vertical layout stretch.
        void setStretch(Stretch horizontal, Stretch vertical);

        //! Set the horizontal and vertical layout stretch.
        void setStretch(Stretch);

        //! Get the horizontal layout alignment.
        HAlign getHAlign() const;

        //! Set the horizontal layout alignment.
        void setHAlign(HAlign);

        //! Get the vertical layout alignment.
        VAlign getVAlign() const;

        //! Set the vertical layout alignment.
        void setVAlign(VAlign);

        //! Set the horizontal and vertical layout alignment.
        void setAlign(HAlign, VAlign);

        //! Get the geometry.
        const Box2I& getGeometry() const;

        //! Set the geometry.
        virtual void setGeometry(const Box2I&);
            
        //! Set the position.
        void setPos(const V2I&);
            
        //! Set the size.
        void setSize(const Size2I&);

        ///@}

        //! Visibility
        ///@{

        //! Is the widget visible?
        bool isVisible(bool andParentsVisible = true) const;

        //! Set whether the widget is visible.
        virtual void setVisible(bool);

        //! Show the widget.
        void show();

        //! Hide the widget.
        void hide();

        //! Is the widget clipped?
        bool isClipped() const;

        //! Get the clipping rect applied to the child widgets. By
        //! default this is the same as the widget geometry.
        virtual Box2I getChildrenClipRect() const;

        ///@}

        //! Enabled
        ///@{

        //! Is the widget enabled?
        bool isEnabled(bool andParentsEnabled = true) const;

        //! Set whether the widget is enabled.
        virtual void setEnabled(bool);

        ///@}

        //! Key Focus
        ///@{

        //! Does this widget accept key focus?
        bool acceptsKeyFocus() const;

        //! Set whether the widget accepts key focus.
        virtual void setAcceptsKeyFocus(bool);

        //! Does this widget have key focus?
        bool hasKeyFocus() const;

        //! Take the key focus.
        virtual void takeKeyFocus();

        //! Release the key focus.
        void releaseKeyFocus();

        ///@}

        //! Tool tips.
        ///@{

        //! Get the tooltip.
        const std::string& getTooltip() const;

        //! Set the tooltip.
        void setTooltip(const std::string&);

        ///@}

        //! Events
        ///@{

        //! Child add event.
        virtual void childAddEvent(const ChildAddEvent&);

        //! Child remove event.
        virtual void childRemoveEvent(const ChildRemoveEvent&);

        //! Tick event.
        virtual void tickEvent(
            bool parentsVisible,
            bool parentsEnabled,
            const TickEvent&);

        //! Size hint event.
        virtual void sizeHintEvent(const SizeHintEvent&);

        //! Clip event.
        virtual void clipEvent(const Box2I&, bool clipped);

        //! Draw event.
        virtual void drawEvent(const Box2I&, const DrawEvent&);

        //! Draw overlay event.
        virtual void drawOverlayEvent(const Box2I&, const DrawEvent&);

        //! Mouse enter event.
        virtual void mouseEnterEvent(MouseEnterEvent&);

        //! Mouse leave event.
        virtual void mouseLeaveEvent();

        //! Mouse move event.
        virtual void mouseMoveEvent(MouseMoveEvent&);

        //! Mouse press event.
        virtual void mousePressEvent(MouseClickEvent&);

        //! Mouse release event.
        virtual void mouseReleaseEvent(MouseClickEvent&);

        //! Scroll event.
        virtual void scrollEvent(ScrollEvent&);

        //! Key focus event.
        virtual void keyFocusEvent(bool);

        //! Key press event.
        virtual void keyPressEvent(KeyEvent&);

        //! Key release event.
        virtual void keyReleaseEvent(KeyEvent&);

        //! Text event.
        virtual void textEvent(TextEvent&);

        //! Drag enter event.
        virtual void dragEnterEvent(DragAndDropEvent&);

        //! Drag leave event.
        virtual void dragLeaveEvent(DragAndDropEvent&);

        //! Drag move event.
        virtual void dragMoveEvent(DragAndDropEvent&);

        //! Drop event.
        virtual void dropEvent(DragAndDropEvent&);

        ///@}

    protected:
        void _setDrawUpdate();
        void _setSizeUpdate();

        void _setSizeHint(const Size2I&);

        void _setMouseHoverEnabled(bool);
        void _setMousePressEnabled(bool, int button = -1, int modifiers = -1);
        virtual void _releaseMouse();
        bool _isMouseInside() const;
        const V2I& _getMousePos() const;
        bool _isMousePressed() const;
        const V2I& _getMousePressPos() const;

    private:
        std::weak_ptr<Context> _context;
        std::string _objectName;
        ColorRole _backgroundRole = ColorRole::None;
        int _updates = 0;
        std::weak_ptr<IWidget> _parent;
        std::list<std::shared_ptr<IWidget> > _children;
        Size2I _sizeHint;
        Stretch _hStretch = Stretch::Fixed;
        Stretch _vStretch = Stretch::Fixed;
        HAlign _hAlign = HAlign::Fill;
        VAlign _vAlign = VAlign::Fill;
        Box2I _geometry;
        bool _visible = true;
        bool _parentsVisible = true;
        bool _clipped = false;
        bool _enabled = true;
        bool _parentsEnabled = true;
        bool _mouseHoverEnabled = false;
        bool _mousePressEnabled = false;
        int _mousePressButton = -1;
        int _mousePressModifiers = -1;
        bool _mouseInside = false;
        V2I _mousePos;
        bool _mousePress = false;
        V2I _mousePressPos;
        bool _acceptsKeyFocus = false;
        bool _keyFocus = false;
        std::string _tooltip;
    };
}

#include <dtk/ui/IWidgetInline.h>

