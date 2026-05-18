#include <gtkmm.h>
#include <fstream>
#include <cstdio>

// ===== КЛАСС БЛОКНОТА =====
class SimpleNotepad : public Gtk::Window
{
private:
    // Основные контейнеры
    Gtk::Box vbox;      // вертикальный контейнер
    Gtk::Box hbox;      // горизонтальный контейнер для кнопок
    
    // Кнопки управления
    Gtk::Button newBtn;
    Gtk::Button loadBtn;
    Gtk::Button saveBtn;
    
    // Информационные надписи
    Gtk::Label fileNameLabel;
    Gtk::Label bottomStatus;
    
    // Текстовая область
    Gtk::TextView editArea;
    Gtk::ScrolledWindow scroller;
    
    // Путь к текущему файлу
    std::string filePath;
    
public:
    // ===== КОНСТРУКТОР =====
    SimpleNotepad()
        : vbox(Gtk::ORIENTATION_VERTICAL),
          hbox(Gtk::ORIENTATION_HORIZONTAL),
          newBtn("Новый"),
          loadBtn("Загрузить"),
          saveBtn("Сохранить")
    {
        // Настройки окна
        set_title("Записная книжка");
        resize(700, 550);
        
        // Прикрепляем главный контейнер
        add(vbox);
        
        // ----- ВЕРХНЯЯ ПАНЕЛЬ С КНОПКАМИ -----
        hbox.set_spacing(12);
        hbox.set_margin_top(8);
        hbox.set_margin_bottom(8);
        hbox.set_margin_start(8);
        
        hbox.pack_start(newBtn, Gtk::PACK_SHRINK);
        hbox.pack_start(loadBtn, Gtk::PACK_SHRINK);
        hbox.pack_start(saveBtn, Gtk::PACK_SHRINK);
        
        vbox.pack_start(hbox, Gtk::PACK_SHRINK);
        
        // ----- ИНФОРМАЦИЯ О ФАЙЛЕ -----
        fileNameLabel.set_text("Нет открытого файла");
        fileNameLabel.set_margin_start(8);
        fileNameLabel.set_margin_bottom(6);
        
        vbox.pack_start(fileNameLabel, Gtk::PACK_SHRINK);
        
        // ----- ПОЛЕ ДЛЯ ТЕКСТА С ПРОКРУТКОЙ -----
        scroller.add(editArea);
        scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        scroller.set_margin_start(8);
        scroller.set_margin_end(8);
        
        vbox.pack_start(scroller);
        
        // ----- НИЖНЯЯ СТРОКА -----
        bottomStatus.set_text("Ожидание действия");
        bottomStatus.set_margin_bottom(6);
        bottomStatus.set_margin_top(6);
        bottomStatus.set_margin_start(8);
        
        vbox.pack_start(bottomStatus, Gtk::PACK_SHRINK);
        
        // ----- ПРИВЯЗКА СОБЫТИЙ -----
        newBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_new));
        loadBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_load));
        saveBtn.signal_clicked().connect(sigc::mem_fun(*this, &SimpleNotepad::on_save));
        
        show_all_children();
    }
    
    // ===== СОЗДАТЬ НОВЫЙ ДОКУМЕНТ =====
    void on_new()
    {
        // Очищаем текст
        editArea.get_buffer()->set_text("");
        
        // Сбрасываем имя файла
        filePath = "";
        
        // Обновляем надписи
        fileNameLabel.set_text("Новый документ (не сохранён)");
        bottomStatus.set_text("Создан новый пустой документ");
    }
    
    // ===== ЗАГРУЗИТЬ ИЗ ФАЙЛА =====
    void on_load()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Выберите файл для открытия",
            Gtk::FILE_CHOOSER_ACTION_OPEN
        );
        
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Открыть", Gtk::RESPONSE_OK);
        
        int answer = dialog.run();
        
        if (answer == Gtk::RESPONSE_OK)
        {
            std::string chosenFile = dialog.get_filename();
            
            std::ifstream inputFile(chosenFile);
            
            if (inputFile.is_open())
            {
                // Читаем содержимое файла
                std::string wholeContent;
                std::string currentLine;
                
                while (std::getline(inputFile, currentLine))
                {
                    wholeContent += currentLine + "\n";
                }
                
                // Вставляем в текстовое поле
                editArea.get_buffer()->set_text(wholeContent);
                
                // Запоминаем путь
                filePath = chosenFile;
                
                // Обновляем интерфейс
                fileNameLabel.set_text("Файл: " + chosenFile);
                bottomStatus.set_text("Документ загружен успешно");
                
                inputFile.close();
            }
            else
            {
                bottomStatus.set_text("Ошибка: не удалось открыть файл");
            }
        }
        else
        {
            bottomStatus.set_text("Открытие отменено");
        }
    }
    
    // ===== СОХРАНИТЬ В ФАЙЛ =====
    void on_save()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Куда сохранить файл?",
            Gtk::FILE_CHOOSER_ACTION_SAVE
        );
        
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Сохранить", Gtk::RESPONSE_OK);
        
        int answer = dialog.run();
        
        if (answer == Gtk::RESPONSE_OK)
        {
            std::string targetFile = dialog.get_filename();
            
            std::ofstream outputFile(targetFile);
            
            if (outputFile.is_open())
            {
                // Получаем текст из редактора
                Glib::RefPtr<Gtk::TextBuffer> buffer = editArea.get_buffer();
                std::string textToSave = buffer->get_text();
                
                // Записываем
                outputFile << textToSave;
                
                // Запоминаем путь
                filePath = targetFile;
                
                // Обновляем интерфейс
                fileNameLabel.set_text("Сохранён: " + targetFile);
                bottomStatus.set_text("Документ сохранён");
                
                outputFile.close();
            }
            else
            {
                bottomStatus.set_text("Ошибка: не удалось создать файл");
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
