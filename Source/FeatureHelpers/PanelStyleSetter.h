#pragma once

#include <CS2/Classes/Color.h>
#include <CS2/Classes/Panorama.h>
#include "GameClasses/Implementation/PanelStyleImpl.h"
#include "PanelStylePropertyFactory.h"

struct ImageShadowParams;

class PanelStyleSetter {
public:
    PanelStyleSetter(cs2::CPanelStyle& style, const PanelStylePropertyFactory& propertyFactory) noexcept
        : thisptr{&style}
        , propertyFactory{propertyFactory}
    {
    }

    void setProperty(const cs2::CStyleProperty* styleProperty) const noexcept
    {
        if (!styleProperty)
            return;

        if (const auto setPropertyFn{PanelStyleImpl::instance().setProperty})
            setPropertyFn(thisptr, styleProperty, true);
    }

    void fitParent() const noexcept
    {
        setWidth(cs2::CUILength{100.0f, cs2::CUILength::k_EUILengthPercent});
        setHeight(cs2::CUILength{100.0f, cs2::CUILength::k_EUILengthPercent});
    }

    void setSimpleForegroundColor(const cs2::Color& color) const noexcept
    {
        setProperty(&propertyFactory.simpleForegroundColor(color));
    }

    void setTransform3D(const cs2::CUtlVector<cs2::CTransform3D*>& transforms) const noexcept
    {
        setProperty(&propertyFactory.transform3D(transforms));
    }

    void setOpacity(float opacity) const noexcept
    {
        setProperty(propertyFactory.opacity(opacity));
    }

    void setWidth(cs2::CUILength width) const noexcept
    {
        setProperty(propertyFactory.width(width));

