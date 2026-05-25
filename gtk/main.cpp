#include "textredactor.h"

int main(int argc, char* argv[])
{
    g_setenv("GSK_RENDERER", "cairo", TRUE);
    g_setenv("GDK_DEBUG", "gl-disabled", TRUE);

    auto app = Gtk::Application::create("org.example.textredactor");
    return app->make_window_and_run<TextRedactor>(argc, argv);
}
