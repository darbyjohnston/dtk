// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/resource/Resource.h>

#include <Fonts/NotoSans-Bold.h>
#include <Fonts/NotoSans-Regular.h>
#include <Fonts/NotoSansMono-Regular.h>

#include <Icons/ArrowDown.h>
#include <Icons/ArrowLeft.h>
#include <Icons/ArrowRight.h>
#include <Icons/ArrowUp.h>
#include <Icons/Audio.h>
#include <Icons/BellowsClosed.h>
#include <Icons/BellowsOpen.h>
#include <Icons/Clear.h>
#include <Icons/Close.h>
#include <Icons/Copy.h>
#include <Icons/Decrement.h>
#include <Icons/Directory.h>
#include <Icons/DirectoryBack.h>
#include <Icons/DirectoryForward.h>
#include <Icons/DirectoryUp.h>
#include <Icons/Edit.h>
#include <Icons/Empty.h>
#include <Icons/File.h>
#include <Icons/FileBrowser.h>
#include <Icons/FileClose.h>
#include <Icons/FileCloseAll.h>
#include <Icons/FileOpen.h>
#include <Icons/FrameEnd.h>
#include <Icons/FrameInOut.h>
#include <Icons/FrameNext.h>
#include <Icons/FramePrev.h>
#include <Icons/FrameStart.h>
#include <Icons/Increment.h>
#include <Icons/MenuArrow.h>
#include <Icons/MenuChecked.h>
#include <Icons/Mute.h>
#include <Icons/Next.h>
#include <Icons/PanelBottom.h>
#include <Icons/PanelLeft.h>
#include <Icons/PanelRight.h>
#include <Icons/PanelTop.h>
#include <Icons/PlaybackForward.h>
#include <Icons/PlaybackReverse.h>
#include <Icons/PlaybackStop.h>
#include <Icons/Prev.h>
#include <Icons/Reload.h>
#include <Icons/Reset.h>
#include <Icons/ReverseSort.h>
#include <Icons/Search.h>
#include <Icons/Settings.h>
#include <Icons/SubMenuArrow.h>
#include <Icons/TimeEnd.h>
#include <Icons/TimeStart.h>
#include <Icons/ViewZoomIn.h>
#include <Icons/ViewZoomOut.h>
#include <Icons/ViewZoomReset.h>
#include <Icons/ViewFrame.h>
#include <Icons/Volume.h>
#include <Icons/WindowFullScreen.h>

#include <cstring>
#include <map>

namespace dtk
{
    namespace
    {
        const std::map<std::string, const std::vector<uint8_t>* > fontResources =
        {
            { "NotoSansMono-Regular", &NotoSansMono_Regular_ttf },
            { "NotoSans-Regular", &NotoSans_Regular_ttf },
            { "NotoSans-Bold", &NotoSans_Bold_ttf }
        };

        const std::map<std::string, const std::vector<uint8_t>* > iconResources =
        {
            { "Audio", &Audio_svg },
            { "ArrowDown", &ArrowDown_svg },
            { "ArrowLeft", &ArrowLeft_svg },
            { "ArrowRight", &ArrowRight_svg },
            { "ArrowUp", &ArrowUp_svg },
            { "BellowsClosed", &BellowsClosed_svg },
            { "BellowsOpen", &BellowsOpen_svg },
            { "Clear", &Clear_svg },
            { "Close", &Close_svg },
            { "Copy", &Copy_svg },
            { "Decrement", &Decrement_svg },
            { "Directory", &Directory_svg },
            { "DirectoryBack", &DirectoryBack_svg },
            { "DirectoryForward", &DirectoryForward_svg },
            { "DirectoryUp", &DirectoryUp_svg },
            { "Edit", &Edit_svg },
            { "Empty", &Empty_svg },
            { "File", &File_svg },
            { "FileBrowser", &FileBrowser_svg },
            { "FileClose", &FileClose_svg },
            { "FileCloseAll", &FileCloseAll_svg },
            { "FileOpen", &FileOpen_svg },
            { "FrameEnd", &FrameEnd_svg },
            { "FrameInOut", &FrameInOut_svg },
            { "FrameNext", &FrameNext_svg },
            { "FramePrev", &FramePrev_svg },
            { "FrameStart", &FrameStart_svg },
            { "Increment", &Increment_svg },
            { "MenuArrow", &MenuArrow_svg },
            { "MenuChecked", &MenuChecked_svg },
            { "Mute", &Mute_svg },
            { "Next", &Next_svg },
            { "PanelBottom", &PanelBottom_svg },
            { "PanelLeft", &PanelLeft_svg },
            { "PanelRight", &PanelRight_svg },
            { "PanelTop", &PanelTop_svg },
            { "PlaybackForward", &PlaybackForward_svg },
            { "PlaybackReverse", &PlaybackReverse_svg },
            { "PlaybackStop", &PlaybackStop_svg },
            { "Prev", &Prev_svg },
            { "Reset", &Reset_svg },
            { "ReverseSort", &ReverseSort_svg },
            { "Reload", &Reload_svg },
            { "Search", &Search_svg },
            { "Settings", &Settings_svg },
            { "SubMenuArrow", &SubMenuArrow_svg },
            { "TimeEnd", &TimeEnd_svg },
            { "TimeStart", &TimeStart_svg },
            { "ViewZoomIn", &ViewZoomIn_svg },
            { "ViewZoomOut", &ViewZoomOut_svg },
            { "ViewZoomReset", &ViewZoomReset_svg },
            { "ViewFrame", &ViewFrame_svg },
            { "Volume", &Volume_svg },
            { "WindowFullScreen", &WindowFullScreen_svg }
        };
    }

    std::vector<std::string> getFontResources()
    {
        std::vector<std::string> out;
        for (const auto& resource : fontResources)
        {
            out.push_back(resource.first);
        }
        return out;
    }

    std::vector<uint8_t> getFontResource(const std::string& name)
    {
        std::vector<uint8_t> out;
        const auto i = fontResources.find(name);
        if (i != fontResources.end())
        {
            out.resize(i->second->size());
            memcpy(out.data(), i->second->data(), i->second->size());
        }
        return out;
    }

    std::vector<std::string> getIconResources()
    {
        std::vector<std::string> out;
        for (const auto& resource : iconResources)
        {
            out.push_back(resource.first);
        }
        return out;
    }

    std::vector<uint8_t> getIconResource(const std::string& name)
    {
        std::vector<uint8_t> out;
        const auto i = iconResources.find(name);
        if (i != iconResources.end())
        {
            out.resize(i->second->size());
            memcpy(out.data(), i->second->data(), i->second->size());
        }
        return out;
    }
}
