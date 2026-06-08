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
    void on_menu_file_new();
    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_save_as();
    void on_menu_file_quit();
    
    void on_font_button_clicked();
    void on_font_size_changed();
    void apply_font_to_all_text();
    void update_font_size_combo();
    
    void setup_tags();
    void highlight_words();
    void on_buffer_changed();
    
    void load_file(const std::string& path);
    void save_file(const std::string& path);

private:
    Gtk::Box main_box;
    Gtk::Box top_bar;
    Gtk::ScrolledWindow scroll_win;
    Gtk::TextView text_view;
    Gtk::MenuButton file_menu_btn;
    
    Glib::RefPtr<Gio::Menu> m_menu_file;
    
    Gtk::Button font_btn;
    Gtk::ComboBoxText size_combo;
    Glib::RefPtr<Gtk::TextTag> font_tag;
    std::string font_family;
    int font_size;
    
    Glib::RefPtr<Gtk::TextBuffer> text_buffer;
    Glib::RefPtr<Gtk::TextTag> red_tag;
    
    std::string current_file;
    Glib::RefPtr<Gtk::FileDialog> file_dialog;
    
    std::vector<std::string> words_to_highlight = {
        "error", "bug", "fixme", "todo", "warning", 
        "красный", "важно", "ошибка", "баг"
    };
    
    bool highlight_enabled;
};

#endif
