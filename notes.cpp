#include <gtkmm.h>
#include <fstream>
#include <cstdio>
#include <regex>
#include <map>

// ===== КЛАСС БЛОКНОТА =====
class SimpleNotepad : public Gtk::Window
{
private:
    // Основные контейнеры
    Gtk::VBox vbox;
    Gtk::HBox hbox;
    Gtk::HBox hbox2;  // Вторая строка для новых кнопок
    
    // Кнопки управления
    Gtk::Button newBtn;
    Gtk::Button loadBtn;
    Gtk::Button saveBtn;
    
    // Новые кнопки
    Gtk::Button fontBtn;      // Выбор шрифта
    Gtk::Button sizeUpBtn;    // Увеличить шрифт
    Gtk::Button sizeDownBtn;  // Уменьшить шрифт
    
    // Информационные надписи
    Gtk::Label fileNameLabel;
    Gtk::Label bottomStatus;
    Gtk::Label fontInfoLabel;  // Показывает текущий шрифт
    
    // Текстовая область
    Gtk::TextView editArea;
    Gtk::ScrolledWindow scroller;
    
    // Путь к текущему файлу
    std::string filePath;
    
    // Текущий шрифт и размер
    std::string currentFontName;
    int currentFontSize;
    
    // ===== ФУНКЦИЯ ПОДСВЕТКИ СЛОВ =====
    void applyHighlighting()
    {
        Glib::RefPtr<Gtk::TextBuffer> buffer = editArea.get_buffer();
        Gtk::TextBuffer::iterator start, end;
        buffer->get_bounds(start, end);
        
        std::string fullText = buffer->get_text();
        std::regex wordRegex(R"([а-яА-Яa-zA-Z]+)");
        std::smatch match;
        
        std::string::const_iterator searchStart(fullText.cbegin());
        
        Glib::RefPtr<Gtk::TextBuffer::TagTable> tagTable = buffer->get_tag_table();
        
        auto createColorTag = [&](const std::string& tagName, const std::string& colorName)
        {
            Glib::RefPtr<Gtk::TextBuffer::Tag> tag = tagTable->lookup(tagName);
            if (!tag)
            {
                tag = Gtk::TextBuffer::Tag::create(tagName);
                tag->property_foreground() = colorName;
                tagTable->add(tag);
            }
            return tag;
        };
        
        auto redTag = createColorTag("red_color", "red");
        auto blueTag = createColorTag("blue_color", "blue");
        auto greenTag = createColorTag("green_color", "green");
        auto yellowTag = createColorTag("yellow_color", "yellow");
        auto cyanTag = createColorTag("cyan_color", "cyan");
        auto orangeTag = createColorTag("orange_color", "orange");
        auto grayTag = createColorTag("gray_color", "gray");
        
        buffer->remove_all_tags(start, end);
        
        while (std::regex_search(searchStart, fullText.cend(), match, wordRegex))
        {
            std::string word = match[0];
            if (!word.empty())
            {
                char firstLetter = tolower(word[0]);
                
                int position = match.position();
                int length = match.length();
                
                Gtk::TextBuffer::iterator wordStart = buffer->get_iter_at_offset(position);
                Gtk::TextBuffer::iterator wordEnd = buffer->get_iter_at_offset(position + length);
                
                switch (firstLetter)
                {
                    case 'к': buffer->apply_tag(redTag, wordStart, wordEnd); break;
                    case 'с': buffer->apply_tag(blueTag, wordStart, wordEnd); break;
                    case 'з': buffer->apply_tag(greenTag, wordStart, wordEnd); break;
                    case 'ж': buffer->apply_tag(yellowTag, wordStart, wordEnd); break;
                    case 'г': buffer->apply_tag(cyanTag, wordStart, wordEnd); break;
                    case 'о': buffer->apply_tag(orangeTag, wordStart, wordEnd); break;
                    case 'ч': case 'б': buffer->apply_tag(grayTag, wordStart, wordEnd); break;
                    default: break;
                }
            }
            searchStart = match.suffix().first;
        }
    }
    
    // ===== ПРИМЕНИТЬ ШРИФТ =====
    void applyFont()
    {
        Glib::RefPtr<Gtk::TextBuffer> buffer = editArea.get_buffer();
        Gtk::TextBuffer::iterator start, end;
        buffer->get_bounds(start, end);
        
        // Создаём тег для шрифта
        Glib::RefPtr<Gtk::TextBuffer::TagTable> tagTable = buffer->get_tag_table();
        Glib::RefPtr<Gtk::TextBuffer::Tag> fontTag = tagTable->lookup("font_tag");
        
        if (!fontTag)
        {
            fontTag = Gtk::TextBuffer::Tag::create("font_tag");
            tagTable->add(fontTag);
        }
        
        // Устанавливаем шрифт и размер
        std::string fontDesc = currentFontName + " " + std::to_string(currentFontSize);
        fontTag->property_font() = fontDesc;
        
        // Применяем ко всему тексту
        buffer->apply_tag(fontTag, start, end);
    }
    
    // ===== ВЫБОР ШРИФТА =====
    void on_font_selected()
    {
        Gtk::FontChooserDialog dialog(*this, "Выберите шрифт", true);
        dialog.set_font(currentFontName + " " + std::to_string(currentFontSize));
        
        int result = dialog.run();
        
        if (result == Gtk::RESPONSE_OK)
        {
            std::string fontStr = dialog.get_font();
            
            // Разбираем строку шрифта (например: "Sans 12")
            size_t spacePos = fontStr.find_last_of(' ');
            if (spacePos != std::string::npos)
            {
                currentFontName = fontStr.substr(0, spacePos);
                currentFontSize = std::stoi(fontStr.substr(spacePos + 1));
                
                fontInfoLabel.set_text("Шрифт: " + currentFontName + ", " + std::to_string(currentFontSize));
                applyFont();
                bottomStatus.set_text("Шрифт изменён на " + currentFontName);
            }
        }
    }
    
    // ===== УВЕЛИЧИТЬ ШРИФТ =====
    void on_size_up()
    {
        currentFontSize += 2;
        if (currentFontSize > 72) currentFontSize = 72;
        
        fontInfoLabel.set_text("Шрифт: " + currentFontName + ", " + std::to_string(currentFontSize));
        applyFont();
        bottomStatus.set_text("Размер шрифта увеличен до " + std::to_string(currentFontSize));
    }
    
    // ===== УМЕНЬШИТЬ ШРИФТ =====
    void on_size_down()
    {
        currentFontSize -= 2;
        if (currentFontSize < 8) currentFontSize = 8;
        
        fontInfoLabel.set_text("Шрифт: " + currentFontName + ", " + std::to_string(currentFontSize));
        applyFont();
        bottomStatus.set_text("Размер шрифта уменьшен до " + std::to_string(currentFontSize));
    }
    
public:
    // ===== КОНСТРУКТОР =====
    SimpleNotepad() : currentFontName("Sans"), currentFontSize(12)
    {
        set_title("Записная книжка с подсветкой и шрифтами");
        set_default_size(700, 600);
        
        // Создаём кнопки
        newBtn.set_label("Новый");
        loadBtn.set_label("Загрузить");
        saveBtn.set_label("Сохранить");
        
        // Новые кнопки
        fontBtn.set_label("Выбрать шрифт");
        sizeUpBtn.set_label("Шрифт +");
        sizeDownBtn.set_label("Шрифт -");
        
        // Настройка контейнеров
        vbox.set_spacing(5);
        hbox.set_spacing(10);
        hbox2.set_spacing(10);
        
        // Первая строка кнопок
        hbox.pack_start(newBtn, Gtk::PACK_SHRINK);
        hbox.pack_start(loadBtn, Gtk::PACK_SHRINK);
        hbox.pack_start(saveBtn, Gtk::PACK_SHRINK);
        
        // Вторая строка кнопок (шрифты)
        hbox2.pack_start(fontBtn, Gtk::PACK_SHRINK);
        hbox2.pack_start(sizeUpBtn, Gtk::PACK_SHRINK);
        hbox2.pack_start(sizeDownBtn, Gtk::PACK_SHRINK);
        
        // Добавляем строки в вертикальный контейнер
        vbox.pack_start(hbox, Gtk::PACK_SHRINK);
        vbox.pack_start(hbox2, Gtk::PACK_SHRINK);
        
        // Информация о шрифте
        fontInfoLabel.set_text("Шрифт: Sans, 12");
        fontInfoLabel.set_margin_start(8);
        fontInfoLabel.set_margin_top(4);
        vbox.pack_start(fontInfoLabel, Gtk::PACK_SHRINK);
        
        // Имя файла
        fileNameLabel.set_text("Нет открытого файла");
        fileNameLabel.set_margin_start(8);
        vbox.pack_start(fileNameLabel, Gtk::PACK_SHRINK);
        
        // Текстовая область
        scroller.add(editArea);
        scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        scroller.set_shadow_type(Gtk::SHADOW_IN);
        vbox.pack_start(scroller);
        
        // Строка статуса
        bottomStatus.set_text("Готов к работе");
        bottomStatus.set_margin_bottom(6);
        bottomStatus.set_margin_top(6);
        bottomStatus.set_margin_start(8);
        vbox.pack_start(bottomStatus, Gtk::PACK_SHRINK);
        
        add(vbox);
        
        // Привязываем события
        newBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_new));
        loadBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_load));
        saveBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_save));
        
        // События для шрифтов
        fontBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_font_selected));
        sizeUpBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_size_up));
        sizeDownBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_size_down));
        
        // Подсветка при изменении текста
        editArea.get_buffer()->signal_changed().connect(sigc::mem_fun(*this, &SimpleNotepad::applyHighlighting));
        
        show_all_children();
    }
    
    // ===== СОЗДАТЬ НОВЫЙ ДОКУМЕНТ =====
    void on_new()
    {
        Glib::RefPtr<Gtk::TextBuffer> buf = editArea.get_buffer();
        buf->set_text("");
        filePath = "";
        fileNameLabel.set_text("Новый документ");
        bottomStatus.set_text("Создан новый файл");
    }
    
    // ===== ЗАГРУЗИТЬ ИЗ ФАЙЛА =====
    void on_load()
    {
        Gtk::FileChooserDialog dialog(*this, "Открыть файл", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Открыть", Gtk::RESPONSE_OK);
        
        int result = dialog.run();
        
        if (result == Gtk::RESPONSE_OK)
        {
            std::string filename = dialog.get_filename();
            std::ifstream inFile(filename.c_str());
            
            if (inFile.is_open())
            {
                std::string content = "", line = "";
                while (std::getline(inFile, line))
                    content += line + "\n";
                
                Glib::RefPtr<Gtk::TextBuffer> buf = editArea.get_buffer();
                buf->set_text(content);
                
                filePath = filename;
                fileNameLabel.set_text("Файл: " + filename);
                bottomStatus.set_text("Файл загружен");
                inFile.close();
            }
            else
            {
                bottomStatus.set_text("Ошибка при открытии");
            }
        }
        else
        {
            bottomStatus.set_text("Операция отменена");
        }
    }
    
    // ===== СОХРАНИТЬ В ФАЙЛ =====
    void on_save()
    {
        Gtk::FileChooserDialog dialog(*this, "Сохранить файл", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Сохранить", Gtk::RESPONSE_OK);
        
        int result = dialog.run();
        
        if (result == Gtk::RESPONSE_OK)
        {
            std::string filename = dialog.get_filename();
            std::ofstream outFile(filename.c_str());
            
            if (outFile.is_open())
            {
                Glib::RefPtr<Gtk::TextBuffer> buf = editArea.get_buffer();
                std::string text = buf->get_text();
                outFile << text;
                
                filePath = filename;
                fileNameLabel.set_text("Файл: " + filename);
                bottomStatus.set_text("Файл сохранён");
                outFile.close();
            }
            else
            {
                bottomStatus.set_text("Ошибка при сохранении");
            }
        }
        else
        {
            bottomStatus.set_text("Сохранение отменено");
        }
    }
};

// ===== ГЛАВНАЯ ФУНКЦИЯ =====
int main(int argc, char *argv[])
{
    auto application = Gtk::Application::create(argc, argv, "my.simple.notepad");
    SimpleNotepad notepad;
    return application->run(notepad);
}
