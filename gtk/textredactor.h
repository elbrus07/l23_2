#ifndef TEXTREDACTOR_H
#define TEXTREDACTOR_H

#include <gtkmm.h>
#include <vector>
#include <string>

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
    
    void setup_tags();
    void highlight_words();
    void on_buffer_changed();
    
    private:
   

    Gtk::Box main_box;
    Gtk::Box button_box;
    Gtk::Button create_btn;
    Gtk::Button open_btn;
    Gtk::Button save_btn;
    Gtk::ScrolledWindow scroll_win;
    Gtk::TextView text_view;


    Glib::RefPtr<Gtk::TextBuffer> text_buffer;
    Glib::RefPtr<Gtk::TextTag> red_tag;  // Тег для красного цвета


    std::string current_file;  // Текущий файл

    // Список слов для подсветки 
    std::vector<std::string> words_to_highlight = {
        "error", "bug", "fixme", "todo", "warning", 
        "красный", "важно", "ошибка", "баг"
    };
    bool highlight_enabled;
};

#endif
