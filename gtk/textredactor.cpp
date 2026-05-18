#include "textredactor.h"
#include <fstream>
#include <iostream>



TextRedactor::TextRedactor()
: main_box(Gtk::Orientation::VERTICAL),
  button_box(Gtk::Orientation::HORIZONTAL),
  create_btn("Создать"),
  open_btn("Открыть"),
  save_btn("Сохранить")
{
 
    set_title("Текстовый редактор");
    set_default_size(800, 600);
    set_child(main_box)

    // Настройка отступов
    main_box.set_margin(10);
    button_box.set_spacing(10);
    button_box.set_margin_bottom(10);

    // Добавляем кнопки в панель
    button_box.append(create_btn);
    button_box.append(open_btn);
    button_box.append(save_btn);
    
    
    
    scroll_win.set_child(TextView);
    scroll_win.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scroll_win.set_expand(true);  //расширяет виджет
    
    text_buffer = Gtk::TextBuffer::create(); //ХРАНИЛИЩЕ ДЛЯ ТЕКСТАР 
    text_view.set_buffer(text_buffer);

   // Собираем всё вместе
    main_box.append(button_box);
    main_box.append(scroll_win);
    
    
    
   
    //подключение обработчика собыитий
    create_btn.signal_clicked().connect(sigc::mem_fun(*this, &TextRedactor::button_create));
    open_btn.signal_clicked().connect(sigc::mem_fun(*this, &TextRedactor::button_open));
    save_btn.signal_clicked().connect(sigc::mem_fun(*this, &TextRedactor::button_save));

    current_file = "";
}

TextRedactor::~TextRedactor() {}

void TextRedactor::button_create()
{

    // Создаем диалог для выбора имени файла
    auto dialog = Gtk::FileDialog::create();
    dialog->set_title("Создать новый файл");
    dialog->set_initial_name("новый_файл.txt");

    dialog->save(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) 
        {
            try {
                auto file = Gtk::FileDialog::create()->save_finish(result);
                if (file) {
                    currentFile = file->get_path();
                    
                    text_buffer->set_text("");
                    std::ofstream out(current_file);
                    out.close();
                    set_title("Текстовый редактор - " + Glib::path_get_basename(current_file));
                }
                    
            }catch (const Glib::Error& err) {
            std::cerr << "Ошибка: " << err.what() << std::endl
        }
    });

}

void TextRedactor::button_open()
{
    auto dialog = Gtk::FileDialog::create();
    dialog->set_title("Открыть файл");
    
    
    
    // Показываем диалог открытия
    dialog->open(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
        try {
            auto file = Gtk::FileDialog::create()->open_finish(result);
            if (file) {
                current_file = file->get_path();
                load_from_file(current_file);
                set_title("Текстовый редактор - " + Glib::path_get_basename(current_file));
            }
        }catch (const Glib::Error& err) {
            std::cerr << "Ошибка: " << err.what() << std::endl;
        }
    });
}

void TextRedactor::button_save()
{
    if (current_file.empty()) {
        // Если файл еще не выбран, показываем диалог сохранения
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Сохранить файл");
        dialog->set_initial_name("документ.txt");
        
        
        
        dialog->save(*this, [this](const Glib::RefPtr<Gio::AsyncResult>& result) {
            try {
                auto file = Gtk::FileDialog::create()->save_finish(result);
                if (file) {
                    current_file = file->get_path();
                    save_to_file(current_file);
                    set_title("Текстовый редактор - " + Glib::path_get_basename(current_file));
                }
            } catch (const Glib::Error& err) {
                std::cerr << "Ошибка: " << err.what() << std::endl;
            }
        });
    } else {
        // Сохраняем в существующий файл
        save_to_file(current_file);
    }

    
}
void TextRedactor::save_to_file(const std::string& path)
{
    std::ofstream file(path);
    if (file.is_open()) {
        auto start = text_buffer->begin();
        auto end = text_buffer->end();
        file << text_buffer->get_text(start, end);
        file.close();
    }
}