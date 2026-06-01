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
