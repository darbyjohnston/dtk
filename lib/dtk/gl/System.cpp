// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/gl/System.h>

#include <dtk/gl/GL.h>

#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>
#include <dtk/core/String.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

namespace dtk
{
    namespace gl
    {
        bool MonitorInfo::operator == (const MonitorInfo& other) const
        {
            return
                name == other.name &&
                size == other.size &&
                colorBits == other.colorBits &&
                refreshRate == other.refreshRate &&
                contentScale == other.contentScale &&
                pos == other.pos &&
                physicalSizeMM == other.physicalSizeMM;
        }

        bool MonitorInfo::operator != (const MonitorInfo& other) const
        {
            return !(*this == other);
        }

        namespace
        {
            void glfwErrorCallback(int, const char* description)
            {
                std::cerr << "GLFW ERROR: " << description << std::endl;
            }

            MonitorInfo getMonitorInfo(GLFWmonitor* monitor)
            {
                MonitorInfo out;
                out.name = glfwGetMonitorName(monitor);
                const GLFWvidmode* vm = glfwGetVideoMode(monitor);
                out.size.w = vm->width;
                out.size.h = vm->height;
                out.colorBits[0] = vm->redBits;
                out.colorBits[1] = vm->greenBits;
                out.colorBits[2] = vm->blueBits;
                out.refreshRate = vm->refreshRate;
                glfwGetMonitorContentScale(monitor, &out.contentScale.x, &out.contentScale.y);
                glfwGetMonitorPos(monitor, &out.pos.x, &out.pos.y);
                glfwGetMonitorPhysicalSize(monitor, &out.physicalSizeMM.w, &out.physicalSizeMM.h);
                return out;
            }

            std::vector<MonitorInfo> getMonitorInfo()
            {
                std::vector<MonitorInfo> out;
                int monitorCount = 0;
                GLFWmonitor** glfwMonitors = glfwGetMonitors(&monitorCount);
                for (int i = 0; i < monitorCount; ++i)
                {
                    out.push_back(getMonitorInfo(glfwMonitors[i]));
                }
                return out;
            }
        }
        
        struct System::Private
        {
            bool glfwInit = false;
            std::shared_ptr<ObservableList<MonitorInfo> > monitors;
            std::shared_ptr<ListObserver<MonitorInfo> > monitorsObserver;

            static void monitorCallback(GLFWmonitor* monitor, int event);

            void monitorsUpdate();
        };

        void System::Private::monitorCallback(GLFWmonitor* monitor, int event)
        {
            System::Private* p = reinterpret_cast<System::Private*>(
                glfwGetMonitorUserPointer(monitor));
            p->monitors->setIfChanged(getMonitorInfo());
            p->monitorsUpdate();
        }

        void System::Private::monitorsUpdate()
        {
            int monitorCount = 0;
            GLFWmonitor** glfwMonitors = glfwGetMonitors(&monitorCount);
            for (int i = 0; i < monitorCount; ++i)
            {
                glfwSetMonitorUserPointer(glfwMonitors[i], this);
            }
        }
        
        System::System(const std::shared_ptr<Context>& context) :
            ISystem(context, "dtk::gl::System"),
            _p(new Private)
        {
            DTK_P();

            // Initialize GLFW.
            glfwSetErrorCallback(glfwErrorCallback);
            int glfwMajor = 0;
            int glfwMinor = 0;
            int glfwRevision = 0;
            glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
            if (!glfwInit())
            {
                throw std::runtime_error("Cannot initialize GLFW");
            }
            p.glfwInit = true;
            auto logSystem = context->getSystem<LogSystem>();
            logSystem->print(
                "dtk::gl::System",
                Format("GLFW version: {0}.{1}.{2}").
                arg(glfwMajor).
                arg(glfwMinor).
                arg(glfwRevision));

            p.monitorsUpdate();
            p.monitors = ObservableList<MonitorInfo>::create(getMonitorInfo());
            p.monitorsObserver = ListObserver<MonitorInfo>::create(
                p.monitors,
                [this](const std::vector<MonitorInfo>& value)
                {
                    if (auto context = _context.lock())
                    {
                        std::vector<std::string> lines;
                        for (const auto& i : value)
                        {
                            lines.push_back(Format("Monitor: {0}").arg(i.name));
                            lines.push_back(Format("    Size: {0}").arg(i.size));
                            lines.push_back(Format("    Color bits: {0} {1} {2}").
                                arg(i.colorBits[0]).
                                arg(i.colorBits[1]).
                                arg(i.colorBits[2]));
                            lines.push_back(Format("    Referesh rate: {0}").arg(i.refreshRate));
                            lines.push_back(Format("    Content scale: {0}").arg(i.contentScale));
                            lines.push_back(Format("    Position: {0}").arg(i.pos));
                            lines.push_back(Format("    Physical size mm: {0}").arg(i.physicalSizeMM));
                        }
                        auto logSystem = context->getSystem<LogSystem>();
                        logSystem->print(
                            "dtk::gl::System",
                            join(lines, '\n'));
                    }
                });
            glfwSetMonitorCallback(&p.monitorCallback);
        }

        System::~System()
        {
            DTK_P();
            if (p.glfwInit)
            {
                glfwTerminate();
            }
        }

        std::shared_ptr<System> System::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<System>(new System(context));
        }

        std::shared_ptr<IObservableList<MonitorInfo> > System::observeMonitors() const
        {
            return _p->monitors;
        }
    }
}
