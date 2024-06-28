#include <tray.hpp>
#include <filesystem>

enum thermal_mode
{
    THERMAL_MODE_QUIET = 1,
    THERMAL_MODE_BALANCE = 2,
    THERMAL_MODE_PERFORMANCE = 3
};

extern "C" bool sysInitialize(const char* sys_path);
extern "C" bool setThermalMode(thermal_mode mode);

auto WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdline, int) -> int
{
    if (!sysInitialize(std::filesystem::current_path().string().c_str()))
    {
        MessageBox(nullptr, "sysInitialize call failed.", "Error", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    auto const icon_id = std::string_view { cmdline }.contains("--dark") ? 102: 101;
    auto const icon_rc = LoadIcon(instance, MAKEINTRESOURCE(icon_id));

    auto tray = Tray::Tray { "v3tool", icon_rc };

    tray.addEntry(Tray::Button("Power Balance", [] { setThermalMode(THERMAL_MODE_BALANCE); }));
    tray.addEntry(Tray::Button("Power Save", [] { setThermalMode(THERMAL_MODE_QUIET); }));
    tray.addEntry(Tray::Button("Power Premium", [] { setThermalMode(THERMAL_MODE_PERFORMANCE); }));

    tray.addEntry(Tray::Separator());
    tray.addEntry(Tray::Button("Exit", [&] { tray.exit(); }));

    tray.run();

    return EXIT_SUCCESS;
}