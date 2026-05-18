#ifndef TEXTREDACTOR_H
#define TEXTREDACTOR_H

#include <gtkmm.h>

class TextRedactor : public Gtk::Window
{
public:
    TextRedactor();
    ~TextRedactor();



private:

    void create_click();
    void open_click();
    void save_click();

    void load_file(const std::string& path);
    void save_file(const std::string& path);
    
    
    Gtk::Box main_box;
    Gtk::Box button_box;
    Gtk::Button create_btn;
    Gtk::Button open_btn;
    Gtk::Button save_btn;
    Gtk::ScrolledWindow scroll_win;
    Gtk::TextView text_view;


    Glib::RefPtr<Gtk::TextBuffer> text_buffer;

    std::string current_file;  // Текущий файл
};

#endif
