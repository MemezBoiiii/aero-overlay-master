#include <render/Surface.hpp>

using namespace drawing;
using namespace render;

Surface::~Surface()
{
}

Font_t Surface::get_font(
    const std::string& name )
{
    std::shared_lock<Mutex> lock( m_mutex );
    return !name.empty() && m_Fonts.count( name ) != 0 
         ? m_Fonts.at( name )
         : nullptr;
}

void Surface::shutdown()
{
    std::unique_lock<Mutex> lock( m_mutex );
    for( auto& kp : m_Fonts ) {
        kp.second->shutdown();
    }
    m_Fonts.clear();
}

void Surface::box_corner(
	const Vector3 foot,
	const Vector3 head,
	const int32_t w,
	const int32_t h,
	ID3DXLine* pLine)
{
	line(head.x, head.y, head.x, head.y + 3, 0, pLine);//top left
	line(head.x, head.y, foot.x + 3, foot.y, 0, pLine);
	line(head.x + w - 3, head.x, head.x + w, head.y, 0, pLine); //top right
	line(head.x + w, head.y, foot.x + w, foot.y + 3, 0, pLine);

}

#define PI 3.14159265

void Surface::circle(
	const int32_t	x,
	const int32_t	y,
	const int32_t	r,
	const int32_t	s,
	const D3DCOLOR  color,
	ID3DXLine* pLine)
{
	D3DXVECTOR2 Line[128];
	float Step = PI * 2.0 / s;
	int Count = 0;
	for (float a = 0; a < PI*2.0; a += Step)
	{
		float t_x = r * cos(a) + x + 25;
		float t_y = r * sin(a) + y + 40;
		float t_x2 = r * cos(a + Step) + x + 25;
		float t_y2 = r * sin(a + Step) + y + 40;
		Line[Count].x = t_x;
		Line[Count].y = t_y;
		Line[Count + 1].x = t_x2;
		Line[Count + 1].y = t_y2;
		Count += 2;
	}

	pLine->Begin();
	pLine->Draw(Line, Count, color);
	pLine->End();
}

void Surface::box(
	const Vector3 foot,
	const Vector3 head,
	const int32_t	w,
	const D3DCOLOR  color,
	ID3DXLine* pLine)
{
	line(foot.x - w, foot.y, foot.x + w, foot.y, color, pLine);
	line(foot.x - w, head.y, foot.x - w, foot.y, color, pLine);
	line(foot.x + w, head.y, foot.x + w, foot.y, color, pLine);
	line(foot.x - w, head.y, foot.x + w, head.y, color, pLine);
}

void Surface::line(
    const int32_t start_x,
    const int32_t start_y,
    const int32_t end_x,
    const int32_t end_y,
	const D3DCOLOR  color,
	ID3DXLine* pLine)
{
	D3DXVECTOR2 dLine[2];

	dLine[0].x = start_x + 25;
	dLine[0].y = start_y + 40;

	dLine[1].x = end_x + 25;
	dLine[1].y = end_y + 40;

	pLine->SetWidth(0.5f);
	pLine->Draw(dLine, 2, color);
}

void Surface::text(
    const int32_t      x,
    const int32_t      y,
    const std::string& font_name,
    const Color&       color,
    const std::string& message )
{
    if( m_Initialized.load() ) {
        auto font = get_font( font_name );
        if( font ) {
            text( x + 25, y + 40, font, color, message );
        }
    }
}



void Surface::FillRGBA(float x, float y, float w, float h, int r, int g, int b, int a, ID3DXLine* pLine)
{
	D3DXVECTOR2 vLine[2];

	pLine->SetWidth(w);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);

	vLine[0].x = x + 25 + w / 2;
	vLine[0].y = y + 40;
	vLine[1].x = x + 25 + w / 2;
	vLine[1].y = y + 40 + h;

	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}

void Surface::DrawBar(Vector3 Head, Vector3 Foot, int value, ID3DXLine* pLine)
{
	Vector3 Box = Foot - Head;
	if (Box.y < 0)
		Box.y *= -1;

	int BoxWidth = (int)Box.y / 2;
	int DrawX = (int)Foot.x - (BoxWidth / 2);
	int DrawY = (int)Head.y;

	DWORD dwDrawWidth = value * (Foot.y - Head.y) / 100;

	float l, r, g;

	g = value * 2.55;
	r = 255 - g;
	l = value / 3;
	FillRGBA(DrawX, DrawY - 1, 3, (Foot.y - Head.y), 0, 0, 0, 255, pLine);
	FillRGBA(DrawX, DrawY, 3, dwDrawWidth, r, g, 0, 255, pLine);
}



void Surface::text_outlined(
	const int32_t      x,
	const int32_t      y,
	const std::string& font_name,
	const Color&       color,
	const std::string& message)
{
	if (m_Initialized.load()) {
		auto font = get_font(font_name);
		if (font) {

			int32_t cor_x = x + 25;
			int32_t cor_y = y + 40;

			RECT rPosition;

			rPosition.left = cor_x + 1.0f;
			rPosition.top = cor_y;

			text(rPosition.left, rPosition.top, font, 0xFF000000, message);

			rPosition.left = cor_x - 1.0f;
			rPosition.top = cor_y;

			text(rPosition.left, rPosition.top, font, 0xFF000000, message);

			rPosition.left = cor_x;
			rPosition.top = cor_y + 1.0f;

			text(rPosition.left, rPosition.top, font, 0xFF000000, message);

			rPosition.left = cor_x;
			rPosition.top = cor_y - 1.0f;

			text(rPosition.left, rPosition.top, font, 0xFF000000, message);

			rPosition.left = cor_x;
			rPosition.top = cor_y;

			text(cor_x, cor_y, font, color, message);
		}
	}
}
