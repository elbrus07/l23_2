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
    
    // Новые методы для работы со шрифтами
    void on_font_click();
    void apply_font(const std::string& font_desc);
    void update_font_button_label();
    
private:

    Gtk::Box main_box;
    Gtk::Box button_box;
    Gtk::Box font_box;  // Новая панель для шрифтов
    Gtk::Button create_btn;
    Gtk::Button open_btn;
    Gtk::Button save_btn;
    Gtk::Button font_btn;  // Кнопка выбора шрифта
    Gtk::ScrolledWindow scroll_win;
    Gtk::TextView text_view;

    Glib::RefPtr<Gtk::TextBuffer> text_buffer;
    Glib::RefPtr<Gtk::TextTag> red_tag;      // Тег для красного цвета
    Glib::RefPtr<Gtk::TextTag> font_tag;     // Тег для шрифта

    std::string current_file;  // Текущий файл
    
    std::string current_font_description;  // Текущее описание шрифта

    // Список слов для подсветки 
    std::vector<std::string> words_to_highlight = {
        "error", "bug", "fixme", "todo", "warning", 
        "красный", "важно", "ошибка", "баг"
    };
    bool highlight_enabled;
};

#endif
