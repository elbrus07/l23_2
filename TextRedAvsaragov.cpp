#include <gtk/gtk.h>
#include <pango/pango.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

GtkWidget* textView;
GtkWidget* fontSizeSpin;
PangoFontDescription* fontDesc = nullptr;

void highlight_syntax()
{
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);
    
    gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    string content = text;
    
    GtkTextTagTable* table = gtk_text_buffer_get_tag_table(buffer);
    GtkTextTag* blueTag  = gtk_text_tag_table_lookup(table, "blue");
    GtkTextTag* greenTag = gtk_text_tag_table_lookup(table, "green");
    GtkTextTag* redTag   = gtk_text_tag_table_lookup(table, "red");
    
    size_t pos = content.find("int");
    while (pos != string::npos) {
        GtkTextIter wordStart, wordEnd;
        gtk_text_buffer_get_iter_at_offset(buffer, &wordStart, pos);
        gtk_text_buffer_get_iter_at_offset(buffer, &wordEnd, pos + 3);
        gtk_text_buffer_apply_tag(buffer, blueTag, &wordStart, &wordEnd);
        pos = content.find("int", pos + 1);
    }
    
    pos = content.find("return");
    while (pos != string::npos) {
        GtkTextIter wordStart, wordEnd;
        gtk_text_buffer_get_iter_at_offset(buffer, &wordStart, pos);
        gtk_text_buffer_get_iter_at_offset(buffer, &wordEnd, pos + 6);
        gtk_text_buffer_apply_tag(buffer, redTag, &wordStart, &wordEnd);
        pos = content.find("return", pos + 1);
    }
    
    pos = content.find("if");
    while (pos != string::npos) {
        GtkTextIter wordStart, wordEnd;
        gtk_text_buffer_get_iter_at_offset(buffer, &wordStart, pos);
        gtk_text_buffer_get_iter_at_offset(buffer, &wordEnd, pos + 2);
        gtk_text_buffer_apply_tag(buffer, greenTag, &wordStart, &wordEnd);
        pos = content.find("if", pos + 1);
    }
    
    g_free(text);
}

void apply_font()
{
    int fontSize = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(fontSizeSpin));
    if (fontDesc) pango_font_description_free(fontDesc);
    
    fontDesc = pango_font_description_new();
    pango_font_description_set_family(fontDesc, "monospace");
    pango_font_description_set_size(fontDesc, fontSize * PANGO_SCALE);
    gtk_widget_override_font(textView, fontDesc);
}

void open_file(GtkWidget* widget, gpointer data)
{
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        ifstream file(filename);
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            GtkTextBuffer* buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
            gtk_text_buffer_set_text(buf, buffer.str().c_str(), -1);
        }
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void save_file(GtkWidget* widget, gpointer data)
{
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Save As",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Save", GTK_RESPONSE_ACCEPT,
        NULL);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "untitled.txt");

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        
        GtkTextBuffer* buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buf, &start);
        gtk_text_buffer_get_end_iter(buf, &end);
        char* text = gtk_text_buffer_get_text(buf, &start, &end, FALSE);

        ofstream file(filename);
        if (file.is_open()) file << text;
        
        g_free(text);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void clear_text(GtkWidget* widget, gpointer data)
{
    GtkTextBuffer* buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_set_text(buf, "", -1);
}

void on_font_size_changed(GtkWidget* widget, gpointer data)
{
    apply_font();
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Блокнот");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(window), main_hbox);

    GtkWidget* left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_hbox), left_vbox, FALSE, FALSE, 5);

    GtkWidget* btnOpen  = gtk_button_new_with_label("Открыть");
    GtkWidget* btnSave  = gtk_button_new_with_label("Сохранить");
    GtkWidget* btnClear = gtk_button_new_with_label("Очистить");

    gtk_box_pack_start(GTK_BOX(left_vbox), btnOpen,  FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(left_vbox), btnSave,  FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(left_vbox), btnClear, FALSE, FALSE, 5);

    GtkWidget* sep = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(left_vbox), sep, FALSE, FALSE, 10);

    GtkWidget* fontLabel = gtk_label_new("Размер шрифта:");
    gtk_box_pack_start(GTK_BOX(left_vbox), fontLabel, FALSE, FALSE, 5);

    GtkAdjustment* adj = gtk_adjustment_new(14, 8, 72, 1, 5, 0);
    fontSizeSpin = gtk_spin_button_new(adj, 1, 0);
    gtk_widget_set_size_request(fontSizeSpin, 100, -1);
    gtk_box_pack_start(GTK_BOX(left_vbox), fontSizeSpin, FALSE, FALSE, 5);

    g_signal_connect(btnOpen,  "clicked", G_CALLBACK(open_file),         window);
    g_signal_connect(btnSave,  "clicked", G_CALLBACK(save_file),         window);
    g_signal_connect(btnClear, "clicked", G_CALLBACK(clear_text),        NULL);
    g_signal_connect(fontSizeSpin, "value-changed", G_CALLBACK(on_font_size_changed), NULL);

    textView = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD_CHAR);

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_create_tag(buffer, "blue",  "foreground", "blue",  NULL);
    gtk_text_buffer_create_tag(buffer, "green", "foreground", "green", NULL);
    gtk_text_buffer_create_tag(buffer, "red",   "foreground", "red",   NULL);

    g_signal_connect(buffer, "changed", G_CALLBACK(+[](GtkTextBuffer*, gpointer) {
        highlight_syntax();
    }), NULL);

    GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), textView);
    gtk_box_pack_start(GTK_BOX(main_hbox), scroll, TRUE, TRUE, 5);

    apply_font();

    gtk_widget_show_all(window);
    gtk_main();

    if (fontDesc) pango_font_description_free(fontDesc);
    return 0;
}