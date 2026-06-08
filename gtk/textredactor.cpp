#include "textredactor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

TextRedactor::TextRedactor()
: main_box(Gtk::Orientation::VERTICAL),
  top_bar(Gtk::Orientation::HORIZONTAL),
  font_btn("Шрифт..."),
  font_family("Sans"),
  font_size(12),
  highlight_enabled(true)
{
    set_title("Текстовый редактор");
    set_default_size(800, 600);
    set_child(main_box);
    main_box.set_margin(10);
    
    top_bar.set_spacing(10);
    top_bar.set_margin_bottom(10);
    
    // Меню
    m_menu_file = Gio::Menu::create();
    m_menu_file->append("Новый", "win.new");
    m_menu_file->append("Открыть...", "win.open");
    m_menu_file->append("Сохранить", "win.save");
    m_menu_file->append("Сохранить как...", "win.save_as");
    m_menu_file->append("Выход", "win.quit");
    
    file_menu_btn.set_label("Файл");
    file_menu_btn.set_menu_model(m_menu_file);
    top_bar.append(file_menu_btn);
    
    // Шрифты
    top_bar.append(font_btn);
    
    std::vector<int> sizes = {8,9,10,11,12,14,16,18,20,22,24,26,28,36,48,72};
    for (int s : sizes) {
        size_combo.append(std::to_string(s));
    }
    size_combo.set_active_text(std::to_string(font_size));
    top_bar.append(size_combo);
    
    main_box.append(top_bar);
    
    // Текст
    scroll_win.set_child(text_view);
    scroll_win.set_expand(true);
    
    text_buffer = Gtk::TextBuffer::create();
    text_view.set_buffer(text_buffer);
    
    main_box.append(scroll_win);
    
    // Действия
    auto action_group = Gio::SimpleActionGroup::create();
    action_group->add_action("new", sigc::mem_fun(*this, &TextRedactor::on_menu_file_new));
    action_group->add_action("open", sigc::mem_fun(*this, &TextRedactor::on_menu_file_open));
    action_group->add_action("save", sigc::mem_fun(*this, &TextRedactor::on_menu_file_save));
    action_group->add_action("save_as", sigc::mem_fun(*this, &TextRedactor::on_menu_file_save_as));
    action_group->add_action("quit", sigc::mem_fun(*this, &TextRedactor::on_menu_file_quit));
    insert_action_group("win", action_group);
    
    // Сигналы
    font_btn.signal_clicked().connect(sigc::mem_fun(*this, &TextRedactor::on_font_button_clicked));
    size_combo.signal_changed().connect(sigc::mem_fun(*this, &TextRedactor::on_font_size_changed));
    text_buffer->signal_changed().connect(sigc::mem_fun(*this, &TextRedactor::on_buffer_changed));
    
    file_dialog = Gtk::FileDialog::create();
    setup_tags();
    apply_font_to_all_text();
}

TextRedactor::~TextRedactor() {}

//ШРИФТЫ 

void TextRedactor::apply_font_to_all_text()
{
    if (!text_buffer) return;
    if (!font_tag) font_tag = text_buffer->create_tag("font_tag");
    
    font_tag->property_font() = font_family + " " + std::to_string(font_size);
    
    auto start = text_buffer->begin();
    auto end = text_buffer->end();
    text_buffer->remove_tag(font_tag, start, end);
    text_buffer->apply_tag(font_tag, start, end);
    highlight_words();
}

void TextRedactor::update_font_size_combo()
{
    size_combo.set_active_text(std::to_string(font_size));
}

void TextRedactor::on_font_button_clicked()
{
    auto dialog = Gtk::make_managed<Gtk::FontChooserDialog>("Выберите шрифт", *this);
    dialog->set_font(font_family + " " + std::to_string(font_size));
    dialog->set_modal(true);
    
    dialog->signal_response().connect([this, dialog](int response_id) {
        if (response_id == Gtk::ResponseType::OK) {
            std::string font_str = dialog->get_font();
            std::vector<std::string> parts;
            std::stringstream ss(font_str);
            std::string part;
            while (ss >> part) parts.push_back(part);
            
            if (parts.size() >= 2) {
                font_family = "";
                for (size_t i = 0; i < parts.size() - 1; ++i) {
                    if (i > 0) font_family += " ";
                    font_family += parts[i];
                }
                try {
                    font_size = static_cast<int>(std::stod(parts.back()));
                    update_font_size_combo();
                    apply_font_to_all_text();
                } catch (...) {}
            }
        }
        dialog->close();
    });
    dialog->show();
}

void TextRedactor::on_font_size_changed()
{
    std::string size_str = size_combo.get_active_text();
    if (!size_str.empty()) {
        try {
            int new_size = std::stoi(size_str);
            if (new_size != font_size) {
                font_size = new_size;
                apply_font_to_all_text();
            }
        } catch (...) {}
    }
}

//ПОДСВЕТКА 

void TextRedactor::setup_tags()
{
    red_tag = text_buffer->create_tag("red");
    red_tag->property_foreground() = "red";
    red_tag->property_weight() = Pango::Weight::BOLD;
}

void TextRedactor::highlight_words()
{
    if (!highlight_enabled) return;
    highlight_enabled = false;
    
    auto start = text_buffer->begin();
    auto end = text_buffer->end();
    std::string text = text_buffer->get_text(start, end);
    
    int cursor_offset = text_buffer->get_insert()->get_iter().get_offset();
    
    text_buffer->remove_tag(red_tag, start, end);
    
    for (const auto& word : words_to_highlight) {
        std::string lower_text = text;
        std::string lower_word = word;
        for (char& c : lower_text) c = std::tolower(static_cast<unsigned char>(c));
        for (char& c : lower_word) c = std::tolower(static_cast<unsigned char>(c));
        
        size_t pos = 0;
        while ((pos = lower_text.find(lower_word, pos)) != std::string::npos) {
            bool is_word_start = (pos == 0 || !std::isalpha(static_cast<unsigned char>(lower_text[pos-1])));
            bool is_word_end = (pos + word.length() >= lower_text.length() || 
                               !std::isalpha(static_cast<unsigned char>(lower_text[pos + word.length()])));
            
            if (is_word_start && is_word_end) {
                text_buffer->apply_tag(red_tag, 
                    text_buffer->get_iter_at_offset(pos),
                    text_buffer->get_iter_at_offset(pos + word.length()));
            }
            pos += word.length();
        }
    }
    
    if (cursor_offset <= text_buffer->get_char_count()) {
        text_buffer->place_cursor(text_buffer->get_iter_at_offset(cursor_offset));
    }
    
    highlight_enabled = true;
}

void TextRedactor::on_buffer_changed()
{
    highlight_words();
}

//  ДЕЙСТВИЯ МЕНЮ 

void TextRedactor::on_menu_file_new()
{
    text_buffer->set_text("");
    current_file = "";
    set_title("Текстовый редактор - Новый файл");
}

void TextRedactor::on_menu_file_open()
{
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Текстовые файлы");
    filter->add_pattern("*.txt");
    filter->add_pattern("*.cpp");
    filter->add_pattern("*.h");
    
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    filters->append(filter);
    file_dialog->set_filters(filters);
    file_dialog->set_title("Открыть файл");
    
    file_dialog->open(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = file_dialog->open_finish(result);
            if (file) {
                std::string path = file->get_path();
                if (!path.empty()) {
                    load_file(path);
                    current_file = path;
                    set_title("Текстовый редактор - " + Glib::path_get_basename(path));
                    apply_font_to_all_text();
                }
            }
        } catch (const Glib::Error& err) {
            auto alert = Gtk::AlertDialog::create("Ошибка");
            alert->set_detail(err.what());
            alert->show(*this);
        }
    });
}

void TextRedactor::on_menu_file_save()
{
    if (current_file.empty()) {
        on_menu_file_save_as();
        return;
    }
    save_file(current_file);
    auto alert = Gtk::AlertDialog::create("Сохранено");
    alert->show(*this);
}

void TextRedactor::on_menu_file_save_as()
{
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Текстовые файлы");
    filter->add_pattern("*.txt");
    
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    filters->append(filter);
    file_dialog->set_filters(filters);
    file_dialog->set_title("Сохранить файл");
    file_dialog->set_initial_name("документ.txt");
    
    file_dialog->save(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = file_dialog->save_finish(result);
            if (file) {
                std::string filename = file->get_path();
                if (filename.find('.') == std::string::npos) filename += ".txt";
                save_file(filename);
                current_file = filename;
                set_title("Текстовый редактор - " + Glib::path_get_basename(filename));
                
                auto alert = Gtk::AlertDialog::create("Сохранено");
                alert->show(*this);
            }
        } catch (const Glib::Error& err) {
            auto alert = Gtk::AlertDialog::create("Ошибка");
            alert->set_detail(err.what());
            alert->show(*this);
        }
    });
}

void TextRedactor::on_menu_file_quit()
{
    get_application()->quit();
}

//  ФАЙЛЫ 

void TextRedactor::load_file(const std::string& path)
{
    std::ifstream file(path);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        highlight_enabled = false;
        text_buffer->set_text(buffer.str());
        highlight_enabled = true;
        highlight_words();
        file.close();
    } else {
        auto alert = Gtk::AlertDialog::create("Ошибка");
        alert->set_detail("Не удалось открыть файл");
        alert->show(*this);
    }
}

void TextRedactor::save_file(const std::string& path)
{
    std::ofstream file(path);
    if (file.is_open()) {
        file << text_buffer->get_text(text_buffer->begin(), text_buffer->end());
        file.close();
    } else {
        auto alert = Gtk::AlertDialog::create("Ошибка");
        alert->set_detail("Не удалось сохранить файл");
        alert->show(*this);
    }
}
