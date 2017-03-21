#pragma once
#include "starlight/_global.h"

#include <string>
#include <memory>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"
#include "starlight/datatypes/Color.h"

#include "starlight/ui/TouchScreenCanvas.h"
#include "starlight/ui/TopScreenCanvas.h"

#include "starlight/ui/Form.h"

#include "starlight/ConfigManager.h"

namespace starlight {
    class Application {
          ////////////////////
         // STATIC MEMBERS //
        ////////////////////
    private:
        static Application* _currentApp;
        static unsigned long long ftime;
        
    public:
        static bool Quit();
        static Config& GetConfig(const std::string& path);
        static std::string AppName();
        static inline Application* Current() { return _currentApp; }
        static inline unsigned long long GetTime() { return ftime; }
        
          //////////////////////
         // INSTANCE MEMBERS //
        //////////////////////
    private:
        bool _appQuit = false;
        bool _sFormState = false;
        void _init();
        void _mainLoop();
        void _end();
        
    public:
        const std::string appId;
        
        Color clearColor = Color::black;
        
        std::shared_ptr<ui::TouchScreenCanvas> touchScreen = nullptr;
        std::shared_ptr<ui::TopScreenCanvas> topScreen = nullptr;
        
        std::list<std::shared_ptr<ui::Form>> forms;
        ui::UIContainer* formTouchScreen = nullptr;
        ui::UIContainer* formTopScreen = nullptr;
        
        Application() = delete;
        Application(std::string id) : appId(id) { }
        virtual ~Application() = default;
        
        void Run();
        
        virtual void Init() { }
        virtual void Update() { }
        virtual void PostUpdate() { }
        virtual void Draw() { }
        virtual void PostDraw() { }
        virtual void End() { }
        
        inline void SignalFormState() { _sFormState = true; }
    };
}
