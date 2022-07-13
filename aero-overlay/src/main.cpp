
#include <render/Device3D9.hpp>

using namespace render;

std::unique_ptr<Overlay> create_overlay(const EDeviceType type, const std::string& window_title)
{
	auto overlay = Overlay::New(type);
	if (!overlay) {
		return nullptr;
	}
	if (!overlay->create(window_title)) {
		return nullptr;
	}

	auto surface = overlay->get_surface();
	if (!surface) {
		return nullptr;
	}

	const auto is_d3d9 = type == EDeviceType::Direct3D9;

	if (!surface->add_font(
		META_STRING("default"),
		META_STRING("Arial"),
		16,
		FW_REGULAR,
		/// or DEFAULT_QUALITY instead of PROOF_QUALITY for anti aliasing
		PROOF_QUALITY
	)) {
		return nullptr;
	}

	return std::move(overlay);
}

void main()
{
	std::unique_ptr<Overlay> overlay = nullptr;

	overlay = create_overlay(EDeviceType::Direct3D9, META_STRING("Arma 3"));

	while (overlay->render()) {
		overlay->scale_overlay();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	overlay->shutdown();
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {

	case DLL_PROCESS_ATTACH:
		while (true)
		{
			if (FindWindow(META_STRING("Arma 3"), NULL))
			{
				DisableThreadLibraryCalls(hInst);
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, hInst, 0, 0);
				break;
			}
		}
		break;
	default:
		break;
	}
	return TRUE;
}


