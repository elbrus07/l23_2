#include <gtkmm.h>
#include <fstream>
#include <iostream>

// ===== КЛАСС ТЕКСТОВОГО РЕДАКТОРА =====
class TextEditor : public Gtk::Window
{
private:

    // Главный контейнер
    Gtk::Box mainBox;

    // Контейнер для кнопок
    Gtk::Box buttonBox;

    // Кнопки
    Gtk::Button btnCreate;
    Gtk::Button btnOpen;
    Gtk::Button btnSave;

    // Надпись с текущим файлом
    Gtk::Label fileLabel;

    // Строка состояния
    Gtk::Label statusLabel;

    // Поле текста
    Gtk::TextView textView;

    // Прокрутка
    Gtk::ScrolledWindow scroll;

    // Имя текущего файла
    std::string currentFile;

public:

    // ===== КОНСТРУКТОР =====
    TextEditor()
        : mainBox(Gtk::ORIENTATION_VERTICAL),
        buttonBox(Gtk::ORIENTATION_HORIZONTAL),
        btnCreate("Создать"),
        btnOpen("Открыть"),
        btnSave("Сохранить")
    {
        // ----- ОКНО -----
        set_title("Текстовый редактор GTKmm");
        set_default_size(800, 600);

        // ----- ДОБАВЛЯЕМ ГЛАВНЫЙ КОНТЕЙНЕР -----
        add(mainBox);

        // ----- КНОПКИ -----
        buttonBox.set_spacing(10);

        buttonBox.pack_start(btnCreate, Gtk::PACK_SHRINK);
        buttonBox.pack_start(btnOpen, Gtk::PACK_SHRINK);
        buttonBox.pack_start(btnSave, Gtk::PACK_SHRINK);

        mainBox.pack_start(buttonBox, Gtk::PACK_SHRINK);

        // ----- ИНФОРМАЦИЯ О ФАЙЛЕ -----
        fileLabel.set_text("Текущий файл: нет");

        mainBox.pack_start(fileLabel, Gtk::PACK_SHRINK);

        // ----- ПРОКРУТКА -----
        scroll.add(textView);

        scroll.set_policy(
            Gtk::POLICY_AUTOMATIC,
            Gtk::POLICY_AUTOMATIC);

        mainBox.pack_start(scroll);

        // ----- СТРОКА СОСТОЯНИЯ -----
        statusLabel.set_text("Готово");

        mainBox.pack_start(statusLabel, Gtk::PACK_SHRINK);

        // ----- СОБЫТИЯ КНОПОК -----
        btnCreate.signal_clicked().connect(
            sigc::mem_fun(*this,
                &TextEditor::on_create_clicked));

        btnOpen.signal_clicked().connect(
            sigc::mem_fun(*this,
                &TextEditor::on_open_clicked));

        btnSave.signal_clicked().connect(
            sigc::mem_fun(*this,
                &TextEditor::on_save_clicked));

        // ----- ПОКАЗАТЬ ВСЁ -----
        show_all_children();
    }

    // ===== СОЗДАТЬ =====
    void on_create_clicked()
    {
        textView.get_buffer()->set_text("");

        currentFile = "";

        fileLabel.set_text("Текущий файл: новый документ");

        statusLabel.set_text("Создан новый документ");
    }

    // ===== ОТКРЫТЬ =====
    void on_open_clicked()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Открыть файл",
            Gtk::FILE_CHOOSER_ACTION_OPEN);

        dialog.add_button(
            "Отмена",
            Gtk::RESPONSE_CANCEL);

        dialog.add_button(
            "Открыть",
            Gtk::RESPONSE_OK);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK)
        {
            std::string filename =
                dialog.get_filename();

            std::ifstream file(filename);

            if (file)
            {
                std::string content;
                std::string line;

                while (getline(file, line))
                {
                    content += line + "\n";
                }

                textView.get_buffer()->set_text(content);

                currentFile = filename;

                fileLabel.set_text(
                    "Текущий файл: " + filename);

                statusLabel.set_text(
                    "Файл успешно открыт");

                file.close();
            }
        }
    }

    // ===== СОХРАНИТЬ =====
    void on_save_clicked()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Сохранить файл",
            Gtk::FILE_CHOOSER_ACTION_SAVE);

        dialog.add_button(
            "Отмена",
            Gtk::RESPONSE_CANCEL);

        dialog.add_button(
            "Сохранить",
            Gtk::RESPONSE_OK);

        int result = dialog.
run();

        if (result == Gtk::RESPONSE_OK)
        {
            std::string filename =
                dialog.get_filename();

            std::ofstream file(filename);

            if (file)
            {
                std::string text =
                    textView.get_buffer()->get_text();

                file << text;

                currentFile = filename;

                fileLabel.set_text(
                    "Текущий файл: " + filename);

                statusLabel.set_text(
                    "Файл успешно сохранён");

                file.close();
            }
        }
    }
};

// ===== MAIN =====
int main(int argc, char* argv[])
{
    auto app =
        Gtk::Application::create(
            argc,
            argv,
            "org.gtkmm.editor");

    TextEditor editor;

    return app->run(editor);
}
