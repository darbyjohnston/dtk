// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkGL/TextureAtlas.h>

#include <dtkGL/Texture.h>

#include <dtkCore/Assert.h>
#include <dtkCore/BoxPack.h>

#include <map>

using namespace dtk::core;

namespace dtk
{
    namespace gl
    {
        struct TextureAtlas::Private
        {
            int textureSize = 0;
            ImageType textureType = ImageType::None;
            int border = 0;
            std::shared_ptr<Texture> texture;
            std::shared_ptr<BoxPack> boxPack;
        };

        void TextureAtlas::_init(
            int textureSize,
            ImageType textureType,
            TextureFilter filter,
            int border)
        {
            DTK_P();

            p.textureSize = textureSize;
            p.textureType = textureType;
            p.border = border;
            TextureOptions textureOptions;
            textureOptions.filters.minify = filter;
            textureOptions.filters.magnify = filter;
            p.texture = Texture::create(
                ImageInfo(textureSize, textureSize, textureType),
                textureOptions);
            p.boxPack = BoxPack::create(
                Size2I(textureSize, textureSize),
                border);
        }

        TextureAtlas::TextureAtlas() :
            _p(new Private)
        {}

        TextureAtlas::~TextureAtlas()
        {}

        std::shared_ptr<TextureAtlas> TextureAtlas::create(
            int textureSize,
            ImageType textureType,
            TextureFilter filter,
            int border)
        {
            auto out = std::shared_ptr<TextureAtlas>(new TextureAtlas);
            out->_init(textureSize, textureType, filter, border);
            return out;
        }

        int TextureAtlas::getTextureSize() const
        {
            return _p->textureSize;
        }

        ImageType TextureAtlas::getTextureType() const
        {
            return _p->textureType;
        }

        unsigned int TextureAtlas::getTexture() const
        {
            return _p->texture->getID();
        }

        bool TextureAtlas::getItem(BoxPackID id, TextureAtlasItem& item)
        {
            DTK_P();
            bool out = false;
            if (auto node = p.boxPack->getNode(id))
            {
                _toTextureAtlasItem(node, item);
                out = true;
            }
            return out;
        }

        bool TextureAtlas::addItem(
            const std::shared_ptr<Image>& image,
            TextureAtlasItem& item)
        {
            DTK_P();
            bool out = false;
            if (auto node = p.boxPack->insert(image->getSize()))
            {
                out = true;

                auto zero = Image::create(node->box.size(), ImageType::L_U8);
                zero->zero();
                p.texture->copy(
                    zero,
                    node->box.min.x,
                    node->box.min.y);

                p.texture->copy(
                    image,
                    node->box.min.x + p.border,
                    node->box.min.y + p.border);

                _toTextureAtlasItem(node, item);
            }
            return out;
        }

        float TextureAtlas::getPercentageUsed() const
        {
            DTK_P();
            float area = 0.F;
            for (const auto node : p.boxPack->getNodes())
            {
                if (node->id != boxPackInvalidID)
                {
                    area += core::area(node->box.size());
                }
            }
            return area / static_cast<float>(p.textureSize * p.textureSize);
        }

        void TextureAtlas::_toTextureAtlasItem(
            const std::shared_ptr<BoxPackNode>& node,
            TextureAtlasItem& out)
        {
            DTK_P();
            out.id = node->id;
            const Size2I size = node->box.size() - p.border * 2;
            out.textureU = RangeF(
                (node->box.min.x + p.border) / static_cast<float>(p.textureSize),
                (node->box.min.x + p.border + size.w + 0) / static_cast<float>(p.textureSize));
            out.textureV = RangeF(
                (node->box.min.y + p.border) / static_cast<float>(p.textureSize),
                (node->box.min.y + p.border + size.h + 0) / static_cast<float>(p.textureSize));
        }
    }
}
