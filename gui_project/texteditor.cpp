#include "texteditor.h"
#include <iostream>
#include <fstream>

TextEditor::TextEditor()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL),
  m_Button_Create("_Создать", true),
  m_Button_Open("_Открыть", true),
  m_Button_Save("_Сохранить", true)
{
    set_title("Текстовый редактор");
    set_default_size(800, 600);
    
    m_VBox.set_margin(10);
    set_child(m_VBox);
    
    m_ScrolledWindow.set_child(m_TextView);
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand(true);
    
    m_refTextBuffer = Gtk::TextBuffer::create();
    m_TextView.set_buffer(m_refTextBuffer);
    
    m_fileDialog = Gtk::FileDialog::create();
    m_currentFile = "";
    
    m_VBox.append(m_ButtonBox);
    m_ButtonBox.append(m_Button_Create);
    m_ButtonBox.append(m_Button_Open);
    m_ButtonBox.append(m_Button_Save);
    
    m_ButtonBox.set_spacing(10);
    m_ButtonBox.set_margin_bottom(10);
    m_ButtonBox.set_halign(Gtk::Align::START);
    
    m_VBox.append(m_ScrolledWindow);
    
    m_Button_Create.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_button_create));
    m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_button_open));
    m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_button_save));
}

TextEditor::~TextEditor() {}

void TextEditor::on_button_create()
{
    if (!m_refTextBuffer->get_text().empty()) {
        auto dialog = Gtk::AlertDialog::create("Создать новый файл?");
        dialog->set_detail("Текущий текст будет потерян.");
        dialog->set_buttons({"Отмена", "Создать"});
        
        dialog->choose(*this, [this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
            if (dialog->choose_finish(result) == 1) {
                m_refTextBuffer->set_text("");
                m_currentFile = "";
                set_title("Текстовый редактор - Новый файл");
            }
        });
    } else {
        m_refTextBuffer->set_text("");
        m_currentFile = "";
        set_title("Текстовый редактор - Новый файл");
    }
}

void TextEditor::on_button_open()
{
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Текстовые файлы");
    filter_text->add_pattern("*.txt");
    filter_text->add_pattern("*.cpp");
    filter_text->add_pattern("*.h");
    
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    filters->append(filter_text);
    
    m_fileDialog->set_filters(filters);
    m_fileDialog->set_title("Открыть файл");
    
    m_fileDialog->open(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = m_fileDialog->open_finish(result);
            if (file) {
                std::string path = file->get_path();
                if (!path.empty()) {
                    std::ifstream in(path);
                    if (in.is_open()) {
                        std::string content, line;
                        while (std::getline(in, line)) content += line + "\n";
                        in.close();
                        m_refTextBuffer->set_text(content);
                        m_currentFile = path;
                        set_title("Текстовый редактор - " + Glib::path_get_basename(path));
                    } else {
                        auto alert = Gtk::AlertDialog::create("Ошибка открытия");
                        alert->set_detail("Не удалось открыть файл: " + Glib::path_get_basename(path));
                        alert->show(*this);
                    }
                }
            }
        } catch (const Glib::Error& err) {
            auto alert = Gtk::AlertDialog::create("Ошибка");
            alert->set_detail(err.what());
            alert->show(*this);
        }
    });
}

void TextEditor::on_button_save()
{
    if (!m_currentFile.empty()) {
        std::ofstream out(m_currentFile);
        if (out.is_open()) {
            out << m_refTextBuffer->get_text();
            out.close();
            auto alert = Gtk::AlertDialog::create("Сохранено");
            alert->show(*this);
        }
        return;
    }
    
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Текстовые файлы");
    filter_text->add_pattern("*.txt");
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    filters->append(filter_text);
    m_fileDialog->set_filters(filters);
    m_fileDialog->set_title("Сохранить файл");
    
    m_fileDialog->save(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = m_fileDialog->save_finish(result);
            if (file) {
                std::string filename = file->get_path();
                if (filename.find('.') == std::string::npos) filename += ".txt";
                std::ofstream out(filename);
                if (out.is_open()) {
                    out << m_refTextBuffer->get_text();
                    out.close();
                    m_currentFile = filename;
                    set_title("Текстовый редактор - " + Glib::path_get_basename(filename));
                    auto alert = Gtk::AlertDialog::create("Сохранено");
                    alert->show(*this);
                }
            }
        } catch (const Glib::Error& err) {
            auto alert = Gtk::AlertDialog::create("Ошибка");
            alert->set_detail(err.what());
            alert->show(*this);
        }
    });
}
