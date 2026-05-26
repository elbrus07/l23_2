#include "textredactor.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

TextRedactor::TextRedactor()
: main_box(Gtk::Orientation::VERTICAL),
  button_box(Gtk::Orientation::HORIZONTAL),
  create_btn("Создать"),
  open_btn("Открыть"),
  save_btn("Сохранить"),
  highlight_enabled(true)
{
    set_title("Текстовый редактор");
    set_default_size(800, 600);

    set_child(main_box);

    main_box.set_margin(10);

    button_box.set_spacing(10);
    button_box.set_margin_bottom(10);

    button_box.append(create_btn);
    button_box.append(open_btn);
    button_box.append(save_btn);

    scroll_win.set_child(text_view);
    scroll_win.set_expand(true);

    text_buffer = Gtk::TextBuffer::create();

    text_view.set_buffer(text_buffer);

    main_box.append(button_box);
    main_box.append(scroll_win);

    create_btn.signal_clicked().connect(
        sigc::mem_fun(*this,&TextRedactor::create_click));

    open_btn.signal_clicked().connect(
        sigc::mem_fun(*this,&TextRedactor::open_click));

    save_btn.signal_clicked().connect(
        sigc::mem_fun(*this,&TextRedactor::save_click));

    setup_tags();
    text_buffer->signal_changed().connect(
        sigc::mem_fun(*this, &TextRedactor::on_buffer_changed));
}

TextRedactor::~TextRedactor(){}

void TextRedactor::setup_tags()
{
    red_tag = text_buffer->create_tag("red");
    red_tag->property_foreground() = "red";
    red_tag->property_background() = "yellow";  // Для проверки - желтый фон
    red_tag->property_weight() = Pango::Weight::BOLD;

    
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
    
    text_buffer->remove_tag(red_tag, start, end);
    
    for (const auto& word : words_to_highlight) {
        std::cout << "Ищем слово: " << word << std::endl;
        
        std::string search_word = word;
        
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
    current_file="новый_файл.txt";

    highlight_enabled = false;
    text_buffer->set_text("");
    highlight_enabled = true;

    std::ofstream out(current_file);
    out.close();

    set_title(
        "Текстовый редактор - " +
        current_file
    );
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
        [this,dialog](int response_id)
        {
            if(response_id==Gtk::ResponseType::ACCEPT)
            {
                auto file=dialog->get_file();

                if(file)
                {
                    current_file=file->get_path();

                    load_file(current_file);

                    set_title(
                        "Текстовый редактор - "+
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
        auto start=text_buffer->begin();
        auto end=text_buffer->end();

        file<<text_buffer->get_text(start,end);

        file.close();
    }
}

