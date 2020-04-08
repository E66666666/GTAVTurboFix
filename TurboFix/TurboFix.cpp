#include "TurboFix.hpp"

#include "TurboScript.hpp"
#include "ScriptMenu.hpp"
#include "Constants.hpp"

#include "Util/Logger.hpp"
#include "Util/Paths.hpp"

#include <inc/main.h>

using namespace TurboFix;

void TurboFix::ScriptMain() {
    const std::string settingsGeneralPath =
        Paths::GetModuleFolder(Paths::GetOurModuleHandle()) +
        Constants::ModDir +
        "\\settings_general.ini";
    const std::string settingsMenuPath =
        Paths::GetModuleFolder(Paths::GetOurModuleHandle()) +
        Constants::ModDir +
        "\\settings_menu.ini";

    CTurboScript script(settingsGeneralPath);
    script.Settings().Load();
    logger.Write(INFO, "Settings loaded");

    auto loaded = script.LoadConfigs();
    logger.Write(INFO, "%u Configs loaded", loaded);

    CScriptMenu menu(settingsMenuPath, 
        []() {
            // OnInit: Nope
        },
        []() {
            // OnExit: Nope
        },
        BuildMenu()
    );

    while(true) {
        script.Tick();
        menu.Tick(script);
        WAIT(0);
    }
}
