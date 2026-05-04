#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <gtkmm.h>

class TextEditor : public Gtk::Window
{
public:
    TextEditor();
    virtual ~TextEditor();

protected:
    void on_button_create();
    void on_button_open();
    void on_button_save();

private:
    Gtk::Box m_VBox;
    Gtk::Box m_ButtonBox;
    Gtk::Button m_Button_Create;
    Gtk::Button m_Button_Open;
    Gtk::Button m_Button_Save;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TextView m_TextView;
    
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
    Glib::RefPtr<Gtk::FileDialog> m_fileDialog;
    
    std::string m_currentFile;
};

#endif
