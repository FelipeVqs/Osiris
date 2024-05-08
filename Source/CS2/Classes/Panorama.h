#ifndef CS2_PANORAMA_H
#define CS2_PANORAMA_H

#include <cstdint>
#include <string>
#include <vector>

#include <Utils/Pad.h>

#include "Color.h"
#include "Vector.h"

namespace cs2 {

using CUtlMap = std::map<std::string, int>;
using CUtlString = std::string;
using CUtlVector = std::vector<int>;

struct CPanel2D {
public:
    explicit CPanel2D(const char* id, CUIPanel* parent)
        : vmt(nullptr), uiPanel(parent) {
        // Initialize id here
    }

    using Create = CPanel2D*(const char* id, CUIPanel* parent);
};

struct CLabel : CPanel2D {
public:
    explicit CLabel(CPanel2D* parent, const char* id)
        : CPanel2D(id, parent), text("") {
        // Initialize other member variables here
    }

    using Constructor = void(CLabel* thisptr, CPanel2D* parent, const char* id);

    std::string text;
    using setTextInternal = void (*)(CLabel* thisptr, const std::string& value, int textType, bool trustedSource);
};

struct CImagePanel : CPanel2D {
public:
    explicit CImagePanel(CPanel2D* parent, const char* id)
        : CPanel2D(id, parent), m_strSource("") {
        // Initialize other member variables here
    }

    using Constructor = void(CImagePanel* thisptr, CPanel2D* parent, const char* id);

    std::string m_strSource;
    using SetImage = void(CImagePanel* thisptr, const std::string& imageUrl, const std::string& defaultImageUrl, ImageProperties* properties);
};

struct CStyleSymbol {
public:
    static constexpr auto kInvalidId = 0xFF;

    [[nodiscard]] bool isValid() const noexcept {
        return m_Id != kInvalidId;
    }

    std::uint8_t m_Id = kInvalidId;
};

struct CStyleProperty {
public:
    const void* vmt;
    CStyleSymbol m_symPropertyName;
    bool m_bDisallowTransition;
};

struct CUILength {
public:
    enum EUILengthTypes {
        k_EUILengthUnset,
        k_EUILengthLength,
        k_EUILengthPercent
    };

    [[nodiscard]] static CUILength pixels(float value) noexcept {
        return CUILength{value, k_EUILengthLength};
    }

    [[nodiscard]] static CUILength percent(float value) noexcept {
        return CUILength{value, k_EUILengthPercent};
    }

    float m_flValue;
    EUILengthTypes m_eType;
};

struct CStylePropertyWidth : CStyleProperty {
public:
    static constexpr auto kName = "width";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyWidth@panorama@@";

    CUILength m_Length;
};

struct CStylePropertyOpacity : CStyleProperty {
public:
    static constexpr auto kName = "opacity";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyOpacity@panorama@@";

    float opacity;
};

struct CStylePropertyZIndex : CStyleProperty {
public:
    static constexpr auto kName = "z-index";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyZIndex@panorama@@";

    float zindex;
};

struct CStylePropertyHeight : CStyleProperty {
public:
    static constexpr auto kName = "height";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyHeight@panorama@@";

    CUILength m_Height;
};

struct CStylePropertyImageShadow : CStyleProperty {
public:
    static constexpr auto kName = "img-shadow";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyImageShadow@panorama@@";

    bool fullySet;
    CUILength horizontalOffset;
    CUILength verticalOffset;
    CUILength blurRadius;
    float strength;
    Color color;
};

struct CStylePropertyPosition : CStyleProperty {
public:
    static constexpr auto kName = "position";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyPosition@panorama@@";

    CUILength x;
    CUILength y;
    CUILength z;
};

struct CStylePropertyTransformOrigin : CStyleProperty {
public:
    static constexpr auto kName = "transform-origin";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyTransformOrigin@panorama@@";

    CUILength x;
    CUILength y;
    bool m_bParentRelative;
};

enum class EHorizontalAlignment : std::uint8_t {
    k_EHorizontalAlignmentUnset,
    k_EHorizontalAlignmentLeft,
    k_EHorizontalAlignmentCenter,
    k_EHorizontalAlignmentRight
};

enum class EVerticalAlignment : std::uint8_t {
    k_EVerticalAlignmentUnset,
    k_EVerticalAlignmentTop,
    k_EVerticalAlignmentCenter,
    k_EVerticalAlignmentBottom
};

struct CStylePropertyAlign : CStyleProperty {
public:
    static constexpr auto kName = "align";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyAlign@panorama@@";

    EHorizontalAlignment m_eHorizontalAlignment;
    EVerticalAlignment m_eVerticalAlignment;
};

struct CStylePropertyWashColor : CStyleProperty {
public:
    static constexpr auto kName = "wash-color";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyWashColor@panorama@@";

    Color color;
    bool fullySet;
};

enum class EFlowDirection : std::uint8_t {
    k_EFlowNone = 1,
    k_EFlowDown,
    k_EFlowRight
};

struct CStylePropertyFlowChildren : CStyleProperty {
public:
    static constexpr auto kName = "flow-children";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyFlowChildren@panorama@@";

    EFlowDirection m_eFlowDirection;
};

enum class EFontStyle : std::int8_t {
    k_EFontStyleUnset = -1,
    k_EFontStyleNormal = 0,
    k_EFontStyleItalic = 2,
};

enum class EFontWeight : std::int8_t {
    k_EFontWeightUnset = -1,
    k_EFontWeightNormal = 0,
    k_EFontWeightMedium = 1,
    k_EFontWeightBold = 2,
    k_EFontWeightBlack = 3,
    k_EFontWeightThin = 4,
    k_EFontWeightLight = 5,
    k_EFontWeightSemiBold = 6,
};

enum class EFontStretch : std::int8_t {
    k_EFontStretchUnset = -1,
    k_EFontStretchNormal = 0,
    k_EFontStretchCondensed = 1,
    k_EFontStretchExpanded = 2
};

struct CStylePropertyFont : CStyleProperty {
public:
    static constexpr auto kName = "font";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyFont@panorama@@";

    CUtlString m_strFontFamily;
    float m_flFontSize;
    EFontStyle m_eFontStyle;
    EFontWeight m_eFontWeight;
    EFontStretch m_eFontStretch;
};

struct CStylePropertyTextShadow : CStyleProperty {
public:
    static constexpr auto kName = "text-shadow";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyTextShadow@panorama@@";

    bool fullySet;
    CUILength horizontalOffset;
    CUILength verticalOffset;
    CUILength blurRadius;
    float strength;
    Color color;
};

struct CStylePropertyDimensionsBase : CStyleProperty {
public:
    CUILength m_left;
    CUILength m_top;
    CUILength m_right;
    CUILength m_bottom;
};

struct CStylePropertyMargin : CStylePropertyDimensionsBase {
public:
    static constexpr auto kName = "margin";
    static constexpr auto kMangledTypeName = ".?AVCStylePropertyMargin@panorama@@";
};

struct CPanelStyle {
public:
    using SetProperty = void(CPanelStyle* thisptr, CStyleProperty* styleProperty, bool transition);

    using StylePropertySymbols = CUtlMap<std::string, CStyleSymbol>;

    StylePropertySymbols symbols;
};

struct CUIPanel {
public:
    const void* vmt;
    CPanel2D* clientPanel;

    using setParent = void(CUIPanel* thisptr, CUIPanel* parent);
    using setVisible = void(CUIPanel* thisptr, bool visible);
    using findChildInLayoutFile = CUIPanel*(CUIPanel* thisptr, const std::string& childId);
    using getAttributeString = const char*(CUIPanel* thisptr, CStyleSymbol attributeName, const std::string& defaultValue);
    using setAttributeString = void(CUIPanel* thisptr, CStyleSymbol attributeName, const std::string& value);

    using childrenVector = std::vector<CUIPanel*>;
    using classesVector = std::vector<CStyleSymbol>;

    virtual ~CUIPanel() = default;

    virtual void draw() = 0;
};

struct ImageProperties {
public:
    int textureWidth;
    int textureHeight;
    float scale;
};

struct CTransform3D {
public:
    const void* vmt;

    virtual ~CTransform3D() = default;

    virtual void transform() = 0;
};

struct CTransformTranslate3D : CTransform3D {
public:
    CUILength m_x;
    CUILength m_y;
    CUILength m_z;

    void transform() override;
};

struct CTransformScale3D : CTransform3D {
public:
    Vector m_VecScale;

    void transform() override;
};

struct CTopLevelWindow {
public:
    using m_flScaleFactor = float;

    virtual void handleEvent(int eventId) = 0;
};

} // namespace cs2

#endif // CS2_PANORAMA_H
