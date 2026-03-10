#include <cstdio>

#include "bgfx/bgfx.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("SDL3 with BGFX",640,480,SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    // In the case that the window could not be made...
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                 SDL_GetError());

    return SDL_APP_FAILURE;
  }

  bgfx::Init init{};
  init.type = bgfx::RendererType::Count;
  init.vendorId = BGFX_PCI_ID_NONE;

  bgfx::PlatformData pd{};

  SDL_PropertiesID props = SDL_GetWindowProperties(window);

#ifdef SDL_PLATFORM_LINUX

  if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "x11") == 0) {
    pd.ndt = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_X11_DISPLAY_POINTER,
                                    NULL);
    pd.nwh = (void *)(uintptr_t)SDL_GetNumberProperty(
        props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);
  } else if (SDL_strcmp(SDL_GetCurrentVideoDriver(), "wayland") == 0) {

    pd.ndt = SDL_GetPointerProperty(
        props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, NULL);
    pd.nwh = SDL_GetPointerProperty(
        props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, NULL);
  }

#elif defined(SDL_PLATFORM_WIN32)

  pd.nwh =
      SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

#endif

  init.platformData = pd;

  init.resolution.width = 640;
  init.resolution.height = 480;
  bgfx::init(init);



  bgfx::reset(640, 480, BGFX_RESET_VSYNC);

  bgfx::setDebug(BGFX_DEBUG_TEXT);
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xff0000ff, 1.0f,
                     0);
  bgfx::setViewRect(0, 0, 0, 640, 480);

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {

  bgfx::touch(0);
  bgfx::dbgTextClear();
  bgfx::dbgTextPrintf(0, 1, 0x4f, "Renderer: %s", bgfx::getRendererName(bgfx::getCaps()->rendererType));
  bgfx::frame();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_FAILURE;
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  bgfx::shutdown();
  SDL_DestroyWindow(window);
  SDL_Quit();
}
