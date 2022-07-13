#pragma once
#ifndef REACTIION_AERO_OVERLAY_SURFACE_HPP
#define REACTIION_AERO_OVERLAY_SURFACE_HPP

#include <render/Font3D9.hpp>
#include "../drawing/Color.hpp"
#include "../engine/Vector3.h"
#include "Font.hpp"

namespace render {

class Surface
{
public:
    /// An alias for the mutex.
    using Mutex = std::shared_timed_mutex;
    /// The maximum render elements.
    static constexpr size_t MAX_RENDER_ELEMENTS = 512;

private:
    /// An typedef for the render object
    using RenderObj  = std::tuple<
        int32_t,       /// x position
        int32_t,       /// y position
        int32_t,       /// width
        int32_t,       /// height
        drawing::Color /// obv. the color
    >;

    /// An alias for the map of fonts.
    using Fonts      = std::map<std::string, Font_t>;
    /// An alias for the render objects.
    using RenderData = std::vector<RenderObj>;    

public:
    ///-------------------------------------------------------------------------------------------------
    /// Default constructor.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    Surface() = default;

    ///-------------------------------------------------------------------------------------------------
    /// Destructor.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual ~Surface();

    ///-------------------------------------------------------------------------------------------------
    /// Initializes this object.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  device  The device.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool initialize(
        const void*        device ) = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Begins a scene.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------
    virtual bool begin_scene() = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Adds a font.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  name        The name.
    /// @param  definition  The definition.
    /// @param  height      The height.
    /// @param  weight      The weight.
    /// @param  flags       The flags.
    ///
    /// @return A Font_t.
    ///-------------------------------------------------------------------------------------------------
    virtual Font_t add_font(
        const std::string& name,
        const std::string& definition,
        const int32_t      height,
        const int32_t      weight,
        const int32_t      flags ) = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Gets a font.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///
    /// @param  name    The name.
    ///
    /// @return The font.
    ///-------------------------------------------------------------------------------------------------
    virtual Font_t get_font(
        const std::string&  name );

protected:
    ///-------------------------------------------------------------------------------------------------
    /// Renders the data.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void render_data() = 0;

public:
    ///-------------------------------------------------------------------------------------------------
    /// Ends a scene.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void end_scene() = 0;

    ///-------------------------------------------------------------------------------------------------
    /// Shuts down this object and frees any resources it is using.
    ///
    /// @author Michael
    /// @date   05.03.2017
    ///-------------------------------------------------------------------------------------------------
    virtual void shutdown();

	virtual void FillRGBA(float x, float y, float w, float h, int r, int g, int b, int a, ID3DXLine* pLine);

	virtual void DrawBar(Vector3 Head, Vector3 Foot, int value, ID3DXLine* pLine);

	virtual void line(
		const int32_t start_x,
		const int32_t start_y,
		const int32_t end_x,
		const int32_t end_y,
		const D3DCOLOR  color,
		ID3DXLine* pLine);
   ///-------------------------------------------------------------------------------------------------
    virtual void text(
        const int32_t         x,
        const int32_t         y,
        const Font_t&         font,
        const drawing::Color& color,
        const std::string&    message ) = 0;

    ///-------------------------------------------------------------------------------------------------
  
    virtual void text(
        const int32_t         x,
        const int32_t         y,
        const std::string&    font_name,
        const drawing::Color& color,
        const std::string&    message );

	virtual void text_outlined(
		const int32_t      x,
		const int32_t      y,
		const std::string& font_name,
		const drawing::Color&       color,
		const std::string& message);

	virtual void box(
		const Vector3 foot,
		const Vector3 head,
		const int32_t	w,
		const D3DCOLOR  color,
		ID3DXLine* pLine);

	virtual void Surface::box_corner(
		const Vector3 foot,
		const Vector3 head,
		const int32_t w,
		const int32_t h,
		ID3DXLine* pLine);

	virtual void Surface::circle(
		const int32_t	x,
		const int32_t	y,
		const int32_t	r,
		const int32_t	s,
		const D3DCOLOR  color,
		ID3DXLine* pLine);
	


protected:
    std::atomic_bool m_Initialized = false;
    RenderData    m_Lines;
    RenderData    m_RectAngles;
    Fonts         m_Fonts;
    mutable Mutex m_mutex;
};





}

#endif
