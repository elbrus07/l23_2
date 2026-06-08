#include "textredactor.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

TextRedactor::TextRedactor()
: main_box(Gtk::Orientation::VERTICAL),
  button_box(Gtk::Orientation::HORIZONTAL),
  font_box(Gtk::Orientation::HORIZONTAL),
  create_btn("Создать"),
  open_btn("Открыть"),
  save_btn("Сохранить"),
  font_btn("Шрифт"),
  highlight_enabled(true),
  current_font_description("Sans 12")
{
    set_title("Текстовый редактор");
    set_default_size(800, 600);

    set_child(main_box);

    main_box.set_margin(10);
    main_box.set_spacing(5);

    button_box.set_spacing(10);
    button_box.set_margin_bottom(5);
    button_box.set_halign(Gtk::Align::CENTER);

    button_box.append(create_btn);
    button_box.append(open_btn);
    button_box.append(save_btn);
    
    // Настройка панели шрифтов
    font_box.set_spacing(10);
    font_box.set_margin_bottom(10);
    font_box.set_halign(Gtk::Align::CENTER);
    font_box.append(font_btn);
    
    scroll_win.set_child(text_view);
    scroll_win.set_expand(true);

    text_buffer = Gtk::TextBuffer::create();
    text_view.set_buffer(text_buffer);

    // Добавляем все панели в главный бокс
    main_box.append(button_box);
    main_box.append(font_box);
    main_box.append(scroll_win);

    // Подключаем сигналы
    create_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &TextRedactor::create_click));

    open_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &TextRedactor::open_click));

    save_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &TextRedactor::save_click));
        
    font_btn.signal_clicked().connect(
        sigc::mem_fun(*this, &TextRedactor::on_font_click));

    setup_tags();
    text_buffer->signal_changed().connect(
        sigc::mem_fun(*this, &TextRedactor::on_buffer_changed));
        
    // Применяем шрифт по умолчанию
    apply_font(current_font_description);
    update_font_button_label();
}

TextRedactor::~TextRedactor(){}

void TextRedactor::setup_tags()
{
    red_tag = text_buffer->create_tag("red");
    red_tag->property_foreground() = "red";
    red_tag->property_background() = "yellow";
    red_tag->property_weight() = Pango::Weight::BOLD;
    
    // Создаем тег для шрифта
    font_tag = text_buffer->create_tag("font");
    
    // Устанавливаем приоритет тегов
    font_tag->set_priority(5);  // Низкий приоритет
    red_tag->set_priority(10);   // Высокий приоритет (поверх шрифта)
}

void TextRedactor::apply_font(const std::string& font_desc)
{
    current_font_description = font_desc;
    
    try {
        // Парсим описание шрифта
        Pango::FontDescription pango_font;
        
        // Разбираем строку вида "Шрифт Размер"
        std::istringstream iss(font_desc);
        std::string font_name;
        int font_size;
        
        if (iss >> font_name >> font_size) {
            pango_font.set_family(font_name);
            pango_font.set_size(font_size * Pango::SCALE);
        } else {
            // Пробуем альтернативный формат
            pango_font = Pango::FontDescription(font_desc);
        }
        
        // Обновляем тег шрифта
        font_tag->property_font_desc() = pango_font;
        
        // Применяем ко всему существующему тексту
        auto start = text_buffer->begin();
        auto end = text_buffer->end();
        
        // Сначала удаляем старый тег шрифта
        text_buffer->remove_tag(font_tag, start, end);
        // Затем применяем новый
        text_buffer->apply_tag(font_tag, start, end);
        
        // Применяем шрифт через CSS для GTK4
        auto provider = Gtk::CssProvider::create();
        std::string css = "textview { font: " + font_desc + "; }";
        provider->load_from_data(css);
        
        auto style_context = text_view.get_style_context();
        style_context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка применения шрифта: " << e.what() << std::endl;
    }
}

void TextRedactor::update_font_button_label()
{
    font_btn.set_label("Шрифт: " + current_font_description);
}

void TextRedactor::on_font_click()
{
    // Создаем диалог выбора шрифта
    auto font_dialog = new Gtk::FontChooserDialog("Выберите шрифт", *this);
    
    // Устанавливаем текущий шрифт
    font_dialog->set_font(current_font_description);
    
    font_dialog->add_button("_Отмена", Gtk::ResponseType::CANCEL);
    font_dialog->add_button("_Применить", Gtk::ResponseType::ACCEPT);
    
    font_dialog->signal_response().connect(
        [this, font_dialog](int response_id) {
            if (response_id == Gtk::ResponseType::ACCEPT) {
                std::string selected_font = font_dialog->get_font();
                
                // Применяем выбранный шрифт
                apply_font(selected_font);
                update_font_button_label();
                
                std::cout << "Выбран шрифт: " << selected_font << std::endl;
            }
            
            delete font_dialog;
        }
    );
    
    font_dialog->show();
}

void TextRedactor::highlight_words()
{
    if (!highlight_enabled) return;
    
    highlight_enabled = false;
    
    auto start = text_buffer->begin();
    auto end = text_buffer->end();
    std::string text = text_buffer->get_text(start, end);
    
    auto cursor_pos = text_buffer->get_insert()->get_iter();
    int cursor_offset = cursor_pos.get_offset();
    
    // Удаляем только тег подсветки, не трогаем тег шрифта
    text_buffer->remove_tag(red_tag, start, end);
    
    for (const auto& word : words_to_highlight) {
        std::cout << "Ищем слово: " << word << std::endl;
        
        // Простой поиск без regex для проверки
        size_t pos = 0;
        std::string lower_text = text;
        std::string lower_word = word;
        
        // Приводим к нижнему регистру для регистронезависимого поиска
        for (char& c : lower_text) c = std::tolower(c);
        for (char& c : lower_word) c = std::tolower(c);
        
        while ((pos = lower_text.find(lower_word, pos)) != std::string::npos) {
            // Проверяем, что это целое слово
            bool is_word_start = (pos == 0 || !std::isalpha(lower_text[pos-1]));
            bool is_word_end = (pos + word.length() >= lower_text.length() || 
                               !std::isalpha(lower_text[pos + word.length()]));
            
            if (is_word_start && is_word_end) {
                std::cout << "Найдено слово на позиции: " << pos << std::endl;
                Gtk::TextIter word_start = text_buffer->get_iter_at_offset(pos);
                Gtk::TextIter word_end = text_buffer->get_iter_at_offset(pos + word.length());
                text_buffer->apply_tag(red_tag, word_start, word_end);
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

void TextRedactor::create_click()
{
    current_file = "новый_файл.txt";

    highlight_enabled = false;
    text_buffer->set_text("");
    
    // Сохраняем текущий шрифт для нового документа
    if (font_tag) {
        auto start = text_buffer->begin();
        auto end = text_buffer->end();
        text_buffer->apply_tag(font_tag, start, end);
    }
    
    highlight_enabled = true;

    std::ofstream out(current_file);
    out.close();

    set_title("Текстовый редактор - " + current_file);
}

void TextRedactor::open_click()
{
    auto dialog = new Gtk::FileChooserDialog(
        "Открыть файл",
        Gtk::FileChooser::Action::OPEN
    );

    dialog->set_transient_for(*this);

    dialog->add_button(
        "_Отмена",
        Gtk::ResponseType::CANCEL
    );

    dialog->add_button(
        "_Открыть",
        Gtk::ResponseType::ACCEPT
    );

    dialog->signal_response().connect(
        [this, dialog](int response_id)
        {
            if(response_id == Gtk::ResponseType::ACCEPT)
            {
                auto file = dialog->get_file();

                if(file)
                {
                    current_file = file->get_path();

                    load_file(current_file);
                    
                    // Применяем текущий шрифт к загруженному тексту
                    if (font_tag) {
                        auto start = text_buffer->begin();
                        auto end = text_buffer->end();
                        text_buffer->apply_tag(font_tag, start, end);
                    }

                    set_title(
                        "Текстовый редактор - " +
                        Glib::path_get_basename(current_file)
                    );
                }
            }

            delete dialog;
        }
    );

    dialog->show();
}

void TextRedactor::save_click()
{
    if(current_file.empty())
    {
        auto dialog = new Gtk::FileChooserDialog(
            "Сохранить файл",
            Gtk::FileChooser::Action::SAVE
        );

        dialog->set_transient_for(*this);

        dialog->set_current_name("документ.txt");

        dialog->add_button(
            "_Отмена",
            Gtk::ResponseType::CANCEL
        );

        dialog->add_button(
            "_Сохранить",
            Gtk::ResponseType::ACCEPT
        );

        dialog->signal_response().connect(
            [this, dialog](int response_id)
            {
                if(response_id == Gtk::ResponseType::ACCEPT)
                {
                    auto file = dialog->get_file();

                    if(file)
                    {
                        current_file = file->get_path();

                        save_file(current_file);

                        set_title(
                            "Текстовый редактор - " +
                            Glib::path_get_basename(current_file)
                        );
                    }
                }

                delete dialog;
            }
        );

        dialog->show();
    }
    else
    {
        save_file(current_file);
    }
}

void TextRedactor::load_file(const std::string& path)
{
    std::ifstream file(path);

    if(file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();

        highlight_enabled = false;
        text_buffer->set_text(buffer.str());
        
        // Применяем текущий шрифт к загруженному тексту
        if (font_tag) {
            auto start = text_buffer->begin();
            auto end = text_buffer->end();
            text_buffer->apply_tag(font_tag, start, end);
        }
        
        highlight_enabled = true;
        highlight_words();

        file.close();
    }
}

void TextRedactor::save_file(const std::string& path)
{
    std::ofstream file(path);

    if(file.is_open())
    {
        auto start = text_buffer->begin();
        auto end = text_buffer->end();

        file << text_buffer->get_text(start, end);

        file.close();
    }
}
