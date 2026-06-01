#include <gtkmm.h>
#include <fstream>
#include <string>

// ==================== РЕДАКТОР ====================
class TextEditor : public Gtk::Window
{
private:

    // Главный контейнер
    Gtk::Box mainBox{Gtk::ORIENTATION_VERTICAL};

    // Меню
    Gtk::MenuBar menuBar;

    Gtk::MenuItem fileItem{"Файл"};
    Gtk::Menu fileMenu;

    Gtk::MenuItem createItem{"Создать"};
    Gtk::MenuItem openItem{"Открыть"};
    Gtk::MenuItem saveItem{"Сохранить"};
    Gtk::MenuItem exitItem{"Выход"};

    // Панель инструментов
    Gtk::Box toolBox{Gtk::ORIENTATION_HORIZONTAL};

    Gtk::Button btnCreate{"Создать"};
    Gtk::Button btnOpen{"Открыть"};
    Gtk::Button btnSave{"Сохранить"};

    Gtk::Label fontLabel{"Шрифт:"};
    Gtk::FontButton fontButton;

    Gtk::Label sizeLabel{"Размер:"};
    Gtk::ComboBoxText sizeCombo;

    // Текстовое поле
    Gtk::ScrolledWindow scroll;
    Gtk::TextView textView;

    // Информация
    Gtk::Label fileLabel;
    Gtk::Label statusLabel;

    std::string currentFile;

public:

    TextEditor()
    {
        set_title("Текстовый редактор");
        set_default_size(900, 600);

        add(mainBox);

        // ==================== МЕНЮ ====================

        fileMenu.append(createItem);
        fileMenu.append(openItem);
        fileMenu.append(saveItem);
        fileMenu.append(exitItem);

        fileItem.set_submenu(fileMenu);

        menuBar.append(fileItem);

        mainBox.pack_start(menuBar, Gtk::PACK_SHRINK);

        // ==================== ПАНЕЛЬ ====================

        toolBox.set_spacing(10);

        toolBox.pack_start(btnCreate, Gtk::PACK_SHRINK);
        toolBox.pack_start(btnOpen, Gtk::PACK_SHRINK);
        toolBox.pack_start(btnSave, Gtk::PACK_SHRINK);

        toolBox.pack_start(fontLabel, Gtk::PACK_SHRINK);
        toolBox.pack_start(fontButton, Gtk::PACK_SHRINK);

        toolBox.pack_start(sizeLabel, Gtk::PACK_SHRINK);

        sizeCombo.append("10");
        sizeCombo.append("12");
        sizeCombo.append("14");
        sizeCombo.append("16");
        sizeCombo.append("18");
        sizeCombo.append("20");
        sizeCombo.append("24");
        sizeCombo.append("28");
        sizeCombo.append("32");

        sizeCombo.set_active_text("14");

        toolBox.pack_start(sizeCombo, Gtk::PACK_SHRINK);

        mainBox.pack_start(toolBox, Gtk::PACK_SHRINK);

        // ==================== ИНФОРМАЦИЯ ====================

        fileLabel.set_text("Файл: новый документ");

        mainBox.pack_start(fileLabel, Gtk::PACK_SHRINK);

        // ==================== ТЕКСТ ====================

        scroll.add(textView);

        scroll.set_policy(
            Gtk::POLICY_AUTOMATIC,
            Gtk::POLICY_AUTOMATIC);

        mainBox.pack_start(scroll);

        // ==================== СТАТУС ====================

        statusLabel.set_text("Готово");

        mainBox.pack_start(statusLabel, Gtk::PACK_SHRINK);

        // ==================== СОБЫТИЯ ====================

        btnCreate.signal_clicked().connect(
            sigc::mem_fun(*this, &TextEditor::createFile));

        btnOpen.signal_clicked().connect(
            sigc::mem_fun(*this, &TextEditor::openFile));

        btnSave.signal_clicked().connect(
            sigc::mem_fun(*this, &TextEditor::saveFile));

        createItem.signal_activate().connect(
            sigc::mem_fun(*this, &TextEditor::createFile));

        openItem.signal_activate().connect(
            sigc::mem_fun(*this, &TextEditor::openFile));

        saveItem.signal_activate().connect(
            sigc::mem_fun(*this, &TextEditor::saveFile));

        exitItem.signal_activate().connect(
            sigc::mem_fun(*this, &TextEditor::close));

        fontButton.signal_font_set().connect(
            sigc::mem_fun(*this, &TextEditor::changeFont));

        sizeCombo.signal_changed().connect(
            sigc::mem_fun(*this, &TextEditor::changeFont));

        show_all_children();
    }

private:

    // ==================== НОВЫЙ ФАЙЛ ====================

    void createFile()
    {
        textView.
get_buffer()->set_text("");

        currentFile.clear();

        fileLabel.set_text("Файл: новый документ");
        statusLabel.set_text("Создан новый документ");
    }

    // ==================== ОТКРЫТЬ ====================

    void openFile()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Открыть файл",
            Gtk::FILE_CHOOSER_ACTION_OPEN);

        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Открыть", Gtk::RESPONSE_OK);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK)
        {
            std::ifstream file(dialog.get_filename());

            if (file)
            {
                std::string text;
                std::string line;

                while (getline(file, line))
                {
                    text += line + "\n";
                }

                textView.get_buffer()->set_text(text);

                currentFile = dialog.get_filename();

                fileLabel.set_text("Файл: " + currentFile);
                statusLabel.set_text("Файл открыт");
            }
        }
    }

    // ==================== СОХРАНИТЬ ====================

    void saveFile()
    {
        Gtk::FileChooserDialog dialog(
            *this,
            "Сохранить файл",
            Gtk::FILE_CHOOSER_ACTION_SAVE);

        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Сохранить", Gtk::RESPONSE_OK);

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK)
        {
            std::ofstream file(dialog.get_filename());

            if (file)
            {
                file << textView.get_buffer()->get_text();

                currentFile = dialog.get_filename();

                fileLabel.set_text("Файл: " + currentFile);
                statusLabel.set_text("Файл сохранён");
            }
        }
    }

    // ==================== ШРИФТ ====================

    void changeFont()
    {
        std::string fontName =
            fontButton.get_font_name();

        std::string size =
            sizeCombo.get_active_text();

        Pango::FontDescription font;

        font.set_family(fontName);

        if (!size.empty())
        {
            font.set_size(std::stoi(size) * PANGO_SCALE);
        }

        textView.override_font(font);

        statusLabel.set_text("Шрифт изменён");
    }
};

// ==================== MAIN ====================

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(
        argc,
        argv,
        "org.editor.project");

    TextEditor editor;

    return app->run(editor);
}
