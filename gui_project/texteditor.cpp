#include "texteditor.h"
#include <iostream>
#include <fstream>
#include <sstream>

TextEditor::TextEditor()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_FontButton("Шрифт...")
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
    
    m_fontTag = m_refTextBuffer->create_tag();
    m_fontFamily = "Sans";
    m_fontSize = 12;
    apply_font_to_all_text();
    
    // Верхняя панель (одна строка)
    Gtk::Box topBar(Gtk::Orientation::HORIZONTAL);
    topBar.set_spacing(10);
    topBar.set_margin_bottom(10);
    
    // Меню "Файл"
    m_MenuFile = Gio::Menu::create();
    m_MenuFile->append("Новый", "win.new");
    m_MenuFile->append("Открыть...", "win.open");
    m_MenuFile->append("Сохранить", "win.save");
    m_MenuFile->append("Сохранить как...", "win.save_as");
    m_MenuFile->append("Выход", "win.quit");
    
    Gtk::MenuButton fileMenuButton;
    fileMenuButton.set_label("Файл");
    fileMenuButton.set_menu_model(m_MenuFile);
    topBar.append(fileMenuButton);
    
    // Кнопка выбора шрифта
    topBar.append(m_FontButton);
    
    // Выпадающий список размеров (как в Word)
    std::vector<int> sizes = {8,9,10,11,12,14,16,18,20,22,24,26,28,36,48,72};
    for (int s : sizes) {
        m_SizeCombo.append(std::to_string(s));
    }
    m_SizeCombo.set_active_text(std::to_string(m_fontSize));
    topBar.append(m_SizeCombo);
    
    m_VBox.append(topBar);
    m_VBox.append(m_ScrolledWindow);
    
    // Действия для меню
    auto actionGroup = Gio::SimpleActionGroup::create();
    actionGroup->add_action("new", sigc::mem_fun(*this, &TextEditor::on_menu_file_new));
    actionGroup->add_action("open", sigc::mem_fun(*this, &TextEditor::on_menu_file_open));
    actionGroup->add_action("save", sigc::mem_fun(*this, &TextEditor::on_menu_file_save));
    actionGroup->add_action("save_as", sigc::mem_fun(*this, &TextEditor::on_menu_file_save_as));
    actionGroup->add_action("quit", sigc::mem_fun(*this, &TextEditor::on_menu_file_quit));
    insert_action_group("win", actionGroup);
    
    // Сигналы панели управления шрифтом
    m_FontButton.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_font_button_clicked));
    m_SizeCombo.signal_changed().connect(sigc::mem_fun(*this, &TextEditor::on_font_size_changed));
    
    m_fileDialog = Gtk::FileDialog::create();
    m_currentFile = "";
}

TextEditor::~TextEditor() {}

void TextEditor::apply_font_to_all_text()
{
    if (!m_refTextBuffer) return;
    std::string fontStr = m_fontFamily + " " + std::to_string(m_fontSize);
    m_fontTag->property_font() = fontStr;
    
    auto start = m_refTextBuffer->begin();
    auto end = m_refTextBuffer->end();
    m_refTextBuffer->remove_all_tags(start, end);
    m_refTextBuffer->apply_tag(m_fontTag, start, end);
    std::cout << "Применён шрифт: " << fontStr << std::endl;
}

void TextEditor::update_font_size_combo()
{
    m_SizeCombo.set_active_text(std::to_string(m_fontSize));
}

void TextEditor::on_menu_file_new()
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
                apply_font_to_all_text();
                update_font_size_combo();
            }
        });
    } else {
        m_refTextBuffer->set_text("");
        m_currentFile = "";
        set_title("Текстовый редактор - Новый файл");
        apply_font_to_all_text();
        update_font_size_combo();
    }
}

void TextEditor::on_menu_file_open()
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
                        apply_font_to_all_text();
                        update_font_size_combo();
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

void TextEditor::on_menu_file_save()
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
    on_menu_file_save_as();
}

void TextEditor::on_menu_file_save_as()
{
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

void TextEditor::on_menu_file_quit()
{
    if (!m_refTextBuffer->get_text().empty()) {
        auto dialog = Gtk::AlertDialog::create("Выйти?");
        dialog->set_detail("Несохраненные изменения будут потеряны.");
        dialog->set_buttons({"Отмена", "Выйти"});
        dialog->choose(*this, [this, dialog](const Glib::RefPtr<Gio::AsyncResult>& result) {
            if (dialog->choose_finish(result) == 1) {
                get_application()->quit();
            }
        });
    } else {
        get_application()->quit();
    }
}

void TextEditor::on_font_button_clicked()
{
    auto dialog = Gtk::make_managed<Gtk::FontChooserDialog>("Выберите шрифт", *this);
    dialog->set_font(m_fontFamily + " " + std::to_string(m_fontSize));
    dialog->set_modal(true);
    
    dialog->signal_response().connect([this, dialog](int response_id) {
        if (response_id == Gtk::ResponseType::OK) {
            std::string fontStr = dialog->get_font();
            std::vector<std::string> parts;
            std::stringstream ss(fontStr);
            std::string part;
            while (ss >> part) parts.push_back(part);
            
            if (parts.size() >= 2) {
                m_fontFamily = "";
                for (size_t i = 0; i < parts.size() - 1; ++i) {
                    if (i > 0) m_fontFamily += " ";
                    m_fontFamily += parts[i];
                }
                double sizeVal = std::stod(parts.back());
                m_fontSize = static_cast<int>(sizeVal);
                update_font_size_combo();
                apply_font_to_all_text();
            }
        }
        dialog->close();
    });
    
    dialog->show();
}

void TextEditor::on_font_size_changed()
{
    std::string sizeStr = m_SizeCombo.get_active_text();
    if (!sizeStr.empty()) {
        int newSize = std::stoi(sizeStr);
        if (newSize != m_fontSize) {
            m_fontSize = newSize;
            apply_font_to_all_text();
        }
    }
}
