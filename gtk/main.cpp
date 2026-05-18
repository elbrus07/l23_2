#include "textredactor.h"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.example.textredactor");
    return app->make_window_and_run<TextRedactor>(argc, argv);
}
