#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <gtkmm.h>

class TextEditor : public Gtk::Window
{
public:
    TextEditor();
    virtual ~TextEditor();

protected:
    void on_menu_file_new();
    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_save_as();
    void on_menu_file_quit();
    
    void on_font_button_clicked();   // выбор шрифта
    void on_font_size_changed();     // выбор размера из списка

private:
    void apply_font_to_all_text();   // применить текущий шрифт ко всему тексту
    void update_font_size_combo();   // синхронизировать комбобокс с текущим размером

    Gtk::Box m_VBox;                 // главный вертикальный контейнер
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TextView m_TextView;
    
    Glib::RefPtr<Gio::Menu> m_MenuFile;
    
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
    Glib::RefPtr<Gtk::FileDialog> m_fileDialog;
    
    Glib::RefPtr<Gtk::TextTag> m_fontTag;
    std::string m_fontFamily;
    int m_fontSize;                  // размер в пунктах (целое)
    
    Gtk::Button m_FontButton;
    Gtk::ComboBoxText m_SizeCombo;
    
    std::string m_currentFile;
};

#endif
